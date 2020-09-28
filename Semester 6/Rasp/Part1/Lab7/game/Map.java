package game;

import java.util.ArrayList;
import game.components.*;

public class Map 
{
    public Map()
    {
        gameObjects = new ArrayList<>();
        mapSize = new Vector2D();
    }

    public void initDefaultMap()
    {
        mapSize = new Vector2D(Const.GameWidth, Const.GameHeight);
        
        for (int i = 0; i < 2; i++)
        {
            Obj duck = new Duck();
            gameObjects.add(duck);
            Drawable drawable = duck.getComponent(Drawable.class);
            if (drawable!=null)
            {
                drawable.initDrawable("Content/duck.png", 150, 150);
            }
            Transform transform = duck.getComponent(Transform.class);
            if (transform!=null)
            {
                transform.initTransform(new Vector2D(150 * i, 150 * i));
            }
        }
    }

    public ArrayList<Obj> getGameObjects()
    {
        return gameObjects;
    }

    public Vector2D getMapSize()
    {
        return mapSize;
    }

    private ArrayList<Obj> gameObjects;
    Vector2D mapSize;
}