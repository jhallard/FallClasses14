// File    - dllist.java
// Author  - John H Allard Jr. (template provided by Prof. Whitehead)
// Purpose - The purpose of this file is to define a doubly-linked-list class. This data structure is a linked list that allows
// O(1) access from either end of the list. This class is used as a helper class in the edfile program. This project was made 
// for CS12B HW #2 Fall Quarter 2014 at UCSC 

import java.util.NoSuchElementException;

public class dllist {

   public enum position {FIRST, PREVIOUS, FOLLOWING, LAST};

   private class node {
      String item;
      node prev;
      node next;
   }

   private node first = null;
   private node current = null;
   private node last = null;
   private int currentPosition = 0;
   private int members = 0;

   public void setPosition(position pos) {

      switch(pos){

         case FIRST:
         current = first;
         currentPosition = 0;
         break;

         case PREVIOUS:
         if(current == null)
            break;
         if(current.prev == null)
            break;
         current = current.prev;
         currentPosition--;
         break;

         case FOLLOWING:
         if(current == null)
            break;
         if(current.next == null)
            break;
         current = current.next;
         currentPosition++;
         break; 

         case LAST:
         current = last;
         currentPosition = members-1;
         break;
        
      }
   }



   public boolean isEmpty () {
      return (first == null && last == null);
   }



   public String getItem () throws NoSuchElementException {
      if(current == null)
         throw new NoSuchElementException();
      return current.item;
   }

   public int getPosition () {
      return currentPosition;
   }

   public void delete () {

      if(current == null || members == 0)
         throw new NoSuchElementException();

      if(currentPosition == 0){
         first = current.next;
         current = current.next;
         members--;
         return;
      }

      if(currentPosition == members-1){
         last = current.prev;
         current = null;
         members--;
         return;
      }

      if(members == 1) {
         first = null;
         last = null;
         current = null;
         members--;
         return;
      }

      // wrap the links in the chain around the current node.
      current.prev.next = current.next;
      current = null;
      members--;
   }

   public void insert (String item, position pos) {
      node temp = new node();
      temp.item = item;


      switch(pos){
         case FIRST:
         if(first != null)
            first.prev = temp;
         temp.next = first;
         first = temp;
         if(members == 0)
            last = temp;
         if(members == 1 && last != null)
            last.prev = temp;

         current = first;
         currentPosition = 0;
         members++;
         break;


         case LAST:
         temp.prev = last;
         temp.next = null;
         if(last != null)
            last.next = temp;
         last = temp;
         if(members == 0)
            first = temp;
         if(members == 1)
            first.next = temp;
         current = last;
         members++;
         currentPosition = members -1;
         break;


         case PREVIOUS:

         if(members == 0)
            insert(item, position.FIRST);
         if(currentPosition == 0)
            throw new IllegalArgumentException();

         temp.prev = current.prev;
         current.prev.next = temp;
         temp.next = current;
         current.prev = temp;
         current = temp;
         members++;
         currentPosition--;
         break;


         case FOLLOWING:
         if(members==0)
            insert(item, position.FIRST);
         if(currentPosition == members-1)
            throw new IllegalArgumentException();

         current.next.prev = temp;
         temp.prev = current;
         temp.next = current.next;
         current.next = temp;
         current = temp;
         members++;
         currentPosition++;
         break;
      }

   }


   public int getMembers(){
      return members;
   }
}

