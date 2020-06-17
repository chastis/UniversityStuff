import entities.Triangle;
import services.TriangleService;

import java.sql.SQLException;
import java.util.List;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws SQLException, ClassNotFoundException {
		/** Варіант №3, Завдання №1 */
		
        Scanner scanner = new Scanner(System.in);
        TriangleService service = new TriangleService();

        System.out.println("Введіть площу: ");
        double square1 = scanner.nextDouble();
        Triangle triangle1 = service.findClosestSquare(square1);
        System.out.println("Трикутник, площа якого найбільш наближена до площі " + square1 + ": " + triangle1);
        System.out.println();

        System.out.println("Введіть площу: ");
        double square2 = scanner.nextDouble();
        List<Triangle> triangles2 = service.findClosestSquareTrians(square2);
        System.out.println("Трикутники, сума площ яких найбільш наближена до площі " + square2 + ":");
        for (Triangle triangle : triangles2){
            System.out.println(triangle);
        }
        System.out.println();

        System.out.println("Введіть радіус: ");
        double radius = scanner.nextDouble();
        List<Triangle> triangles3 = service.findTriansWithLessRadius(radius);
        System.out.println("Трикутники, які поміщаються в окружність з радіусом " + radius + ":");
        for (Triangle triangle : triangles3){
            System.out.println(triangle);
        }
    }
}
