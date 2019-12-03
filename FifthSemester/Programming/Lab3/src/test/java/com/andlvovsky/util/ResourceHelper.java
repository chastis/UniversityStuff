package com.andlvovsky.util;

import java.net.URL;
import java.net.URLDecoder;

public class ResourceHelper {
    private ResourceHelper() {}

    public static String getFilename(String filename) {
        ClassLoader classLoader =
                Thread.currentThread().getContextClassLoader();
        URL url = classLoader.getResource(filename);
        try {
            filename = URLDecoder.decode(url.getPath(), "UTF-8");
        } catch(Exception ex) {
            ex.printStackTrace();
        }
        return filename;
    }
}