package com.andlvovsky.parser;

import com.andlvovsky.domain.Device;
import com.andlvovsky.util.ResourceHelper;

import org.junit.Test;

import static org.junit.Assert.assertEquals;

public class XmlDeviceParserDomTest {
    @Test
    public void shouldParseDevice(){
        //given
        XmlDeviceParser parser = new XmlDeviceParserDom();

        //when
        Device device = parser.parse(ResourceHelper.getFilename("xml/valid_device.xml"));

        //then
        Device.Type deviceType = device.getType();

        assertEquals("id-1", device.getId());
        assertEquals(true, device.isCritical());
        assertEquals("Display AGK-1203, 20 inch, IPS", device.getName());
        assertEquals("USA", device.getOrigin());
        assertEquals(200.75, device.getPrice(), 0.0000001);

        assertEquals(true, deviceType.isPeriphery());
        assertEquals(50, deviceType.getEnergyConsumption());
        assertEquals(false, deviceType.isWithCooler());
        assertEquals(Device.Type.ComponentGroup.OUTPUT_DEVICE, deviceType.getComponentGroup());
        assertEquals(Device.Type.Port.VGA, deviceType.getPort());
    }
}