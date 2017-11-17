#include "lexer.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
#include <cstdlib>

using namespace std;

FILE *yyin;         // input stream
FILE *yyout;        // output stream
int   yyleng;       // length of current lexeme
char *yytext;       // text of current lexeme



//Counters used to differentiate when the same state is entered and exited
static int pCount = 0;
static int sCount = 0;
static int aCount = 0;
static int eCount = 0;
static int bCount = 0;
static int rCount = 0;
static int tCount = 0;
static int fCount = 0;
static int uCount = 0;
static int gCount = 0;
static int oCount = 0;
static int cCount = 0;
static int wCount = 0;


// Production functions
void   P( void );
void   S( void );
void   A( void );
float  E( void );
float  B( void );
float  R( void );
float  T( void );
float  F( void );
float  U( void );
void   G( void );
void   O( void );
void   C( void );
void   W( void );

// Function declarations for checking whether the current token is
// in the first set of each production rule.
bool IsFirstOfP( void );
bool IsFirstOfS( void );
bool IsFirstOfA( void );
bool IsFirstOfE( void );
bool IsFirstOfB( void );
bool IsFirstOfR( void );
bool IsFirstOfT( void );
bool IsFirstOfF( void );
bool IsFirstOfU( void );
bool IsFirstOfG( void );
bool IsFirstOfO( void );
bool IsFirstOfC( void );
bool IsFirstOfW( void );

// Data type for the Symbol Table
typedef map<string, float> SymbolTableT;

// Needed global variables
int iTok;                  // The current token
SymbolTableT SymbolTable;  // The symbol table

//Will be used to correct for a special case in which an if statement is read in with no else
bool enterCNoElse = false;

int main() {

    // Set the input and output streams
    yyin = stdin;
    yyout = stdout;

    // Get the first token
    iTok = yylex();

    // Fire up the parser!
    try {
        if( !IsFirstOfP() ) // Check for {
            throw "missing '{' at beginning of program";

        // Process P Production
        P();

      if( iTok != TOK_EOF )
          throw "end of file expected, but there is more here!";

    }
    catch( char const *errmsg ) {

        cout << endl << "***ERROR: "<< errmsg << endl;
        return 1;
    }

    // Tell the world about our success!!
    cout << endl
         << "=== Your parse was successful! ==="
         << endl << endl;;

    // Print out the symbol table
    SymbolTableT::iterator it;
    cout.precision(1);
    for( it = SymbolTable.begin(); it != SymbolTable.end(); ++it ) {
        cout << "symbol = " << it->first << fixed << ", value = " << it->second << endl;
    }

    return 0;

}//end main

//*****************************************************************************
// P --> { {S} }
void P( void ) {

    char const *Perr = "statement does not start with \"let\", \"read\", \"print\", \"if\", \"while\"";

    cout << "enter P " << pCount << endl;

    int locPCount = pCount;

    pCount++;

    //We already know the first token is a { so just print it and get next token
    cout << "-->found " << yytext << endl;
    iTok = yylex();

    //Will iterate through all S states until no more input can be read in, or the end of the program has been found
    while((iTok != TOK_EOF ) && (iTok != TOK_CLOSEBRACE)) {

        //Check for First of S
        if ( IsFirstOfS() )
            S();
        else
            throw Perr;

    }//end while


    //Final token should be a '}'
    if( iTok != TOK_CLOSEBRACE )
        throw "missing '}' at end of program";

    cout << "-->found " << yytext << endl;

    //Will print out spaces to show what level the state being entered is in
    for(int i = 0; i < locPCount; i++)
        cout << " ";

    cout << "exit P " << locPCount << endl;

}//end P

// S --> A | G | O | C | W
void  S( void ){

    char const *Serr = "statement does not start with \"let\", \"read\", \"print\", \"if\", \"while\"";

    //Will print out spaces to show what level the state being entered is in
    for(int i = 0; i < sCount; i++)
        cout << " ";

    cout << "enter S " << sCount << endl;

    int locSCount = sCount;

    sCount++;

    //Finds which state to go to next: A, G, O, C, or W. If none of those state are right, then an error is thrown
    if( IsFirstOfA() )
        A();
    else if( IsFirstOfG() )
        G();
    else if( IsFirstOfO() )
        O();
    else if( IsFirstOfC() )
        C();
    else if( IsFirstOfW() )
        W();
    else
        throw Serr;

    //Will print out spaces to show what level the state being entered is in
    for(int i = 0; i < locSCount; i++)
        cout << " ";

    cout << "exit S " << locSCount << endl;

    if(enterCNoElse)
        enterCNoElse = false;
    else
        iTok = yylex();

}//end S

