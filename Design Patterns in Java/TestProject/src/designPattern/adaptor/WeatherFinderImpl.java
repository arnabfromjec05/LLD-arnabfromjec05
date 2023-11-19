package designPattern.adaptor;

public class WeatherFinderImpl implements IWeatherFinder{
    @Override
    public int find(String city) throws Exception {
        switch (city) {
            case "Bengaluru":
                return 25;
            case "Delhi":
                return 15;
            case "Mumbai":
                return 30;
            default:
                throw new Exception("City not found in the db");
        }
    }
}
