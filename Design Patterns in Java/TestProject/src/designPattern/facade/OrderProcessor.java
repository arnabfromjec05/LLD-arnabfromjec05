package designPattern.facade;

import java.util.Random;

public class OrderProcessor {
    public String processOrder(String item, int qty) {
        System.out.println("Processing item: " + item + " and qty: " + qty);
        return "ORD" + new Random().nextLong();
    }
}
