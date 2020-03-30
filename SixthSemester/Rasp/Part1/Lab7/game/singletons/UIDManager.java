package game.singletons;


public class UIDManager
{
    private UIDManager()
    {
        curentUID = 0;
    }

    public static UIDManager instance()
    {
        if (instance == null)
        {
            instance = new UIDManager();
        }
        return instance;
    }
    
    public int getNewUID()
    {
        return curentUID++;
    }

    private static UIDManager instance = null;
    private int curentUID;
}