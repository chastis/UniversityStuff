package com.company;

import java.util.ArrayList;
import org.xml.sax.helpers.DefaultHandler;
import org.xml.sax.*;



public class SAXPars extends DefaultHandler{

    private ArrayList<Candy> candies = new ArrayList<Candy>();
    private Candy curr = new Candy();
    private Ingredient currIngr = new Ingredient();
    private String thisElement = "";

    public ArrayList<Candy> getCandies(){
        return candies;
    }

    @Override
    public void startDocument() throws SAXException {
        System.out.println("Start parse XML...");
    }
    // Метод вызывается когда SAXParser "натыкается" на начало тэга
    @Override
    public void startElement(String namespaceURI, String localName, String qName, Attributes attrs) throws SAXException {
        thisElement = qName;
        if(thisElement.equals("Candy")) {// Если тэг имеет имя Candy то мы этот момент отмечаем - начался тэг Candy
            curr = new Candy();
            curr.setName(attrs.getValue(0));
            if(Boolean.valueOf(attrs.getValue(1)) == true) {
                curr.setFilled(true);
            } else {
                curr.setFilled(false);
            }
        }
        if(thisElement.equals("Ingredient")) {
            currIngr = new Ingredient();
        }
    }

    @Override
    public void endElement(String namespaceURI, String localName, String qName) throws SAXException {
        if(qName.equals("Candy")) {
            candies.add(curr);
        }
        if(qName.equals("Ingredient")) {
            curr.addIngredient(currIngr);
        }
        thisElement = "";
    }

    // Метод вызывается когда SAXParser считывает текст между тэгами
    @Override
    public void characters(char[] ch, int start, int length) throws SAXException {
        if (thisElement.equals("Energy")) { // Если перед этим отмечен этот тег - надо формировать строку.
            curr.setEnergy(new Integer(new String(ch, start, length)));
        }
        if (thisElement.equals("Type")) {
            curr.setType(new String(ch, start, length));
        }
        if (thisElement.equals("Name")) {
            currIngr.setName(new String(ch, start, length));
        }
        if (thisElement.equals("Count")) {
            currIngr.setCount(new Integer(new String(ch, start, length)));
        }
        if (thisElement.equals("Proteins")) {
            curr.setProteins(new Integer(new String(ch, start, length)));
        }
        if (thisElement.equals("Fats")) {
            curr.setFats(new Integer(new String(ch, start, length)));
        }
        if (thisElement.equals("Carbohydrates")) {
            curr.setCarbohydrates(new Integer(new String(ch, start, length)));
        }
        if (thisElement.equals("Production")) {
            curr.setProduction(new String(ch, start, length));
        }
    }

    @Override
    public void endDocument() {
        System.out.println("Stop parse XML...");
        System.out.println("--------------------------");
    }
}