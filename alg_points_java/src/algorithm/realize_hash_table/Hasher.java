package algorithm.realize_hash_table;

import sun.awt.image.ImageWatched;

import java.util.ArrayList;

/*
设计散列表
 */
public class Hasher<K, V> {

    /*
    链表类, 静态类一般都是静态内部类
     */
    private static class LinkedListNode<K, V> {
        public LinkedListNode<K, V> next;
        public LinkedListNode<K, V> prev;
        public K key;
        public V value;
        public  LinkedListNode(K k, V v) {
            key = k;
            value = v;
        }
    }

    private ArrayList<LinkedListNode<K, V>> arr;

    public Hasher(int capacity) {
        arr = new ArrayList<LinkedListNode<K, V>>();
        arr.ensureCapacity(capacity);
        for (int i = 0; i < capacity; i++) {
            arr.add(null);
        }
    }

    public int getIndexForKey(K key) {
        return Math.abs(key.hashCode() % arr.size());
    }
    /* 获取键对应的链表节点 */
    private LinkedListNode<K, V> getNodeForKey(K key) {
        int index = getIndexForKey(key);
        LinkedListNode<K, V> current = arr.get(index);
        while (current.key != null) {
            if (current.key == key){
                return current;
            }
            current = current.next;
        }
        return null;
    }

    /* 向散列表中插入键和值 */
    public void put(K key, V value) {
        LinkedListNode<K, V> node = getNodeForKey(key);
        if (node != null) {
            V oldValue = node.value;
            node.value = value;
        }

        node = new LinkedListNode<K, V>(key, value);
        int index = getIndexForKey(key);
        if (arr.get(index) != null) {
            node.next = arr.get(index);
            node.next.prev = node;
        }
        arr.set(index, node);
    }

    public V remove(K key) {
        LinkedListNode<K, V> node = getNodeForKey(key);
        if (node == null) {
            return null;
        }

        if (node.prev != null) {
            node.prev.next = node.next;
        } else {
            int index = getIndexForKey(key);
            arr.set(index, node.next);
        }

        if (node.next != null) {
            node.next.prev = node.prev;
        }
        return node.value;
    }

    public V get(K key) {
        if (key == null) return null;
        LinkedListNode<K, V> node = getNodeForKey(key);
        return node == null ? null : node.value;
    }
}
