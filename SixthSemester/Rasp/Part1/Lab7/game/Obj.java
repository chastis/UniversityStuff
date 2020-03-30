package game;

import game.Const.EObjType;
import game.components.*;
import game.singletons.ObjManager;
import java.util.ArrayList;

public class Obj implements ObjType {
    public Obj() {
        UID = ObjManager.instance().register(this);
        components = new ArrayList<>();
        Drawable drawable = new Drawable();
        Transform transform = new Transform();
        addComponent(drawable);
        addComponent(transform);
    }

    @Override
    public EObjType getObjType()
    {
        return Const.EObjType.None;
    }

    @Override
    public int getUID()
    {
        return UID;
    }

    public void update()
    {
        for (Component component : components)
        {
            component.update();
        }
    }

    public void addComponent(Component component)
    {
        if (component != null)
        {
            components.add(component);
            component.init(this);
        }
    }

    public <T extends Component> T getComponent(Class<T> type)
    {
        for (Component component : components)
        {
            if (type.isInstance(component))
            {
                return type.cast(component);
            }
        }

        return null;
    }

    public void kill()
    {
        ObjManager.instance().remove(UID);
    }

    protected ArrayList<Component> components;
    protected int UID;

}