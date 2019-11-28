package Parser;

import Plane.*;

import javax.xml.stream.XMLEventReader;
import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.XMLStreamException;
import javax.xml.stream.events.EndElement;
import javax.xml.stream.events.StartElement;
import javax.xml.stream.events.XMLEvent;
import javax.xml.stream.XMLStreamConstants;

import java.io.FileInputStream;
import java.io.FileNotFoundException;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by Chastis on 03.11.2019.
 */
public class StAXParser implements ParserXML {
    private XMLHandler handler;

    StAXParser(XMLHandler handler) {
        this.handler = handler;
    }

    @Override
    public void parse(String xmlPath) {
        XMLInputFactory factory = XMLInputFactory.newInstance();
        XMLEventReader reader = null;
        try {
            reader = factory.createXMLEventReader(new FileInputStream(xmlPath));
        } catch (FileNotFoundException | XMLStreamException e) {
            e.printStackTrace();
        }

        while (reader.hasNext()) {
            try {
                XMLEvent event = reader.nextEvent();

                switch (event.getEventType()) {
                    case XMLStreamConstants.END_DOCUMENT:
                        break;

                    case XMLStreamConstants.START_ELEMENT:
                        StartElement startElement = event.asStartElement();
                        event = reader.nextEvent();
                        handler.setTag(startElement.getName().getLocalPart(), event.asCharacters().getData());
                        break;

                    case XMLStreamConstants.END_ELEMENT:
                        EndElement endElement = event.asEndElement();
                        if (endElement.getName().getLocalPart().equalsIgnoreCase(handler.name)) {
                            handler.endTag(handler.name);
                        }
                        break;
                }
            } catch (XMLStreamException e) {
            }
        }
        return;
    }

}
