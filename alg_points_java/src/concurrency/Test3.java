package concurrency;

import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Future;
import java.util.concurrent.FutureTask;

public class Test3 {
    public static void main(String[] args) {
        FutureTask<Integer> task = new FutureTask<>(new Callable<Integer>(){
            @Override
            public Integer call() throws Exception {
                System.out.println("running...");
                Thread.sleep(1000);
                return 100;
            }
        });

        Thread t1 = new Thread(task, "t1");
        t1.start();

        try {
            System.out.println(task.get());
        } catch (InterruptedException e) {
            Thread.interrupted();
        } catch (ExecutionException e) {
            e.printStackTrace();
        }

    }
}
