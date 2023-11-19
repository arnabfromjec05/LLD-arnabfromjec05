package designPattern.templateMethod;

public abstract class DataRenderer {

    // this is the template method common to subclasses
    public void render() {
        String data = readData();
        String processedData = processData(data);
        // some methods to render data
        System.out.println(processedData);
    }

    protected abstract String readData();
    protected abstract String processData(String data);
}

class XMLDataRenderer extends DataRenderer {
    @Override
    protected String readData() {
        return "Read xml data";
    }

    @Override
    protected String processData(String data) {
        System.out.println(data);
        return "Processed xml data";
    }
}

class CsvDataRenderer extends DataRenderer {
    @Override
    protected String readData() {
        return "Read csv data";
    }

    @Override
    protected String processData(String data) {
        System.out.println(data);
        return "Processed csv data";
    }
}


