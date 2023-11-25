package designPattern.command;

public class OnCommand implements ICommand {
    Television television;

    public OnCommand(Television television) {
        this.television = television;
    }

    @Override
    public void execute() {
        television.On();
    }
}