// A --> let ID := E;
void  A( void ){

    //Will print out spaces to show what level the state being entered is in
    for(int i = 0; i < aCount; i++)
        cout << " ";

    cout << "enter A " << aCount << endl;

    int locACount = aCount;

    aCount++;

    //Should print out that the "let" keyword has been found
    cout << "-->found " << yytext << endl;

    //Will get the next token
    iTok = yylex();

    float result;

    //If the next token is not an ID, then an error is thrown
    if(iTok != TOK_IDENTIFIER)
        throw "assignment is not given an identifier";

    //Prints out the ID being used in the assignment statement
    cout << "-->found ID: " << yytext << endl;

    string assignID = yytext;



    //Continues parsing through the assignment statement
    iTok = yylex();

    //If the next token is not an assignment operator ":=", then an error is thrown
    if(iTok != TOK_ASSIGN)
        throw "no assignment operator given";


    //Should print out that the assignment operator has been found
    cout << "-->found " << yytext << endl;

    //Continues parsing through the assignment statement
    iTok = yylex();

    if( IsFirstOfE() )
        result = E();
    else
        throw "statement after assignment variable "
                "does not start with: \"not\", \"-\", \"(\", an identifier, or a number";



    if(iTok != TOK_SEMICOLON)
        throw "assignment statement must end with a semicolon";

    //Should print out that the semicolon has been found
    cout << "-->found " << yytext << endl;

    SymbolTable.insert(pair <string, float> (assignID, result));

    //Will print out spaces to show what level the state being entered is in
    for(int i = 0; i < locACount; i++)
        cout << " ";

    cout << "exit A " << locACount << endl;

}//end A

// E --> B {( and | or ) B }
float  E( void ){

    char const *Eerr = "statement does not start with \"not\", \"-\", \"(\", an identifier, or a number";

    //Will print out spaces to show what level the state being entered is in
    for(int i = 0; i < eCount; i++)
        cout << " ";

    cout << "enter E " << eCount << endl;

    int locECount = eCount;

    eCount++;

    //Will hold the float to be returned through the chain of state changes
    float retE;

    if( IsFirstOfB() )
        retE = B();
    else
        throw Eerr;



    //Will process all additional B states
    while (iTok == TOK_AND || iTok == TOK_OR) {

        cout << "-->found " << yytext << endl;

        iTok = yylex();

        if( IsFirstOfB() )
           retE = B();
        else
            throw Eerr;

    }//end while

    //Will print out spaces to show what level the state being entered is in
    for(int i = 0; i < locECount; i++)
        cout << " ";

    cout << "exit E " << locECount << endl;

    return retE;

}//end E

// B --> R [( < | > | == ) R ]
float  B( void ){

    char const *Berr = "statement does not start with \"not\", \"-\", \"(\", an identifier, or a number";

    //Will print out spaces to show what level the state being entered is in
    for(int i = 0; i < bCount; i++)
        cout << " ";

    cout << "enter B " << bCount << endl;

    int locBCount = bCount;

    bCount++;

    float retB;

    if( IsFirstOfR() )
        retB = R();
    else
        throw Berr;



    //Will process all additional B states
    while (iTok == TOK_LESSTHAN || iTok == TOK_GREATERTHAN || iTok == TOK_EQUALTO) {

        cout << "-->found " << yytext << endl;

        if( IsFirstOfR() )
           retB = R();
        else
            throw Berr;


    }//end while


    //Will print out spaces to show what level the state being entered is in
    for(int i = 0; i < locBCount; i++)
        cout << " ";

    cout << "exit B " << locBCount << endl;

    return retB;

}//end B

