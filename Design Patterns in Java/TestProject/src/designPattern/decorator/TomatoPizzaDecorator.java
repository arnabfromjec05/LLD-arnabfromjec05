package designPattern.decorator;

public class TomatoPizzaDecorator extends PizzaDecorator {

    public TomatoPizzaDecorator(IPizza basePizza) {
        super(basePizza);
    }

    @Override
    public void bake() {
        super.bake();
        System.out.println("Add tomato seasoning.");
    }
}
