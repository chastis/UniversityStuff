package Parser;

import org.xml.sax.SAXException;

import javax.xml.transform.stream.StreamSource;
import javax.xml.validation.Schema;
import javax.xml.validation.SchemaFactory;
import javax.xml.validation.Validator;
import java.io.File;
import java.io.IOException;

/**
 * Created by chastis
 */
public class XMLValidator {
    public static boolean validateXML(String xmlFile, String xsdFile){
        try {
            SchemaFactory factory = SchemaFactory.newInstance("http://www.w3.org/2001/XMLSchema");
            Schema schema = factory.newSchema(new File(xsdFile));
            Validator validator = schema.newValidator();
            validator.validate(new StreamSource(new File(xmlFile)));
        } catch (SAXException e) {
            System.out.println("Validation error because " + e.getMessage());
            return false;
        } catch (IOException e) {
            System.out.println("Validation error because " + e.getMessage());
            return false;
        }
        return true;
    }


}
