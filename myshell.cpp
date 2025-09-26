#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
#include "param.hpp"
#include "parse.hpp"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <vector>
using namespace std;

// Detect -Debug flag
static bool hasDebugFlag(int argc, char **argv){
    for (int i = 1; i < argc; ++i){
        if (strcmp(argv[i], "-Debug") == 0)
            return true;
    }
    return false;
}

// Trim leading/trailing whitespace
static string trim(const string &s){
    size_t a = s.find_first_not_of(" \t\n\r");
    if (a == string::npos)
        return "";
    size_t b = s.find_last_not_of(" \t\n\r");
    return s.substr(a, b - a + 1);
}

int main(int argc, char **argv){
    bool debug = hasDebugFlag(argc, argv);
    std::vector<pid_t> bg_pids; // Track background processes

    while (true){
        cout << "$$$ " << flush;

        string line;
        if (!getline(cin, line))
            break;

        string t = trim(line);
        if (t == "exit")
            break; 
        if (t.empty())
            continue; 

        Param P;
        P.parseFromLine(line.c_str());

        if (debug)
            P.printParams();

        if (P.getArgumentCount() == 0)
            continue;

        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            continue;
        }
        if (pid == 0) { 
            // Input redirection
            if (P.getInputRedirect()) {
                int fd = open(P.getInputRedirect(), O_RDONLY);
                if (fd < 0) {
                    perror("open input");
                    exit(1);
                }
                dup2(fd, STDIN_FILENO);
                close(fd);
            }
            // Output redirection
            if (P.getOutputRedirect()) {
                int fd = open(P.getOutputRedirect(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd < 0) {
                    perror("open output");
                    exit(1);
                }
                dup2(fd, STDOUT_FILENO);
                close(fd);
            }
   
            char *argv_exec[MAXARGS+1];
            char* const* argVector = P.getArgumentVector();
            for (int i = 0; i < P.getArgumentCount(); ++i)
                argv_exec[i] = argVector[i];
            argv_exec[P.getArgumentCount()] = NULL;

            execvp(argv_exec[0], argv_exec);
        
            perror("myshell: command not found");
            exit(127);
        } else { 
            if (P.getBackground()) {
                bg_pids.push_back(pid);
                cout << "[background pid: " << pid << "]" << endl;
            } else {
                int status = 0;
                waitpid(pid, &status, 0);
            }
       
            for (auto it = bg_pids.begin(); it != bg_pids.end(); ) {
                int status = 0;
                pid_t result = waitpid(*it, &status, WNOHANG);
                if (result == *it) {
                    cout << "[background pid " << *it << " exited]" << endl;
                    it = bg_pids.erase(it);
                } else {
                    ++it;
                }
            }
        }
    }

    // Wait for all background children
    for (pid_t pid : bg_pids) {
        int status = 0;
        waitpid(pid, &status, 0);
        cout << "[background pid " << pid << " exited]" << endl;
    }

    return 0;
}