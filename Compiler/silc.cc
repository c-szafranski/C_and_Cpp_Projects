/*
  CSE 109
  Chris Szafranski
  cjs218
  This program will run the compiler 
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

  cout<< "Starting Parser"<<endl;
  Lexer lexObj(cin);
  cout<< "Lexer Constructed"<< endl;
  Parser par(lexObj, cout);
	cout<<"Parser created"<<endl;

	Parser::TreeNode * root = par.program();
	cout<< Parser::TreeNode::toString(root)<<endl;
	
	//tits
  return 0;
}
