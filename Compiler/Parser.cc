 #include "Parser.h"
 #include "Token.h"
#include "Lexer.h"
#include <cstring>


const string Parser::ops[] = {"ADD", "SUB", "MULT", "DIV", "AND", "OR", "JMPEQ", "JMPGE", "JMPGT", "JMPLE",
			      "JMPLT", "JMPNE", "JMP", "LIT", "VAR", "STORE", "LABEL", "PRINT", "SEQ", "PRINTLN",
			      "ISEQ","ISLT","ISLE","ISGE","ISNE","JUMP","JUMPF","JUMPT"};

Parser::Parser(Lexer& lexerx, ostream& outx): lexer(lexerx), out(outx), lindex(1), tindex(1) {
  
  token = lexer.nextToken();
}

Parser::~Parser() {
}

void Parser::error(string message) {
  cerr << message << " Found " << token.lex() << " at line " << token.line() << " position " << token.pos() << endl;
  exit(1);
}

void Parser::check(int tokenType, string message) {
  if (token.type() != tokenType)
    error(message);
}


Parser::TreeNode* Parser::factor() {

  
  //  TreeNode * node = NULL;
  cout<< "Factor gets "<< token.lex()<<" of type "<<token.type()<<endl;
  if(token.type()==Token :: LPAREN)
    {
	  
      token = lexer.nextToken();
      TreeNode *node =  expression();
	
      if(token.type()==Token :: RPAREN)
	{
	  token = lexer.nextToken();
	  return node;
	  
	}
      else
	{
	  error("Missing Right Parentheis");
	}
    }
  
  else if(token.type() == Token::IDENT){
    string str = token.lex();
    token = lexer.nextToken();
    return  new TreeNode(VAR,str);
  }
  else  if(token.type() == Token :: INTLIT){
    string str = token.lex();
     token = lexer.nextToken();
    return  new TreeNode(LIT,str);
  }
  
  else{
    error("Expected a left parenthesis integer or identifier");
    
  }

  return NULL;
}

Parser::TreeNode* Parser::term() {
  
  TreeNode * node = factor();
  
  while(token.type() == Token::TIMES||token.type()==Token::DIVIDE){
  if(token.type()==Token::TIMES){
    token = lexer.nextToken();
    node = new TreeNode(MULT,node,factor());
  }
  else if(token.type()==Token::DIVIDE){
    token = lexer.nextToken();
    node = new  TreeNode(DIV,node,factor());
  }
  }
  return node;
}

Parser::TreeNode* Parser::expression() {
  
  TreeNode * node = term();
  
  while(token.type()== Token::PLUS||token.type()==Token::MINUS){
    if(token.type()==Token::PLUS){	  
       token = lexer.nextToken();
      node = new TreeNode(ADD,node, term());
    }
    else if(token.type() ==Token:: MINUS){
      token = lexer.nextToken();
      node =  new TreeNode(SUB,node, term());
    }
   }
  
  return node;
}

Parser::TreeNode* Parser::relationalExpression(){
  cout << "relationalExpression():"<<token.lex()<<endl;
  TreeNode * node =  expression();
  cout<<"after Expression() in relationalExpression:"<<token.lex()<<endl;
  int toktype = token.type();
  if(toktype==Token::EQ||toktype==Token::LT||toktype==Token::LE||toktype==Token::GT||toktype==Token::GE||toktype==Token::NE){
    
    //save token type
    //       token = lexer.nextToken();
	
    if(toktype == Token::EQ){
      cout <<"Found EQ!"<<endl;
      token = lexer.nextToken();
      return new TreeNode(ISEQ,node,expression());
    }
    else if(toktype == Token::LT){
      return new TreeNode(ISLT,node,expression());
    }
    else if(toktype == Token::LE){
      return new TreeNode(ISLE,node,expression());
    }
    else if(toktype == Token::GT){
      return new TreeNode(ISGT,node,expression());
    }
    else if(toktype == Token::GE){
      return new TreeNode(ISGE,node,expression());
    }
    else if(toktype == Token::NE){
      return new TreeNode(ISNE,node,expression());
    }

  }
  else
    
    error("Relational Expression not found");
  return NULL;
 
}

Parser::TreeNode* Parser::logicalExpression() {
  cout<<"logicalExpression:"<<token.lex()<<endl;
  TreeNode *node =relationalExpression();
  cout<<"Token after relationalExpression:"<<token.lex()<<endl;
  while(token.type()==Token::AND||token.type()==Token::OR){
    if(token.type() == Token::AND){
      token = lexer.nextToken();
      node = new TreeNode(AND,node, relationalExpression());
    }
    else if(token.type()==Token::OR){
      token = lexer.nextToken();
      node = new TreeNode(OR,node,relationalExpression());
    }
  }
  
  return node;
}

