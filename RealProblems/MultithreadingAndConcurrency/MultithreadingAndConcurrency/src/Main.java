import java.util.*;

public class Main {
    public static void main(String[] args) {
        testMultithreading();
        testBlockingQueue();

        // Uncomment below to see deadlock situation.
        // testDeadlock();
    }

    private static void testBlockingQueue() {
        BlockingQueue queue = new BlockingQueue(1);
        for (int i=0; i<50; i++) {
            Thread producer1 = new Thread(() -> queue.write(1), "P1");
            Thread producer2 = new Thread(() -> queue.write(2), "P2");
            Thread consumer1 = new Thread(() -> queue.read(), "C1");
            Thread consumer2 = new Thread(() -> queue.read(), "C2");
            producer1.start();
            producer2.start();
            consumer1.start();
            consumer2.start();
        }
    }

    private static void testMultithreading() {
        System.out.println("Main thread started");
        Thread thread1 = new Thread1("Thread1");
        thread1.start();

        Thread thread2 = new Thread(new Thread2(), "Thread2");
        thread2.start();

        // initialize thread using lambda
        Thread thread3 = new Thread(() -> {
            System.out.println("Thread " + Thread.currentThread().getName() + " started");
            for (int i=0; i<10; i++) {
                System.out.println("Thread: " + Thread.currentThread() + " in progress " + i);
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
            }
        }, "Thread3");
        thread3.start();

        try {
            thread1.join(); // blocking until thread1 joins to main thread. Similarly thread2, thread3
            thread2.join();
            thread3.join();
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }

        System.out.println("Main thread finished");
    }

    private static void testDeadlock() {
        Object lock1 = new Object();
        Object lock2 = new Object();
        System.out.println("Main thread entered");

        Thread t1 = new Thread(() -> {
            synchronized (lock1) {
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
                synchronized (lock2) {
                    System.out.println(Thread.currentThread().getName() + " - Both locks acquired");
                }
            }
        }, "T1");

        Thread t2 = new Thread(() -> {
            synchronized (lock2) {
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
                synchronized (lock1) {
                    System.out.println(Thread.currentThread().getName() + " - Both locks acquired");
                }
            }
        }, "T2");

        t1.start();
        t2.start();
    }
}