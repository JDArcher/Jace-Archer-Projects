//
// Created by Jace on 11/3/2017.
//
#include "lexer.h"
#include <ctype.h>
#include <assert.h>
#include <string>

using namespace std;

//*****************************************************************************


char lexeme[MAX_LEXEME_LEN];  // Character buffer for lexeme
bool decimalFound;  // Will be used to differentiate between a int and a float

int yylex() {

    //Used to tell if the first character has been read in
    static char c = -1;

    //Used to differentiate a float input from an integer
    decimalFound = false;

    //Will be used to determine the class of lexeme read in, helping manage what process
    //it needs to go through to find its end state
    //Different Values and Meanings: "ID" for identifiers or keywords, "NUM" for numbers (either floats or ints),
    //"STRING" for string literals
    string state;

    //Prepares the buffer to hold the lexeme
    for( int i = 0; i < MAX_LEXEME_LEN; i++ )
        lexeme[i] = '\0';

    //Resets the information variables for the new lexeme being processed
    yytext = lexeme;
    yyleng = 0;

    // If the very first character has not yet been read, this will read it
    if( c < 0 )
        c = fgetc( yyin );

    //Skips to the next non-whitespace character of the input
    while(isspace(c))
        c = fgetc(yyin);


    //Tests for end of file
    if( feof(yyin) ) {

        //Resets c for the next time this function is called
        c = -1;

        return( TOK_EOF );

    }

    //Next Series of IF's will check for any single character punctuation, and go ahead and process them
    if(c == ';'){

        lexeme[yyleng++] = c;
        yytext = lexeme;
        c = fgetc(yyin);
        return TOK_SEMICOLON;

    }

    else if(c == '('){

        lexeme[yyleng++] = c;
        yytext = lexeme;
        c = fgetc(yyin);
        return TOK_OPENPAREN;

    }

    else if(c == ')'){

        lexeme[yyleng++] = c;
        yytext = lexeme;
        c = fgetc(yyin);
        return TOK_CLOSEPAREN;

    }

    else if(c == '['){

        lexeme[yyleng++] = c;
        yytext = lexeme;
        c = fgetc(yyin);
        return TOK_OPENBRACKET;

    }

    else if(c == ']'){

        lexeme[yyleng++] = c;
        yytext = lexeme;
        c = fgetc(yyin);
        return TOK_CLOSEBRACKET;

    }

    else if(c == '{'){

        lexeme[yyleng++] = c;
        yytext = lexeme;
        c = fgetc(yyin);
        return TOK_OPENBRACE;

    }

    else if(c == '}'){

        lexeme[yyleng++] = c;
        yytext = lexeme;
        c = fgetc(yyin);
        return TOK_CLOSEBRACE;

    }

    else if(c == ','){

        lexeme[yyleng++] = c;
        yytext = lexeme;
        c = fgetc(yyin);
        return TOK_COMMA;

    }

    else if(c == '+'){

        lexeme[yyleng++] = c;
        yytext = lexeme;
        c = fgetc(yyin);
        return TOK_PLUS;

    }

    else if(c == '-'){

        lexeme[yyleng++] = c;
        yytext = lexeme;
        c = fgetc(yyin);
        return TOK_MINUS;

    }

    else if(c == '*'){

        lexeme[yyleng++] = c;
        yytext = lexeme;
        c = fgetc(yyin);
        return TOK_MULTIPLY;

    }

    else if(c == '/'){

        lexeme[yyleng++] = c;
        yytext = lexeme;
        c = fgetc(yyin);
        return TOK_DIVIDE;

    }


    else if(c == '>'){

        lexeme[yyleng++] = c;
        yytext = lexeme;
        c = fgetc(yyin);
        return TOK_GREATERTHAN;

    }

        //Next IF's will handle the special cases that have one or two characters "<>, ==, and :="
    else if(c == '<'){

        lexeme[yyleng++] = c;
        c = fgetc(yyin);

        if(c == '>'){

            lexeme[yyleng++] = c;
            yytext = lexeme;
            c = fgetc(yyin);
            return TOK_NOTEQUALTO;

        }

        yytext = lexeme;
        return TOK_LESSTHAN;

    }

    else if(c == ':'){

        lexeme[yyleng++] = c;
        c = fgetc(yyin);

        if(c == '='){

            lexeme[yyleng++] = c;
            yytext = lexeme;
            c = fgetc(yyin);
            return TOK_ASSIGN;

        }

        yytext = lexeme;
        return TOK_UNKNOWN;

    }

    else if(c == '='){

        lexeme[yyleng++] = c;
        c = fgetc(yyin);

        if(c == '='){

            lexeme[yyleng++] = c;
            yytext = lexeme;
            c = fgetc(yyin);
            return TOK_EQUALTO;

        }

        yytext = lexeme;
        return TOK_UNKNOWN;

    }


    //Next IF's set the state based on what c is
    if(isalpha(c) != 0)
        state = "ID";
    else if(isdigit(c))
        state = "NUM";
    else if(c == '.') {

        state = "NUM";
        decimalFound = true;

    }

    else if(c == '"'){

        state = "STRING";
        lexeme[yyleng++] = c;
        c = fgetc(yyin);

        if(c == '"') {

            lexeme[yyleng++] = c;
            yytext = lexeme;
            c = fgetc(yyin);
            return TOK_STRINGLIT;

        }

    }


    // Test for end of file
    if( feof(yyin) ) {
        // Ready for next time
        c = -1;
        // Done!
        return( TOK_EOF );
    }

    //The loop will process indefinitely. An entire lexeme will be processed and a return statement will be hit
    while(true){

        //Checks to make sure the character is not an end of file character
        if(c == EOF){

            //Returns the token representing that the EOF was hit while processing a string literal
            if(state.compare("STRING") == 0)
                return TOK_EOF_SL;

                //Returns the token representing that the EOF was hit while processing another type of lexeme
            else
                return TOK_EOF;

        }

        if(state.compare("ID") == 0){

            if(isalnum(c) == 0) {

                yytext = lexeme;
                return checkToken(state);

            }

        }//end ID state

        else if(state.compare("NUM") == 0){
            if(isdigit(c) == 0) {

                if(c == '.' && !decimalFound){

                    decimalFound = true;

                }

                else {

                    yytext = lexeme;
                    return checkToken(state);

                }

            }

        }//end NUM state

        else if(state.compare("STRING") == 0){
            if(c == '"'){

                lexeme[yyleng++] = c;
                c = fgetc(yyin);
                yytext = lexeme;
                return checkToken(state);

            }
        }//end STRING state

        lexeme[yyleng++] = c;
        c = fgetc(yyin);

    }//end while
}

