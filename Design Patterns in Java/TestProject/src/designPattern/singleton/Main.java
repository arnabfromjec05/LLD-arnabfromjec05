package designPattern.singleton;

import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException, ClassNotFoundException {
        System.out.println("Design pattern driver class");
        DateUtil dateUtil = DateUtil.getInstance();
        DateUtil dateUtil1 = DateUtil.getInstance();
        if (dateUtil1 == dateUtil) {
            System.out.println(dateUtil1 + " is equal to " + dateUtil);
            System.out.println(dateUtil1.hashCode());
            System.out.println(dateUtil.hashCode());
        } else {
            System.out.println("Objects are different");
        }

        // serializable
        ObjectOutputStream oso = new ObjectOutputStream(new FileOutputStream(
                new File("/Users/arnabjana/Documents/dev/Design Patterns in Java/testFile.ser")));
        oso.writeObject(dateUtil);

        ObjectInputStream iso = new ObjectInputStream(new FileInputStream(
                new File("/Users/arnabjana/Documents/dev/Design Patterns in Java/testFile.ser")));
        if (((DateUtil) iso.readObject()).hashCode() == dateUtil.hashCode()) {
            System.out.println("Object read is equal to object serialized");
        } else {
            System.out.println("Object read is not equal to object serialized");
        }
    }
}
