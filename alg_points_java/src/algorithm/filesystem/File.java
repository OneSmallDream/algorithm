package algorithm.filesystem;

public class File extends Entry {

    private String content;
    private int size;

    public File(String n, Directory p, int size) {
        super(n, p);
        this.size = size;
    }


    public int size() {return size;}

    public String getContent() {return content; }
    public void setContent(String s) {this.content = s; }

}
