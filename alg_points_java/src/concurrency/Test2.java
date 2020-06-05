package concurrency;

/**
 * 第二个
 */
public class Test2 {

    public static void main(String[] args) {
        Runnable r = new Runnable() {
            @Override
            public void run() {
                System.out.println("son thread is running");
            }
        };

        // Thread t = new Thread(r, "father");
        Thread t = new Thread(()->{System.out.println("son thread is running.");}, "father");
        t.start();
    }
}
