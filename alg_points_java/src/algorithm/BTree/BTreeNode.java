package algorithm.BTree;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

public class BTreeNode<K, V> {
    /**
     * 节点的项，按键非降序存放
     */
    private List<Entry<K, V>> entries;
    /**
     * 内节点的子节点, 相当于C++中存的指向子节点的指针
     */
    private List<BTreeNode<K, V>> children;

    private boolean leaf;

    /**
     * 键的比较函数对象
     */
    private Comparator<K> kComparator;

    public BTreeNode() {
        entries = new ArrayList<Entry<K, V>>();
        children = new ArrayList<BTreeNode<K, V>>();
        leaf = false;
    }

    public BTreeNode(Comparator<K> kComparator) {
        this();
        this.kComparator = kComparator;
    }

    public boolean isLeaf() {
        return leaf;
    }

    public void setLeaf(boolean leaf) {
        this.leaf = leaf;
    }

    public int size() {
        return entries.size();
    }

    int compare(K key1, K key2) {
        return kComparator==null?((Comparable<K>) key1).compareTo(key2): kComparator.compare(key1, key2);
    }

    public SearchResult<V> searchKey(K key) {
        int low = 0;
        int high = entries.size()-1;
        int mid = 0;
        while (low <= high) {
            mid = low + (high - low) / 2;
            Entry<K, V> entry = entries.get(mid);
            if (compare(entry.getKey(), key) == 0) break;
            else if (compare(entry.getKey(), key) > 0) high = mid-1;
            else low = mid + 1;
        }
        boolean result = false;
        int index = 0;
        V value = null;
        if (low <= high) {
            // 查找成功
            result = true;
            index = mid; // 元素所在的位置
            value = entries.get(index).getValue();
        }else {
            // 没找到
            result = false;
            index = low; // 表示元素要插入的位置

        }

        return new SearchResult<V>(result, index, value);
    }

    public void addEntry(Entry<K, V> entry) {
        this.entries.add(entry);
    }

    public void removeEntry(int index) {
        this.entries.remove(index);
    }

    public Entry<K, V> entryAt(int index) {
        return this.entries.get(index);
    }

    /**
     * 如果节点中存在给定的键，则更新; 如果不存在，则插入
     */
    public V putEntry(Entry<K, V> entry) {
        SearchResult<V> result = searchKey(entry.getKey());
        if (result.isExist()) {
            // 更新值
            int curIndex = result.getIndex();
            this.entries.get(curIndex).setValue(entry.getValue());
            return result.getValue();
        }else {
            // 不存
            int curIndex = result.getIndex();
            this.entries.add(curIndex, entry); // ArrayList将entry插入到curIndex
            return null;
        }
    }

    public boolean insertEntry(Entry<K, V> entry) {
        SearchResult<V> result = searchKey(entry.getKey());
        if (result.isExist()) {
            // 如果存在, 返回false;
            return false;
        }else {
            this.entries.add(result.getIndex(), entry);
            return true;
        }
    }

    /**
     * 返回指定索引的子节点
     * @param index
     * @return
     */
    public BTreeNode<K, V> childAt(int index) {
        if (isLeaf()) throw new UnsupportedOperationException("Leaf node does not have children");
        return children.get(index);
    }

    /**
     * 将给定的子节点追加到该节点的末尾
     * @param child
     */
    public void addChild(BTreeNode<K, V> child) {
        this.children.add(child);
    }

    public void removeChild(int index) {
        children.remove(index);
    }

    /**
     * 将给定的子节点插入到该节点中给定索引
     */
    public void insertChild(BTreeNode<K, V> child, int index) {
        this.children.add(index, child);
    }
}
