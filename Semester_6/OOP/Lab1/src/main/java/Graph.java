import javafx.geometry.Point3D;

import java.util.*;


public class Graph {
    private final List<Vertex> vertexes;
    private final List<Edge> edges;

    public Graph() {
        vertexes = new ArrayList<Vertex>();
        edges = new ArrayList<Edge>();

        vertexes.add(new Vertex(-25, 30, 5, 0, "Node_0"));
        vertexes.add(new Vertex(10, 20, 30, 1, "Node_1"));
        vertexes.add(new Vertex(-10, 40, 35, 2, "Node2"));
        vertexes.add(new Vertex(20, -15, -20, 3, "Node3"));
        vertexes.add(new Vertex(35, -30, -15, 4, "Node4"));
        vertexes.add(new Vertex(-35, 40, -25, 5, "Node5"));
        vertexes.add(new Vertex(-25, 10, -15, 6, "Node6"));
        vertexes.add(new Vertex(55, -20, 50, 7, "Node7"));
        vertexes.add(new Vertex(25, 15, -50, 8, "Node8"));
        vertexes.add(new Vertex(30, 30, 15, 9, "Node9"));
        vertexes.add(new Vertex(-20, -30, 20, 10, "Node10"));


        addLane("Edge_0", 0, 1);
        addLane("Edge_1", 0, 2);
        addLane("Edge_2", 0, 4);
        addLane("Edge_3", 2, 6);
        addLane("Edge_4", 2, 7);
        addLane("Edge_5", 3, 7);
        addLane("Edge_6", 5, 8);
        addLane("Edge_7", 8, 9);
        addLane("Edge_8", 7, 9);
        addLane("Edge_9", 4, 9);
        addLane("Edge_10", 9, 10);
        addLane("Edge_11", 1, 10);
    }

    public Graph(List<Vertex> vertexes, List<Edge> edges) {
        this.vertexes = vertexes;
        this.edges = edges;
    }

    public List<Vertex> getVertexes() {
        return vertexes;
    }

    public List<Edge> getEdges() {
        return edges;
    }

    private void addLane(String laneId, int sourceLocNo, int destLocNo) {
        Edge lane = new Edge(laneId, vertexes.get(sourceLocNo), vertexes.get(destLocNo));
        edges.add(lane);
        lane = new Edge(laneId, vertexes.get(destLocNo), vertexes.get(sourceLocNo));
        edges.add(lane);
    }
}
