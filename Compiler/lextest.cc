/*
  CSE 109
  Chris Szafranski
  cjs218
  This program will hold the main function for the lexer test
*/

#include <string>
#include <iostream>
#include <cstring>
#include <fstream>
#include "Token.h"
#include "Lexer.h"
#include "Parser.h"

using namespace std;

int main(int argc, char** argv){

	Lexer lexObject(cin);
	
	while(cin){
    Token tok= lexObject.nextToken();
    cout<<"  " <<tok.lex()<<endl;
	
    }
  
  return 0;
}
