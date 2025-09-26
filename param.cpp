#include "param.hpp"
static bool ends_with_amp(const char *s){
	size_t n = strlen(s);
	return n > 0 && s[n - 1] == '&';
}

void Param::reset(){
	if (inputRedirect){
		free(inputRedirect);
		inputRedirect = NULL;
	}
	if (outputRedirect){
		free(outputRedirect);
		outputRedirect = NULL;
	}
	for (int i = 0; i < argumentCount; ++i){
		free(argumentVector[i]);
		argumentVector[i] = NULL;
	}
	for (int i = argumentCount; i < MAXARGS; ++i)
		argumentVector[i] = NULL;
	argumentCount = 0;
	background = 0;
}

void Param::parseFromLine(const char *line){
	reset();
	if (!line)
		return;

	char *buf = (char *)malloc(strlen(line) + 1);
	if (!buf)
		return;
	strcpy(buf, line);

	const char *delims = " \t\n"; // split on spaces, tabs, newlines
	char *saveptr = NULL;
	char *tok = strtok_r(buf, delims, &saveptr);

	bool expectIn = false;	
	bool expectOut = false; 

	while (tok){
		if (expectIn){
			inputRedirect = dupOrNull(tok);
			expectIn = false;
		}
		else if (expectOut){
			outputRedirect = dupOrNull(tok);
			expectOut = false;
		}
		else if (tok[0] == '<'){
			if (tok[1] != '\0')
				inputRedirect = dupOrNull(tok + 1);
			else
				expectIn = true;
		}
		else if (tok[0] == '>'){
			if (tok[1] != '\0')
				outputRedirect = dupOrNull(tok + 1);
			else
				expectOut = true;
		}
		else if (strcmp(tok, "&") == 0){
			background = 1; // standalone background symbol
		}
		else if (ends_with_amp(tok)){
			background = 1;
			tok[strlen(tok) - 1] = '\0'; // strip trailing '&'
			if (tok[0] != '\0' && argumentCount < MAXARGS)
			{
				argumentVector[argumentCount++] = dupOrNull(tok);
			}
		}
		else{
			if (argumentCount < MAXARGS){
				argumentVector[argumentCount++] = dupOrNull(tok);
			}
		}

		tok = strtok_r(NULL, delims, &saveptr);
	}

	free(buf);
}

void Param::printParams(){
	printf("\nParsed Parameters\n");
	printf("argumentCount: %d\n", argumentCount);
	for (int i = 0; i < argumentCount; ++i){
		printf("argumentVector[%d]: %s\n", i, argumentVector[i] ? argumentVector[i] : "(null)");
	}
	printf("inputRedirect : %s\n", inputRedirect ? inputRedirect : "(null)");
	printf("outputRedirect: %s\n", outputRedirect ? outputRedirect : "(null)");
	printf("background : %d\n", background);
	printf("\n\n");
}