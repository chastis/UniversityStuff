package game;

import java.awt.*;
import javax.swing.JPanel;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.Timer;
import game.components.*;
import game.singletons.GameManager;

public class Render extends JPanel implements ActionListener
{  

    public Render()
    {
        timer = new Timer(Const.Delay, this);
        timer.start();
    }
    
    @Override
    public void paintComponent(Graphics g)
    {
        super.paintComponent(g);

        Graphics2D g2d = (Graphics2D) g;

        for (Obj obj : GameManager.instance().getGameMap().getGameObjects())
        {
            Drawable drawable = obj.getComponent(Drawable.class);
            Transform transform = obj.getComponent(Transform.class);
            if (drawable!=null && transform!=null)
            {
                g2d.drawImage(drawable.getSprite(), transform.getCoordinates().x, transform.getCoordinates().y, this);
            }
        }
        Toolkit.getDefaultToolkit().sync();
    }

    @Override
    public void actionPerformed(ActionEvent e)
    {
        for (Obj obj : GameManager.instance().getGameMap().getGameObjects())
        {
            obj.update();
        }

        repaint();
    }
    
    private Timer timer;
    private static final long serialVersionUID = 2L;
}