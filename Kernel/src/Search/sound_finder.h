/*
 * sound_finder.h
 *
 *  Created on: 8 janv. 2017
 *      Author: Thomas
 */

#ifndef SEARCH_SOUND_FINDER_H_
#define SEARCH_SOUND_FINDER_H_

#include "../Tools/data_handler.h"
HashMap file_content (DataFile df, int size_window, int nb_intervalles);
CellHashMap histogramme(CellHashMap hist, double valeur, int nb_intervalles);
//void find_sound(DataFile df, char *taille_fenetre, char *nb_barres);
#endif /* SEARCH_SOUND_FINDER_H_ */
