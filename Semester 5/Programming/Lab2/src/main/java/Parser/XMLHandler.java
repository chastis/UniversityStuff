package Parser;

import Plane.*;

import java.util.ArrayList;
import java.util.List;


public class XMLHandler {
    private Plane plane;
    private List<Plane> planes;
    public String name;

    public XMLHandler() {
        plane = new Plane();
        planes = new ArrayList<>();
        name = "Plane";
    }

    public Plane getPlane(){
        return plane;
    }

    public List<Plane> getPlanes(){
        return planes;
    }

    public void setTag( String element, String value){
        switch (element.toLowerCase()){
            case "plane":
                plane = new Plane();
            case "id":
                plane.setId(value);
                break;
            case "model":
                plane.setModel(value);
                break;
            case "origin":
                plane.setOrigin(value);
                break;
            case "type":
                plane.getChars().setType(PlaneType.valueOf(value));
                break;
            case "seats":
                plane.getChars().setSeats(Integer.parseInt(value));
                break;
            case "radar":
                plane.getChars().setRadar(Boolean.parseBoolean(value));
                break;
            case "length":
                plane.getParameters().setLength(Integer.parseInt(value));
                break;
            case "height":
                plane.getParameters().setHeight(Integer.parseInt(value));
                break;
            case "width":
                plane.getParameters().setWidth(Integer.parseInt(value));
                break;
            default:
                break;
        }
    }

    public void endTag(String element){
        if(element.equalsIgnoreCase("plane")) {
            planes.add(plane);
            plane = new Plane();
        }
    }
}


