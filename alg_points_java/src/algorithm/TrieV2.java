package algorithm;

import header.TrieNodeV2;

import javax.swing.tree.TreeNode;
import java.util.ArrayList;
import java.util.List;

public class TrieV2 {
    private TrieNodeV2 root;

    public TrieV2() {
        root = new TrieNodeV2();
    }

    public void insert(String word) {
        if (word==null) return ;
        TrieNodeV2 node = root;
        for (int i = 0; i < word.length(); i++) {
            String str = ""+ word.charAt(i);
            // 根据当前字符来确定, 走到下一步
            if (node.nexts.get(str) == null) {
                node.nexts.put(str, new TrieNodeV2());
            }
            node = node.nexts.get(str);
            node.path++;
        }
        node.end++;
    }

    public boolean startsWith(String word) {
        TrieNodeV2 node = root;
        for (int i = 0; i < word.length(); i++) {
            String str = "" + word.charAt(i);
            if (node.nexts.get(str) == null) {
                return false;
            }
            node = node.nexts.get(str);
        }
        return true;
    }

    public List<String> getData(String preword) {
        List<String> list = new ArrayList<String>();
        if (!startsWith(preword)) {
            return null;
        }else {
            StringBuilder str = new StringBuilder("");
            str.append(preword);
            TrieNodeV2 node = root;

            for (int i = 0; i < str.length(); i++) {
                node = node.nexts.get(""+str.charAt(i));
            }

            dfs(node, str, list);
        }
        return list;
    }

    public void dfs(TrieNodeV2 node, StringBuilder str, List<String> list) {
        // 满足结果插入条件
        if (node.end >= 1) {
            list.add(str.toString());
            // 满足返回条件
            if (node.nexts.size() == 0) {
                return ;
            }
        }

        for (String s: node.nexts.keySet()) {
            str.append(s);
            dfs(node.nexts.get(s), str, list);
            str.delete(str.length()-1, str.length());
        }
    }

}
