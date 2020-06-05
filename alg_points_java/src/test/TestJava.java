package test;

import apple.laf.JRSUIUtils;

import java.util.ArrayList;
import java.util.List;

public class TestJava {

    int findResult = -1;

    public static class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;
        public TreeNode(int v) {
            this.val = v;
            this.left = null;
            this.right = null;
        }
        public TreeNode(int v, TreeNode left, TreeNode right) {
            this.val = v;
            this.left = left;
            this.right = right;
        }
    }

    public static TreeNode constructTree() {

        TreeNode root = new TreeNode(10);
        root.left = new TreeNode(5);
        root.right = new TreeNode(15);
        TreeNode left = root.left;
        left.left = new TreeNode(3);
        left.right = new TreeNode(7);
        TreeNode right = root.right;
        right.left = new TreeNode(13);
        right.right = new TreeNode(18);
        return root;
    }

    public static int findKey(TreeNode root, int key) {

        int result = -1;

        if (root.val == key) {
            return key;
        }else {
            if (key > root.val) {
                result = findKey(root.right, key);
            }else {
                result = findKey(root.left, key);
            }
        }
        return result;
    }

    public static void main(String args[]) {

        int result = -1;
        TreeNode root = constructTree();
        int res = findKey(root, 13);
        System.out.println(res);
    }
}
