package designPattern.flyweight;

public class Rectangle extends Shape {
    private String label;

    public Rectangle() {
        this.label = "Rectangle";
    }

    @Override
    public void draw(int length, int breadth, String fillStyle) {
        System.out.println("Drawing a " + this.label + " with length " + length + " and breadth " +
                breadth + " and filled with style " + fillStyle);
    }
}
