#include "parse.hpp"
#include <cstring>
#include <cctype>

// Helper function to trim leading/trailing whitespace
char* trimWhitespace(char* str) {
    char* end;
    
    while (isspace((unsigned char)*str)) str++;
    
    if (*str == 0) 
        return str;
    
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    
    *(end + 1) = 0;
    
    return str;
}

// Parse command line and populate Param object
void parseCommandLine(const char* line, Param& param) {
    param.parseFromLine(line);
}