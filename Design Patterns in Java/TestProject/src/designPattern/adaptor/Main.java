package designPattern.adaptor;

public class Main {
    public static void main(String[] args) throws Exception{
        WeatherUI ui = new WeatherUI();
        System.out.println(ui.find(5001));
        System.out.println(ui.find(6000));
        System.out.println(ui.find(7000));
        System.out.println(ui.find(8000)); // edge case
    }
}
