#include "Command.h"
#include "ArithmeticExpression.h"
#include "BooleanExpression.h"

Command::Command()
{

}

void Command::executePrint(std::ostream & o){

}

std::string Command::getPrintString() {
  return 0;
}

int Command::executeValPrint () {
  return 0;
}

std::string Command::executeVarLet() {
  return 0;
}

std::string Command::executeVarArrLet() {
  return 0;
}

int Command::executeValLet() {
  return 0;
}

int Command::executeGoto ()
{
  return 0;
}

int Command::executeIfthen () {
  return 0;
}


// print value of the arithmetic expression
Print::Print (int lineSrc, ArithmeticExpression *ae1)
{
  _lineSrc = lineSrc;
  _ae1 = ae1;
}

Print::Print (Command *state)
{
  _state = state;
}

Print::~Print ()
{
  delete _ae1;
  //delete _state;
}
  
void Print::print (std::ostream & o) const
{
  o << _lineSrc;
  o << " PRINT ";
  _ae1->print (o);
  o << std::endl;
}

void Print::executePrint (std::ostream &o)
{
  o << _ae1->getValue() << std::endl;
}

int Print::executeValPrint ()
{
  int result = _ae1->getValue();
  return result;
}

std::string Print::getPrintString()
{
  std::stringstream ss;
  _ae1->print(ss);
  return ss.str();
}

// write the value of the ae into the specified variable
Let::Let (int lineSrc, ArithmeticExpression *ae1, ArithmeticExpression *ae2)
{
  _lineSrc = lineSrc;
  _ae1 = ae1;
  _ae2 = ae2;
}

Let::Let (Command *state)
{
  _state = state;
}

Let::~Let ()
{
  delete _ae1;
  delete _ae2;
  //delete _state;
}
  
void Let::print (std::ostream & o) const
{
  o << _lineSrc;
  o << " LET ";
  _ae1->print(o);
  o << " ";
  _ae2->print(o);
  o << std::endl;
}


std::string Let::executeVarLet ()
{
  //std::string varLName = _ae1->getString();
  //return varLName;
  std::stringstream ss;
  _ae1->print(ss);
  return ss.str();
}

std::string Let::executeVarArrLet()
{
  std::string varLArrName = _ae2->getString();
  return varLArrName;  
}

int Let::executeValLet ()
{
  int varLVal = _ae2->getValue();
  return varLVal;
}

// jump to the specified line
Goto::Goto (int lineSrc, int lineDest)
{
  _lineSrc = lineSrc;
  _lineDest = lineDest;
}

Goto::Goto (Command* state)
{
  _state = state;
}

Goto::~Goto ()
{
  //delete _state;
}
  
void Goto::print (std::ostream & o) const
{
  o << _lineSrc;
  o << " GOTO <";
  o << _lineDest;
  o << ">" << std::endl;
}

int Goto::executeGoto ()
{ 
  int lineDest = _lineDest;
  return lineDest;
}

// if the boolean expression is true, then jump to specified line
Ifthen::Ifthen (int lineSrc, BooleanExpression *be, int lineDest)
{
  _lineSrc = lineSrc;
  _be = be;
  _lineDest = lineDest;
}

Ifthen::Ifthen (Command *state)
{
  _state = state;
}

Ifthen::~Ifthen ()
{
  delete _be;
  //delete _state;
}
  
void Ifthen::print (std::ostream & o) const
{
  o << _lineSrc;
  o << " IF [";
  _be->print (o);
  o << "] THEN <";
  o << _lineDest;
  o << ">" << std::endl;
}


int Ifthen::executeIfthen ()
{
  if (_be->getValue())
  {
    int lineDest = _lineDest;
    return lineDest;
  }
  else
  {
    int lineDest = -1;
    return lineDest;
  }
}

// jump to specified line and remember where you came from
Gosub::Gosub (int lineSrc, int lineDest)
{
  _lineSrc = lineSrc;
  _lineDest = lineDest;
}

Gosub::Gosub (Command* state)
{
  _state = state;
}

Gosub::~Gosub ()
{
 //delete _state;
}
  
void Gosub::print (std::ostream & o) const
{
  o << _lineSrc;
  o << " GOSUB <";
  o << _lineDest;
  o << ">" << std::endl;
}

int Gosub::executeGosub ()
{
  return _lineDest;
}

// go back to the line immediately after the line whence the most 
// recent GOSUB started
Return::Return (int lineSrc)
{
  _lineSrc = lineSrc;
}

Return::Return (Command* state)
{
  _state = state;
}

Return::~Return ()
{
 //delete _state;
}
  
void Return::print (std::ostream & o) const
{
  o << _lineSrc;
  o << " RETURN" << std::endl;
}

// terminate execution of program
End::End (int lineSrc)
{
  _lineSrc = lineSrc;
}

End::End (Command *state)
{
  _state = state;
}

End::~End ()
{
  //delete _state;
}
  
void End::print (std::ostream & o) const
{
  o << _lineSrc;
  o << " END" << std::endl;
}