package Parser.SAXParser;

import Parser.ParserXML;
import Parser.XMLHandler;
import Plane.Plane;
import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by Chastis on 03.11.2019.
 */
public class SAXPlaneParser implements ParserXML{
    private XMLHandler handler;
    public SAXPlaneParser(XMLHandler handler){
        this.handler = handler;
    }

    @Override
    public void parse(String xmlPath) throws IllegalArgumentException {

        SAXParserFactory saxParserFactory = SAXParserFactory.newInstance();
        try {
            SAXParser saxParser = saxParserFactory.newSAXParser();
            SAXHandler saxHandler = new SAXHandler(handler);
            saxParser.parse(new File(xmlPath), saxHandler);

        } catch (ParserConfigurationException | SAXException | IOException e) {
            e.printStackTrace();
            throw new IllegalArgumentException("Error: " + e.getMessage());
        }
    }
}
