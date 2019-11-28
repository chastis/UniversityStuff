import Parser.PlaneParser;
import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.stream.XMLStreamException;
import java.io.IOException;

public class Main {
    public static void main(String[] args) throws IOException, SAXException, ParserConfigurationException, XMLStreamException {

        PlaneParser planeParser = new PlaneParser();

        System.out.println("SAX parser");
        planeParser.parse("src/main/resources/Plane.xml",
                "src/main/resources/Plane.xsd", "sax");

        System.out.println("\nStAX parser");
        planeParser.parse("src/main/resources/Plane.xml",
                "src/main/resources/Plane.xsd", "stax");

        System.out.println("\nDOM parser");
        planeParser.parse("src/main/resources/Plane.xml",
                "src/main/resources/Plane.xsd", "dom");
    }
}
