package designPattern.command;

public class RemoteControl {
    private ICommand command;

    public void pressButton() {
        command.execute();
    }

    public ICommand getCommand() {
        return command;
    }

    public void setCommand(ICommand command) {
        this.command = command;
    }
}
