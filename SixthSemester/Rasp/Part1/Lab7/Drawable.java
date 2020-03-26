import java.awt.Image;
import java.awt.Point;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;

public class Drawable
{
    public void Init(String path)
    {
        try
        {
            sprite = ImageIO.read(new File(path));
        }
        catch (IOException e)
        {
            sprite = null;
            e.printStackTrace();
        }
        coordinates = null;
    }
    public Image getSprite()
    {
        return sprite;
    }
    public Point getCoordinates()
    {
        return coordinates;
    }


    protected Image sprite;
    protected Point coordinates;
}