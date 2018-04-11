#include <iostream>
#include <map>
#include <sstream>

class ArithmeticExpression;
class BooleanExpression;
class Variable;
class VarArray;

class Command {
  // abstract class for a BASIC Command

 public:
  Command();
  virtual ~Command () {};
  virtual void print (std::ostream & o) const = 0;
  virtual int getType () = 0;
  virtual int getDestLine () = 0;  
  virtual void executePrint(std::ostream & o);
  virtual std::string getPrintString();   
  virtual int executeValPrint ();
  virtual std::string executeVarLet();
  virtual std::string executeVarArrLet();
  virtual int executeValLet();
  virtual int executeGoto ();
  virtual int executeIfthen ();  

protected:
  int _lineSrc;
};

// add below other classes that are needed
class Print : public Command {
 public:
  Print (int lineSrc, ArithmeticExpression *ae1);
  ~Print ();
  Print (Command *state);
  void executePrint(std::ostream & o);
  int executeValPrint ();
  std::string getPrintString();  
  virtual int getType () {return 1;};
  virtual int getDestLine () {return 0;};
  
  virtual void print (std::ostream & o) const;  

 private:
  ArithmeticExpression *_ae1; // the left and right term
  Command *_state;
};

class Let : public Command {
 public:
  Let (int lineSrc, ArithmeticExpression *ae1, ArithmeticExpression *ae2);
  ~Let ();
  Let (Command *state);
  std::string executeVarLet ();
  std::string executeVarArrLet();
  int executeValLet ();

  virtual void print (std::ostream & o) const;
  virtual int getType () {return 2;};  
  virtual int getDestLine () {return 0;};

 private:
  ArithmeticExpression *_ae1; // the left and right term
  ArithmeticExpression *_ae2;
  Command *_state;

};

class Goto : public Command {
 public:
  Goto (int lineSrc, int lineDest);
  ~Goto ();
  Goto(Command *state);
  
  virtual int executeGoto();  
  virtual void print (std::ostream & o) const;
  virtual int getType () {return 3;};
  virtual int getDestLine () {return _lineDest;};

 private:
  int _lineDest; // the left and right term
  Command *_state;
};

class Ifthen : public Command {
 public:
  Ifthen (int lineSrc, BooleanExpression *be, int lineDest);
  ~Ifthen ();
  Ifthen (Command *state);
  int executeIfthen();

  virtual void print (std::ostream & o) const;
  virtual int getType () {return 4;};
  virtual int getDestLine () {return 0;};
  
 private:
  BooleanExpression *_be; // the left and right term
  int _lineDest;
  Command *_state;

};

class Gosub : public Command {
 public:
  Gosub (int lineSrc, int lineDest);
  ~Gosub ();
  Gosub (Command *state);
  int executeGosub();
  
  virtual void print (std::ostream & o) const;
  virtual int getType () {return 5;};
  virtual int getDestLine () {return _lineDest;};
 
 private:
  int _lineDest; // the left and right term
  Command *_state;
};

class Return : public Command {
 public:
  Return (int lineSrc);
  ~Return ();
  Return (Command *state);


  virtual void print (std::ostream & o) const;
  virtual int getType () {return 6;};
  virtual int getDestLine () {return 0;};
 
 private:
  Command *_state;
};

class End : public Command {
 public:
  End (int lineSrc);
  ~End ();
  End (Command *state);

  
  virtual void print (std::ostream & o) const;
  virtual int getType () {return 7;};
  virtual int getDestLine () {return 0;};

 private:
  Command *_state;  
};
