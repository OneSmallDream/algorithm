package com.cg_bytedance;

// 第二章中，要编写正确的并发程序，关键问题在于：在访问共享的可变状态时，需要进行正确的管理
// 一种常见的误解，认为关键字Synchronized只能用于实现原子性或者确定"临界区"。同步还有另一个重要的方面：内存可见性。我们不仅希望
// 防止某个线程正在使用对象状态而另一个线程在同时修改该状态，而且希望确保当一个线程修改了对象状态后，其他线程能够看到发生的状态变化。
// 如果没有同步，那么这种情况就无法实现。
public class ThirdClass {
}

// 下述代码中，主线程和读线程都将访问共享变量ready 和 number。
// 由于没有同步机制，无法保证主线程写入的ready值和number值对于读线程是可见的。
// NoVisibility可能会持续下去，因为读线程可能永远看不到ready的值。
// 另一种现象是，NoVisibility可能会输出0，因为读线程可能看到了写入ready的值，但却没有看到写入number的值，这种现象被称为"重排序"

// 在没有同步的情况下，编译器、处理器以及运行时等都可能对操作的执行顺序进行一些意想不到的调整。在缺乏足够同步的多线程程序中，要想对
// 内存操作的执行顺序进行判断，几乎无法得出正确的结论。
public class NoVisibility {
    private static boolean ready;
    private static int number;

    private static class ReaderThread extends Thread {
        public void run() {
            while (!ready) {
                Thread.yield();
            }
            System.out.println(number);
        }
    }

    public static void main(String[] args) {
        new ReaderThread().start();
        number = 42;
        ready = true;
    }
}

// NoVisibility 展示了一种错误情况: 失效数据
@NotThreadSafe
public class MutableInteger {
    private int value;
    public int get() {return value;}
    public void set(int value) {this.value=value;}
}
// 例如上述程序，因为get 和 set 方法都是在没有同步的情况下使用，如果某个线程调用了set，那么另一个正在调用get的线程可能会看到更新
// 后的value, 也可能看不到。

// 下述程序对上述进行了修改。进队set方法进行同步是不够的，调用get的线程仍然会看见失效值
@ThreadSafe
public class SynchronizedInteger {
    @GuardedBy("this") private int value;

    public synchronized int get(){return value; }
    public synchronized void set(int value) {this.value = value; }
}

// 当线程在没有同步的情况下读取变量时，可能会得到一个失效值，但至少这个值是由之前某个线程设置的值，而不是一个随机的值。
// 这种安全性保证也被成为最低安全性。
// 最低安全性使用于绝大多数变量，但是存在一个例外: 非volatile类型的64位数值变量(double 和 long)
// java内存模型要求，变量的写入和读取操作都必须是原子操作，但对于非volatile类型的long 和 double变量，JVM允许将64位的读操作或写操作
// 分解为两个32位的操作，当读取一个非volatile类型的long变量时，如果对该变量的读操作和写操作在不同的线程中执行，那么很可能会读取到你某个
// 值的高32位和另一个值的低32位，因此，即使不考虑失效数据问题，在多线程程序中使用共享且可变的long 和 double 等类型的变量也是不安全的。
// 除非用关键字volatile来声明他们，或者用锁保护起来



// 加锁与可见性
// 内置锁 可以用于确保某个线程以一种可预测的方式来查看另一个线程的执行结果。
// 加锁的含义不仅仅局限于互斥行为，还包括内存可见性。为了确保所有线程都能看到共享变量的最新值，所有执行读操作或者写操作的线程必须在
// 同一个锁上同步。


// volatile
// java提供一种稍弱的同步机制, volatile变量，用来确保将变量的更新操作通知到其他线程。当把变量声明为volatile类型后，编译器与运行时
// 都会注意到这个变量是共享的，因此不会将该变量上的操作与其他内存操作一起重排序。volatile变量不会缓存在寄存器或者对其他处理器不可见
// 的地方，因此在读取volatile类型的变量时，总会返回最新写入的值。
// 访问volatile变量时不会执行加锁操作，因此也不会执行线程阻塞，因此volatile变量是一种比synchronized关键字更轻量级的同步机制。
// 吸入人volatile变量相当于退出同步代码块，而读取volatile变量就相当于进入同步代码块。然后，不建议过度依赖volatile变量提供的可见性。
// 以下是volatile的一种典型用法，检查某个标记以判断是否退出循环。！！！！！！！！！volatile变量通常用作某个操作完成、发生中断或者状态
// 的标志
{
    volatile boolean asleep;
            ...
            while(!asleep)
            countSomeSheep();
}
// ！！！！！当且仅当满足以下所有条件时，才应该使用volatile变量
//  1. 对变量的写入操作不依赖于变量的当前值，或者你能确保只有单个线程更新变量的值
//  2. 该变量不会与其他状态变量一起纳入不变性条件中。
//  3. 在访问变量时不需要加锁


// 发布与逸出
// "发布"一个对象的意思是指，使对象能够在当前作用域之外的代码中使用
// 当某个不应该发布的对象被发布时，这种情况被成为"逸出"

// 发布对象最简单的方法是将对象的引用保存到一个公有的静态变量中，以便任何类或者线程都能看见该对象。
public static Set<Secret> knowSecrets;
public void initialize() {
    knownSecrets = new HashSet<Secrets>();
}
// 当发布一个对象时，在该对象的非私有域中引用的所有对象同样会被发布。一般来说，如果一个已经发布的对象能够通过非私有的变量引用和方法
// 调用到达其他对象，那么这些对象也都会被发布

