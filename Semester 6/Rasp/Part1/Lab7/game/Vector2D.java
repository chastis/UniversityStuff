package game;

public class Vector2D
{
    public int x;
    public int y;

    public static Vector2D ZeroVector = new Vector2D(0, 0);

    public Vector2D()
    {
        x = y = 0;
    }
    public Vector2D(int inX, int inY)
    {
        x = inX;
        y = inY;
    }
    
    public double size()
    {
        return Math.sqrt(x * x + y * y);
    }

    public int sizeSqr()
    {
        return x * x + y * y;
    }

    public Vector2D rotate(int angle)
    {
        // https://stackoverflow.com/questions/4780119/2d-euclidean-vector-rotations
        final double rad = Math.toRadians(angle);
        final double cs = Math.cos(rad);
        final double sn = Math.sin(rad);
        int newX = (int) Math.round(x * cs - y * sn);
        int newY = (int) Math.round(x * sn + y * cs);
        return new Vector2D(newX, newY);
    }

    public Vector2D multiply(int n)
    {
        return new Vector2D(x*n, y*n);
    }

    public Vector2D plus(Vector2D a)
    {
        return new Vector2D(x + a.x, y + a.y);
    }

    public Vector2D minus(Vector2D a)
    {
        return new Vector2D(x - a.x, y - a.y);
    }

    public int dotProduct(Vector2D vector)
    {
        return x * vector.x + y * vector.y;
    }

    public Vector2D getReversed(Vector2D ZeroPoint)
    {
        return ZeroPoint.multiply(2).minus(this);
    }

    public Vector2D getReversed()
    {
        return getReversed(ZeroVector);
    }
}