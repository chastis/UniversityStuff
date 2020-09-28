package game.singletons;

import game.*;

public class GameManager
{
    private GameManager()
    {
        currentMap = new Map();
    }

    public static GameManager instance()
    {
        if (instance == null)
        {
            instance = new GameManager();
        }
        return instance;
    }
    
    public void initDefaultGame()
    {
        currentMap.initDefaultMap();
    }

    public Map getGameMap()
    {
        return currentMap;
    }

    private static GameManager instance = null;
    private Map currentMap;
}