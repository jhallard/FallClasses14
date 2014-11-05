// edfile.java
// Template for a line-oriented text editor inspired by ed.

import java.util.Scanner;
import static java.lang.System.*;
import java.io.BufferedReader;
import java.io.FileReader;

class edfile{

   // member variables
   public static boolean want_echo = false;
   public static String filename;
   private static dllist lines;
   public static void main (String[] args) {

      if(!validateInput(args))
         return;

      // Create new doubly-linked list
       try{
        lines = populateList();
       }catch(Exception ex){
        ex.printStackTrace();
      }

      Scanner stdin = new Scanner (in);
      for (;;) {

         // if eof, break from inf loop
         if (!stdin.hasNextLine()) break;

         // get next line of input from user
         String inputline = stdin.nextLine();

         // echo the line if user requested
         if (want_echo) out.printf("%s%n", inputline);

         // ?? regex of some sort
         if (inputline.matches("^\\s*$")) continue;

         // Get the command, the first input char
         char command = inputline.charAt(0);
         switch (command) {

            // Ignored Comment by User
            case '#':  break;

            // Set current line to last line
            case '$':
              auxlib.STUB ("Call $ command function.");
              lines.setPosition(dllist.position.LAST);
              try{
                 System.out.println(lines.getItem());
              }catch(Exception ex){
                 ex.printStackTrace();
              }
            break;

            // Display all lines in the current list
            case '*': 
              auxlib.STUB ("Call * command function.");
              lines.setPosition(dllist.position.FIRST);
              for(int i = 0; i < lines.getMembers(); i++){
                 try{
                   System.out.println(lines.getItem()+"\n");
                 }catch(Exception ex){
                   ex.printStackTrace();
                 }
              }
              lines.setPosition(dllist.position.LAST);
            break;

            // Display current line
            case '.':
              try{
                 System.out.println(lines.getItem());
              }catch(Exception ex){
                 ex.printStackTrace();
              }
              auxlib.STUB ("Call . command function.");
            break;


            // set current line to first and print first line
            case '0':
              auxlib.STUB ("Call 0 command function."); 
              lines.setPosition(dllist.position.FIRST);
              try{
                 System.out.println(lines.getItem());
              }catch(Exception ex){
                 ex.printStackTrace();
              }
            break;

            // Go to previous line and display it
            case '<':
            auxlib.STUB ("Call < command function.");
              lines.setPosition(dllist.position.PREVIOUS);
              try{
                 System.out.println(lines.getItem());
              }catch(Exception ex){
                 ex.printStackTrace();
              }
            break;

            // Go to next line and display it
            case '>':
            auxlib.STUB ("Call > command function.");
             lines.setPosition(dllist.position.FOLLOWING);
              try{
                 System.out.println(lines.getItem());
              }catch(Exception ex){
                 ex.printStackTrace();
              }
            break;


            case 'a': auxlib.STUB ("Call a command function."); break;
            case 'd': auxlib.STUB ("Call d command function."); break;
            case 'i': auxlib.STUB ("Call i command function."); break;
            case 'r': auxlib.STUB ("Call r command function."); break;
            case 'w': auxlib.STUB ("Call w command function."); break;
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
      newlist.insert(line, dllist.position.FOLLOWING);
      }
 
      br.close();
      return newlist;
   }


}

