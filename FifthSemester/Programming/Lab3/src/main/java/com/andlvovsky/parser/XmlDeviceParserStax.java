package com.andlvovsky.parser;

import com.andlvovsky.builder.DeviceBuilder;
import com.andlvovsky.domain.Device;
import com.andlvovsky.exception.XmlParserException;

import java.io.FileInputStream;
import java.util.Iterator;

import javax.xml.stream.XMLEventReader;
import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.XMLStreamException;
import javax.xml.stream.events.Attribute;
import javax.xml.stream.events.StartElement;
import javax.xml.stream.events.XMLEvent;

public class XmlDeviceParserStax implements XmlDeviceParser {
  private DeviceBuilder deviceBuilder = new DeviceBuilder();

  @Override
  public Device parse(String filename) {
    XMLInputFactory xmlInputFactory = XMLInputFactory.newInstance();
    try {
      XMLEventReader xmlEventReader = xmlInputFactory.createXMLEventReader(new FileInputStream(filename));
      while(xmlEventReader.hasNext()){
        XMLEvent xmlEvent = xmlEventReader.nextEvent();
        if (xmlEvent.isStartElement()){
          handleStartElement(xmlEvent, xmlEventReader);
        }
      }
      return deviceBuilder.build();
    } catch (Exception e) {
      throw new XmlParserException("Parsing device failed with stax parser", e);
    }
  }

  private void handleStartElement(XMLEvent xmlEvent, XMLEventReader xmlEventReader) throws XMLStreamException {
    StartElement startElement = xmlEvent.asStartElement();
    for (Iterator<Attribute> it = startElement.getAttributes(); it.hasNext(); ) {
      Attribute attr = it.next();
      deviceBuilder.setField(attr.getName().toString(), attr.getValue());
    }

    xmlEvent = xmlEventReader.nextEvent();
    String fieldName = startElement.getName().getLocalPart();
    deviceBuilder.setField(fieldName, xmlEvent.asCharacters().getData());
  }
}
