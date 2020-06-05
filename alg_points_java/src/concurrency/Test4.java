package concurrency;

public class Test4 {

    public static void main(String[] args) {
        Thread t1 = new Thread("t1") {
            @Override
            public void run() {
                System.out.println("running...");
            }
        };
        // 对比start和run, 直接调用run属于主线程
        t1.start();
//        t1.run();
    }
}