// R -->  T {( + | - ) T }
float  R( void ){

    char const *Rerr = "statement does not start with \"not\", \"-\", \"(\", an identifier, or a number";

    //Will print out spaces to show what level the state being entered is in
    for(int i = 0; i < rCount; i++)
        cout << " ";

    cout << "enter R " << rCount << endl;

    int locRCount = rCount;

    rCount++;

    float retR = -1;

    if( IsFirstOfT() )
       retR = T();
    else
        throw Rerr;


    //Used to hold the plus or minus sign code
    int opCode = 0;

    //Will process all additional T states
    while (iTok == TOK_PLUS || iTok == TOK_MINUS) {

        cout << "-->found " << yytext << endl;

        opCode = iTok;

        iTok = yylex();

        if( IsFirstOfT() ) {

            if( opCode == TOK_PLUS)
                retR = retR + T();
            else
                retR = retR - T();

        }//end if

        else
            throw Rerr;

    }//end while


    //Will print out spaces to show what level the state being entered is in
    for(int i = 0; i < locRCount; i++)
        cout << " ";

    cout << "exit R " << locRCount << endl;

    return retR;

}//end R

// T --> F {( * | / ) F }
float T( void ){

    char const *Terr = "statement does not start with \"not\", \"-\", \"(\", an identifier, or a number";

    //Will print out spaces to show what level the state being entered is in
    for(int i = 0; i < tCount; i++)
        cout << " ";

    cout << "enter T " << tCount << endl;

    int locTCount = tCount;

    tCount++;

    float retT;

    if( IsFirstOfF() )
        retT = F();
    else
        throw Terr;

    iTok = yylex();

    int opCode;

    //Will process all additional B states
    while (iTok == TOK_MULTIPLY || iTok == TOK_DIVIDE) {

        opCode = iTok;
        cout << "-->found " << yytext << endl;
        iTok = yylex();

        if( IsFirstOfF() ){

            if(opCode == TOK_MULTIPLY)
                retT = retT * F();

            else if (opCode == TOK_DIVIDE) {
                float temp = F();

                if(temp != 0)
                    retT = retT / F();
                else
                    throw "Divide by Zero error";
            }
        }

        else
            throw Terr;

        iTok = yylex();

    }//end while


    //Will print out spaces to show what level the state being entered is in
    for(int i = 0; i < locTCount; i++)
        cout << " ";

    cout << "exit T " << locTCount << endl;

    return retT;

}//end T

// F -->  [ not | - ] U
float  F( void ){

    char const *Ferr = "statement does not start with \"not\", \"-\", \"(\", an identifier, or a number";

    //Will print out spaces to show what level the state being entered is in
    for(int i = 0; i < fCount; i++)
        cout << " ";

    cout << "enter F " << fCount << endl;

    int locFCount = fCount;

    fCount++;

    float retF;

    //Will be used to complete the unary minus operation. It will only negate the result if TOK_MINUS is found
    int negSwitch = 1;

    if(iTok == TOK_NOT){

        //Should print out that the "not" keyword has been found
        cout << "-->found " << yytext << endl;

        iTok = yylex();
    }

    else if(iTok == TOK_MINUS){

        //Should print out that the "-" operator has been found
        cout << "-->found " << yytext << endl;

        negSwitch = -1;

        iTok = yylex();

    }

    if( IsFirstOfU() )
        retF = U();
    else
        throw Ferr;


    //Will print out spaces to show what level the state being entered is in
    for(int i = 0; i < locFCount; i++)
        cout << " ";

    cout << "exit F " << locFCount << endl;

    return (retF * negSwitch);

}//end F

