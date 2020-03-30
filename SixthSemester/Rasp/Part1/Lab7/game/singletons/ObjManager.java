package game.singletons;

import java.util.HashMap;
import game.Obj;

public class ObjManager
{
    private ObjManager()
    {
        gameObjects = new HashMap<>();
    }

    public static ObjManager instance()
    {
        if (instance == null)
        {
            instance = new ObjManager();
        }
        return instance;
    }
    
    public int register(Obj newObject)
    {
        final int newObjUID = UIDManager.instance().getNewUID();
        gameObjects.put(newObjUID, newObject);
        return newObjUID;
    }

    public Obj getObjByUID(int UID)
    {
        return gameObjects.get(UID);
    }

    public void remove(Obj removeObject)
    {
        if (removeObject != null)
        {
            gameObjects.remove(removeObject.getUID());
        }
    }

    public void remove(int removeObjectUID)
    {
        gameObjects.remove(removeObjectUID);
    }

    private static ObjManager instance = null;
    private HashMap<Integer, Obj> gameObjects = null;
}