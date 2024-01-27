public class Main {
    public static void main(String[] args) {
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

        System.out.println("Main thread finished");
    }
}