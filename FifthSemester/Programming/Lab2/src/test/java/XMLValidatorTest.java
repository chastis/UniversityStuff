import Parser.XMLValidator;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

public class XMLValidatorTest {

    @Test
    void validXMLvalidation(){
        assertTrue(XMLValidator.validateXML("src/main/resources/test/example.xml",
                "src/main/resources/Plane.xsd"));
    }

    @Test
    void invalidXMLvalidation(){
        assertFalse(XMLValidator.validateXML("src/main/resources/test/invalid.xml",
                "src/main/resources/Plane.xsd"));
    }
}
