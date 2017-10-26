//
// Created by Jace


#ifndef CSC_442_PROGRAMMING_LANGUAGES_LEXER_H
#define CSC_442_PROGRAMMING_LANGUAGES_LEXER_H


// Include standard IO streams
#include <stdio.h>
#include <string>

// The lexical analyzer global variables and functions

//Processes each lexeme until and end state is reached
extern int   yylex();

//Takes in an end state and returns the token of that lexeme
extern int checkToken(std::string);

//input stream
extern FILE *yyin;

//output stream
extern FILE *yyout;

//length of the current lexeme
extern int   yyleng;

//text content of the current lexeme
extern char *yytext;

// Maximum lexeme length
#define MAX_LEXEME_LEN 100

// List of token codes

//Keywords
#define TOK_IF           1001
#define TOK_ELSE         1002
#define TOK_FOR          1003
#define TOK_WHILE        1004
#define TOK_PRINT        1005
#define TOK_RETURN       1006
#define TOK_CONTINUE     1007
#define TOK_BREAK        1008
#define TOK_DEBUG        1009
#define TOK_READ         1010
#define TOK_LET          1011

//Datatype Specifiers
#define TOK_INT          1100
#define TOK_FLOAT        1101
#define TOK_STRING       1102

//Punctuation
#define TOK_SEMICOLON    2000
#define TOK_OPENPAREN    2001
#define TOK_CLOSEPAREN   2002
#define TOK_OPENBRACKET  2003
#define TOK_CLOSEBRACKET 2004
#define TOK_OPENBRACE    2005
#define TOK_CLOSEBRACE   2006
#define TOK_COMMA        2007

//Operators
#define TOK_PLUS         3000
#define TOK_MINUS        3001
#define TOK_MULTIPLY     3002
#define TOK_DIVIDE       3003
#define TOK_ASSIGN       3004
#define TOK_EQUALTO      3005
#define TOK_LESSTHAN     3006
#define TOK_GREATERTHAN  3007
#define TOK_NOTEQUALTO   3008
#define TOK_AND          3009
#define TOK_OR           3010
#define TOK_NOT          3011
#define TOK_LENGTH       3012

//Useful Abstractions
#define TOK_IDENTIFIER   4000
#define TOK_INTLIT       4001
#define TOK_FLOATLIT     4002
#define TOK_STRINGLIT    4003
#define TOK_EOF          5000  // end of file
#define TOK_EOF_SL       5001  // end of file while parsing string literal,
#define TOK_UNKNOWN      6000  // unknown lexeme



#endif //CSC_442_PROGRAMMING_LANGUAGES_LEXER_H
