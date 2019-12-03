package com.andlvovsky.builder;

import com.andlvovsky.domain.Device;

import java.util.Collections;
import java.util.HashMap;
import java.util.Map;
import java.util.function.BiConsumer;

public class DeviceBuilder {
  private static final String DEVICE = "device";
  private static final String ID = "id";
  private static final String CRITICAL = "critical";
  private static final String NAME = "name";
  private static final String ORIGIN = "origin";
  private static final String PRICE = "price";
  private static final String TYPE = "type";
  private static final String PERIPHERY = "periphery";
  private static final String ENERGY_CONSUMPTION = "energyConsumption";
  private static final String WITH_COOLER = "withCooler";
  private static final String COMPONENT_GROUP = "componentGroup";
  private static final String PORT = "port";

  private static final Map<String, BiConsumer<Device, String>> SETTERS;
  static {
    Map<String, BiConsumer<Device, String>> setters = new HashMap<>();
    setters.put(DEVICE, (device, value) -> {});
    setters.put(ID, Device::setId);
    setters.put(CRITICAL, (device, value) -> device.setCritical(Boolean.parseBoolean(value)));
    setters.put(NAME, Device::setName);
    setters.put(ORIGIN, Device::setOrigin);
    setters.put(PRICE, (device, value) -> device.setPrice(Double.parseDouble(value)));
    setters.put(TYPE, (device, value) -> {});
    setters.put(PERIPHERY, (device, value) -> device.getType().setPeriphery(Boolean.parseBoolean(value)));
    setters.put(ENERGY_CONSUMPTION, (device, value) -> device.getType().setEnergyConsumption(Integer.parseInt(value)));
    setters.put(WITH_COOLER, (device, value) -> device.getType().setWithCooler(Boolean.parseBoolean(value)));
    setters.put(COMPONENT_GROUP, (device, value) -> device.getType().setComponentGroup(Device.Type.ComponentGroup.valueOf(value)));
    setters.put(PORT, (device, value) -> device.getType().setPort(Device.Type.Port.valueOf(value)));
    SETTERS = Collections.unmodifiableMap(setters);
  }

  private Device device;

  public DeviceBuilder() {
    device = new Device();
    device.setType(new Device.Type());
  }

  public void setField(String name, String value) {
    BiConsumer<Device, String> fieldSetter = SETTERS.get(name);
    if (fieldSetter != null) {
      fieldSetter.accept(device, value);
    }
  }

  public Device build() {
    return device;
  }
}
