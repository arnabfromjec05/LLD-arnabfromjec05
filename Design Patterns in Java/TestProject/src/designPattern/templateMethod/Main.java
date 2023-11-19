package designPattern.templateMethod;

public class Main {
    public static void main(String[] args) {
        DataRenderer csvDataRenderer = new CsvDataRenderer();
        DataRenderer xmlDataRenderer = new XMLDataRenderer();
        csvDataRenderer.render();
        xmlDataRenderer.render();
    }
}
