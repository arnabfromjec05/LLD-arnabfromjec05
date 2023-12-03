package designPattern.decorator;

public class Main {

    public static void main(String[] args) {
        // 3 orders
        IPizza margerritaPizza = new MargerritaPizzaDecorator(new PlainPizza());
        IPizza tomatoPizza = new TomatoPizzaDecorator(new PlainPizza());
        IPizza tomatoStuffedMargerritaPizza = new TomatoPizzaDecorator(
                new MargerritaPizzaDecorator(new PlainPizza()));

        // let's bake them
        margerritaPizza.bake();
        tomatoPizza.bake();
        tomatoStuffedMargerritaPizza.bake();
    }
}
