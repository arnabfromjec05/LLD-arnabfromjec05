package designPattern.facade;

/**
 * Facade class which abstracts out the order processing and takes off the load from client on maintaining different
 * components of the system like orderProcessing, shipping etc.
 */
public class OrderFacade {
    private OrderStock orderStock = new OrderStock();
    private OrderProcessor orderProcessor = new OrderProcessor();
    private OrderShip orderShip = new OrderShip();

    public void placeOrder(String item, int qty) {
        if (orderStock.checkStock(item, qty)) {
            String orderId = orderProcessor.processOrder(item, qty);
            orderShip.shipOrder(orderId);
        } else {
            System.out.println("Item with requested qty not available in stock!");
        }
    }
}
