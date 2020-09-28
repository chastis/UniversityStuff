package game.components;

import game.Obj;

public abstract class Component
{
    public Obj getOwner()
    {
        return componentOwner;
    }

    public void init(Obj parent)
    {
        componentOwner = parent;
    }

    public void update()
    {}

    protected Obj componentOwner;
}