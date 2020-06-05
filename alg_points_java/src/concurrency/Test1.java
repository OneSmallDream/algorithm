package concurrency;

/**
 * 第一个创建线程的方法
 */
public class Test1 {

    public static void main(String[] args) {

        Thread t = new Thread() {

            @Override
            public void run() {
                System.out.println("son thread is running.");
            }
        };

        t.setName("son");
        t.start();

        System.out.println("father thread is running.");

    }
}
