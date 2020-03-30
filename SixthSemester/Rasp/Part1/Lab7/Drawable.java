import java.awt.Image;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;
import javax.swing.ImageIcon;

public class Drawable extends Component
{

    Drawable()
    {
        sprite = new ImageIcon().getImage();
    }

    public void InitDrawable(String path)
    {
        try
        {
            sprite = ImageIO.read(new File(path)).getScaledInstance(400, 300, 0);
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

    protected Image sprite;
}