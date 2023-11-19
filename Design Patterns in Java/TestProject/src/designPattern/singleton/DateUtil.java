package designPattern.singleton;

import java.io.Serializable;

public class DateUtil implements Serializable, Cloneable {

    // volatile keyword ensures value is read from main memory and not from cpu cache (Avoids issues in multithreaded
    // environment)
    private static volatile DateUtil dateUtil = null;

    private DateUtil() {
        System.out.println("Instance of DateUtil class created");
    }

    public static DateUtil getInstance() {
        // This check is used as after first time dateUtils get initialized it is not recommended to make synchronized
        // check again, as it's a costly operation. So outer layer null check is used. (Double null check)
        if (dateUtil == null) {
            synchronized (DateUtil.class) {
                if (dateUtil == null) {
                    dateUtil = new DateUtil();
                }
            }
        }
        return dateUtil;
    }

    // for retaining singleton property in case of serialization
    protected Object readResolve() {
        return dateUtil;
    }

    @Override
    protected Object clone() throws CloneNotSupportedException {
        throw new CloneNotSupportedException();
    }
}
