package designPattern.adaptor;

public interface IWeatherFinder {
    /**
     * Takes city name and returns the weather in form of temperature.
     * @param city
     * @return temperature
     * @throws if city not found
     */
    int find(String city) throws Exception;
}
