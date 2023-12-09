package designPattern.prototype;

public class Main {
    public static void main(String[] args) throws CloneNotSupportedException {
        Game g1 = new Game();
        g1.setId(1);
        g1.setName("first");
        g1.setMembership(new Membership());

        Game g2 = g1.clone();
        System.out.println(g1);
        System.out.println(g2);

        Game g3 = new Game(g1);
        System.out.println(g3);
    }
}
