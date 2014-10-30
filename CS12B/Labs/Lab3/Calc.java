/*
	Author - John Allard, ID: 1437547
	Class  - CS12B, Lab#3
	Date   - Oct 25th, 2014
	
	File   - Calc.java
	Info   - This file defines the reverse-polish-notation calculator required by Lab 3. This file defines the
  Clac class, which will implement the simple calculator. This entire class is really just a wrapping around 
  a stack object that I defined in @file Stack.java. This calculator will allow the user to push and pop operands
  from the stack, as well as add, divide, multiple, subtract, and reciprocate the numers on the top of the stack.
*/


import static java.lang.System.*; 
import java.util.*;

class Calc {

  private Stack stack;

  /* Default Constructor */
  Calc() {
   stack = new Stack();
  }

  public boolean push(double value) throws IllegalArgumentException {
  	 return stack.push(value);
  }

  public double pop() throws EmptyStackException {
      return stack.pop();
  }

   public double peek() throws EmptyStackException {
      return stack.peek();
  }


  public double add() throws IllegalArgumentException {
    double num1, num2;

    try{
       num1 = stack.pop();
       num2 = stack.pop();
    }catch(EmptyStackException ex){
      throw new IllegalArgumentException("Need at least two Elements to Multiply");
    }

    double ret = num1+num2;
    stack.push(ret);

    return ret;
  }

    public double subtract() throws IllegalArgumentException {
    double num1, num2;
    
    try{
       num1 = stack.pop();
       num2 = stack.pop();
    }catch(EmptyStackException ex){
      throw new IllegalArgumentException("Need at least two Elements to Multiply");
    }

    double ret = num2-num1;
    stack.push(ret);

    return ret;
  }

    public double multiply() throws IllegalArgumentException {
    double num1, num2;
    
    try{
       num1 = stack.pop();
       num2 = stack.pop();
    }catch(EmptyStackException ex)
    {
      throw new IllegalArgumentException("Need at least two Elements to Multiply");
    }

    double ret = num1*num2;
    stack.push(ret);

    return ret;
  }

    public double divide() throws IllegalArgumentException {
    double num, den;
    
    try{
       den = stack.pop();
       num = stack.pop();
    }catch(EmptyStackException ex) {
      throw new IllegalArgumentException("Need at least two Elements to Multiply");
    }

    if(den == 0)
      throw new IllegalArgumentException("Divisor Equal to Zero");

    double ret = num/den;
    stack.push(ret);

    return ret;
  }

  public double reciprocal() throws IllegalArgumentException {
    double num,den;
    num = 1.0;
    
    try{
          den = stack.pop();
       }catch(EmptyStackException ex){
          throw new IllegalArgumentException("Empty Stack");
       }

    if(den == 0)
      throw new IllegalArgumentException("Divisor Equal to Zero");

    double ret = num/den;
    stack.push(ret);

    return ret;
  }

  public int depth() {
    return stack.getSize();
  }

  public double getCapactity() {
    return stack.getCapacity();
  }
  
}