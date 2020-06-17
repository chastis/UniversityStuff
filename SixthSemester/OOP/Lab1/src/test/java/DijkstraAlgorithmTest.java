import org.junit.Test;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import static org.junit.Assert.*;

public class DijkstraAlgorithmTest {
    private final List<Vertex> vertexList = Arrays.asList(
            new Vertex(1, 1, 1, 1, "vertex 1"),
            new Vertex(2, 2, 2, 2, "vertex 2"),
            new Vertex(3, 3, 3, 3, "vertex 3"),
            new Vertex(0, 4, 4, 4, "vertex 4"));
    private final List<Edge> edgesList = Arrays.asList(
            new Edge("edge 1", vertexList.get(0), vertexList.get(1)),
            new Edge("edge 1", vertexList.get(1), vertexList.get(2)),
            new Edge("edge 1", vertexList.get(0), vertexList.get(3)),
            new Edge("edge 1", vertexList.get(3), vertexList.get(2))
    );

    private final Graph graph = new Graph(vertexList, edgesList);
    private final Graph emptyGraph = new Graph(new ArrayList<Vertex>(), new ArrayList<Edge>());

    private final List<Vertex> path = Arrays.asList(
            new Vertex(1, 1, 1, 1, "vertex 1"),
            new Vertex(2, 2, 2, 2, "vertex 2"),
            new Vertex(3, 3, 3, 3, "vertex 3")
    );

    private final DijkstraAlgorithm dijkstraAlgorithm = new DijkstraAlgorithm(graph);
    private final DijkstraAlgorithm emptyDijkstraAlgorithm = new DijkstraAlgorithm(emptyGraph);

    @Test
    public void getPath() {
        assertNull(emptyDijkstraAlgorithm.getPath(new Vertex(0, 0, 0, 0, "vertex")));

        emptyDijkstraAlgorithm.setEdges(graph);
        dijkstraAlgorithm.execute(vertexList.get(0));
        emptyDijkstraAlgorithm.execute(vertexList.get(0));

        assertEquals(path, dijkstraAlgorithm.getPath(vertexList.get(2)));
        assertEquals(path, emptyDijkstraAlgorithm.getPath(vertexList.get(2)));
        assertEquals(dijkstraAlgorithm.getPath(vertexList.get(2)), emptyDijkstraAlgorithm.getPath(vertexList.get(2)));
    }
}