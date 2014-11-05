// dllist.java
// Template code for doubly-linked list of strings.
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
         temp.next = first;
         first = temp;
         currentPosition = 0;
         break;

         case LAST:
         temp.prev = last;
         last = temp;
         currentPosition = members-1;
         break;

         case PREVIOUS:
         if(currentPosition == 0)
            throw new IllegalArgumentException();

         temp.prev = current.prev;
         current.prev.next = temp;
         temp.next = current;
         current.prev = temp;
         break;

         case FOLLOWING:
         if(currentPosition == members-1)
            throw new IllegalArgumentException();

         current.next.prev = temp;
         temp.prev = current;
         temp.next = current.next;
         current.next = temp;
         currentPosition++;
         break;
      }

      members++;
   }


   public int getMembers(){
      return members;
   }
}

