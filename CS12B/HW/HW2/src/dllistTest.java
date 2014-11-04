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
        lst.insert("true", dllist.position.FIRST);
        assertEquals(true, lst.isEmpty());
    }

}
