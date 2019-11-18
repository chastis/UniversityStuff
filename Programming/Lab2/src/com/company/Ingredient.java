package com.company;
public class Ingredient {
    private String name;
    private int count;

    Ingredient() {}
    Ingredient(String name, int count) {
        this.name = name;
        this.count = count;
    }
    public String getName() {
        return name;
    }
    public void setName(String name) {
        this.name = name;
    }
    public int getCount() {
        return count;
    }
    public void setCount(int count) {
        this.count = count;
    }
}