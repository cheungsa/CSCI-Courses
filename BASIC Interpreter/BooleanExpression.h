#include <iostream>

class ArithmeticExpression;

// This file is for classes that have to do with Boolean expressions

class BooleanExpression {
  // abstract class for a Boolean expression

 public:
  BooleanExpression();
  virtual void print (std::ostream & o) const = 0;
  virtual ~BooleanExpression () {};

  virtual bool getValue();
  // pure virtual print function. Don't implement!
};

// add below other classes that are needed
class Equal : public BooleanExpression {
 public:
  Equal (ArithmeticExpression *ae1, ArithmeticExpression *ae2);
  ~Equal ();
  
  virtual void print (std::ostream & o) const;
  virtual bool getValue();  
  
 private:
  ArithmeticExpression *_ae1, *_ae2; // the left and right term
};

class Less : public BooleanExpression {
 public:
  Less (ArithmeticExpression *ae1, ArithmeticExpression *ae2);
  ~Less ();
  
  virtual void print (std::ostream & o) const;
  virtual bool getValue();
  
 private:
  ArithmeticExpression *_ae1, *_ae2; // the left and right term
};

class Greater : public BooleanExpression {
 public:
  Greater (ArithmeticExpression *ae1, ArithmeticExpression *ae2);
  ~Greater ();
  
  virtual void print (std::ostream & o) const;
  virtual bool getValue();
  
 private:
  ArithmeticExpression *_ae1, *_ae2; // the left and right term
};