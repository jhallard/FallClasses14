// dllistTest.java
// Unit tests for dllist

import org.junit.*;
import static org.junit.Assert.assertEquals;

public class dllistTest {

    @Test
    public void startsEmptyTest() {
        dllist lst = new dllist();
        assertEquals(true, lst.isEmpty());
    }

    @Test
    public void addFive() {
        dllist lst = new dllist();
        lst.insert("1", dllist.position.FIRST);
        lst.insert("2", dllist.position.FIRST);
        lst.insert("3", dllist.position.FIRST);
        lst.insert("4", dllist.position.FIRST);
        lst.insert("5", dllist.position.FIRST);
        assertEquals(5, lst.getMembers());
    }

    @Test
    public void checkEmpty() {
        dllist lst = new dllist();
        lst.insert("1", dllist.position.FIRST);
        assertEquals(false, lst.isEmpty());
    }

    @Test //#10 from handout
    public void listEndInsert() {
        dllist lst = new dllist();
        lst.insert("1", dllist.position.LAST);
        lst.insert("2", dllist.position.LAST);

        assertEquals("2", lst.getItem());
    }

    @Test //#10 from handout
    public void listFrontInsert() {
        dllist lst = new dllist();
        lst.insert("1", dllist.position.FIRST);
        lst.insert("2", dllist.position.FIRST);
        lst.insert("abc", dllist.position.FIRST);

        assertEquals("abc", lst.getItem());
    }

    @Test // #14 from handout
    public void check2ndPosition() {
        dllist lst = new dllist();
        lst.insert("1", dllist.position.FIRST);
        lst.insert("2", dllist.position.FIRST);
        lst.insert("3", dllist.position.FIRST);
        lst.insert("4", dllist.position.FIRST);
        lst.insert("5", dllist.position.FIRST);
        lst.setPosition(dllist.position.FIRST);
        lst.setPosition(dllist.position.FOLLOWING);
        assertEquals(true, lst.getItem().equals("4"));
    }

    @Test // #14 from handout
    public void checkLastPosition() {
        dllist lst = new dllist();
        lst.insert("1", dllist.position.FIRST);
        lst.insert("2", dllist.position.FIRST);
        lst.insert("3", dllist.position.FIRST);
        lst.insert("4", dllist.position.FIRST);
        lst.insert("5", dllist.position.FIRST);
        lst.setPosition(dllist.position.LAST);
        assertEquals(true, lst.getItem().equals("1"));
    }

    // Step 16 Test #1
    @Test
    public void checkPosition2() {
        dllist lst = new dllist();
        lst.insert("A", dllist.position.LAST);
        lst.insert("B", dllist.position.LAST);
        lst.insert("C", dllist.position.LAST);
        lst.insert("D", dllist.position.PREVIOUS);
        lst.setPosition(dllist.position.LAST);
        assertEquals(true, lst.getItem().equals("C"));
    }

    // Step 16 Test #2
    @Test
    public void check5() {
        dllist lst = new dllist();
        lst.insert("A", dllist.position.FIRST);
        lst.insert("B", dllist.position.FIRST);
        lst.insert("C", dllist.position.FIRST);
        lst.insert("D", dllist.position.FOLLOWING);
        lst.setPosition(dllist.position.FIRST);
        assertEquals(true, lst.getItem().equals("C"));
    }

        // Step 18 Test #1
    @Test
    public void traverse() {
        dllist lst = new dllist();
        lst.insert("A", dllist.position.LAST);
        lst.insert("B", dllist.position.LAST);
        lst.insert("C", dllist.position.LAST);
        lst.insert("D", dllist.position.LAST);

        lst.setPosition(dllist.position.FIRST);
        String temp = lst.getItem();

        lst.setPosition(dllist.position.FOLLOWING);
        temp += lst.getItem();

        lst.setPosition(dllist.position.FOLLOWING);
        temp += lst.getItem();

        lst.setPosition(dllist.position.FOLLOWING);
        temp += lst.getItem();

        assertEquals(true, temp.equals("ABCD"));
    }

         // Step 20 Test #1
    @Test
    public void traverse2() {
        boolean hold = false;
        dllist lst = new dllist();
        lst.insert("A", dllist.position.LAST);
        lst.insert("B", dllist.position.LAST);
        lst.insert("C", dllist.position.LAST);
        lst.insert("D", dllist.position.LAST);

        lst.setPosition(dllist.position.FIRST);
        int temp = lst.getPosition();
        hold = (temp == 0);


        lst.setPosition(dllist.position.FOLLOWING);
        temp = lst.getPosition();
        hold = (temp == 1);

        lst.setPosition(dllist.position.FOLLOWING);
        temp = lst.getPosition();
        hold = (temp == 2);

        lst.setPosition(dllist.position.FOLLOWING);
        temp = lst.getPosition();
        hold = (temp == 3);

        assertEquals(true, hold);
    }


             // Step 20 Test #1
    @Test
    public void deleteTest() {
        boolean hold = false;
        dllist lst = new dllist();
        lst.insert("A", dllist.position.LAST);
        lst.insert("B", dllist.position.LAST);
        lst.insert("C", dllist.position.LAST);
        lst.insert("D", dllist.position.LAST);

        lst.setPosition(dllist.position.FIRST);
        
        lst.delete();
        lst.delete();
        lst.delete();

        assertEquals("D", lst.getItem());
    }


}
