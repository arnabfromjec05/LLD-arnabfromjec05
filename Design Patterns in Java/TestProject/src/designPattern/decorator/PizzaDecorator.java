package designPattern.decorator;

public abstract class PizzaDecorator implements IPizza{
    private IPizza basePizza;

    // basePizza will be passed from concrete decorators to avoid code redundancy.
    public PizzaDecorator(IPizza basePizza) {
        this.basePizza = basePizza;
    }

    @Override
    public void bake() {
        this.basePizza.bake();
    }
}
