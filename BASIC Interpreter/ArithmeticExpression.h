#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <stdexcept>

// This file is for classes that have to do with arithmetic expressions

class ArithmeticExpression {
  // abstract class for an arithmetic expression

 public:
  ArithmeticExpression();
  virtual void print (std::ostream & o) const = 0;
  virtual ~ArithmeticExpression() {};
  virtual std::string getString () = 0;
  virtual int getValue ();
  virtual std::string getStringAE1();
  virtual std::string getStringAE2();    
  // pure virtual print function. Don't implement!
};

class Constant : public ArithmeticExpression {
public:
  Constant(std::string val);
  ~Constant ();  

  virtual void print (std::ostream & o) const;
  virtual int getValue ();
  virtual std::string getString();

private:
  std::string _val;
  int i_val;
};

class Variable : public ArithmeticExpression {
public:
  Variable(std::string var, std::map<std::string,int>& m);
  ~Variable ();
  void declareVar(std::string var);
  void setVar(std::string var, int val);
  bool isDefined (std::string var);
  
  virtual std::string getString();
  virtual void print (std::ostream & o) const;
  virtual int getValue ();

private:
  std::string _var; 
  int i_var;
  std::map<std::string,int>* varTracker;
};

class VarArray : public ArithmeticExpression {
public:
  VarArray(Variable *var, ArithmeticExpression *ae, std::map<std::string,int>& m);
  ~VarArray ();

  void declareVarArr(std::string varArr);
  std::string setString();
  void setVarArr(std::string varArr, int val);
  bool isDefined (std::string varArr);

  virtual std::string getString();
  virtual void print (std::ostream & o) const;
  virtual int getValue ();

private:
  Variable *_var;
  ArithmeticExpression *_ae;
  std::map<std::string,int>* varTracker; // position, value
};

class Addition : public ArithmeticExpression {
 public:
  Addition (ArithmeticExpression *ae1, ArithmeticExpression *ae2);
  ~Addition ();
  
  virtual void print (std::ostream & o) const;
  virtual int getValue ();
  virtual std::string getString();
  
 private:
  ArithmeticExpression *_ae1, *_ae2; // the left and right term
};

// add below other classes that are needed
class Subtraction : public ArithmeticExpression {
 public:
  Subtraction (ArithmeticExpression *ae1, ArithmeticExpression *ae2);
  ~Subtraction ();
  
  virtual void print (std::ostream & o) const;
  virtual int getValue ();
  virtual std::string getString();
  
 private:
  ArithmeticExpression *_ae1, *_ae2; // the left and right term
};

class Multiplication : public ArithmeticExpression {
 public:
  Multiplication (ArithmeticExpression *ae1, ArithmeticExpression *ae2);
  ~Multiplication ();
  
  virtual void print (std::ostream & o) const;
  virtual int getValue ();
  virtual std::string getString();
  
 private:
  ArithmeticExpression *_ae1, *_ae2; // the left and right term
};

class Division : public ArithmeticExpression {
 public:
  Division (ArithmeticExpression *ae1, ArithmeticExpression *ae2);
  ~Division ();
  std::string getStringAE1();
  std::string getStringAE2();  
  
  virtual void print (std::ostream & o) const;
  virtual int getValue ();
  virtual std::string getString();
  
 private:
  ArithmeticExpression *_ae1, *_ae2; // the left and right term
};