/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package view.controller;

import java.util.ArrayList;
import java.util.List;
import java.util.Observable;
import java.util.Observer;

import com.jfoenix.controls.JFXButton;

/**
 *
 * @author mathieu
 */
public class GraphicSearchGroup implements Observer{
    protected List<GraphicSearch> searchList;
    private TabListener listener;

    public GraphicSearchGroup() {
        searchList = new ArrayList<>();
    }

    public List<GraphicSearch> getSearchList() {
        return searchList;
    }
    
    public void addSearch(GraphicSearch search){
        if (listener != null) listener.onNewTab(search);
        searchList.add(search);
    }
    
    public void setTabListener (TabListener listener) {
        this.listener = listener;
    }

    @Override
    public void update(Observable o, Object arg) {
        GraphicSearch activeSearch = (GraphicSearch) arg;
        for (GraphicSearch search : searchList) {
            if (activeSearch != search) {
                search.active = false;
                search.searchWindow.setVisible(false);
                search.searchTab.setColorTabText(false, search.searchTab.plusButton);
            } else {
                search.searchWindow.setVisible(true);
                search.searchTab.setColorTabText(true, search.searchTab.plusButton);
                
                if (search.currentRequest == null) {
					GraphicLauncher.getInstance().getBaseController().getSaveButton().setVisible(false);
				} else {
					GraphicLauncher.getInstance().getBaseController().getSaveButton().setVisible(true);
				}
                
            }
        }
    }
}
