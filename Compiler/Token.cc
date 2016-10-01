/*
  CSE 109
  Chris Szafranski
  cjs218
  This class will fill out the Token.h file with functions that will
  parse the incoming code

*/

#include <string>
#include <cstring>
#include <iostream>
#include "Token.h"
#include "Lexer.h"

using namespace std;

int Token:: type(){return tokenType;}
string Token:: lex(){return lexeme;}
int Token::line(){return lineNumber;}
int Token :: pos(){return charPos;}
Token:: Token(int tokType, string lex, int lineFound, int pos){
  tokenType= tokType;
  lexeme= lex;
  lineNumber= lineFound;
  charPos= pos;
  }
Token:: Token(){}



