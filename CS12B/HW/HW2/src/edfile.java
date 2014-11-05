// File    - edfile.java
// Author  - John H Allard Jr. (template provided by Prof. Whitehead)
// Purpose - This file defines the edfile program, a simple command line text file editor. This program represents the file as a 
// sequence of nodes in a doubly linked list, with each line in the file representing a single node in the list. 

import java.util.Scanner;
import java.util.NoSuchElementException;
import static java.lang.System.*;
import java.io.BufferedReader;
import java.io.FileReader;

class edfile{

   // member variables
   public static boolean want_echo = false;
   public static String filename;
   private static dllist lines;
   public static void main (String[] args) {

      // validate the command-line input
      if(!validateInput(args))
         return;

      // Create new doubly-linked list
      try{ lines = populateList(); }
      catch(Exception ex){ ex.printStackTrace(); }

      lines.setPosition(dllist.position.LAST);

      Scanner stdin = new Scanner (in);
      for (;;) {

  
         if (!stdin.hasNextLine()) break;                 // if eof, break from inf loop

         String inputline = stdin.nextLine();             // get next line of input from user
         if (want_echo) out.printf("%s%n", inputline);    // echo the line if user requested

         if (inputline.matches("^\\s*$")) continue;       // ?? regex of some sort

         char command = inputline.charAt(0);              // Get the command, the first input char


         switch (command) {

            // Ignored Comment by User
            case '#':  break;


            // Set current line to last line in the list
            case '$':
              lines.setPosition(dllist.position.LAST);
              try{
                 System.out.println(lines.getItem());
              }catch(Exception ex){
                 ex.printStackTrace();
              }
            break;


            // Display all lines in the current list
            case '*': 
              lines.setPosition(dllist.position.FIRST);
              for(int i = 0; i < lines.getMembers(); i++){
                 try{
                   System.out.println(lines.getItem()+"\n");
                 }catch(Exception ex){
                   ex.printStackTrace();
                 }
                lines.setPosition(dllist.position.FOLLOWING);
              }
              lines.setPosition(dllist.position.LAST);
            break;


            // Display the current line
            case '.':
              try{
                 System.out.println(lines.getItem());
              }catch(Exception ex){
                 ex.printStackTrace();
              }
             
            break;


            // Set current line to first and print first line
            case '0':
              lines.setPosition(dllist.position.FIRST);
              try{
                 System.out.println(lines.getItem());
              }catch(Exception ex){
                 ex.printStackTrace();
              }
            break;


            // Go to previous line and display it
            case '<':
              lines.setPosition(dllist.position.PREVIOUS);
              try{
                 System.out.println(lines.getItem());
              }catch(Exception ex){
                 ex.printStackTrace();
              }
            break;


            // Go to next line and display it
            case '>':
             lines.setPosition(dllist.position.FOLLOWING);
              try{
                 System.out.println(lines.getItem());
              }catch(Exception ex){
                 ex.printStackTrace();
              }
            break;

            // Insert the string following 'a' into the next line of the file.
            case 'a': 
              String temp = inputline.substring(1);
              try {
              lines.insert(temp, dllist.position.FOLLOWING);
              System.out.println(lines.getItem());
              }catch(IllegalArgumentException ex){
                ex.printStackTrace();
              }
            break;

            // Delete the current line in the file.
            case 'd': 
              try {
              lines.delete();
              }catch( NoSuchElementException ex){
                ex.printStackTrace();
              }
            break;

            case 'i': 
              String temp1 = inputline.substring(1);
              try {
              lines.insert(temp1, dllist.position.PREVIOUS);
              System.out.println(lines.getItem());
              }catch(IllegalArgumentException ex){
                ex.printStackTrace();
              }
            break;

            case 'r': 
            try{ 
              if(!appendList(inputline.substring(1)))
                System.out.println("File not found!\n");
            }catch(Exception ex){
              ex.printStackTrace();
            }
             break;
            default : auxlib.STUB ("Print invalid command."); break;
         }
      }
      auxlib.STUB ("(eof)");
   }




   // Validates the command line input from the user
   private static boolean validateInput(String[] args){
       // Make sure input format is valid
      if(args.length == 0){
         System.out.println("Usage edfile [-e] filename");
         return false;
      }

      //Check if user wants to echo lines
      if(args.length == 2){
         want_echo = args[0].equals("-e");
         filename = args[1];
      }
      else{
        want_echo = false;
         filename = args[0];
      }
      return true;
   }




   // This function populates the doubly linked list with the lines from the file entered in the command line 
   // by the user.
   private static dllist populateList() throws Exception{
      dllist newlist = new dllist();
      // Construct BufferedReader from FileReader
      BufferedReader br = new BufferedReader(new FileReader(filename));
 
      String line = null;
      while ((line = br.readLine()) != null) {
      newlist.insert(line, dllist.position.LAST);
      }
 
      br.close();
      return newlist;
   }

   // This function appends the contents of a new file onto the current file.
   private static boolean appendList(String fn) throws Exception {

      BufferedReader br;
      // Construct BufferedReader from FileReader
      try{
        br = new BufferedReader(new FileReader(fn));
      } catch(Exception ex){
        return false;
      }
 
      String line = null;
      int x = 0;
      while ((line = br.readLine()) != null) {
      lines.insert(line, dllist.position.LAST);
      x++;
      }
 
      br.close();

      System.out.println(x+" Lines Added To File \n");
      lines.setPosition(dllist.position.LAST);
      return true;
   }


}

