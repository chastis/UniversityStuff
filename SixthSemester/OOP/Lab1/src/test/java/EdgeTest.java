import org.junit.Test;

import static org.junit.Assert.*;

public class EdgeTest {
    private final Vertex source = new Vertex(1, 1, 1, 1, "source");
    private final Vertex destination = new Vertex(2, 2, 2, 2, "destination");

    private final String id = "edge";

    private final Edge edge = new Edge(id, source, destination);

    @Test
    public void getId() {
        assertEquals(id, edge.getId());
    }

    @Test
    public void getDestination() {
        assertEquals(destination, edge.getDestination());
    }

    @Test
    public void getSource() {
        assertEquals(source, edge.getSource());
    }

    @Test
    public void getWeight() {
        assertEquals(source.toPoint(destination), edge.getWeight());
    }

    @Test
    public void testToString() {
        assertEquals(source + " " + destination, edge.toString());
    }
}