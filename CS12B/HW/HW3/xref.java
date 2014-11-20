import java.io.*;
import java.util.Scanner;
import static java.lang.System.*;

class xref {

    static void processFile(String filename, boolean debug) throws IOException {
        Scanner scan = new Scanner (new File(filename));
        Tree tree = new Tree();
        for (int linenr = 1; scan.hasNextLine (); ++linenr) {
            for (String word: scan.nextLine().split ("\\W+")) {
                out.printf ("%s: %d: %s%n", filename, linenr, word);
                tree.insert(word, linenr);
            }
        }
        scan.close();
        if (debug) {
            tree.debug();
        } else {
            tree.output();
        }
    }

    public static void main(String[] args) {
        // This code does not handle -d option
        int num = args.length;
        String filename = "";
        boolean debug = false;

        if(num == 1)
            filename = args[0];
        else if(num ==2) {
            debug = true;
            filename = args[1];
        }

        try {
            processFile(filename, debug);
        }catch (IOException error) {
            auxlib.warn (error.getMessage());
        }
        auxlib.exit();
    }

}

