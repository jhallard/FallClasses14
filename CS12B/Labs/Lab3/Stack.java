/*
	Author - John Allard, ID: 1437547
	Class  - CS12B, Lab#3
	Date   - Oct 25st, 2014
	
	File   - Stack.java
	Info   - This file defines a helper class for the Calculator program. The calculator that we are required to
  build is a reverse polish notation calculator, which means we need some sort of stack to make our calculator work.
  Thus this class defines a simple stack that with be used by the calculator to perform calculations. 
*/


import static java.lang.System.*; 
import java.util.*;

class Stack {

  public int capacity;
  public int items;

  private double[] stack;

  /* Default Constructor */
  Stack() {
   capacity = 100;
   items = 0;
   stack = new double[capacity];
  }

  public boolean push(double value) throws IllegalArgumentException {
  	if(items == capacity){
      throw new IllegalArgumentException();
    }
    else {
      // push the item on top of the stack, and increment the item counter
      stack[items++] = value;
      return true;
    }
  }

  public double pop() throws EmptyStackException {
    if(items == 0)
      throw new EmptyStackException();

    // return the top item, and decrement the item counter
    double ret = stack[--items];
    return ret;

  }

    public double peek() throws EmptyStackException {
    if(items == 0)
      throw new EmptyStackException();

    // return the last element without decrementing the counter
    return stack[items-1];

  }

  
  public int getSize() {
    return items;
  }

  public double getCapacity() {
    return capacity;
  }
  
}