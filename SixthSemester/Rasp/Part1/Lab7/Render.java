import java.awt.*;
import java.util.ArrayList;

import javax.swing.JPanel;  

public class Render extends JPanel
{  

    Render()
    {
        renderObjects = new ArrayList<>();
    }
    
    @Override
    public void paintComponent(Graphics g) {
        super.paintComponent(g);

        Graphics2D g2d = (Graphics2D) g;

        for (Obj obj : renderObjects)
        {
            Drawable drawable = obj.getComponent(Drawable.class);
            Transform transform = obj.getComponent(Transform.class);
            if (drawable!=null && transform!=null)
            {
                g2d.drawImage(drawable.getSprite(), transform.getCoordinates().x, transform.getCoordinates().y, this);
            }
        }
        //Toolkit.getDefaultToolkit().sync();
    }
    
    public void addObject(Obj newObject)
    {
        renderObjects.add(newObject);
    }

    private ArrayList<Obj> renderObjects;
}