/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package mygame;

import com.jme3.bullet.control.RigidBodyControl;
import com.jme3.math.Vector3f;
import com.jme3.renderer.Camera;
import java.util.Random;

/**
 *
 * @author Chastis
 */
public class Physics {
    
    public static Vector3f calcPosition(Camera cam) {
        Vector3f v = cam.getDirection();
        Vector3f p = cam.getLocation();

        return new Vector3f((v.x * (0.5f - p.y) / v.y) + p.x, 0.5f, (v.z * (0.5f - p.y) / v.y) + p.z);
    }

    public static Vector3f calcDirection(Camera cam, RigidBodyControl ball_phy) {
        Vector3f v = cam.getDirection();
        Vector3f p = cam.getLocation();
        Random rand = new Random();

        return new Vector3f((v.x * (0.5f - p.y) / v.y) + p.x - ball_phy.getPhysicsLocation().x, 0.5f,
                (v.z * (0.5f - p.y) / v.y) + p.z - ball_phy.getPhysicsLocation().z + rand.nextFloat() % 3f);
    }
    
}
