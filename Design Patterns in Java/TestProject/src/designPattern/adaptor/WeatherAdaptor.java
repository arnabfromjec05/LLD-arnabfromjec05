package designPattern.adaptor;

public class WeatherAdaptor {

    private IWeatherFinder weatherFinder = new WeatherFinderImpl();

    public int findTemperature(int zipCode) throws Exception {
        String city = null;
        switch (zipCode) {
            case 5000:
            case 5001:
            case 5002:
                city = "Bengaluru";
                break;
            case 6000:
                city = "Mumbai";
                break;
            case 7000:
                city = "Delhi";
                break;
            default:
                throw new Exception("No valid city found with given zipcode");
        }
        return weatherFinder.find(city);
    }
}
