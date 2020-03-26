import java.awt.*;
import java.util.ArrayList;  

public class Render extends Canvas
{  
      
    public void paint(Graphics graphics)
    {  
        for (Drawable drawable : renderObjects)
        {
            graphics.drawImage(drawable.getSprite(), drawable.getCoordinates().x, drawable.getCoordinates().y, null);
        }
        g.drawString("Hello",40,40);  
        setBackground(Color.WHITE);  
        g.fillRect(130, 30,100, 80);  
        g.drawOval(30,130,50, 60);  
        setForeground(Color.RED);  
        g.fillOval(130,130,50, 60);  
        g.drawArc(30, 200, 40,50,90,60);  
        g.fillArc(30, 130, 40,50,180,40);  
          
    } 
  
    ArrayList<Drawable> renderObjects;
}