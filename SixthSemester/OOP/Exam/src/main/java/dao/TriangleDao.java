package dao;

import entities.Point;
import entities.Triangle;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

public class TriangleDao {
    public List<Triangle> findAll() throws SQLException, ClassNotFoundException {
        Connection conn = DBConnection.initDB();
        Statement statement = conn.createStatement();

        String sql = "select * from triangles";

        ResultSet rs = statement.executeQuery(sql);

        List<Triangle> triangles = new ArrayList<Triangle>();
        while (rs.next()){
            int id = rs.getInt("triangle_id");
            int p1_id = rs.getInt("p1_id");
            int p2_id = rs.getInt("p2_id");
            int p3_id = rs.getInt("p3_id");
            Point p1 = findPointById(p1_id);
            Point p2 = findPointById(p2_id);
            Point p3 = findPointById(p3_id);
            triangles.add(new Triangle(id, p1, p2, p3));
        }

        rs.close();
        conn.close();

        return triangles;
    }

    public Point findPointById(int id) throws SQLException, ClassNotFoundException {
        Connection conn = DBConnection.initDB();
        Statement statement = conn.createStatement();

        String sql = "select * from points where point_id="+id;

        ResultSet rs = statement.executeQuery(sql);

        Point point = null;
        if (rs.next()){
            int x = rs.getInt("x");
            int y = rs.getInt("y");
            point = new Point(id, x, y);
        }

        rs.close();
        conn.close();

        return point;
    }
}
