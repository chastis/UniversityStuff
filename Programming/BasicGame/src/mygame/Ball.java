/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package mygame;

import com.jme3.asset.AssetManager;
import com.jme3.asset.TextureKey;
import com.jme3.bullet.BulletAppState;
import com.jme3.bullet.control.RigidBodyControl;
import com.jme3.material.Material;
import com.jme3.math.Vector3f;
import com.jme3.renderer.Camera;
import com.jme3.scene.Geometry;
import com.jme3.scene.Node;
import com.jme3.scene.shape.Sphere;
import com.jme3.texture.Texture;
import java.util.ArrayList;
import java.util.Random;

/**
 *
 * @author Chastis
 */
public class Ball {

    private Node rootNode;
    private BulletAppState bulletAppState;
    private Material material;
    private ArrayList<RigidBodyControl> ball_phys = new ArrayList<>();
    private static final Sphere SPHERE;

    static {
        SPHERE = new Sphere(32, 32, 0.6f, true, false);
        SPHERE.setTextureMode(Sphere.TextureMode.Projected);
    }

    Ball() {

    }

    Ball(AssetManager assetManager, Node rootNode, BulletAppState bulletAppState) {
        this.rootNode = rootNode;
        this.bulletAppState = bulletAppState;


        initMaterials(assetManager);
        initBalls(new Vector3f(-6, 0.4f, 1));
        initBalls(new Vector3f(-7, 0.4f, 2));
        initBalls(new Vector3f(-7, 0.4f, 0));
    }


    private void initMaterials(AssetManager assetManager) {
        material = new Material(assetManager, "Common/MatDefs/Misc/Unshaded.j3md");
        TextureKey key2 = new TextureKey("Textures/ball.jpg");
        key2.setGenerateMips(true);
        Texture tex2 = assetManager.loadTexture(key2);
        material.setTexture("ColorMap", tex2);
    }

    private void initBalls(Vector3f position) {
        RigidBodyControl ball_phy;
        Geometry ball_geo = new Geometry("cannon ball", SPHERE);
        ball_geo.setMaterial(material);
        rootNode.attachChild(ball_geo);

        ball_phy = new RigidBodyControl(2);
        ball_geo.addControl(ball_phy);

        bulletAppState.getPhysicsSpace().add(ball_phy);
        ball_phy.setPhysicsLocation(position);
    }

    protected void createBall(Camera cam) {
        RigidBodyControl ball_phy;
        Geometry ball_geo = new Geometry("cannon ball", SPHERE);
        ball_geo.setMaterial(material);
        rootNode.attachChild(ball_geo);

        ball_phy = new RigidBodyControl(2);
        ball_geo.addControl(ball_phy);

        bulletAppState.getPhysicsSpace().add(ball_phy);
        ball_phy.setPhysicsLocation(Computations.calcPosition(cam));

        ball_phys.add(ball_phy);
    }

    protected void move(Camera cam) {
        Random rand = new Random();
        for (RigidBodyControl ball_phy : ball_phys) {
            ball_phy.setLinearVelocity(Computations.calcDirection(cam, ball_phy).mult(2 + rand.nextInt(1)));
        }
    }

}


