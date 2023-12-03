package designPattern.decorator;

public class MargerritaPizzaDecorator extends PizzaDecorator {

    public MargerritaPizzaDecorator(IPizza basePizza) {
        super(basePizza);
    }

    @Override
    public void bake() {
        super.bake();
        System.out.println("Add cheese topping.");
    }
}