Parser::TreeNode* Parser::setStatement() {

	
  token = lexer.nextToken();
  check(Token :: IDENT, "Identifier Expected");
  TreeNode* node = new TreeNode(STORE,token.lex());
  token = lexer.nextToken();
  
  check(Token::ASSIGN,"Assignment Expected");
  
  token = lexer.nextToken();
  return new TreeNode(SEQ,expression(),node);
  
}

Parser::TreeNode* Parser::printStatement() {


   token = lexer.nextToken();
TreeNode* node= expression();
	
   while(token.type()==Token::COMMA){	
      token = lexer.nextToken();
      return new TreeNode(SEQ,printStatement(),new TreeNode(SEQ, node,new TreeNode(PRINT))); 
    }
	  
    return new TreeNode(SEQ,node,new TreeNode(PRINT));
 
}

Parser::TreeNode* Parser::whileStatement() {

  token = lexer.nextToken();  
  string lab1 = makeLabel();
  string lab2 = makeLabel();
  
  TreeNode * tre1 = new TreeNode(SEQ, new TreeNode(LABEL,lab1),logicalExpression());
	    
  check(Token::DO,"Expected DO");
		
  token = lexer.nextToken();
  TreeNode * tre2= new TreeNode(SEQ,new TreeNode(JUMPF,lab2),compoundStatement());
		
  check(Token::END,"Expected END");	  
  token = lexer.nextToken();		

  return new TreeNode(SEQ,new TreeNode(SEQ,tre1,tre2),new TreeNode(SEQ,new TreeNode(JUMP,lab1),new TreeNode(LABEL,lab2)));
}

Parser::TreeNode* Parser::ifStatement() {


  string lab1 = makeLabel();
  string lab2 = makeLabel();
  token = lexer.nextToken();
  TreeNode* tree1= new TreeNode(SEQ, logicalExpression(),new TreeNode(JUMPF, lab1));

  check(Token::THEN,"Expected THEN");
      
  token = lexer.nextToken();
   TreeNode* comp= compoundStatement();
  TreeNode* tree2= new TreeNode(SEQ, tree1,comp);
  TreeNode* elsenode = NULL;
    
  if(token.type()==Token::ELSE){
    token = lexer.nextToken();
    TreeNode *hold = new TreeNode(SEQ, comp, new TreeNode(JUMPT,lab2));
        tree2 = new TreeNode (SEQ, tree1,hold);
        elsenode = new TreeNode(SEQ, new TreeNode(LABEL,lab2+":") ,compoundStatement());
        
        
  }
    
	  TreeNode * tree5 = NULL; 
    if(elsenode == NULL) {
        
        tree5 = new TreeNode(SEQ,tree2,new TreeNode(LABEL,lab1+":"));
    }
    else {
        TreeNode * temp= new TreeNode(SEQ,tree2,elsenode);
        tree5 = new TreeNode(SEQ, temp, new TreeNode(LABEL, lab1+":"));
    }
    
  check(Token::ENDIF,"Expected ENDIF");
  token = lexer.nextToken();
  
  return  tree5;
}
Parser::TreeNode * Parser::statement(){
  if(token.type() == Token::SET){
    setStatement();
  }
  else if(token.type() == Token::WHILE){
    whileStatement();
  }
  else if(token.type() == Token::IF){
    ifStatement();
  }
  else if(token.type() == Token::PRINT){
    printStatement();
  }
  else{
    error("Statement missing");
  }

  return NULL;
}
Parser::TreeNode* Parser::compoundStatement() {
     
 TreeNode * node = statement();
  while(token.type() == Token::SET||token.type()==Token::PRINT||token.type()==Token::WHILE||token.type()==Token::IF){
      node = new TreeNode(SEQ,node,statement());   
  }
  return node;
  
}

Parser::TreeNode* Parser::program() {
	check(Token::PROGRAM,"Program invalid");
	
	token = lexer.nextToken();
	check(Token::IDENT,"Program invalid");
	
	token = lexer.nextToken();
	TreeNode * head = compoundStatement();
	
	check(Token::END,"Program invalid");
	token = lexer.nextToken();
	
	check(Token::PROGRAM,"Program invalid");
	
	return head;
}

