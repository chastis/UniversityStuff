package com.andlvovsky.parser;

import com.andlvovsky.domain.Device;

public interface XmlDeviceParser {
  Device parse(String filename);
}
