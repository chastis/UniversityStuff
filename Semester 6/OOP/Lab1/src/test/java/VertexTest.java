import javafx.geometry.Point3D;
import org.junit.Test;

import static org.junit.Assert.*;

public class VertexTest {
    private final int x = 1, y = 1, z = 1, id = 1;
    private final String name = "vertex";

    private final Vertex vertex = new Vertex(x, y, z, id, name);
    private final Vertex pointVertex = new Vertex(new Point3D(x, y, z), id, name);

    private final Vertex destination = new Vertex(2, 2, 2, 2, "name");
    private final int distance = (int) Math.sqrt(2.0);

    @Test
    public void toPoint() {
        assertEquals(distance, vertex.toPoint(destination));
        assertEquals(distance, destination.toPoint(vertex));

        assertEquals(distance, pointVertex.toPoint(destination));
        assertEquals(distance, destination.toPoint(pointVertex));

        assertEquals(0, pointVertex.toPoint(vertex));
        assertEquals(0, vertex.toPoint(pointVertex));
        assertEquals(0, vertex.toPoint(vertex));
        assertEquals(0, pointVertex.toPoint(pointVertex));
    }

    @Test
    public void getId() {
        assertEquals(id, vertex.getId());
        assertEquals(id, pointVertex.getId());
    }

    @Test
    public void getName() {
        assertEquals(name, vertex.getName());
        assertEquals(name, pointVertex.getName());
    }

    @Test
    public void testEquals() {
        Vertex testVertex = new Vertex(x, y, z, id + 1, name);

        assertNotEquals(testVertex, vertex);
        assertNotEquals(testVertex, pointVertex);
        assertNotEquals(vertex, testVertex);
        assertNotEquals(pointVertex, testVertex);

        assertNotEquals(new Object(), vertex);
        assertNotEquals(new Object(), pointVertex);
        assertNotEquals(vertex, new Object());
        assertNotEquals(pointVertex, new Object());

        assertNotEquals(null, vertex);
        assertNotEquals(null, pointVertex);
        assertNotEquals(vertex, null);
        assertNotEquals(pointVertex, null);

        assertEquals(vertex, pointVertex);
        assertEquals(pointVertex, vertex);
    }

    @Test
    public void testToString() {
        assertEquals(name, vertex.toString());
        assertEquals(name, pointVertex.toString());
    }

    @Test
    public void getP() {
        assertEquals(new Point3D(x, y, z), vertex.getP());
        assertEquals(new Point3D(x, y, z), pointVertex.getP());
    }
}