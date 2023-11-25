package designPattern.flyweight;

import java.util.HashMap;
import java.util.Map;

public class ShapeFactory {

    // in-memory shape cache
    private static Map<ShapeTypes, Shape> shapeCache = new HashMap<ShapeTypes, Shape>();

    public static Shape getShape(ShapeTypes type) throws Exception {
        if (shapeCache.get(type) == null) {
            System.out.println("obj created"); // verified object created
            Shape shape = null;
            switch (type) {
                case CIRCLE:
                    shape = new Circle();
                    break;
                case RECTANGLE:
                    shape = new Rectangle();
                    break;
                default:
                    throw new Exception("Unidentified shape");
            }
            shapeCache.put(type, shape);
        }
        return shapeCache.get(type);
    }
}
