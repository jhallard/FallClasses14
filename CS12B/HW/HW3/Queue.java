
import java.util.Iterator;
import java.util.NoSuchElementException;

class Queue <Item> implements Iterable <Item> {

   private class Node {
      Item item;
      Node next;
   }
   private Node head = null;
   private Node tail = null;

   public boolean isempty() {
      return (head == null);
   }

   public void insert(Item newitem) {
      Node newnode = new Node();
      newnode.item = newitem;
      newnode.next = null;

      if(tail == null) {
         tail = newnode;

         if(head == null)
            head = newnode;

         return;
      }

      tail.next = newnode;
      tail = newnode;
   }

   public Iterator <Item> iterator() {
      return new Itor ();
   }

   class Itor implements Iterator <Item> {
      Node current = head;
      public boolean hasNext() {
         return current != null;
      }
      public Item next() {
         if (! hasNext ()) throw new NoSuchElementException();
         Item result = current.item;
         current = current.next;
         return result;
      }
      public void remove() {
      }
   }

}
