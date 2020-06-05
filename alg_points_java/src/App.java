import header.TrieNode;
import header.TrieNodeV2;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class App {
    public static void main(String args[]) {

        List<Integer> nums = new ArrayList<Integer>();
        nums.add(20);
        foo(nums);
        for (int i = 0; i < nums.size(); i++) {
            System.out.println(nums.get(i));
        }
    }

    public static void foo(List nums) {
        nums.add(10);
    }

}
