package com.company;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.*;
import javax.xml.stream.*;



public class STAXPars {

    private XMLInputFactory factory;
    private XMLStreamReader reader; //(1)
    private Candy curr = new Candy();
    private List<Candy> res = new ArrayList<Candy>();
    private Ingredient currIngr = new Ingredient();

    STAXPars(String name) {
        tryRead(name);
    }

    private void tryRead(String name) {
        try {
            factory = XMLInputFactory.newInstance();
            reader = factory.createXMLStreamReader(new FileReader(name)); //создается объект класса XMLStreamReader,
            // который позволяет перемещаться последовательно по всем элементам XML
        } catch (FileNotFoundException e) {
            System.out.println("Can't find such a file!");
        } catch (XMLStreamException e) {
            System.out.println("XMLStreamException");
        }
    }

    public void parse() {
        String currElement = new String();
        try {
            while(reader.hasNext()) {
                int event = reader.next();
                switch(event) {
                    case XMLStreamConstants.START_ELEMENT:
                        currElement = reader.getLocalName();
                        if(reader.getLocalName().equals("Candy")) {
                            curr = new Candy();
                            curr.setName(reader.getAttributeValue(0));
                            if(Boolean.valueOf(Boolean.valueOf(reader.getAttributeValue(1)) == true)) {
                                curr.setFilled(true);
                            } else {
                                curr.setFilled(false);
                            }
                        }
                        if(reader.getLocalName().equals("Ingredient")) {
                            currIngr = new Ingredient();
                        }
                        break;

                    case XMLStreamConstants.CHARACTERS:
                        if (currElement.equals("Energy")) {
                            curr.setEnergy(new Integer(reader.getText()));
                        }
                        if (currElement.equals("Type")) {
                            curr.setType(reader.getText());
                        }
                        if (currElement.equals("Name")) {
                            currIngr.setName(reader.getText());
                        }
                        if (currElement.equals("Count")) {
                            currIngr.setCount(new Integer(reader.getText()));
                        }
                        if (currElement.equals("Proteins")) {
                            curr.setProteins(new Integer(reader.getText()));
                        }
                        if (currElement.equals("Fats")) {
                            curr.setFats(new Integer(reader.getText()));
                        }
                        if (currElement.equals("Carbohydrates")) {
                            curr.setCarbohydrates(new Integer(reader.getText()));
                        }
                        if (currElement.equals("Production")) {
                            curr.setProduction(reader.getText());
                        }
                        break;

                    case XMLStreamConstants.END_ELEMENT:
                        if(reader.getLocalName().equals("Ingredient")) {
                            curr.addIngredient(currIngr);
                        }
                        if(reader.getLocalName().equals("Candy")) {
                            res.add(curr);
                        }
                        currElement = "";
                        break;
                }
            }
        } catch (NumberFormatException e) {
            System.out.println("NumberFormatException!");
        } catch (XMLStreamException e) {
            System.out.println("XMLStreamException!");
        }
    }

    public List<Candy> getCandies() {
        return res;
    }

}