// U -->  ID | FLOATLIT | (E)
float U( void ){

    char const *Uerr = "statement does not start with \"(\", an identifier, or a number";

    //Will print out spaces to show what level the state being entered is in
    for(int i = 0; i < uCount; i++)
        cout << " ";

    cout << "enter U " << uCount << endl;

    int locUCount = uCount;

    uCount++;

    float retU;

    if(iTok == TOK_OPENPAREN){

        //Should print out that the open parenthesis been found
        cout << "-->found " << yytext << endl;

        iTok = yylex();

        if( IsFirstOfE() )
           retU = E();
        else
            throw "statement does not start with \"not\", \"-\", \"(\", an identifier, or a number";


        //Should print out that the close parenthesis been found
        cout << "-->found HIT" << yytext << endl;

        if(iTok != TOK_CLOSEPAREN)
            throw "statement must end with ')'";

    }//end if

    else if(iTok == TOK_FLOATLIT){

        cout << "-->found FLOATLIT: " << yytext << endl;

        //Returns the float value found
        retU = atof(yytext);

    }

    else if(iTok == TOK_IDENTIFIER){

        //Should print out the ID passed in
        cout << "-->found " << yytext << endl;

        //Tries to find the value of the passed in ID
        SymbolTableT::iterator it = SymbolTable.find(yytext);

        //Throws an error if the value can not be found
        if(it == SymbolTable.end())
            throw "ID given was not found";

        //Returns the value of the given ID from the symbol table
        retU = SymbolTable.find(yytext)->second;

    }

    //Will print out spaces to show what level the state being entered is in
    for(int i = 0; i < locUCount; i++)
        cout << " ";

    cout << "exit U " << locUCount << endl;

    return retU;

}//end U

// G --> read [STRINGLIT] ID;
void  G( void ){

    //Will print out spaces to show what level the state being entered is in
    for(int i = 0; i < gCount; i++)
        cout << " ";

    cout << "enter G " << gCount << endl;

    //Should print out that the "read" keyword has been found
    cout << "-->found " << yytext << endl;

    int locGCount = gCount;

    gCount++;

    iTok = yylex();

    if(iTok == TOK_STRINGLIT){

        //Should print out the string literal that was found
        cout << "-->found " << yytext << endl;

        iTok = yylex();

    }//end if

    //Should print out the identifier that was found
    cout << "-->found " << yytext << endl;


    if(iTok == TOK_IDENTIFIER) {

        //Should print out the identifier that was found
        cout << "-->found " << yytext << endl;

        SymbolTable.insert(pair<string, float>(yytext, 0.0));

    }//end if

    else
        throw "read statement must have an identifier";

    iTok = yylex();

    //Should print out the semicolon that was found
    cout << "-->found " << yytext << endl;

    if(iTok != TOK_SEMICOLON)
        throw "read must end with a semicolon";

    //Will print out spaces to show what level the state being entered is in
    for(int i = 0; i < locGCount; i++)
        cout << " ";

    cout << "exit G " << locGCount << endl;

}//end G

// O -->  print [STRINGLIT] [ID];
void  O( void ){

    //Will print out spaces to show what level the state being entered is in
    for(int i = 0; i < oCount; i++)
        cout << " ";

    cout << "enter O " << oCount << endl;

    //Should print out that the "print" keyword has been found
    cout << "-->found " << yytext << endl;

    int locOCount = oCount;

    oCount++;

    iTok = yylex();

    if(iTok == TOK_STRINGLIT){

        //Should print out the string literal that was found
        cout << "-->found " << yytext << endl;

        iTok = yylex();

    }//end if


    if(iTok == TOK_IDENTIFIER)
        //Should print out the identifier that was found
        cout << "-->found " << yytext << endl;

    iTok = yylex();

    //Should print out the semicolon that was found
    cout << "-->found " << yytext << endl;

    if(iTok != TOK_SEMICOLON)
        throw "print must end with a semicolon";

    //Will print out spaces to show what level the state being entered is in
    for(int i = 0; i < locOCount; i++)
        cout << " ";

    cout << "exit O " << locOCount << endl;

}//end O

// C --> if (E) P [ else P ]
void  C( void ){

    //Will print out spaces to show what level the state being entered is in
    for(int i = 0; i < cCount; i++)
        cout << " ";

    cout << "enter C " << cCount << endl;

    //Should print out that the "if" keyword has been found
    cout << "-->found " << yytext << endl;

    int locCCount = cCount;

    cCount++;

    iTok = yylex();

    if(iTok != TOK_OPENPAREN)
        throw "if condition statement must start with '('";

    //Should print out that the open parenthesis has been found
    cout << "-->found " << yytext << endl;

    iTok = yylex();

    //Will process the if's condition statement
    if( IsFirstOfE() )
        E();
    else
        throw "if statement must have a condition";

    //iTok = yylex();

    if(iTok != TOK_CLOSEPAREN)
        throw "if statement's condition statement must end with ')'";

    //Should print out that the close parenthesis has been found
    cout << "-->found " << yytext << endl;

    iTok = yylex();

    if( IsFirstOfP() )
        P();
    else
        throw "if statement body must start with '{'";

    iTok = yylex();

    //Will process the else statement
    if(iTok == TOK_ELSE){

        iTok = yylex();

        if( IsFirstOfP() )
            P();
        else
            throw "else statement body must start with '{'";

    }//end if

    else
        enterCNoElse = true;


    //Will print out spaces to show what level the state being entered is in
    for(int i = 0; i < locCCount; i++)
        cout << " ";

    cout << "exit C " << locCCount << endl;

}//end C

