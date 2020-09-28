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
import com.jme3.math.Vector2f;
import com.jme3.scene.Geometry;
import com.jme3.scene.Node;
import com.jme3.scene.shape.Box;
import com.jme3.texture.Texture;

/**
 *
 * @author Chastis
 */

public final class Floor {
    private Material material;
    private RigidBodyControl floor_phy;
    private static final Box FLOOR;
    
    static{
        FLOOR = new Box(15f, 0.1f, 10f);
        FLOOR.scaleTextureCoordinates(new Vector2f(3, 6));
    }
    
    Floor(AssetManager assetManager, Node rootNode, BulletAppState bulletAppState){
        initMaterials(assetManager);
        initPhysics(rootNode, bulletAppState);
    }
    
    private void initMaterials(AssetManager assetManager){
        material = new Material(assetManager, "Common/MatDefs/Misc/Unshaded.j3md");
        TextureKey key3 = new TextureKey("Textures/table2.jpg");
        key3.setGenerateMips(true);
        Texture tex3 = assetManager.loadTexture(key3);
        tex3.setWrap(Texture.WrapMode.Repeat);   
        material.setTexture("ColorMap", tex3);
    }
    
    private void initPhysics(Node rootNode, BulletAppState bulletAppState){
        Geometry floor_geo = new Geometry("Floor", FLOOR);
        floor_geo.setMaterial(material);
        floor_geo.setLocalTranslation(0, -0.1f, 0);
        rootNode.attachChild(floor_geo);

        floor_phy = new RigidBodyControl(0.0f);
        floor_geo.addControl(floor_phy);
        bulletAppState.getPhysicsSpace().add(floor_phy);
    }
    
}
