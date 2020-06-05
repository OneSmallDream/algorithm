package concurrency;

import com.sun.org.apache.xpath.internal.operations.Bool;

public class InterrupTest implements Runnable {
    // interrupt() 方法并不能立即中断线程，该方法仅仅告诉线程外部已经有中断请求，至于是否中断还取决于线程自己
    public void run() {
        try{
            while (true) {
                Boolean a = Thread.currentThread().isInterrupted();
                System.out.println("in run() - about to sleep for 20 seconds-------");
                Thread.sleep(20000); // 阻塞方法
                System.out.println("in run() - woke up");
            }
        } catch (InterruptedException e) {
            //如果不加上这一句，那么c d将会都是false，因为在捕捉到InterruptedException异常的时候就会自动的中断标志置为了false
            Thread.currentThread().interrupt();
//            Boolean c = Thread.interrupted();
//            Boolean d = Thread.interrupted();
//            System.out.println("c="+c);
//            System.out.println("d="+d);
        }

    }

    public static void main(String[] args) {
        InterrupTest si = new InterrupTest();
        Thread t = new Thread(si);

        t.start();
        // 主线程休眠2秒, 从而确保刚才启动的线程有机会执行一段时间
        try {
            Thread.sleep(2000);
        }catch(InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println("in main() - interrupting other thread");
        // 中断线程t
        t.interrupt();
        System.out.println("in main() - leaving");
    }
}
