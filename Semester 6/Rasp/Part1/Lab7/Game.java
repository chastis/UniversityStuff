import java.awt.*;
import javax.swing.JFrame;
import game.*;
import game.singletons.GameManager;

public class Game extends JFrame
{
    public Game()
    {
        GameManager.instance().initDefaultGame();

        Render render = new Render();
        add(render);
        setTitle("s m o r q");
        setSize(GameManager.instance().getGameMap().getMapSize().x, GameManager.instance().getGameMap().getMapSize().y);
        setLocationRelativeTo(null);
        //setResizable(false);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    public void launch()
    {
        EventQueue.invokeLater(
        () -> {
            setVisible(true);
        });
    }


    private static final long serialVersionUID = 1L;
}