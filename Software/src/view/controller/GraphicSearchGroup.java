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

import view.GraphicLauncher;

/**
 *
 * @author mathieu
 * 
 * Keeping all the GraphicSearch(es) together
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
    
    // Add new search to the group
    public void addSearch(GraphicSearch search){
        if (listener != null) listener.onNewTab(search);
        searchList.add(search);
    }
    
    public void setTabListener (TabListener listener) {
        this.listener = listener;
    }

    // On opening tab (or closing), or just requesting focus, focusing the right stuff
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
