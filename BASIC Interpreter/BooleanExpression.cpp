#include "BooleanExpression.h"
#include "ArithmeticExpression.h"

BooleanExpression::BooleanExpression()
{
  
}

bool BooleanExpression::getValue()
{
  return true;
}

// equal to
Equal::Equal (ArithmeticExpression *ae1, ArithmeticExpression *ae2)
{
  _ae1 = ae1;
  _ae2 = ae2;
}

Equal::~Equal ()
{
  delete _ae1;
  delete _ae2;
}
  
void Equal::print (std::ostream & o) const
{
  _ae1->print (o);
  o << " = ";
  _ae2->print (o);
}

bool Equal::getValue()
{
  if (_ae1->getValue() == _ae2->getValue())
  {
    return true;
  }
  return false;
}

// less than
Less::Less (ArithmeticExpression *ae1, ArithmeticExpression *ae2)
{
  _ae1 = ae1;
  _ae2 = ae2;
}

Less::~Less ()
{
  delete _ae1;
  delete _ae2;
}
  
void Less::print (std::ostream & o) const
{
  _ae1->print (o);
  o << " < ";
  _ae2->print (o);
}

bool Less::getValue()
{
  if (_ae1->getValue() < _ae2->getValue())
  {
    return true;
  }
  return false;
}

// greater than
Greater::Greater (ArithmeticExpression *ae1, ArithmeticExpression *ae2)
{
  _ae1 = ae1;
  _ae2 = ae2;
}

Greater::~Greater ()
{
  delete _ae1;
  delete _ae2;
}
  
void Greater::print (std::ostream & o) const
{
  _ae2->print (o);
  o << " < ";
  _ae1->print (o);
}

bool Greater::getValue()
{
  if (_ae1->getValue() > _ae2->getValue())
  {
    return true;
  }
  return false;
}