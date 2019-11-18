package com.company;
import java.util.*;
import javax.xml.parsers.*;
import org.xml.sax.SAXException;
import java.io.File;
import java.io.IOException;
import javax.xml.XMLConstants;
import javax.xml.transform.stream.StreamSource;
import javax.xml.validation.Schema;
import javax.xml.validation.SchemaFactory;
import javax.xml.validation.Validator;


public class Main {

    public static void main(String argv[]) {
        Scanner in = new Scanner(System.in);
        System.out.print("Input a number: ");
        int num = in.nextInt();

        switch (num) {
            case 1:
                System.out.println("\tDOM ...");
                System.out.println("--------------------------");
                DOMPars parser = new DOMPars("Candy.xml");
                parser.parse();
                List<Candy> res = parser.getCandies();
                for (Candy temp : res) {
                    System.out.println(temp);
                    System.out.println("--------------------------");
                }

                break;

            case 2:
                System.out.println("SAXParser ...");
                System.out.println("--------------------------");
                STAXPars parser1 = new STAXPars("Candy.xml");
                parser1.parse();
                List<Candy> res1 = parser1.getCandies();
                for(Candy temp: res1) {
                    System.out.println(temp);
                    System.out.println("--------------------------");
                }

                break;

            case 3:
                System.out.println("StAXParser ...");
                System.out.println("--------------------------");
                STAXPars parser2 = new STAXPars("Candy.xml");
                parser2.parse();
                List<Candy> res2 = parser2.getCandies();
                for(Candy temp: res2) {
                    System.out.println(temp);
                    System.out.println("--------------------------");
                }

                break;

            case 4:
                boolean answer = validateXMLSchema("Candy.xsd", "Candy.xml");
                System.out.println("Result:" + answer);
            default:
                break;
        }
    }
    public static boolean validateXMLSchema(String xsdPath, String xmlPath)
    {
        try {
            // Получить фабрику для схемы
            SchemaFactory factory = SchemaFactory.newInstance(XMLConstants.W3C_XML_SCHEMA_NS_URI);
            // Загрузить схему из XSD
            Schema schema = factory.newSchema(new File(xsdPath));
            // Создать валидатор (проверялбщик)
            Validator validator = schema.newValidator();
            // Запусить проверку - если будет исключение, значит есть ошибки.
            // Если нет - все заполнено правильно
            validator.validate(new StreamSource(new File(xmlPath)));
        } catch (IOException | SAXException e) {
            System.out.println("Exception: " + e.getMessage());
            return false;
        }
        return true;
    }
}



