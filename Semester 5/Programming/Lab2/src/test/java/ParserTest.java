import Parser.PlaneParser;
import Parser.XMLHandler;
import Plane.*;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.assertEquals;
import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.stream.XMLStreamException;
import java.io.IOException;

public class ParserTest {
    PlaneParser planeParser;
    Plane plane1;
    Plane plane2;

    ParserTest(){
        planeParser = new PlaneParser();
        plane1 = new Plane();
        plane2 = new Plane();

        plane1.setId("841");
        plane1.setModel("ACAZ C.2");
        plane1.setOrigin("Belgium");
        plane1.setChars(new Chars(PlaneType.valueOf("fighter"), 2,false));
        plane1.setParameters(new Parameters(8,3,12));

        plane2.setId("111");
        plane2.setModel("Lockheed U-2");
        plane2.setOrigin("US");
        plane2.setChars(new Chars(PlaneType.valueOf("reconnaissance"), 1,true));
        plane2.setParameters(new Parameters(19,5,32));

    }

    @Test
    void DOMParserTest() throws ParserConfigurationException, XMLStreamException, SAXException, IOException {
        Planes planes = planeParser.parse("src/main/resources/test/example.xml",
                "src/main/resources/Plane.xsd", "dom");
        assertEquals(planes.getList().get(0), plane2);
        assertEquals(planes.getList().get(1), plane1);
    }

    @Test
    void SAXParserTest() throws ParserConfigurationException, XMLStreamException, SAXException, IOException {
        Planes planes = planeParser.parse("src/main/resources/test/example.xml",
                "src/main/resources/Plane.xsd", "sax");
        assertEquals(planes.getList().get(0), plane2);
        assertEquals(planes.getList().get(1), plane1);
    }

    @Test
    void StAXParserTest() throws ParserConfigurationException, XMLStreamException, SAXException, IOException {
        Planes planes = planeParser.parse("src/main/resources/test/example.xml",
                "src/main/resources/Plane.xsd", "stax");
        assertEquals(planes.getList().get(0), plane2);
        assertEquals(planes.getList().get(1), plane1);
    }

    @Test
    void XMLHandlerTest(){
        XMLHandler handler = new XMLHandler();
        handler.setTag("id", "841");
        handler.setTag("model", "ACAZ C.2");
        handler.setTag("origin", "Belgium");
        handler.setTag("type","fighter");
        handler.setTag("seats", "2");
        handler.setTag("radar", "false");
        handler.setTag("length", "8");
        handler.setTag("height","3");
        handler.setTag("width", "12");

        assertEquals(plane1, handler.getPlane());
    }
}
