// edfile.java
// Template for a line-oriented text editor inspired by ed.

import java.util.Scanner;
import static java.lang.System.*;

class edfile{

   // member variables
   public static boolean want_echo = false;
   public static String filename;

   public static void main (String[] args) {

      if(!validateInput(args))
         return;

      // Create new doubly-linked list
      dllist lines = new dllist();
      
      auxlib.STUB ("Load file from args filename, if any.");
      Scanner stdin = new Scanner (in);
      for (;;) {
         if (! stdin.hasNextLine()) break;
         String inputline = stdin.nextLine();
         if (want_echo) out.printf ("%s%n", inputline);
         if (inputline.matches ("^\\s*$")) continue;
         char command = inputline.charAt(0);
         switch (command) {

            // Ignored Comment by User
            case '#': break;

            // Set current line to last line
            case '$':
              lines.setPosition(dllist.position.LAST);
              try{
                 System.out.println(lines.getItem());
              }catch(Exception ex){
                 ex.printStackTrace();
              }
            break;

            case '*': auxlib.STUB ("Call * command function."); break;
            case '.': auxlib.STUB ("Call . command function."); break;
            case '0': auxlib.STUB ("Call 0 command function."); break;
            case '<': auxlib.STUB ("Call < command function."); break;
            case '>': auxlib.STUB ("Call > command function."); break;
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

}

