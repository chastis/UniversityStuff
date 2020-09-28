import org.junit.Test;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import static org.junit.Assert.*;

public class GraphTest {
    private final Vertex vertexFrom = new Vertex(1, 1, 1, 1, "vertex");
    private final Vertex vertexTo = new Vertex(2, 2, 2, 2, "edge");

    private final Edge edge = new Edge("1", vertexFrom, vertexTo);

    private final List<Vertex> vertexList = Arrays.asList(vertexFrom, vertexTo);
    private final List<Edge> edgeList = Arrays.asList(edge);

    private final Graph defaultGraph = new Graph();
    private final Graph filledGraph = new Graph(vertexList, edgeList);


    @Test
    public void getVertexes() {
        assertNotNull(this.defaultGraph.getVertexes());
        assertFalse(this.defaultGraph.getVertexes().isEmpty());

        assertNotNull(this.filledGraph.getVertexes());
        assertFalse(this.filledGraph.getVertexes().isEmpty());
        assertEquals(vertexList.size(), filledGraph.getVertexes().size());
        assertEquals(vertexFrom, filledGraph.getVertexes().get(0));
        assertEquals(vertexTo, filledGraph.getVertexes().get(1));
    }

    @Test
    public void getEdges() {
        assertNotNull(this.defaultGraph.getEdges());
        assertFalse(this.defaultGraph.getEdges().isEmpty());

        assertNotNull(this.filledGraph.getEdges());
        assertFalse(this.filledGraph.getEdges().isEmpty());
        assertEquals(edgeList.size(), filledGraph.getEdges().size());
        assertEquals(edge, filledGraph.getEdges().get(0));
    }
}