package header;

import java.util.HashMap;
import java.util.Map;

//兼容中英文和其他字符串, 但是这样容易造成对象内存过大
public class TrieNodeV2 {
    // 同TrieNode, 这里String代表当前节点的字符串, TrieNodeV2代表当前节点
    public Map<String, TrieNodeV2> nexts;
    public int path;
    public int end;
    public TrieNodeV2() {
        this.nexts = new HashMap<String, TrieNodeV2>();
        this.path = 0;
        this.end = 0;
    }
}
