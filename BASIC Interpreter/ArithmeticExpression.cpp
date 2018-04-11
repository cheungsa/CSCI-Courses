#include "ArithmeticExpression.h"

ArithmeticExpression::ArithmeticExpression()
{

}

int ArithmeticExpression::getValue()
{
  return 0;
}

std::string ArithmeticExpression::getStringAE1() {
  return 0;
} 

std::string ArithmeticExpression::getStringAE2() {
  return 0;
} 

// constants
Constant::Constant(std::string val)
{
  _val = val;
}

Constant::~Constant ()
{

}

void Constant::print (std::ostream & o) const
{
  o << _val;
}

int Constant::getValue () 
{
  i_val = stoi(_val);
  return i_val;
}

std::string Constant::getString()
{ 
  return _val;
}

// variables
Variable::Variable(std::string var, std::map<std::string,int>& m)
{
  _var = var;
  i_var = 0;
  varTracker = &m;
}

Variable::~Variable ()
{

}

void Variable::setVar(std::string var, int val)
{
  std::map<std::string,int>::iterator it;
  it = varTracker->find(var);

  if (it != varTracker->end())
  {
    varTracker->insert( std::pair<std::string,int>(var,val) );
  }
  else
  {
    varTracker->erase(var);
    varTracker->insert( std::pair<std::string,int>(var,val) );    
  }
}

bool Variable::isDefined (std::string var)
{
  std::map<std::string,int>::iterator it;
  it = varTracker->find(var);

  if (it != varTracker->end() || varTracker->at(var) != 0)
  {
    return false;
  }
  else
  {
    return true;
  }
}

std::string Variable::getString()
{
  return _var;
}

int Variable::getValue ()
{
    std::map<std::string,int>::iterator it;
    std::string varName = _var;
    it = varTracker->find(varName);

    if (it == varTracker->end())
    {
      i_var = 0;
      return i_var;
    }
    else
    {
      i_var = varTracker->at(varName);
      return i_var;
    }    
}

void Variable::print (std::ostream & o) const
{
  o << _var;
}

// variable arrays
VarArray::VarArray(Variable *var, ArithmeticExpression *ae, std::map<std::string,int>& m)
{
  _var = var;
  _ae = ae;
  varTracker = &m;
}

VarArray::~VarArray ()
{
  delete _var;
  delete _ae;
}

void VarArray::print (std::ostream & o) const
{
  _var->print(o);
  o << "[";
  _ae->print (o);
  o << "]";
}

void VarArray::declareVarArr(std::string varArr)
{
  int zero = 0;
  varTracker->insert( std::pair<std::string,int>(varArr,zero) );
}

void VarArray::setVarArr(std::string varArr, int val)
{
  std::map<std::string,int>::iterator it;
  it = varTracker->find(varArr);

  if (it != varTracker->end())
  {
    varTracker->insert( std::pair<std::string,int>(varArr,val) );
  }
  else
  {
    varTracker->erase(varArr);
    varTracker->insert( std::pair<std::string,int>(varArr,val) );    
  }
}

bool VarArray::isDefined (std::string varArr)
{
  std::map<std::string,int>::iterator it;
  it = varTracker->find(varArr);

  if (it != varTracker->end())
  {
    return false;
  }
  else
  {
    return true;
  }
}

std::string VarArray::getString()
{ 
  std::stringstream ss;
  _ae->print(ss);
  return ss.str();
}

int VarArray::getValue ()
{
    std::stringstream ss1;
    _var->print(ss1);
    std::string sVar = ss1.str(); 

    std::stringstream ss2;
    _ae->print(ss2);
    std::string sAe = ss2.str();    

    std::string varArrName = sVar;
    std::string varArrElement = sAe;
    std::string varArrNameWhole = varArrName + "[" + varArrElement + "]";

    std::map<std::string,int>::iterator it;
    it = varTracker->find(varArrNameWhole);

    if (it != varTracker->end())
    {
      int zero = 0;
      return zero;
    }
    else
    {
      int result = varTracker->at(varArrNameWhole);
      return result;
    }  
}

