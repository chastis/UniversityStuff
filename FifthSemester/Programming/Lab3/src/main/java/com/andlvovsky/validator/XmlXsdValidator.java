package com.andlvovsky.validator;

import com.andlvovsky.exception.XmlValidatorException;

import java.io.FileInputStream;
import java.io.InputStream;

import javax.xml.XMLConstants;
import javax.xml.transform.stream.StreamSource;
import javax.xml.validation.Schema;
import javax.xml.validation.SchemaFactory;
import javax.xml.validation.Validator;

public class XmlXsdValidator {
    public void validate(String xmlFilename, String xsdFilename) {
        try {
            InputStream xmlInputStream = new FileInputStream(xmlFilename);
            InputStream xsdInputStream = new FileInputStream(xsdFilename);
            SchemaFactory factory =
                SchemaFactory.newInstance(XMLConstants.W3C_XML_SCHEMA_NS_URI);
            Schema schema = factory.newSchema(new StreamSource(xsdInputStream));
            Validator validator = schema.newValidator();
            validator.validate(new StreamSource(xmlInputStream));
        } catch (Exception e) {
            throw new XmlValidatorException("Validation failed", e);
        }
    }
}
