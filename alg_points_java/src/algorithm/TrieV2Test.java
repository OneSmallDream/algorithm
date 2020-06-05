package algorithm;

import org.junit.jupiter.api.Test;

import java.util.List;

import static org.junit.jupiter.api.Assertions.*;

class TrieV2Test {

    private TrieV2 tree;

    public TrieV2Test() {
        tree = new TrieV2();
    }

    @Test
    void insert() {

        String word1 = "窦文韬";
        String word2 = "窦文好强";
        String word3 = "窦文大淘";
        String word4 = "窦文牛逼";
        String word5 = "窦文牛逼";
        tree.insert(word1);
        tree.insert(word2);
        tree.insert(word3);
        tree.insert(word4);
        tree.insert(word5);
    }

    @Test
    void startsWith() {
        insert();
        Boolean isStartsWith = tree.startsWith("窦文");
        System.out.println(isStartsWith);
    }

    @Test
    void getData() {
        insert();
        String preword = "窦文";
        List<String> res = this.tree.getData(preword);
        for (String str: res) {
            System.out.println(str);
        }

    }

    @Test
    void dfs() {
    }
}