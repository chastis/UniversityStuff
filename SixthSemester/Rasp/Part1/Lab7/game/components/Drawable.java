package game.components;

import java.awt.Image;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;
import javax.swing.ImageIcon;

public class Drawable extends Component
{

    public Drawable()
    {
        sprite = new ImageIcon().getImage();
    }

    public void initDrawable(String path, int width, int height)
    {
        try
        {
            sprite = ImageIO.read(new File(path)).getScaledInstance(width, height, 0);
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
    }

    public Image getSprite()
    {
        return sprite;
    }

    public int getSpriteHeight()
    {
        return sprite.getHeight(null);
    }

    public int getSpriteWitdh()
    {
        return sprite.getWidth(null);
    }

    protected Image sprite;
}