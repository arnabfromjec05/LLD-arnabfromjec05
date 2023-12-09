package designPattern.facade;

public class OrderStock {
    public boolean checkStock(String item, int qty) {
        if (item == "mac" && qty <= 5) {
            return true;
        }
        return false;
    }
}
