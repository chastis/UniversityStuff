package com.andlvovsky.parser;

import com.andlvovsky.builder.DeviceBuilder;
import com.andlvovsky.domain.Device;
import com.andlvovsky.exception.XmlParserException;

import org.xml.sax.Attributes;
import org.xml.sax.helpers.DefaultHandler;

import java.io.File;

import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;

public class XmlDeviceParserSax implements XmlDeviceParser {

  private static class DeviceHandler extends DefaultHandler {
    private DeviceBuilder deviceBuilder = new DeviceBuilder();
    private String elementValue;

    @Override
    public void characters(char[] ch, int start, int length) {
      elementValue = new String(ch, start, length);
    }

    @Override
    public void startElement(String uri, String localName, String qualifiedName, Attributes attrs) {
      for (int i = 0; i < attrs.getLength(); i++) {
        deviceBuilder.setField(attrs.getQName(i), attrs.getValue(i));
      }
    }

    @Override
    public void endElement(String uri, String localName, String qualifiedName) {
      deviceBuilder.setField(qualifiedName, elementValue);
    }

    public Device getDevice() {
      return deviceBuilder.build();
    }
  }

  @Override
  public Device parse(String filename) {
    try {
      SAXParserFactory factory = SAXParserFactory.newInstance();
      SAXParser saxParser = factory.newSAXParser();
      DeviceHandler deviceHandler = new DeviceHandler();
      saxParser.parse(new File(filename), deviceHandler);
      return deviceHandler.getDevice();
    } catch (Exception e) {
      throw new XmlParserException("Parsing device failed with sax parser", e);
    }
  }
}
