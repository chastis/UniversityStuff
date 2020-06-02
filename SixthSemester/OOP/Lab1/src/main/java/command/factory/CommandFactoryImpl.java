package command.factory;

import command.*;
import database.ConcreteDAO;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class CommandFactoryImpl implements CommandFactory {

    private CommandFactoryImpl(){};
    private static CommandFactoryImpl factory=new CommandFactoryImpl();
    public static CommandFactory getFactory(){
        return factory;
    }
    @Override
    public Command getCommand(String name, HttpServletRequest request, HttpServletResponse response) throws IllegalArgumentException {
        if (name==null){
            throw new IllegalArgumentException("Name cannot be NULL") ;
        }
        else{
            Command command=null;

            //----------------------------//
            if (name.equals("Block")) {
                command = new BlockCommand();
            }
            else if (name.equals("TopUp")){
                command = new TopUpCommand();
            }
            else if(name.equals("Pay")){
                command = new PayCommand();
            }
            else if (name.equals("Authorization")){
                command = new AuthorizationCommand();
            }
            else if (name.equals("Payments")){
                command = new PaymentsCommand();
            }
            else if (name.equals("Unblock")){
                command = new UnblockCommand();
            }
            else if (name.equals("Registration")){
                command = new RegistrationCommand();
            }

            //---------------------------//


            if (command==null){
                throw new IllegalArgumentException("Wrong command name");
            }

            command.setResp(response);
            command.setReq(request);
            command.setDao(ConcreteDAO.getInstance());
            return command;
        }


    }

}
