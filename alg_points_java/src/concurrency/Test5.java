package concurrency;

public class Test5 {

    public static void main(String[] args) {
        Thread t1 = new Thread("t1") {
            @Override
            public void run() {
                System.out.println("running...");
            }
        };
        System.out.println(t1.getState());
        t1.start();
        System.out.println(t1.getState());
//        t1.run();
    }
}