// W --> while (E) P
void  W( void ){

    char const *Werr = "statement does not start with \"while\"";

    //Will print out spaces to show what level the state being entered is in
    for(int i = 0; i < wCount; i++)
        cout << " ";

    cout << "enter W " << wCount << endl;

    //Should print out that the "while" keyword has been found
    cout << "-->found " << yytext << endl;

    int locWCount = wCount;

    wCount++;

    iTok = yylex();

    if(iTok != TOK_OPENPAREN)
        throw "while loop condition statement must start with '('";

    //Should print out that the open parenthesis has been found
    cout << "-->found " << yytext << endl;

    iTok = yylex();

    //Will process the while loop's condition statement
    if( IsFirstOfE() )
        E();
    else
        throw "while loop must have a condition";


    if(iTok != TOK_CLOSEPAREN)
        throw "while loop condition statement must end with ')'";

    //Should print out that the close parenthesis has been found
    cout << "-->found " << yytext << endl;

    iTok = yylex();

    if( IsFirstOfP() )
        P();
    else
        throw "while loop body must start with '{'";


    //Will print out spaces to show what level the state being entered is in
    for(int i = 0; i < locWCount; i++)
        cout << " ";

    cout << "exit W " << locWCount << endl;

}//end W


//*****************************************************************************
bool IsFirstOfP( void ) {

    return iTok == TOK_OPENBRACE;

}//end IsFirstOfP

bool IsFirstOfS( void ){

    return iTok == TOK_LET || iTok == TOK_READ || iTok == TOK_PRINT || iTok == TOK_IF || iTok == TOK_WHILE;

}//end IsFirstOfS

bool IsFirstOfA( void ){

    return iTok == TOK_LET;

}//end IsFirstOfA

bool IsFirstOfE( void ){

    return iTok == TOK_NOT || iTok == TOK_MINUS || iTok == TOK_OPENPAREN || iTok == TOK_IDENTIFIER
           || iTok == TOK_FLOATLIT;

}//end IsFirstOfE

bool IsFirstOfB( void ){

    return iTok == TOK_NOT || iTok == TOK_MINUS || iTok == TOK_OPENPAREN || iTok == TOK_IDENTIFIER
           || iTok == TOK_FLOATLIT;;

}//end IsFirstOfB

bool IsFirstOfR( void ){

    return iTok == TOK_NOT || iTok == TOK_MINUS || iTok == TOK_OPENPAREN || iTok == TOK_IDENTIFIER
           || iTok == TOK_FLOATLIT;;

}//end IsFirstOfR

bool IsFirstOfT( void ){

    return iTok == TOK_NOT || iTok == TOK_MINUS || iTok == TOK_OPENPAREN || iTok == TOK_IDENTIFIER
           || iTok == TOK_FLOATLIT;;

}//end IsFirstOfT

bool IsFirstOfF( void ){

    return iTok == TOK_NOT || iTok == TOK_MINUS || iTok == TOK_OPENPAREN || iTok == TOK_IDENTIFIER
           || iTok == TOK_FLOATLIT;;

}//end IsFirstOfF

bool IsFirstOfU( void ){

    return iTok == TOK_OPENPAREN || iTok == TOK_IDENTIFIER || iTok == TOK_FLOATLIT;;

}//end IsFirstOfU

bool IsFirstOfG( void ){

   return iTok == TOK_READ;

}//end IsFirstOfG

bool IsFirstOfO( void ){

    return iTok == TOK_PRINT;

}//end IsFirstOfO

bool IsFirstOfC( void ){

    return iTok == TOK_IF;

}//end IsFirstOfC

bool IsFirstOfW( void ){

    return iTok == TOK_WHILE;

}//end IsFirstOfW