//This method will be passed the state the program is in, and then return the token id of the lexeme
int checkToken(string state){

    //if a decimal was found in lexeme, it is a float, otherwise it is just an integer
    if(state.compare("NUM") == 0){

        if(decimalFound)
            return TOK_FLOATLIT;
        else
            return TOK_FLOATLIT;

    }

    //if the string state was passed in, then the lexeme can only be a string literal
    else if(state.compare("STRING") == 0){

        return TOK_STRINGLIT;

    }


    //If the lexeme is an identifier, it is either a keyword or a standard variable name
    else if(state.compare("ID") == 0){

        //Converts the char buffer into a string
        string strLex = string(lexeme);

        //This series of ifs/else ifs will check to see if the lexeme is a keyword and, if it matches one, will return
        //the corresponding token for that word
        if(strLex == "if")
            return TOK_IF;
        else if(strLex == "else")
            return TOK_ELSE;
        else if(strLex == "for")
            return TOK_FOR;
        else if(strLex == "while")
            return TOK_WHILE;
        else if(strLex == "print")
            return TOK_PRINT;
        else if(strLex == "return")
            return TOK_RETURN;
        else if(strLex == "continue")
            return TOK_CONTINUE;
        else if(strLex == "break")
            return TOK_BREAK;
        else if(strLex == "debug")
            return TOK_DEBUG;
        else if(strLex == "read")
            return TOK_READ;
        else if(strLex == "let")
            return TOK_LET;
        else if(strLex == "int")
            return TOK_INT;
        else if(strLex == "float")
            return TOK_FLOAT;
        else if(strLex == "string")
            return TOK_STRING;
        else if(strLex == "and")
            return TOK_AND;
        else if(strLex == "or")
            return TOK_OR;
        else if(strLex == "not")
            return TOK_NOT;
        else if(strLex == "length")
            return TOK_LENGTH;

        //If the lexeme isn't a keyword, but is still in the ID state, then it is a normal identifier
        else
            return TOK_IDENTIFIER;

    }

    //If the lexeme passed in is not recognized, a token will be passed to signal that it is unknown and an
    //error message will be printed
    else
        return TOK_UNKNOWN;

}//end checkToken