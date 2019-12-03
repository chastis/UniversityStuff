package com.andlvovsky.parser;

import com.andlvovsky.builder.DeviceBuilder;
import com.andlvovsky.domain.Device;
import com.andlvovsky.exception.XmlParserException;

import org.w3c.dom.Document;
import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import java.io.FileInputStream;
import java.io.InputStream;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;

public class XmlDeviceParserDom implements XmlDeviceParser {
	private DeviceBuilder deviceBuilder = new DeviceBuilder();

	@Override
	public Device parse(String filename) {
		Document document = parseDom(filename);
		traverse(document.getDocumentElement(), deviceBuilder);
		return deviceBuilder.build();
	}

	private Document parseDom(String filename) {
		try {
			InputStream inputStream = new FileInputStream(filename);
			return parseDom(inputStream);
		} catch (Exception e) {
			throw new XmlParserException("Parsing device failed with dom parser", e);
		}
	}
	
	private Document parseDom(InputStream inputStream) throws Exception {
		DocumentBuilderFactory documentBuilderFactory = DocumentBuilderFactory.newInstance();
		DocumentBuilder documentBuilder;
		documentBuilder = documentBuilderFactory.newDocumentBuilder();
		Document document;
		document = documentBuilder.parse(inputStream);
		return document;
	}

	private void traverse(Node node, DeviceBuilder deviceBuilder) {
		deviceBuilder.setField(node.getNodeName(), node.getTextContent());

		NamedNodeMap attrs = node.getAttributes();

		for (int i = 0; i < attrs.getLength(); i++) {
			Node attr = attrs.item(i);
			deviceBuilder.setField(attr.getNodeName(), attr.getTextContent());
		}

		NodeList nodes = node.getChildNodes();
		for (int i = 0; i < nodes.getLength(); i++) {
			Node nextNode = nodes.item(i);
			if (nextNode.getNodeType() == Node.ELEMENT_NODE) {
				traverse(nextNode, deviceBuilder);
			}
		}
	}
}