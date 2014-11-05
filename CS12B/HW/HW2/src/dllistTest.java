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
    public void check2() {
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

    @Test
    public void check3() {
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
    public void check4() {
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

}
