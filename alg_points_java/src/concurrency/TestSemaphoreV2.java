package concurrency;

import java.util.concurrent.Semaphore;

public class TestSemaphoreV2 {

    final Semaphore s1 = new Semaphore(1);
    Thread t1 = new Thread() {
        public void run() {
            try {
                s1.acquire();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

        }
    };

}
