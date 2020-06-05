package algorithm;


import header.TrieNode;

//英文版本--基础
// 这里几乎没什么用，所以不写测试代码了
public class Trie {
    private TrieNode root;
    public Trie() {
        // 初始化的时候，指向26个子节点，但是26个子节点没有初始化，均为空
        root = new TrieNode();
    }

    public void insert(String word) {
        if (word == null) {
            return ;
        }
        char[] chs = word.toCharArray();
        TrieNode node = root;
        int index = 0;
        for (int i = 0; i < chs.length; i++) {
            index = chs[i]-'a';
            if (node.map[index]==null) {
                node.map[index] = new TrieNode();
            }
            // 进入下一层节点
            node = node.map[index];
            // 即使到了end char, path也需要++(为了prefixNumber函数可以直接返回path作为返回值)
            node.path++;
        }
        // 最后执行end++
        node.end++;
    }
    public boolean search(String word) {
        if (word == null) return false;
        char[] chs = word.toCharArray();
        TrieNode node = root;
        int index = 0;
        for (int i = 0; i < chs.length; i++) {
            index = chs[i] - 'a';
            if (node.map[index] == null) {
                return false;
            }
            node = node.map[index];
        }
        // 这一步很重要，因为可能最后一个字符只是在路径中，而其没有作为end而存在的情况。
        return node.end != 0;
    }
    public void delete(String word) {
        if (!search(word)) return ;
        char[] chs = word.toCharArray();
        TrieNode node = root;
        int index = 0;
        for (int i = 0; i < chs.length; i++) {
            index = chs[i] - 'a';
            // 如果发现下一个节点（当前遍历的字符）其path为1，直接将该路径以下置位null
            if (node.map[index].path--==1){
                node.map[index] = null;
                return ;
            }
            node = node.map[index];
        }
        node.end--;
    }

    public int prefixNumber(String pre) {
        if (pre == null) return 0;
        char[] chs = pre.toCharArray();
        TrieNode node = root;
        int index = 0;
        for (int i = 0; i < chs.length; i++) {
            index = chs[i] - 'a';
            if (node.map[index] == null) {
                return 0;
            }
            node = node.map[index];
        }
        return node.path;
    }
}
