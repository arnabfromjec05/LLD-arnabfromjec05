package designPattern.flyweight;

public class PaintApp {
    public void render(int numShapes) throws Exception {
        Shape[] shapes = new Shape[numShapes];

        for (int i = 0; i < numShapes; i++) {
            if (i % 2 == 0) {
                shapes[i] = ShapeFactory.getShape(ShapeTypes.CIRCLE);
                shapes[i].draw(10, "Orange");
            } else {
                shapes[i] = ShapeFactory.getShape(ShapeTypes.RECTANGLE);
                shapes[i].draw(20, 30, "abc");
            }
        }
    }
}