// addition
Addition::Addition (ArithmeticExpression *ae1, ArithmeticExpression *ae2)
{
  _ae1 = ae1;
  _ae2 = ae2;
}

Addition::~Addition ()
{
  delete _ae1;
  delete _ae2;
}
  
void Addition::print (std::ostream & o) const
{
  o << "(";
  _ae1->print (o);
  o << " + ";
  _ae2->print (o);
  o << ")";
}

int Addition::getValue ()
{
  int result = _ae1->getValue() + _ae2->getValue();
  return result;
}

std::string Addition::getString()
{ 
  std::stringstream ss1;
  _ae1->print(ss1);
  std::stringstream ss2;
  _ae1->print(ss2);  
  std::string result = ss1.str() + ss2.str();
  return result;
}

// subtraction
Subtraction::Subtraction (ArithmeticExpression *ae1, ArithmeticExpression *ae2)
{
  _ae1 = ae1;
  _ae2 = ae2;
}

Subtraction::~Subtraction ()
{
  delete _ae1;
  delete _ae2;
}
  
void Subtraction::print (std::ostream & o) const
{
  o << "(";
  _ae1->print (o);
  o << " - ";
  _ae2->print (o);
  o << ")";
}

int Subtraction::getValue ()
{
  int result = _ae1->getValue() - _ae2->getValue();
  return result;
}

std::string Subtraction::getString()
{ 
  std::stringstream ss1;
  _ae1->print(ss1);
  std::stringstream ss2;
  _ae1->print(ss2);  
  std::string result = ss1.str() + ss2.str();
  return result;
}

// multiplication
Multiplication::Multiplication (ArithmeticExpression *ae1, ArithmeticExpression *ae2)
{
  _ae1 = ae1;
  _ae2 = ae2;
}

Multiplication::~Multiplication ()
{
  delete _ae1;
  delete _ae2;
}
  
void Multiplication::print (std::ostream & o) const
{
  o << "(";
  _ae1->print (o);
  o << " * ";
  _ae2->print (o);
  o << ")";
}

int Multiplication::getValue ()
{
  int result = _ae1->getValue() * _ae2->getValue();
  return result;
}

std::string Multiplication::getString()
{ 
  std::stringstream ss1;
  _ae1->print(ss1);
  std::stringstream ss2;
  _ae1->print(ss2);  
  std::string result = ss1.str() + ss2.str();
  return result;
}

// division
Division::Division (ArithmeticExpression *ae1, ArithmeticExpression *ae2)
{
  _ae1 = ae1;
  _ae2 = ae2;
}

Division::~Division ()
{
  delete _ae1;
  delete _ae2;
}
  
void Division::print (std::ostream & o) const
{
  o << "(";
  _ae1->print (o);
  o << " / ";
  _ae2->print (o);
  o << ")";
}

int Division::getValue () 
{
  if (_ae2->getValue() == 0) 
  {

    std::cout << "Division by 0: " ;
    _ae1->print(std::cout);
    std::cout << " = " ;
    std::cout << _ae1->getValue();
    std::cout << ", " ;    
    _ae2->print(std::cout);
    std::cout << " = "; 
    std::cout << _ae2->getValue() << "." << std::endl;
    throw std::logic_error("");    
  }      

  int result = _ae1->getValue() / _ae2->getValue();
  return result;
}

std::string Division::getString()
{ 
  std::stringstream ss1;
  _ae1->print(ss1);
  std::stringstream ss2;
  _ae2->print(ss2);  
  std::string result = ss1.str() + ss2.str();
  return result;
}

std::string Division::getStringAE1()
{ 
  std::stringstream ss1;
  _ae1->print(ss1);
  std::string result = ss1.str();
  return result;
}

std::string Division::getStringAE2()
{ 
  std::stringstream ss2;
  _ae2->print(ss2);  
  std::string result = ss2.str();
  return result;
}