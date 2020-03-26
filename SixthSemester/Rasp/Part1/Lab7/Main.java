import javax.swing.JFrame; 

public class Main
{
    public static void main(String[] args)
    {
        RenderTarget m=new RenderTarget();  
        JFrame f=new JFrame();  
        f.add(m);  
        f.setSize(400,400);  
        //f.setLayout(null);  
        f.setVisible(true); 
    }
}