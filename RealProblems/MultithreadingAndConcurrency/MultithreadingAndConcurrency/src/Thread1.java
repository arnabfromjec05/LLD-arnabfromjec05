/**
 * By extending thread class.
 */
public class Thread1 extends Thread {

    public Thread1(String name) {
        super(name);
    }

    @Override
    public void run() {
        System.out.println("Thread " + Thread.currentThread().getName() + " started");
        for (int i=0; i<10; i++) {
            System.out.println("Thread: " + Thread.currentThread() + " in progress " + i);
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }
    }
}
