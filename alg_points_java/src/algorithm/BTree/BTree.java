package algorithm.BTree;

import org.junit.platform.commons.logging.LoggerFactory;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

/**
 * B 树实现
 * @param <K> - 键类型
 * @param <V> - 值类型
 */
public class BTree<K, V> {
    private static final int DEFAULT_T = 2;
    /**
     * B树的根节点
     */
    private BTreeNode<K, V> root;

    private int t = DEFAULT_T;

    private int minKeySize = t-1;

    private int maxKeySize = 2*t-1;

    private  Comparator<K> kComparator;

    public BTree() {
        this.root = new BTreeNode<K, V>();
        root.setLeaf(true);
    }

    public BTree(int t) {
        this();
        this.t = t;
        minKeySize = t-1;
        maxKeySize = 2*t-1;
    }

    /**
     * 以给定的键值比较函数对象构造一颗B树
     */
    public BTree(Comparator<K> kComparator) {
        root = new BTreeNode<K, V>(kComparator);
        root.setLeaf(true);
        this.kComparator = kComparator;
    }

    public BTree(Comparator<K> kComparator, int t) {
        this(kComparator);
        this.t = t;
        minKeySize = t - 1;
        maxKeySize = 2*t-1;
    }

    int compare(K key1, K key2) {
        return this.kComparator==null ? ((Comparable<K>) key1).compareTo(key2) : kComparator.compare(key1, key2);
    }

    public V search(K key) {
        return search(root, key);
    }


    /**
     * 该递归过程 有疑问 todo 检查逻辑是否正确
     * @param node
     * @param key
     * @return
     */
    private V search(BTreeNode<K, V> node, K key) {
        V searchRes = null;
        SearchResult<V> result = node.searchKey(key);
        if (result.isExist()) {
            return result.getValue();
        }else {
            if (node.isLeaf()) {
                return null;
            }else {
                searchRes = search(node.childAt(result.getIndex()), key);
            }
        }
        return searchRes;
    }

    /**
     * 分裂一个满子节点
     * 首先需要保证你给定的子节点是满节点
     * @param parentNode 父节点
     * @param childNode 满子节点
     * @param index 满子节点在父节点中的索引
     */

    private void splitNode(BTreeNode<K, V> parentNode, BTreeNode<K, V> childNode, int index) {
        assert childNode.size() == maxKeySize;

        BTreeNode<K, V> siblingNode = new BTreeNode<K, V>(kComparator);
        siblingNode.setLeaf(childNode.isLeaf()); // 如果当前子节点是叶子节点，那么也将该节点设置为叶子节点

        // 将满子节点中索引为[t, 2t-2]的(t-1)个项插入新的节点中
        for (int i = 0; i < minKeySize; ++i) {
            siblingNode.addEntry(childNode.entryAt(t+i));
        }
        // 提取满子节点中的中间项，其索引为(t-1)
        Entry<K, V> entry = childNode.entryAt(t-1);
        // 删除满子节点中索引为[t-1, 2t-2]的t个项
        for (int i = maxKeySize-1; i >= t-1; --i) {
            childNode.removeEntry(i);
        }

    }


}
