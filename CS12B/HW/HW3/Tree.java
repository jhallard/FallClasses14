import static java.lang.System.*;

class Tree {

    private class Node {
        String key;
        Queue<Integer> value;
        Node left;
        Node right;
    }

    private Node root;

    private void debugHelper(Node tree, int depth) {
        String temp = "";
        for(int i = 0; i < depth; i++)
            temp += "  ";

        if(tree == null) {
            return;
        }

        debugHelper(tree.left, depth+1);

        System.out.println(temp+depth+tree.key+"\n");

        debugHelper(tree.right, depth+1);

    }

    private void outputHelper(Node tree) {
        String values = "";
 
        if(tree == null)
            return;

        outputHelper(tree.left);


        for(Integer i : tree.value) {
            values += String.valueOf(i) + " ";
        }
        out.printf("%s : %s \n", tree.key, values);

        outputHelper(tree.right);
    }

    private void insertHelper(Node t, String key, Integer linenum) {

        if(t == null) {
            t = new Node();
            t.value = new Queue();
            t.key = key;
            t.value.insert(linenum);
            t.left = null;
            t.right = null;
            if(root == null)
                root = t;
            // out.printf("new node " + t.key + "\n");
            return;
        }
        else if(t.key.compareTo(key) < 0) {
            // Node tmep = tree.right;
            insertHelper(t.right, key, linenum);
            return;
        }
        else if(t.key.compareTo(key) > 0) {
            insertHelper(t.left, key, linenum);
            return;
        }
        else {
            t.value.insert(linenum);
            return;
        }

    }

    public void insert(String key, Integer linenum) {
         if(root == null) {
            root = new Node();
            root.value = new Queue();
            root.key = key;
            root.value.insert(linenum);
            return;
         }

        Node temp = root;

        while(temp != null) {
            if(temp.key.compareTo(key) > 0) {
                out.printf("left\n");
                if(temp.left == null) {
                    temp.left = new Node();
                    temp.left.value = new Queue();
                    temp.left.key = key;
                    temp.left.value.insert(linenum);
                    return;
                }
                temp = temp.left;
            }
            else if(temp.key.compareTo(key) < 0) {
                out.printf("right\n");
                if(temp.right == null) {
                    temp.right = new Node();
                    temp.right.value = new Queue();
                    temp.right.key = key;
                    temp.right.value.insert(linenum);
                    return;
                }
                else 
                    temp = temp.right;
            }
            else if(temp.key.compareTo(key) == 0) {
                temp.value.insert(linenum);
                return;
            }
        }

    }

    public void debug() {
        // Show debug output of tree
        debugHelper(root, 0);
    }

    public void output() {
        // Show sorted words with lines where each word appears
        outputHelper(root);
    }

}
