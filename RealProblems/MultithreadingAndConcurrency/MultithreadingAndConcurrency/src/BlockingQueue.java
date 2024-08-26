import java.util.LinkedList;
import java.util.List;

/**
 * Solving Producer-Consumer problem using a blocking queue.
 * Blocking queue lets only one producer or a consumer to simultaneously access the queue for writes/reads.
 * It's also called as Pub-Sub problem.
 */
public class BlockingQueue {
    private volatile List<Integer> queue;
    private final int capacity;

    public BlockingQueue(int capacity) {
        this.capacity = capacity;
        queue = new LinkedList<>();
    }

    /**
     * Writes an element to the queue and return the operation status.
     */
    public boolean write(int element) {
        synchronized (queue) {
            while (queue.size() == capacity) {
                try {
                    queue.wait();
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
            }
            queue.addLast(element);
            System.out.println(Thread.currentThread().getName() + " writes " + element);
            queue.notifyAll();
            return true;
        }
    }

    /**s
     * Consumes an element from the queue and return it.
     */
    public int read() {
        synchronized (queue) {
            while (queue.size() == 0) {
                try {
                    queue.wait();
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
            }
            int element = queue.removeFirst();
            System.out.println(Thread.currentThread().getName() + " reads " + element);
            queue.notifyAll();
            return element;
        }
    }
}
