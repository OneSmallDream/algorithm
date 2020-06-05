package concurrency;

import java.util.concurrent.Delayed;
import java.util.concurrent.TimeUnit;

/**
 * DelayQueue是一个BlockingQueue队列，它本质就是封装了一个PriorityQueue(内部使用完全二叉堆)来实现队列元素排序。
 * 我们在向DelayQueue队列中添加元素时，会给元素一个Delay时间作为排序条件，队列中最小的元素会优先放在队首。队列中的元素只有
 * 到了Delay时间才允许从队列中取出。队列中可以放基本数据类型或者自定义实体类，在存放基本数据类型时，优先队列中元素默认升序排列，
 * 自定义实体类就需要我们根据类属性值比较计算了
 */
public class DelayQueue {

    // 要实现DelayQueue延时队列，队中元素要implements Delayed接口，这个接口里只有一个getDelay方法
    public class Order implements Delayed {
        /**
         * 延迟时间
         */
        @JsonFormat(locale = "zh", timezone = "GMT+8", pattern = "yyyy-MM-dd HH:mm:ss")
        private long time;
        String name;

        public Order(String name, long time, TimeUnit unit) {
            this.name = name;
            this.time = System.currentTimeMillis() + (time > 0 ? unit.toMillis(time) : 0);
        }

        @Override
        public long getDelay(TimeUnit unit) {
            return this.time - System.currentTimeMillis();
        }

        @Override
        public int compareTo(Delayed o) {
            Order order = (Order) o;
            long diff = this.time - order.time;
            if (diff <= 0) {
                return -1;
            }else {
                return 1;
            }
        }
    }
    // DelayQueue的put方法是线程安全的，因为put方法内部使用了ReentrantLock锁进行线程同步。DelayQueue还提供了
    // 两种出队方法poll()和take()，poll()非阻塞获取，没有到期的元素直接返回NULL; take()为阻塞方式获取，没有到期的元素线程
    // 将会等待
    public class DelayQueueDemo {
        public static void main(String[] args) throws InterruptedException {

        }
    }
}
