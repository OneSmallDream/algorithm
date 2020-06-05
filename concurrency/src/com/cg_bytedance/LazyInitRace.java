package com.cg_bytedance;

// 竞态条件

import java.math.BigInteger;
import java.util.concurrent.atomic.AtomicLong;

// 1， 先检查后执行
// 假设线程A和B同时调用getInstance，此时A B都判断instance为null, 那么instance 会被创建两次。
// 两次调用可能会出现不同的结果，即使在getInstance默认是返回相同实例的情况下。
public class LazyInitRace {
    private ExpensiveObject instance = null;
    public ExpensiveObject getInstance() {
        if (instance == null) instance = new ExpensiveObject();
        return instance;
    }
}


// 2. 读取 -> 修改 -> 写入
// 如下 ++count 便是例子, 先读取count值，将值加1，再将值写入count.
// 要递增一个计数器，必须知道它之前的值，并确保在执行更新的过程中没有其他线程会修改或使用这个值
public class UnsafeCountingFactorizer implements Servlet {
    private long count = 0;
    public long getCount() {return count; }
    public void service(ServletRequest req, ServletResponse resp) {
        BigInteger i = extractFromRequest(req);
        BigInteger[] factors = factor(i);
        ++count;
        encodeIntoResponse(resp, factors);
    }
}

// 要避免竞态条件问题，就必须在某个线程修改变量的时候，通过某种方式防止其他线程使用这个变量，从而确保其他
// 线程只能在修改操作完成之前或之后读取和修改状态，而不是在修改状态的过程中。

// 我们将"先检查后执行"和"读取-修改-写入"等操作统称为复合操作: 包含了一组必须以原子方式执行的操作以确保线程安全性。
// 目前先用线程安全类来修复以上问题
@ThreadSafe
public class CountingFactorizer implements Servlet {
    private final AtomicLong count = new AtomicLong(0);
    public long getCount() {
        return count.get();
    }
    public void service(ServletRequest req, ServletResponse resp) {
        BigInteger i = extractFromRequest(req);
        Biginteger[] factors = factor(i);
        count.incrementAndGet();
        encodeIntoResponse(resp, factors);
    }
}
// 当在无状态的勒种添加一个状态时，如果该状态完全由线程安全的对象来管理，那么这个类仍然是线程安全的。

// 内置锁
// 要保持状态一致性，就需要在单个原子操作中更新所有相关的状态变量
// java提供了一种内置锁机制来支持原子性: 同步代码块, 同步代码块包含两个部分: 一个作为锁的对象引用，一个作为由这个锁保护的代码块。
// 每个java对象都可以用作一个实现同步的锁，这些锁被称为内置锁(Intrinsic Lock)或者(Monitor Lock)监视器锁
// 任何一个执行同步代码块的线程，都不可能看到有其他线程正在执行由同一个锁保护的同步代码块。

@ThreadSafe
public class SynchronizedFactorizer implements Servlet {
    @GuardedBy("this") private BigInteger lastNumber;
    @GuardedBy("this") private BigInteger[] lastFactors;

    public synchronized void service(ServletRequest req, ServletResponse resp) {
        BigInteger i = extractFromRequest(req);
        if (i.equals(lastNumber)) {
            encodeIntoResponse(resp, lastFactors);
        }else {
            BigInteger[] factors = factor(i);
            lastNumber = i;
            lastFactors = factors;
            encodeIntoResponse(resp, factors);
        }
    }
}

// 重入
// 当某个线程请求一个由其他线程持有的锁的时候，发出请求的线程就会阻塞。然而由于内置锁是可重入的，因此如果某个线程试图
// 获得一个已经由它自己持有的锁，那么这个请求就会成功。"重入"一位着获取锁的粒度是"线程"而不是"调用"。重入的一种实现方法
// 为每个锁关联一个获取计数值和一个所有者线程，当计数值为0时，这个锁就被认为是没有任何线程持有，当线程请求一个未被持有的
// 锁时，JVM将记下锁的持有者，并且将获取计数值置位1，如果同一个线程再次获取这个锁，计数值将递增，而当线程退出同步代码块
// 时，计数器会相应的递减。当计数值为0时，这个锁将被释放。

public class Widget {
    public synchronized  void doSomething(){...}
}

public class LoggingWidget extends Widget {
    public synchronized void doSomething() {
        super.doSomething();
    }
}
// 上述代码中，子类改写了负类的synchronized方法，然后调用父类中的方法。此时如果没有可重入锁，那么这段代码将产生死锁
// 由于Widget 和 LoggingWidget 中doSomething方法都是synchronized方法，因此每个doSomething方法在执行前都会获取Widget上的锁
// 如果内置锁是不可重入的，那么在调用super.doSomething将无法获得Widget上的锁，因为这个锁已经被持有了。

@ThreadSafe
public class CachedFactorizer implements Servlet {
    @GuardedBy("this") private BigInteger lastNumber;
    @GuardedBy("this") private BigInteger[] lastFactors;
    @GuardedBy("this") private long hits;
    @GuardedBy("this") private long cacheHits;

    public synchronized long getHits() {return hits;}

    public synchronized double getCacheHitRatio() {
        return (double) cacheHits / (double) hits;
    }

    public void service(ServletRequest req, ServletReponse resp) {
        BigInteger i = extractFromRequest(req);
        BigInteger[] factors = null;
        synchronized (this) {
            ++hits;
            if (i.equals(lastNumber)) {
                ++cacheHits;
                factors = lastFactors.clone();
            }
        }

        if (factors == null) {
            factors = factor(i);
            synchronized (this) {
                lastNumber = i;
                lastFactors = factors.clone();
            }
        }

        encodeIntoResponse(resp, factors);
    }
}