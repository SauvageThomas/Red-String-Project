package view.controller;

import java.util.EventListener;

/**
*
* @author mathieu
* 
* Custom event to manage resizing w/o messing w/ layout
*/
public interface ResizeListener extends EventListener{
	void onResize();
}
