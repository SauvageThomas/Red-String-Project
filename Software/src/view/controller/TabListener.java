/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package view.controller;

/**
 *
 * @author mathieu
 * 
 * Manages closing and creating windows
 */
public interface TabListener {
    void onNewTab(GraphicSearch newSearch);
    void onCloseTab(GraphicSearch removedSearch);
}
