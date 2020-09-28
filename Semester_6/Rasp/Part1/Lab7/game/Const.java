package game;

import java.util.Random;

public class Const
{
    public static int GameWidth = 800;
    public static int GameHeight = 600;
    public static int Delay = 42;
    public static int MaxDuckSpeed = 4;
    public static int MaxDegreesAIDispersion = 30;
    public static double SmallValue = 0.01;

    public static enum EObjType
    {
        Duck,
        Player,
        None
    }
    
    public static enum EChance
    {
        Small,
        Medium,
        Often
    }


    public static boolean isChangeGood(EChance chance)
    {
        Random random = new Random();
        boolean good = false;
        switch (chance)
        {
            case Small:
            {
                if (random.nextInt(101)>=75)
                {
                    good = true;
                }
                break;
            }
            case Medium:
            {
                if (random.nextInt(101)>=50)
                {
                    good = true;
                }
                break;
            }
            case Often:
            {
                if (random.nextInt(101)>=25)
                {
                    good = true;
                }
                break;
            }
        }
        return good;
    }
}

