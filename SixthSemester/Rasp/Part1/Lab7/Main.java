import java.awt.*;

import javax.swing.JFrame; 

public class Main extends JFrame
{

    Main()
    {
        Render r = new Render();
        Obj duck = new Obj();
        Drawable drawable = duck.getComponent(Drawable.class);
        if (drawable!=null)
        {
            drawable.InitDrawable("Content/duck.png");
        }
        r.addObject(duck);
        add(r);
        setTitle("g a v n o");
        setSize(1000, 1000);
        setLocationRelativeTo(null);
        //setResizable(false);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
    public static void main(String[] args)
    {
        EventQueue.invokeLater(() -> {
            Main ex = new Main();
            ex.setVisible(true);
        });
    }
}

// continue up here
// http://zetcode.com/tutorials/javagamestutorial/movingsprites/
// http://zetcode.com/tutorials/javagamestutorial/