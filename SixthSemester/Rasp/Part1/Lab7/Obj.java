import java.util.ArrayList;

public class Obj
{
    Obj()
    {
        components = new ArrayList<>();
        Drawable drawable = new Drawable();
        Transform transform = new Transform();
        addComponent(drawable);
        addComponent(transform);
    }

    public void Update()
    {
        for (Component component : components)
        {
            component.Update();
        }
    }

    protected void addComponent(Component component)
    {
        if (component != null)
        {
            components.add(component);
            component.Init(this);
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

    protected ArrayList<Component> components;
}