package designPattern.command;

public class Main {
    public static void main(String[] args) {

        Television tv = new Television();
        RemoteControl rc = new RemoteControl();

        // note: here tv and rc are decoupled, independent objects without knowing others presence
        // rc job is just to invoke any command issued by person

        // on command invoked
        OnCommand onCommand = new OnCommand(tv);
        rc.setCommand(onCommand);
        rc.pressButton();

        // off command invoked
        OffCommand offCommand = new OffCommand(tv);
        rc.setCommand(offCommand);
        rc.pressButton();
    }
}
