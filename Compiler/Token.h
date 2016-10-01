/*
  CSE 109
  Chris Szafranski
  cjs218
  This header file describes a Token for a lexical anylizer
*/

#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <cstring>

using namespace std;

class Token{

private:
  int tokenType;
  string lexeme;
  int lineNumber;
  int charPos;
public:
  //getter methods
  int type();
  string lex();
  int line();
  int pos();
  Token(int tokenType, string lexeme, int line, int Pos );//constructor
  Token();
  static const int INTLIT =1;
static const int IDENT =2;
static const int PLUS =3;
static const int MINUS =4;
static const int TIMES =5;
static const int DIVIDE =6;
static const int REM=7;
static const int ASSIGN =8;
static const int LPAREN=9;
static const int RPAREN=10;
static const int COMMA =11;
static const int EQ =12;
static const int LT =13;
static const int LE =14;
static const int GT =15;
static const int GE =16;
static const int NE =17;
static const int SET =18;
static const int PRINT =19;
static const int WHILE =20;
static const int DO =21;
static const int END =22;
static const int AND =23;
static const int OR =24;
static const int IF =25;
static const int THEN =26;
static const int ELSE =27;
static const int ENDIF =28;
static const int PROGRAM =29;

static const int ERROR =0;
};


#endif
