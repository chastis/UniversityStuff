package entities;

public class Triangle {
    private int id;
    private Point p1;
    private Point p2;
    private Point p3;

    public Triangle(int id, Point p1, Point p2, Point p3) {
        this.id = id;
        this.p1 = p1;
        this.p2 = p2;
        this.p3 = p3;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public Point getP1() {
        return p1;
    }

    public void setP1(Point p1) {
        this.p1 = p1;
    }

    public Point getP2() {
        return p2;
    }

    public void setP2(Point p2) {
        this.p2 = p2;
    }

    public Point getP3() {
        return p3;
    }

    public void setP3(Point p3) {
        this.p3 = p3;
    }

    @Override
    public String toString() {
        return "Трикутник{" +
                "id=" + id +
                ", точка1=" + p1 +
                ", точка2=" + p2 +
                ", точка3=" + p3 +
                '}';
    }
}
