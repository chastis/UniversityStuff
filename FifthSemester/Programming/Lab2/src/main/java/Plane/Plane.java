package Plane;

import java.util.Objects;

/**
 * Created by chastis
 */
public class Plane implements Comparable{
    private String id;
    private String model;
    private String origin;
    private Chars chars;
    private Parameters parameters;

    public Plane(){
        chars = new Chars();
        parameters = new Parameters();
    }

    @Override
    public int compareTo(Object o) {
        return id.compareTo(((Plane) o).getId());
    }

    @Override
    public String toString(){
        return "\nPlane{ "
                +"\n\tId: " + id
                + ", \n\tmodel: " + model
                + ", \n\torigin: " + origin
                + ", \n\tchars: " + chars
                + ", \n\tparameters: " + parameters
                +"\n}";

    }

    @Override
    public boolean equals(Object o){
        if (this == o) return true;
        if (!(o instanceof Plane)) return false;
        Plane plane = (Plane) o;
        return id.equals(plane.getId())
                && model.equals(plane.getModel())
                && origin.equals(plane.getOrigin())
                && chars.equals(plane.getChars())
                && parameters.equals(plane.getParameters());
    }
    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getModel() {
        return model;
    }

    public void setModel(String model) {
        this.model = model;
    }

    public String getOrigin() {
        return origin;
    }

    public void setOrigin(String origin) {
        this.origin = origin;
    }

    public Chars getChars() {
        return chars;
    }

    public void setChars(Chars chars) {
        this.chars = chars;
    }

    public Parameters getParameters() {
        return parameters;
    }

    public void setParameters(Parameters parameters) {
        this.parameters = parameters;
    }
}
