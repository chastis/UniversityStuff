/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package mygame;

import com.jme3.bullet.control.RigidBodyControl;
import com.jme3.math.Vector3f;
import com.jme3.renderer.Camera;
import org.junit.Test;
import static org.junit.Assert.*;
import org.mockito.Mockito;


/**
 *
 * @author Chastis
 */
public class UnitTest {
    
    Camera camera;
    RigidBodyControl ball_phys;   
    Vector3f cameraLocation;
    Vector3f cameraDirection;


    public UnitTest() {
        cameraLocation = new Vector3f(0, 15f, 15f);
        cameraDirection = new Vector3f(-1, -7, -1);

        camera = Mockito.mock(Camera.class);
        Mockito.when(camera.getLocation()).thenReturn(cameraLocation);
        Mockito.when(camera.getDirection()).thenReturn(cameraDirection);
        
        ball_phys = Mockito.mock(RigidBodyControl.class);
        Vector3f position = Physics.calcPosition(camera);
        Mockito.when(ball_phys.getPhysicsLocation()).thenReturn(position);
    }
    
    
     @Test
     public void positionTest() {    
        Vector3f p = cameraLocation;
        Vector3f v = cameraDirection;
        
        Vector3f position = new Vector3f((v.x*(0.5f-p.y)/v.y)+p.x,0.5f,(v.z*(0.5f-p.y)/v.y)+p.z);
          
        assertTrue((Physics.calcPosition(camera).x == position.x));
        assertTrue((Physics.calcPosition(camera).y == position.y));
        assertTrue((Physics.calcPosition(camera).z == position.z));
     }
     

     
     @Test
     public void directionTest() {
   
        Vector3f p = cameraLocation;
        Vector3f v = cameraDirection;
        
        Vector3f direction = new Vector3f((v.x*(0.5f-p.y)/v.y)+p.x - ball_phys.getPhysicsLocation().x,0.5f,
                        (v.z*(0.5f-p.y)/v.y)+p.z - ball_phys.getPhysicsLocation().z);  
        
        Vector3f compDirection = Physics.calcDirection(camera, ball_phys);
        
        assertTrue((direction.x == compDirection.x));
        assertTrue((direction.y == compDirection.y));
        assertTrue(Math.abs(direction.z - compDirection.z) < 3);
     }
}
