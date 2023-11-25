package designPattern.flyweight;

public class Circle extends Shape {
    private String label;

    public Circle() {
        this.label = "Circle";
    }

    @Override
    public void draw(int radius, String fillColor) {
        System.out.println("Drawing a " + this.label + " with radius " + radius + " and fill color " + fillColor);
    }
}
