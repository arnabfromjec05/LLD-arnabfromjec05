package designPattern.adaptor;

public class WeatherUI {
    public int find(int zipCode) throws Exception {
        WeatherAdaptor adaptor = new WeatherAdaptor();
        return adaptor.findTemperature(zipCode);
    }
}
