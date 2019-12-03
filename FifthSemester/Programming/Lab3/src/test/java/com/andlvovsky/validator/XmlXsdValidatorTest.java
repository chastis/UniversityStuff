package com.andlvovsky.validator;

import com.andlvovsky.exception.XmlValidatorException;
import com.andlvovsky.util.ResourceHelper;

import org.junit.Test;

public class XmlXsdValidatorTest {
    @Test(expected = Test.None.class)
    public void shouldNotThrowAnyExceptionWhenValidatingValidDevice() {
        XmlXsdValidator validator = new XmlXsdValidator();
        validator.validate(
            ResourceHelper.getFilename("xml/valid_device.xml"),
            ResourceHelper.getFilename("xsd/device.xsd"));
    }

    @Test(expected = XmlValidatorException.class)
    public void shouldThrowXmlValidatorExceptionWhenValidatingInvalidDevice() {
        XmlXsdValidator validator = new XmlXsdValidator();
        validator.validate(
            ResourceHelper.getFilename("xml/invalid_device.xml"),
            ResourceHelper.getFilename("xsd/device.xsd"));
    }
}
