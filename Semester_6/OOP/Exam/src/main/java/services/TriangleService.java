package services;

import dao.TriangleDao;
import entities.Point;
import entities.Triangle;

import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class TriangleService {
    private TriangleDao dao = new TriangleDao();

    public Triangle findClosestSquare(double square) throws SQLException, ClassNotFoundException {
        List<Triangle> triangles = dao.findAll();

        Triangle closestSqTri = null;
        double sq_diff = Double.MAX_VALUE;
        for (Triangle triangle : triangles){
            double tri_sq = calcSquare(triangle.getP1(), triangle.getP2(), triangle.getP3());
            if (Math.abs(square - tri_sq) < sq_diff){
                closestSqTri = triangle;
                sq_diff = Math.abs(square - tri_sq);
            }
        }

        return closestSqTri;
    }

    public List<Triangle> findClosestSquareTrians(double square) throws SQLException, ClassNotFoundException {
        List<Triangle> triangles = dao.findAll();

        List<Integer> mainIndeces = new ArrayList<Integer>();
        double min_diff = Double.MAX_VALUE;
        for (int i = 0; i < triangles.size(); i++) {
            double sq_diff = square;
            List<Integer> indeces = new ArrayList<Integer>();
            for (int j = 0; j < triangles.size(); j++) {
                double tri_sq = calcSquare(triangles.get(j).getP1(), triangles.get(j).getP2(), triangles.get(j).getP3());
                if (sq_diff - tri_sq > 0){
                    indeces.add(j);
                    sq_diff -= tri_sq;
                } else break;
            }

            if (sq_diff < min_diff){
                min_diff = sq_diff;
                mainIndeces.addAll(indeces);
            }
        }

        List<Triangle> trianglesClosestSq = new ArrayList<Triangle>();
        for (int i = 0; i < mainIndeces.size(); i++) {
            triangles.add(triangles.get(i));
        }

        return trianglesClosestSq;
    }

    public List<Triangle> findTriansWithLessRadius(double radius) throws SQLException, ClassNotFoundException {
        List<Triangle> triangles = dao.findAll();

        List<Triangle> result = new ArrayList<Triangle>();
        for (Triangle triangle : triangles){
            double tri_radius = calcRadiusCircleTri(triangle.getP1(), triangle.getP2(), triangle.getP3());
            if (tri_radius < radius){
                result.add(triangle);
            }
        }

        return result;
    }

    private double calcRadiusCircleTri(Point p1, Point p2, Point p3){
        double line1 = calcLineLength(p1, p2);
        double line2 = calcLineLength(p2, p3);
        double line3 = calcLineLength(p1, p2);
        double halfP = (line1 + line2 + line3) / 2;

        return (line1 * line2 * line3) / (4 * Math.sqrt(halfP * (halfP - line1) * (halfP - line2) * (halfP - line3)));
    }

    private double calcSquare(Point p1, Point p2, Point p3){
        double line1 = calcLineLength(p1, p2);
        double line2 = calcLineLength(p2, p3);
        double line3 = calcLineLength(p1, p2);
        double halfP = (line1 + line2 + line3) / 2;

        return Math.sqrt(halfP * (halfP - line1) * (halfP - line2) * (halfP - line3));

    }

    private double calcLineLength(Point p1, Point p2){
        return Math.sqrt(Math.pow(p2.getX() - p1.getX(), 2) + Math.pow(p2.getY() - p1.getY(), 2));
    }
}
