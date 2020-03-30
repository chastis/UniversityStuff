package game.components;

import java.util.Random;

import game.Const;
import game.Obj;
import game.Vector2D;

public class AI extends Component
{
    public AI()
    {
        speed = new Vector2D(1, 0);
    }

    public void initDefaultAI()
    {
        Random random = new Random();
        speed = new Vector2D(1, 0);
        speed = speed.multiply(random.nextInt(Const.MaxDuckSpeed)+1);
        updateSpeed();
    }

    @Override
    public void update()
    {
        Obj owner = getOwner();
        Transform transform = owner.getComponent(Transform.class);
        if (transform != null)
        {
            updateSpeed();
            transform.move(speed);
        }
        if (speed.sizeSqr()==0 && Const.isChangeGood(Const.EChance.Medium));
        {

        }
    }
    
    private void updateSpeed()
    {
        Random random = new Random();
        int angle = random.nextInt(Const.MaxDegreesAIDispersion*2+1)-Const.MaxDegreesAIDispersion;
        speed = speed.rotate(angle);
    }
    
    private Vector2D speed;
}