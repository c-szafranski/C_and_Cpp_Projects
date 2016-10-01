
#ifndef PARSER_H
#define PARSER_H

#include "Token.h"
#include "Lexer.h"
#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <sstream>

using namespace std;

class Parser {
  private:

  enum Operation {
    ADD, SUB, MULT, DIV, AND, OR, JMPEQ, JMPGE, JMPGT, JMPLE, JMPLT,
    JMPNE, JMP, LIT, VAR, STORE, LABEL, PRINT, SEQ, PRINTLN,ISEQ,ISLT,ISLE,ISGT,ISGE,ISNE,JUMP,JUMPF,JUMPT
  };
  
public:  
  class TreeNode {
    
  public:

    Operation op;
    string val;
    TreeNode *leftChild;
    TreeNode *rightChild;

    void init(Operation opx, string valx, TreeNode *leftChildx, TreeNode *rightChildx) {
      op = opx;
      val = valx;
      leftChild = leftChildx;
      rightChild = rightChildx;
    }


    TreeNode(Operation op, string val) {
      init(op, val, NULL, NULL);
    }
    
    TreeNode(Operation op, string val, TreeNode *leftChild, TreeNode *rightChild) {
      init(op, val, leftChild, rightChild);
    }

    TreeNode(Operation op) {
      init(op, "", NULL, NULL);
    }

    TreeNode(Operation op, TreeNode *leftChild, TreeNode *rightChild) {
      init(op, "", leftChild, rightChild);
    }

    static string operandFormat(TreeNode *node) {
       if (node->op == PRINT) 
          return "\"" + node->val + "\"";
       return node->val;      
    }

    static string toString(TreeNode *node) {
      cout<<"In toString"<<endl;
      return toString0(node, 0);
    }
    
    static string toString0(TreeNode *node, int spaces) {
      cout<<"In toString0"<<endl;
      cout<<"test1"<<endl;
      string blanks = "                                ";
      cout<<"Test "<<endl; 
      string left = "";
      string right = "";
      bool isLeaf = true;
      cout<<"1.."<<endl;
      if (node->leftChild != NULL) {
	left = toString0(node->leftChild, spaces+2);
	isLeaf = false;
      }
      cout<<"2..";
      if (node->rightChild != NULL) {
	right = toString0(node->rightChild, spaces+2);
	isLeaf = false;	
      }
      cout<<"3...";
      string ret;
      if (isLeaf) {
	ret = blanks.substr(0, spaces) + ops[node->op] + "[" + operandFormat(node) + "]";
      } else {
	ret = blanks.substr(0, spaces) + ops[node->op] + "(\n" + left + ",\n" + right + "\n" + 
	      blanks.substr(0, spaces) + ")";
      }
      cout<<"returning...";
      return ret;
    }
    
  };
  
private:

  Lexer lexer;
  ostream& out;
  int lindex;
  int tindex;
  Token token;
  
  
  

  string itos(int i) { stringstream ss; ss << i; string res = ss.str(); return res;}  
  string makeLabel() { string tmp = "L"; stringstream ss; ss << ++lindex; string res = ss.str(); tmp = tmp + res; return tmp;}
  string makeTemp() { string tmp = "$TEMP"; stringstream ss; ss << ++tindex; string res = ss.str(); tmp = tmp + res; return tmp;}
  static const string ops[];  
  



  void error(string message);
  void check(int tokenType, string message);
  
 public:
  TreeNode *program();
  TreeNode* compoundStatement();
  TreeNode* statement();
  TreeNode* setStatement();
  TreeNode* printStatement();
  TreeNode* whileStatement();
  TreeNode* ifStatement();
  TreeNode* logicalExpression();
  TreeNode* relationalExpression();
  TreeNode* expression();
  TreeNode* term();
  TreeNode* factor();
  void emit(TreeNode *node);
  void geninst(TreeNode *node);
  void genasm(TreeNode *node);
  void vardefs(TreeNode *node);
  
  Parser(Lexer& lexer, ostream& out);
  ~Parser(); 


};

#endif
