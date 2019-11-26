package com.company;
import java.util.ArrayList;

public class Candy {  //класс - соответствующий описанию
    private String name, type;
    private boolean filled;
    private int energy;
    private String production;
    private ArrayList<Ingredient> ingredients = new ArrayList<Ingredient>();
    private int proteins, fats, carbohydrates;

    public String getName() {
        return name;
    }
    public void setName(String name) {
        this.name = name;
    }
    public String getType() {
        return type;
    }
    public void setType(String type) {
        this.type = type;
    }
    public boolean isFilled() {
        return filled;
    }
    public void setFilled(boolean filled) {
        this.filled = filled;
    }
    public int getEnergy() {
        return energy;
    }
    public void setEnergy(int energy) {
        this.energy = energy;
    }
    public String getProduction() {
        return production;
    }
    public void setProduction(String production) {
        this.production = production;
    }
    public ArrayList<Ingredient> getIngredients() {
        return ingredients;
    }
    public void addIngredient(Ingredient temp) {
        ingredients.add(temp);
    }
    public int getProteins() {
        return proteins;
    }
    public void setProteins(int proteins) {
        this.proteins = proteins;
    }
    public int getFats() {
        return fats;
    }
    public void setFats(int fats) {
        this.fats = fats;
    }
    public int getCarbohydrates() {
        return carbohydrates;
    }
    public void setCarbohydrates(int carbohydrates) {
        this.carbohydrates = carbohydrates;
    }

    @Override
    public String toString() {
        String temp = "Candy: " + name + "\nFilled: " + filled + "\nType: " + type + "\nEnergy: " + energy + "\nProduction: " +
                production + "\nIngredients:\n";
        for(int i = 0; i < ingredients.size(); ++i) {
            temp = temp + "\t- " + ingredients.get(i).getName() + ": " + ingredients.get(i).getCount() + "\n";
        }
        temp = temp + "Value:\n\t- Proteins: " + proteins + "\n\t- Fats: " + fats + "\n\t- Carbohydrates: " + carbohydrates;
        return temp;
    }
}