package com.company;
import java.io.*;
import java.util.*;

import javax.xml.parsers.*;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;



public class DOMPars {
    private DocumentBuilderFactory f; //(1)
    private DocumentBuilder builder;
    private Document doc; // (2)
    private List <Candy> res = new ArrayList<Candy>();
    private Candy curr = new Candy();

    DOMPars(String name) {
        tryRead(name);
    }

    private void tryRead(String name) {
        try {
            f = DocumentBuilderFactory.newInstance(); //(1) Для того, чтобы загрузить структуру создается объект класса DocumentBuilder
            f.setValidating(false);
            builder = f.newDocumentBuilder();
            doc = builder.parse(new File(name)); //загружается XML и разбирается, получая объект Document - doc //(2)
        } catch (ParserConfigurationException e) {
            System.out.println("Parser Configuration Exception!");
        } catch (SAXException e) {
            System.out.println("SAXException!");
        } catch (IOException e) {
            System.out.println("Can't find such a file!");
        }
    }

    public void parse() { //«обход» дерева, используя методы, которые предоставляют стандартные объекты DOM — Node, NodeList
        // Candy list
        NodeList candyList = doc.getDocumentElement().getChildNodes();
        for(int m = 0; m < candyList.getLength(); m++) { // Просматриваем все подэлементы корневого
            Node tempCandy = candyList.item(m);
            if (tempCandy instanceof Element && tempCandy.getNodeName().equals("Candy")) {
                curr = new Candy();
                curr.setName(tempCandy.getAttributes().getNamedItem("name").getNodeValue());
                if(tempCandy.getAttributes().getNamedItem("filled") != null) {
                    if(Boolean.valueOf(tempCandy.getAttributes().getNamedItem("filled").getNodeValue()) == true) {
                        curr.setFilled(true);
                    } else {
                        curr.setFilled(false);
                    }
                }
                // List of candy fields
                NodeList nodeList = candyList.item(m).getChildNodes();
                for (int i = 0; i < nodeList.getLength(); i++) {
                    Node temp = nodeList.item(i);
                    if (temp instanceof Element) {

                        switch (temp.getNodeName()) {
                            case "Energy":
                                curr.setEnergy(new Integer(temp.getLastChild().getTextContent()));
                                break;
                            case "Type":
                                curr.setType(temp.getLastChild().getTextContent());
                                break;
                            case "Production":
                                curr.setProduction(temp.getLastChild().getTextContent());
                                break;
                            case "Value":
                                NodeList valueNodes = nodeList.item(i).getChildNodes();
                                for (int j = 0; j < valueNodes.getLength(); j++) {
                                    Node temp2 = valueNodes.item(j);
                                    if (temp2 instanceof Element) {
                                        if(temp2.getNodeName().equals("Proteins"))
                                            curr.setProteins(new Integer(temp2.getLastChild().getTextContent()));

                                        if(temp2.getNodeName().equals("Fats"))
                                            curr.setFats(new Integer(temp2.getLastChild().getTextContent()));

                                        if(temp2.getNodeName().equals("Carbohydrates"))
                                            curr.setCarbohydrates(new Integer(temp2.getLastChild().getTextContent()));
                                    }
                                }
                                break;
                            case "Ingredients":
                                NodeList ingredientsNodes = nodeList.item(i).getChildNodes();
                                for (int j = 0; j < ingredientsNodes.getLength(); j++) {
                                    Node temp2 = ingredientsNodes.item(j);
                                    if (temp2 instanceof Element && temp2.getNodeName().equals("Ingredient")) {
                                        Ingredient ingrTemp = new Ingredient();
                                        NodeList ingredientNodes = ingredientsNodes.item(j).getChildNodes();
                                        for (int k = 0; k < ingredientNodes.getLength(); k++) {
                                            Node temp3 = ingredientNodes.item(k);
                                            if (temp3 instanceof Element) {
                                                if(temp3.getNodeName().equals("Name"))
                                                    ingrTemp.setName(temp3.getLastChild().getTextContent());

                                                if(temp3.getNodeName().equals("Count"))
                                                    ingrTemp.setCount(new Integer(temp3.getLastChild().getTextContent()));
                                            }
                                        }
                                        curr.addIngredient(ingrTemp);
                                    }
                                }
                                break;
                        }
                    }
                }
                res.add(curr);
            }
        }


    }

    public List<Candy> getCandies() {
        return res;
    }
}