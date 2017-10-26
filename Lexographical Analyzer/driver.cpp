//*****************************************************************************
// Lexical Analyzer Assignment
// Driver for lexical analyzer
//*****************************************************************************

#include "lexer.h"
#include <iostream>

// Instantiate global variables
FILE *yyin;         // input stream
FILE *yyout;        // output stream
int   yyleng;       // length of current lexeme
char *yytext;       // text of current lexeme


int main(int argc, char* argv[] )
{
    int token;   // hold each token code

    // Sets the input and output streams
    yyin = stdin;
    yyout = stdout;

    //Processes the first lexeme
    token = yylex();

    //Will display the derived information, and then process the next lexeme
    while( token != TOK_EOF ) {

        //Displays the information about the passed in lexeme
        printf("lexeme: |%s|, length: %d, token: %d\n", yytext, yyleng, token);

        //Handles unknown input
        if( token == TOK_UNKNOWN )
            printf("   ERROR: unknown token\n");

        token = yylex();
    }
}