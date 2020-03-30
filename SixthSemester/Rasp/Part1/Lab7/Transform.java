import java.awt.Point;

public class Transform extends Component
{
    Transform()
    {
        coordinates = new Point();
        coordinates.x = 0;
        coordinates.y = 0;
    }

    public void Move(Point vector)
    {
        coordinates.x = coordinates.x + vector.x;
        coordinates.y = coordinates.y + vector.y;
    }

    public Point getCoordinates()
    {
        return coordinates;
    }
    
   protected Point coordinates;
}