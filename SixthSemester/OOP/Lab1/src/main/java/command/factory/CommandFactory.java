package command.factory;


import command.Command;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public interface CommandFactory {

    Command getCommand(String name, HttpServletRequest request, HttpServletResponse response) throws IllegalArgumentException;

}
