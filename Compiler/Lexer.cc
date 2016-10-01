/*
  CSE 109
  Chris Szafranski
  cjs218
  This file will fill out the methods described in the Lexer.h file

*/

#include <string>
#include <cstring>
#include <iostream>

#include "Lexer.h"
#include "Token.h"

using namespace std;

	
	
  
Lexer:: Lexer(istream& is):in(is){
	pos = 1;
	lineNum = 1; 
	c = ' ';
}
	


char Lexer:: nextChar(){
  if(c=='#'){
    do{
      pos++;
      c = in.get();
    }while(c!='#'||c!='\0');
  }
  if(c=='\0'){
    return '$';
  }
  char prev = c;
  pos++;
  c=in.get();
  cout<< "char:("<< prev<< ")"<<endl;
  return prev;
}

Token Lexer:: nextToken(){
 
  string lexeme = "";
  char ch = nextChar();
  
  while(ch == '\n'|| ch == ' '||ch == 9||ch == 10){//we ommit bs 
     if(ch == '\n'){
	   lineNum++ ;
	  pos =1; 
	  ch = nextChar();
    }
    else{ch = nextChar();}
  }

  lexeme += ch; //concactnate new char to lexeme
  //cout<< "Lexeme so far: "<<lexeme<< endl;
  
   if( ch<='9'&& ch>='0'){//check if number 
	   
    while((c<='9' &&  c>='0' )||(c>='a' && c<='f')){
      ch = nextChar();
      lexeme += ch ;
    }
	
    return Token(Token:: INTLIT,lexeme ,lineNum, pos);
  }
  
  if((ch<='z' && ch>='a') || (ch<='Z' && ch>='A')){//check if word 
	  
    while((c<='z'&&c>='a')||(c<='Z'&&c>='A')||(c<='9'&&c>='0')){
      ch = nextChar();
      lexeme+=ch;
    }
    if(lexeme=="set"){
      return Token(Token:: SET,lexeme,lineNum,pos);
    }
    else if(lexeme=="print"){
      return Token(Token:: PRINT,lexeme,lineNum,pos);
    }
    else if(lexeme=="while"){
      return   Token(Token:: WHILE,lexeme,lineNum,pos);
    }
    else if(lexeme=="do"){
      return   Token(Token:: DO,lexeme,lineNum,pos);
    }
    else if(lexeme=="end"){
      return   Token(Token:: END,lexeme,lineNum,pos);

    }
    else if(lexeme=="and"){
      return   Token(Token:: AND,lexeme,lineNum,pos);

    }
    else if(lexeme=="or"){
      return   Token(Token:: OR,lexeme,lineNum,pos);

    }
    else if((lexeme=="if")){
      return   Token(Token:: IF,lexeme,lineNum,pos);

    }
    else if((lexeme=="then")){
      return   Token(Token:: THEN,lexeme,lineNum,pos);

    }
    else if((lexeme=="else")){
      return   Token(Token:: ELSE,lexeme,lineNum,pos);

    }
    else if((lexeme=="endif")){
      return   Token(Token:: ENDIF,lexeme,lineNum,pos);

    }
    else if((lexeme=="program")){
      return Token(Token:: PROGRAM,lexeme,lineNum,pos);

    }
    else{//if non of these match it must be an identifier 
      return Token(Token:: IDENT,lexeme,lineNum,pos);
    }
  }
  if (ch=='+') {
    return   Token(Token:: PLUS,lexeme,lineNum,pos);
  }
  if(ch=='-'){
    return   Token(Token:: MINUS,lexeme,lineNum,pos);
  }
  if(ch=='*'){
    return   Token(Token:: TIMES,lexeme,lineNum,pos);
  }
  if(ch=='/'){
    return   Token(Token:: DIVIDE,lexeme,lineNum,pos);
  }
  if(ch=='%'){
    return   Token(Token:: REM,lexeme,lineNum,pos);
  }
  if(ch=='='){
    ch = nextChar();
    if(ch=='='){
      ch = nextChar();
      lexeme+=ch;
      return   Token(Token:: EQ,lexeme,lineNum,pos);
    }
    else{
      return   Token(Token:: ASSIGN,lexeme,lineNum,pos);
    }
  }
  if(ch=='('){
    return   Token(Token:: LPAREN,lexeme,lineNum,pos);
  }
  if(ch==')') {
    return   Token(Token:: RPAREN,lexeme,lineNum,pos);
  }
  if(ch==','){
    return   Token(Token:: COMMA,lexeme,lineNum,pos);
  }
  if(ch=='<'){
    if(ch=='='){
      ch = nextChar();
      lexeme+=ch;
      return   Token(Token:: LE,lexeme,lineNum,pos);
    }
    else{
      return   Token(Token:: LT,lexeme,lineNum,pos);
    }
  }
  if(ch=='>'){//check 
    if(ch=='='){
      ch = nextChar();
      lexeme+=ch;
      return   Token(Token:: GE,lexeme,lineNum,pos);
    }
    else{
      return   Token(Token:: GT,lexeme,lineNum,pos);
    }
  }
  if(ch=='!'){//check current char for '!'
    if(ch=='='){//check if next char is '='
      ch = nextChar();
      lexeme+=ch;
      return   Token(Token:: NE,lexeme,lineNum,pos);
    }
    else{
      cout<<"FUCK!"<<endl;
      return   Token(Token:: ERROR,lexeme,lineNum,pos);
    }
  }
  cout<<"FUCK"<<endl;
  return   Token(Token:: ERROR,lexeme,lineNum,pos);

}
  
/*
while(c == ' '|| c == '\n'){
    c = nextChar();
  }
  
  if(c == '#"){
	  return Token(token::EOF,"",lineNum,pos);
  }
  pos ++;
  if(c == '$'){
    Token tok(30, "EOF", lineNum,pos);
    return tok;
  }
 //isalpha(c) returns true if c is an alpha numeric char 
  
  if(isalpha(c)){ 
  while(isalpha(c)){
    lexeme+= c;
   
    c= nextChar();
    pos++;
    
  }
  }
 
    if(find(lexeme)!=-1){
      Token toke (find(lexeme),lexeme, lineNum,pos);
      return toke;
    }
    else{
      Token tokel(2,lexeme,lineNum,pos);
      return tokel;
    }

  

  if(c == ' '){
  Token toker (0,"SPACE",0,0);
  return toker;
  }
  */

