package game.components;

import game.Vector2D;

public class Transform extends Component
{
    public Transform()
    {
        coordinates = new Vector2D();
        coordinates.x = 0;
        coordinates.y = 0;
    }

    public void move(Vector2D vector)
    {
        coordinates.x = coordinates.x + vector.x;
        coordinates.y = coordinates.y + vector.y;
    }

    public void initTransform(Vector2D start)
    {
        coordinates = start;
    }

    public Vector2D getCoordinates()
    {
        return coordinates;
    }

    protected Vector2D coordinates;
}