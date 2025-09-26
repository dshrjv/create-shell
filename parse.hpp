#ifndef PARSE_HPP
#define PARSE_HPP

#include "param.hpp"

void parseCommandLine(const char* line, Param& param);

// Helper function to trim whitespace
char* trimWhitespace(char* str);

#endif