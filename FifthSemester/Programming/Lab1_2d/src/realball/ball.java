package realball;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.geom.Ellipse2D;

public class ball {

    private float x;
    private float y;
    private float diametar;
    Color color;
    private double xSpeed;
    private double ySpeed;

    public ball(float x, float y, float diameter, Color color) {
        this.x = x;
        this.y = y;

        this.diametar = diameter;
        this.color = color;
    }

    public void draw(Graphics g) {
        Graphics2D g2d = (Graphics2D) g;
        Ellipse2D.Double circle = new Ellipse2D.Double(getX() - getDiametar() / 2, getY() - getDiametar() / 2, getDiametar(), getDiametar());
        g2d.fill(circle);
    }

    public void move() {
        setX((float) (getX() + getxSpeed()));

        if (getX() - getDiametar() / 2 < 0) {
            setX(getDiametar() / 2);
            setxSpeed(-getxSpeed());
        } else if (getX() + getDiametar() / 2 > 390) {
            setxSpeed(-getxSpeed());
        }

        setY((float) (getY() + getySpeed()));

        if (getY() - getDiametar() / 2 < 0) {
            setySpeed(-getySpeed());
        } else if (getY() + getDiametar() / 2 > 360) {
            setY(360 - getDiametar() / 2);
            setySpeed(-getySpeed());
        }
    }

    /**
     * @return the xSpeed
     */
    public double getxSpeed() {
        return xSpeed;
    }

    /**
     * @param xSpeed the xSpeed to set
     */
    public void setxSpeed(double xSpeed) {
        this.xSpeed = xSpeed;
    }

    /**
     * @return the ySpeed
     */
    public double getySpeed() {
        return ySpeed;
    }

    /**
     * @param ySpeed the ySpeed to set
     */
    public void setySpeed(double ySpeed) {
        this.ySpeed = ySpeed;
    }

    /**
     * @return the x
     */
    public float getX() {
        return x;
    }

    /**
     * @param x the x to set
     */
    public void setX(float x) {
        this.x = x;
    }

    /**
     * @return the y
     */
    public float getY() {
        return y;
    }

    /**
     * @param y the y to set
     */
    public void setY(float y) {
        this.y = y;
    }

    /**
     * @return the diametar
     */
    public float getDiametar() {
        return diametar;
    }

    /**
     * @param diameter
     */
    public void setDiametar(float diameter) {
        this.diametar = diameter;
    }
}