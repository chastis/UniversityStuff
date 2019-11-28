package Plane;

import java.util.Objects;

/**
 * Created by Chastis on 02.11.2019.
 */
public class Chars {
    private PlaneType type;
    private int seats;
    private boolean radar;

    public Chars() {
    }

    public Chars(PlaneType type, int seats, boolean radar) {
        this.type = type;
        this.seats = seats;
        this.radar = radar;
    }

    @Override
    public String toString() {
        return "{type: " + type
                + ", number of seats: " + seats
                + ", radar: " + (radar ? "yes" : "no")
                + '}';

    }

    @Override
    public boolean equals(Object o) {

        if (this == o) return true;

        if (!(o instanceof Chars)) {
            return false;
        }

        Chars chars = (Chars) o;
        return type == chars.getType()
                && seats == chars.getSeats()
                && radar == chars.isRadar();
    }


    public PlaneType getType() {
        return type;
    }

    public void setType(PlaneType type) {
        this.type = type;
    }

    public int getSeats() {
        return seats;
    }

    public void setSeats(int seats) {
        this.seats = seats;
    }

    public boolean isRadar() {
        return radar;
    }

    public void setRadar(boolean radar) {
        this.radar = radar;
    }
}
