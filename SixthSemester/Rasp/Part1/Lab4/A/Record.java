package base_package;

public class Record {
    private String name;
    private String surname;
    private String father;
    private String number;

    public Record(String name, String surname, String father, String number) {
        this.name = name;
        this.surname = surname;
        this.father = father;
        this.number = number;
    }

    public String getName() {
        return name;
    }
    public String getSurname() {
        return surname;
    }
    public String getFather() {
        return father;
    }
    public String getNumber() {
        return number;
    }

    public void setName(String name) {
        this.name = name;
    }
    public void setSurname(String surname) {
        this.surname = surname;
    }
    public void setFather(String father) {
        this.father = father;
    }
    public void setNumber(String number) {
        this.number = number;
    }

    @Override
    public String toString() {
        return "Name: " + name + ", Surname: " + surname + ", Father: " + father + ", Phone: " + number + "\n";
    }
}
