package mygame;

import com.jme3.app.SimpleApplication;
import com.jme3.bullet.BulletAppState;
import com.jme3.font.BitmapText;
import com.jme3.input.MouseInput;
import com.jme3.input.controls.ActionListener;
import com.jme3.input.controls.MouseButtonTrigger;
import com.jme3.math.Vector3f;

/**
 *
 * @author Chastis
 */
public class Interface extends SimpleApplication {
    private BulletAppState bulletAppState;
    private Ball balls;
    private final static String FONT = "Interface/Fonts/Default.fnt";
  
    
    @Override
    public void simpleInitApp() {
      bulletAppState = new BulletAppState();
     // bulletAppState.setDebugEnabled(true);
      stateManager.attach(bulletAppState);

      cam.setLocation(new Vector3f(0, 10f, 20f));
      cam.lookAt(new Vector3f(0, 0, -10), Vector3f.UNIT_Y);
      
      Floor floor = new Floor(assetManager, rootNode, bulletAppState);
      balls = new Ball(assetManager, rootNode, bulletAppState);

      inputManager.addMapping("create", 
              new MouseButtonTrigger(MouseInput.BUTTON_LEFT));
      inputManager.addListener(actionListener, "create");    
      inputManager.addMapping("move", 
              new MouseButtonTrigger(MouseInput.BUTTON_RIGHT));
      inputManager.addListener(actionListener, "move");
      
      initCrossHairs();
    }
   
    
    private final ActionListener actionListener = new ActionListener() {
      @Override
      public void onAction(String name, boolean keyPressed, float tpf) {
          if (name.equals("create") && !keyPressed) {
          balls.createBall(cam);
          }
          if (name.equals("move") && !keyPressed) {
             balls.move(cam);
          }
      }
    };

    
    private void initCrossHairs() {
      guiNode.detachAllChildren();
      guiFont = assetManager.loadFont(FONT);
      BitmapText ch = new BitmapText(guiFont, false);
      ch.setSize(guiFont.getCharSet().getRenderedSize() * 2);
      ch.setText("+");        
      ch.setLocalTranslation( 
          settings.getWidth() / 2 - guiFont.getCharSet().getRenderedSize() / 3 * 2,
          settings.getHeight() / 2 + ch.getLineHeight() / 2, 0);
      guiNode.attachChild(ch);
    }

}
