#include <iostream>
#include <fstream>
#include <sstream>
#include <ctype.h>
#include <stdlib.h>
#include <queue>
#include <vector>
#include <stack>
#include "ArithmeticExpression.h"
#include "BooleanExpression.h"
#include "Command.h"

using namespace std;

bool isOperator (char s)
{
	if ((s == '+') || (s == '-') || (s == '*') || (s == '/'))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isBoolOperator (char s)
{
	if ((s == '<') || (s == '>') || (s == '='))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isDigit (char s)
{
	if ((s == '0') || (s == '1') || (s == '2') || (s == '3') || (s == '4') || 
		(s == '5') || (s == '6') || (s == '7') || (s == '8') || (s == '9'))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isNegative (char s)
{
	if (s == '-')
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isArray (string s)
{
	for (unsigned int i=0; i<s.length(); i++)
	{
		if (s[i] == '[')
		{
			return true;
		}
	}
	return false;
}

//Constant* parseConstant (string s, int & pos)
ArithmeticExpression* parseConstant (string s, int & pos)
{
	string numstring = "";
	numstring = numstring + s[pos];
	pos++;
	//while s still has digits append them to number_string
	//move pos to match the char i am looking at in s
	//at end s[pos] will be a non-digit
	while (isNegative(s[pos]) || isDigit(s[pos]))
	{
		numstring = numstring + s[pos];
		pos++;
	}
	Constant *co = new Constant(numstring);
	//ArithmeticExpression *myConstant = new Constant(numstring);
	return co;
}

string parseVariableName (string s, int & pos)
{
	string varName = "";
	varName = varName + s[pos];
	pos++;
	//while s still as uppercase letters append them to varName
	///move pos to match the char i am looking at in s
	//at end s[pos] will be a non uppercase letter
	while (isupper(s[pos]))
	{
		varName = varName + s[pos];
		pos++;
	}
	return varName;
}

ArithmeticExpression* ParseArithmeticExpression(string s, int & pos, std::map<string,int>& m)
{
	while (isspace(s[pos]))
	{
		pos++;
	}

	ArithmeticExpression * result = NULL;

	char element = s[pos];
	if (isDigit(element) || isNegative(element))
	{
		return parseConstant(s, pos);
	}
	// else if (element is char)
	else if (isupper(element))
	{
		string varName = parseVariableName(s,pos);
		unsigned int pos1 = pos;
		if (pos1 == s.length())
		{
			Variable* myVar = new Variable(varName, m);

			string varString = myVar->getString();	
			return myVar;
		}
		//pos++;
		//skip whitespace by updating pos
		while (isspace(s[pos]))
		{
			pos++;
		}
		if (s[pos] != '[')
		{
			Variable *myVar = new Variable(varName, m);
			
			string varString = myVar->getString();			
			return myVar;
		}
		else
		{
			//i have an array
			Variable *myVarA = new Variable(varName, m);
			// skip [
			if (s[pos] == '[')
			{
				pos++;
			}

			string varString = myVarA->getString();
			// skip whitespace by updating pos
			//while ((s[pos] = ' '))
			while (isspace(s[pos]))
			{
				pos++;
			}
			ArithmeticExpression* myAE = ParseArithmeticExpression(s, pos, m);
			// skip whitespace by updating pos
			while (isspace(s[pos]))
			{
				pos++;
			}
			//skip ] and update pos
			if (s[pos] == ']')
			{
				pos++;
			}
			ArithmeticExpression* myArray = new VarArray(myVarA, myAE, m);

			string varArrString = myArray->getString();
			//m.insert( std::pair<string,int> (varArrString,0) );
			return myArray;
		}
	}
	else if(s[pos] == '(')
	{
		//must be a '(' and contains a binary expression
		pos++; 
		ArithmeticExpression* left = ParseArithmeticExpression(s, pos, m);

		//skip whitespace-update pos
		while (isspace(s[pos]))
		{
			pos++;
		}
		//get operator-update pos	
		char op = s[pos];
		pos++;
		while (isspace(s[pos]))
		{
			pos++;
		}

		if (isOperator(s[pos]))
		{
			op = s[pos];	
		} 
		//skip whitespace-update pos
		while (isspace(s[pos]))
		{
			pos++;
		}

		ArithmeticExpression* right = ParseArithmeticExpression(s, pos, m);

		//skip whitespace
		while (isspace(s[pos]))
		{
			pos++;
		}

		// in middle operator of nested ae, right is 0x0 but left has address for parsed 5+7
		if (op == '+')
		{
			result = new Addition(left, right);
		}
		if (op == '-')
		{
			result = new Subtraction(left, right);
		}
		if (op == '*')
		{
			result = new Multiplication(left, right);
		}
		if (op == '/')
		{
			result = new Division(left, right);
		}
		pos++;

	}

	return result;
}

BooleanExpression* ParseBooleanExpression(string s, int & pos, std::map<string,int>& m)
{
	int bpos = 0;
	string left = "";
	string right = "";
	int zero1 = 0;
	int zero2 = 0;

	while (isspace(s[bpos]))
	{
		bpos++;
	}

	int count = bpos;

	while (!isBoolOperator(s[count]))
	{
		left = left + s[count];
		count++;
		bpos++;
	}

	ArithmeticExpression *ae1 = ParseArithmeticExpression(left, zero1, m);

	while (isspace(s[bpos]))
	{
		bpos++;
	}

	char oper = s[bpos];
	if (isBoolOperator(s[bpos]))
	{
		oper = s[bpos];
	}
	bpos++;

	while (isspace(s[bpos]))
	{
		bpos++;
	}
	count = bpos;	

	for (unsigned int i=count; i<s.length(); i++)
	{
		right = right + s[i];
		count++;
		bpos++;
	}

	ArithmeticExpression *ae2 = ParseArithmeticExpression(right, zero2, m);

	if (oper == '<')
	{
		return new Less(ae1, ae2);
	}
	else if (oper == '>')
	{
		return new Greater(ae1, ae2);
	}
	else
	{
		return new Equal(ae1, ae2);
	}
}

int main(int argc, char* argv[])
{
  if(argc < 2){
    cerr << "Please provide an input file." << endl;
    return 1;
  }

  ifstream input(argv[1]);

  if (!input)
  {
  	cout << "File " << argv[1] << " cannot be opened." << endl;
  	return 1;
  }

  string curr; // the current line
  // stores key of line number (int) and value of corresponding command (Command*)
  std::map<int,Command*> coTracker; 

  // stores the ordered line numbers (int); for line-jumping commands
  std::vector<int> lineTracker;
  // stores key of ae (string) and value of evaluated ae (int)
  std::map<string,int> pointMap;

  Command *coPrint = NULL;
  Command *coLet = NULL;
  Command *coGoto = NULL; 
  Command *coIfthen = NULL; 
  Command *coGosub = NULL; 
  Command *coReturn = NULL;
  Command *coEnd = NULL;

  //loop to read all lines of the program
  while(getline(input, curr)) {
	  stringstream ss;
	  ss << curr;
    string command; // the command
    int line;  // the line number
    
    ss >> line;
    ss >> command;

    lineTracker.push_back(line);

    // if open parentheses then arithmetic
    // boolean no parentheses 

    if (!command.compare("PRINT")) {
		string expr;
		getline(ss, expr);
		int curr = 0;
		
		while (isspace(expr[curr]))
		{
			curr++;
		}
//		curr++;
		string subexpr = expr.substr(curr, expr.length()-curr);
		int zero_index = 0;

		ArithmeticExpression *ae = ParseArithmeticExpression(subexpr, zero_index, pointMap);

		coPrint = new Print(line, ae);
		coPrint->print(std::cout);
		coTracker.insert( std::pair<int,Command*>(line,coPrint) );
    }
    else if (!command.compare("LET")) {
		string expr;
		getline(ss, expr);
		int curr = 0;
		int zero_index = 0;

		string letExpr = "";

		while (isspace(expr[curr]))
		{
			curr++;
		}
		for (unsigned int i=curr; i<expr.length(); i++)
		{
			letExpr += expr[i];
		}
		ArithmeticExpression* ae1 = ParseArithmeticExpression(letExpr, zero_index, pointMap);
		ArithmeticExpression* ae2 = ParseArithmeticExpression(letExpr, zero_index, pointMap);


		coLet = new Let(line, ae1, ae2);
		coLet->print(std::cout);
		coTracker.insert( std::pair<int,Command*>(line,coLet) );
    }
    else if (!command.compare("GOTO")) {
		int destLine;
		ss >> destLine;


		coGoto = new Goto(line, destLine);
		coGoto->print(std::cout);
		coTracker.insert( std::pair<int,Command*>(line,coGoto) );
    }
    else if (!command.compare("IF")) {
		string expr;
		getline(ss, expr);
		int zero_index = 0;

		size_t index = expr.find_last_of(("THEN")) - 3;

		string strBexpr = expr.substr(0, index);

		BooleanExpression *bexpr = ParseBooleanExpression(strBexpr, zero_index, pointMap);
		string strDestLine = expr.substr(index + 4);

		int destLine = stoi(strDestLine);

		coIfthen = new Ifthen(line, bexpr, destLine);
		coIfthen->print(std::cout);
		coTracker.insert( std::pair<int,Command*>(line,coIfthen) );
    }
    else if (!command.compare("GOSUB")) {
		int destLine;
		ss >> destLine;

		coGosub = new Gosub(line, destLine);
		coGosub->print(std::cout);
		coTracker.insert( std::pair<int,Command*>(line,coGosub) );
    }
    else if (!command.compare("RETURN")) {
		coReturn = new Return(line);
		coReturn->print(std::cout);
		coTracker.insert( std::pair<int,Command*>(line,coReturn) );
    }
    else if (!command.compare("END")) {
		coEnd = new End(line);
		coEnd->print(std::cout);
		coTracker.insert( std::pair<int,Command*>(line,coEnd) );
    }
    else {
      // This should never happen - print an error?
      cout << "Error - incorrect command" << endl;
    }
  }

  std::stack<int> gosubStack;
  int lineTrackerSize = lineTracker.size();
  int count = 0;

  while (!coTracker.empty()) // empty when "END" is called
  {
  	
  	int currLine = lineTracker.at(count);

  	// store vector of int line numbers, as i see them push them to the back of the 
  	// vector, go through the vector to get line number
  	if ((coTracker[currLine])->getType() == 1) // command is PRINT
  	{
  		map<int,Command*>::iterator it = coTracker.find(currLine);
				
		try {    
  	 		it->second->executeValPrint();  
		}  
		catch (std::logic_error&) {  
    		coTracker.clear();  
    		break;
		}  		

		std::string printStr = it->second->getPrintString();
	
		if (isDigit(printStr[0]) || printStr[0] == '(')		
		{
			it->second->executePrint(std::cout);			
		}
		else // if just a variable
		{	
  			map<string,int>::iterator it2 = pointMap.find(printStr);
  			it2 = pointMap.find(printStr);			
			if (it2 == pointMap.end())
			{
				cout << "0" << endl;
			}
			else
			{
				cout << pointMap[printStr] << endl;
			}

		}
		
		count++;
  	}
  	else if ((coTracker[currLine])->getType() == 2) // command is LET
  	{

  		map<int,Command*>::iterator it = coTracker.find(currLine);

		try {    
  	 		it->second->executeValLet();  
		}  
		catch (std::logic_error&) {  
    		
    		coTracker.clear();  
    		break;
		}
  		
  		std::string varLName = it->second->executeVarLet();
  		int varLVal = it->second->executeValLet();

  		std::map<std::string,int>::iterator it2;
  		it2 = pointMap.find(varLName);

		pointMap[varLName] = varLVal;     	  		

  		count++;					
  	}
  	else if ((coTracker[currLine])->getType() == 3) // command is GOTO
  	{

  		map<int,Command*>::iterator it = coTracker.find(currLine);
  		int lineDest = it->second->executeGoto();

  		int lineDNE = -1; //checks if line does not exist
  		
  		for (int i=0; i<lineTrackerSize; i++)
  		{
  			if (lineTracker.at(i) == lineDest)
  			{
  				count = i;
  				lineDNE = i;
  			}
 
  		}

  		if (lineDNE == -1 )
  		{
  			cout << "Error in Line " << currLine << ": GOTO to non-existent line " <<
  			currLine << "." << endl;
  			coTracker.clear();
  		}
  	}
  	else if ((coTracker[currLine])->getType() == 4) // command is IFTHEN
  	{
  		map<int,Command*>::iterator it = coTracker.find(currLine);

		try {    
  	 		it->second->executeIfthen();
		}  
		catch (std::logic_error&) {  
    		
    		coTracker.clear();  
    		break;
		}

  		int lineDest = it->second->executeIfthen();

  		int lineDNE = -1; //checks if line does not exist
  	
  		if (lineDest != -1)
  		{
  			for (int i=0; i<lineTrackerSize; i++)
  			{
  				if (lineTracker.at(i) == lineDest)
  				{
  					count = i;
  					lineDNE = i;
  				}
 
	  		}

	  		if (lineDNE == -1 )
	  		{
  				cout << "Error in Line " << currLine << 
  				": IF jump to non-existent line " << currLine << "." << endl;
  				coTracker.clear();
  			}
  		}	
  		else
  		{
  			count++;
  		}  		  		

  	}
  	else if ((coTracker[currLine])->getType() == 5) // command is GOSUB
  	{
  		gosubStack.push(currLine); // store gosub line in stack	

		int nextLine = (coTracker[currLine])->getDestLine();
  		
  		int lineDNE = 0; //checks if line does not exist
  		
  		for (int i=0; i<lineTrackerSize; i++)
  		{
  			if (lineTracker.at(i) == nextLine)
  			{
  				count = i;
  			}
  			lineDNE++;
  		}

  		if (lineDNE == lineTrackerSize && lineTracker.at(count) != nextLine)
  		{
			cout << "Error in Line " << currLine << 
			": GOSUB to non-existent line " << nextLine << "." << endl;
			coTracker.clear();
  		}

  	}
  	else if ((coTracker[currLine])->getType() == 6) // command is RETURN
  	{

 		int returnLine = 0; // line of most recent GOSUB
 		
 		if (!gosubStack.empty())
 		{
 			returnLine = gosubStack.top(); 
 			gosubStack.pop();
 		  	for (int i=0; i<lineTrackerSize; i++)
  			{
  				if (lineTracker.at(i) == returnLine)
  				{
  					count = i; // index of most recent GOSUB line
  				}
  			}
  			count++; // go to next command line after GOSUB	
 		}
 		else
 		{
			cout << "Error in Line " << currLine << 
			": No matching GOSUB for RETURN." << endl;
			coTracker.clear();
 		}		  		
  	}
  	else if ((coTracker[currLine])->getType() == 7) // command is end
  	{
  		//clear contents of map
  		coTracker.clear();
  	}
  	else
  	{
  		cout << "END has not been reached" << endl;
  		coTracker.clear();
  	}
  }

  return 0;
}