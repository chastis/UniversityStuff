import javafx.geometry.Point3D;

public class Vertex {
    final private int id;
    final private String name;
    final public Point3D p;

    public Vertex(int x, int y, int z, int id, String name) {
        p = new Point3D(x, y, z);
        this.id = id;
        this.name = name;
    }

    public Vertex(Point3D p, int id, String name) {
        this.p = p;
        this.id = id;
        this.name = name;
    }

    public int toPoint(Vertex v) {
        return (int) p.distance(v.p);
    }

    public int getId() {
        return id;
    }

    public String getName() {
        return name;
    }


    @Override
    public boolean equals(Object obj) {
        if (this == obj)
            return true;
        if (obj == null)
            return false;
        if (getClass() != obj.getClass())
            return false;
        Vertex other = (Vertex) obj;
        return id == other.id;
    }

    @Override
    public String toString() {
        return name;
    }

    public Point3D getP() {
        return p;
    }

}
