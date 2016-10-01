/*
  CSE109
  Chris Szafranski
  cjs218
  This header file describes a Lexer analysis class
*/

#ifndef LEXER_H
#define LEXER_H
#include <string>
#include <cstring>
#include <iostream>
#include "Token.h"

using namespace std;

class Lexer{
  
private:
  istream& in;
  int pos;
  int lineNum;
  char c;
  //string speChar;
  //string digits;
  //string hexDig;

  char nextChar();
 
public:
  Lexer(istream& is);
  
  Token nextToken();

  
};

#endif
