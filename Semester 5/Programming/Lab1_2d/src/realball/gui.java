package realball;

import java.awt.Color;
import java.awt.Graphics;
import javax.swing.JPanel;

public class gui extends JPanel implements Runnable {

    ball[] balls = new ball[10];
    boolean going = true;
    Thread animator;

    int ballsCount = 2;
    public gui() {
        balls[0] = new ball(50, 80, 40, Color.blue);
        balls[0].setX(50);
        balls[0].setY(80);
        balls[0].setxSpeed(4);
        balls[0].setySpeed(2);

        balls[1] = new ball(50, 80, 70, Color.blue);
        balls[1].setX(150);
        balls[1].setY(80);
        balls[1].setxSpeed(4);
        balls[1].setySpeed(2);

        animator = new Thread(this);
        animator.start();

    }

    @Override
    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        for (int i = 0; i < ballsCount; i++) {
            balls[i].draw(g);
        }

        g.setColor(Color.red);

    }

    @Override
    public void run() {
        while (going) {
            for (int i = 0; i < ballsCount; i++) {
                balls[i].move();
            }

            checkCollision();

            repaint();

            try {
                Thread.sleep(20);
            } catch (InterruptedException ex) {
            }
        }
    }

    public void checkCollision() {

        for (int i = 0; i < ballsCount; i++)
        {
            for (int j = 0; j < ballsCount; j++)
            {
                if (j == i)
                    break;
                ball b1 = balls[i];
                ball b2 = balls[j];

                float deltaX = Math.abs(b1.getX() - b2.getX());
                float deltaY = Math.abs(b1.getY() - b2.getY());
                float distance = deltaX * deltaX + deltaY * deltaY;

                if (distance < (b1.getDiametar() / 2 + b2.getDiametar() / 2) * (b1.getDiametar() / 2 + b2.getDiametar() / 2)) {

                    double newxSpeed1 = (b1.getxSpeed() * (b1.getDiametar() - b2.getDiametar()) + (2 * b2.getDiametar() * b2.getxSpeed())) / (b1.getDiametar()+b2.getDiametar());

                    double newxSpeed2 = (b2.getxSpeed() * (b2.getDiametar() - b1.getDiametar()) + (2 * b1.getDiametar() * b1.getxSpeed())) / (b1.getDiametar()+b2.getDiametar());

                    double newySpeed1 = (b1.getySpeed() * (b1.getDiametar() - b2.getDiametar()) + (2 * b2.getDiametar() * b2.getySpeed())) / (b1.getDiametar()+b2.getDiametar());

                    double newySpeed2 = (b2.getySpeed() * (b2.getDiametar() - b1.getDiametar()) + (2 * b1.getDiametar() * b1.getySpeed())) / (b1.getDiametar()+b2.getDiametar());

                    b2.setxSpeed(newxSpeed2);
                    b2.setySpeed(newySpeed2);
                    b1.setxSpeed(newxSpeed1);
                    b1.setySpeed(newySpeed1);

                }
            }
        }
    }

}