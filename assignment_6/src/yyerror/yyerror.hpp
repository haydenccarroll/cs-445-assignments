#pragma once

#include "../error/include.hpp"

// write a nice error message
#define YYERROR_VERBOSE

// NOTE: make sure these variables interface with your code!!!
extern int lineNum;        // line number of last token scanned in your scanner (.l)
extern char *lastToken; // last token scanned in your scanner (connect to your .l)

void initErrorProcessing();    // WARNING: MUST be called before any errors occur (near top of main)!
void yyerror(const char *msg); // error routine called by Bison
