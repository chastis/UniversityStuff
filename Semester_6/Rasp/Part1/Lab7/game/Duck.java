package game;

import game.components.AI;

public class Duck extends Obj {
    public Duck() {
        super();
        AI componentAI = new AI();
        addComponent(componentAI);
        componentAI.initDefaultAI();
    }

    @Override
    public Const.EObjType getObjType()
    {
        return Const.EObjType.Duck;
    }
}