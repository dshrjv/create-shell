#ifndef PARAM_HPP
#define PARAM_HPP

#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

#define MAXARGS 32 // Maximum number of command-line arguments allowed

class Param {
private:
    char *inputRedirect;           // filename after '<' or NULL
    char *outputRedirect;          // filename after '>' or NULL
    int background;                // 1 if '&' present, else 0
    int argumentCount;             // number of args in argumentVector
    char *argumentVector[MAXARGS]; // argv-like array of C-strings

    static char *dupOrNull(const char *s) {
        if (!s)
            return NULL;
        size_t n = strlen(s) + 1;
        char *p = (char *)malloc(n);
        if (p)
            memcpy(p, s, n);
        return p;
    }

public:
    Param() : inputRedirect(NULL), outputRedirect(NULL), background(0), argumentCount(0)
    {
        memset(argumentVector, 0, sizeof(argumentVector));
    }
    ~Param() { reset(); }

    void reset();

    // Handles tokens, <, >, and &
    void parseFromLine(const char *line);

    void printParams();

    // Getters
    const char* getInputRedirect() const { return inputRedirect; }
    const char* getOutputRedirect() const { return outputRedirect; }
    int getBackground() const { return background; }
    int getArgumentCount() const { return argumentCount; }
    char* const* getArgumentVector() const { return argumentVector; }

    // Setters
    void setInputRedirect(const char* filename) {
        if (inputRedirect) {
            free(inputRedirect);
        }
        inputRedirect = dupOrNull(filename);
    }

    void setOutputRedirect(const char* filename) {
        if (outputRedirect) {
            free(outputRedirect);
        }
        outputRedirect = dupOrNull(filename);
    }

    void setBackground(int bg) { background = bg; }

    void addArgument(const char* arg) {
        if (argumentCount < MAXARGS) {
            argumentVector[argumentCount] = dupOrNull(arg);
            argumentCount++;
        }
    }
};

#endif