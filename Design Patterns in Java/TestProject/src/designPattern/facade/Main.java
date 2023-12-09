package designPattern.facade;

public class Main {
    public static void main(String[] args) {
        OrderFacade orderFacade = new OrderFacade();
        orderFacade.placeOrder("mac", 3);
        orderFacade.placeOrder("windows", 2);
        orderFacade.placeOrder("mac", 7);
    }
}
