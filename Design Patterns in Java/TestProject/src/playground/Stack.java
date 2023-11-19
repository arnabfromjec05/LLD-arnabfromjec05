package playground;

import java.util.ArrayList;
import java.util.List;

/**
 * Generic stack class
 * @param <T>
 */
public class Stack<T> {
    private List<T> stack;
    Stack() {
        stack = new ArrayList<>();
    }

    public boolean push(T element) {
        return stack.add(element);
    }

    public T pop() throws Exception{
        if (stack.isEmpty()) {
            throw new Exception("Empty stack, no element can be popped");
        }
        return stack.removeLast();
    }

    public T peek() throws Exception {
        if (stack.isEmpty()) {
            throw new Exception("No element in stack");
        }
        return stack.getLast();
    }
}
