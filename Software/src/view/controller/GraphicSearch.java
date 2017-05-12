/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package view.controller;

import java.util.Observable;
import java.util.Observer;

import controller.ControllerSoftware;
import javafx.scene.layout.VBox;
import model.entities.Request;

/**
 *
 * @author mathieu
 * 
 * All elements forming an actual reasearch are stored here
 */
public class GraphicSearch extends Observable{
    protected VBox searchWindow;
    protected ControllerTab searchTab;
    protected boolean active;
    protected Request currentRequest;

    public GraphicSearch(Observer o, ControllerSoftware controllerSoftware) {
        searchWindow = new ControllerHomeSearch(this, controllerSoftware);
        searchTab = new ControllerTab(false, this);
        this.addObserver(o);
        setActive(true);
    }

    // Setting the research active on demand
    public void setActive(boolean active) {
        this.active = active;
        this.setChanged();
        this.notifyObservers(this);
    }
}
