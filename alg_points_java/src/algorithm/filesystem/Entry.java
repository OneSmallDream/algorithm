package algorithm.filesystem;

// 抽象类，不能被实例化; 抽象方法必须被重写
public abstract class Entry {
    // 父级目录, 创建时间，最近更新时间，最近打开时间，名称
    protected Directory parent;
    protected long created;
    protected long lastUpdated;
    protected long lastAccessed;
    protected String name;

    public Entry(String n, Directory p) {
        name = n;
        parent = p;
        created = System.currentTimeMillis();
        lastUpdated = System.currentTimeMillis();
        lastAccessed = System.currentTimeMillis();
    }

    public boolean delete() {
        if (parent == null) return false;
        return parent.deleteEntry(this);
    }

    public abstract int size(); // entry大小

    public String getFullPath() {
        if (parent == null) return name;
        else return parent.getFullPath() + "/" + name;
    }

    /* getter and setter */

}
