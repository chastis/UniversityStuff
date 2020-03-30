
abstract class Component extends Object
{
    public Object GetOwner()
    {
        return owner;
    }

    public void Init(Object parent)
    {
        owner = parent;
    }

    public void Update()
    {}

    protected Object owner;
}