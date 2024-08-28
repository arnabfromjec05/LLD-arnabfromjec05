// First thread - 1, 3
// second thread - 2, 4 ..
public class PrintNNumbersUsingTwoThreads {
    private int n;
    private Thread oddThread;
    private Thread evenThread;
    private State currentValue = new State(1);

    public PrintNNumbersUsingTwoThreads(int n) {
        this.n = n;
        this.oddThread = new Thread(
                new OddThread(n, this.currentValue),
                "OddThread");
        this.evenThread = new Thread(
                new EvenThread(n, this.currentValue),
                "EvenThread");
    }

    public void startPrinting() {
        this.oddThread.start();
        this.evenThread.start();
    }
}

class OddThread implements Runnable {
    private final int n;
    private State currentValue;
    public OddThread(int n, State currentValue) {
        this.n = n;
        this.currentValue = currentValue;
    }

    @Override
    public void run() {
        synchronized (this.currentValue) {
            while(this.currentValue.getCurrentValue() <= this.n) {
                if (this.currentValue.getCurrentValue() % 2 == 1) {
                    System.out.println(
                            "Thread " + Thread.currentThread().getName() + " - " + this.currentValue.getCurrentValue());
                    this.currentValue.incrementCurrentValue();
                    this.currentValue.notify();
                } else {
                    try {
                        this.currentValue.wait();
                    } catch (InterruptedException e) {
                        throw new RuntimeException(e);
                    }
                }
            }
        }
    }
}

class EvenThread implements Runnable {
    private final int n;
    private State currentValue;
    public EvenThread(int n, State currentValue) {
        this.n = n;
        this.currentValue = currentValue;
    }

    @Override
    public void run() {
        synchronized (this.currentValue) {
            while(this.currentValue.getCurrentValue() <= this.n) {
                if (this.currentValue.getCurrentValue() % 2 == 0) {
                    System.out.println(
                            "Thread " + Thread.currentThread().getName() + " - " + this.currentValue.getCurrentValue());
                    this.currentValue.incrementCurrentValue();
                    this.currentValue.notify();
                } else {
                    try {
                        this.currentValue.wait();
                    } catch (InterruptedException e) {
                        throw new RuntimeException(e);
                    }
                }
            }
        }
    }
}

// Stores the current iteration value
class State {
    private volatile int currentValue;
    public State(int val) {
        this.currentValue = val;
    }

    public int getCurrentValue() {
        return currentValue;
    }

    public void incrementCurrentValue() {
        this.currentValue += 1;
    }
}

