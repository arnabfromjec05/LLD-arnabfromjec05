package playground;

public class Main {
    public static void main(String[] args) throws Exception {
        Stack<Integer> st = new Stack<Integer>();
        st.push(1);
        st.push(2);
        System.out.println(st.pop());
        System.out.println(st.peek());

        Queue<Integer> q = new Queue<Integer>();
        q.enqueue(3);
        q.enqueue(4);
        q.enqueue(5);
        q.printAll();
        q.dequeue();
        q.dequeue();
        q.printAll();
    }
}

