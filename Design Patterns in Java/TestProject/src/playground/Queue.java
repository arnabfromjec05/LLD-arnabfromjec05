package playground;

import java.util.ArrayList;
import java.util.List;

/**
 * Generic queue class
 * @param <T>
 */
public class Queue<T> {
    private List<T> queue;
    Queue() {
        queue =  new ArrayList<T>();
    }

    public boolean enqueue(T element) {
        return queue.add(element);
    }

    public T dequeue() throws Exception{
        if (queue.isEmpty()) {
            throw new Exception("playground.Queue is empty, no element can be dequeued");
        }
        return queue.removeFirst();
    }

    public void printAll() {
        System.out.println("Elements in queue are :");
        queue.stream().forEach((T ele) -> {
            System.out.println(ele);
        });
        System.out.println("------>");
    }
}
