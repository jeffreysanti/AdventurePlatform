/*
 *  Jeffrey Santi
 *  AdventurePlatform
 *
 *  Drawer.h
 *
 *
 */

#ifndef DRAWER_H_
#define DRAWER_H_

#include "DrawLayer.h"
#include <vector>

class Drawer {
public:
	Drawer(int wid, int hei, Color bg=BLACK);
	virtual ~Drawer();

	DrawLayer *newLayer();
	DrawLayer *newLayer(int wid, int hei);

	std::vector<DrawLayer *> _L;

	int getWidth();
	int getHeight();

	DrawLayerGroup printFormattedTextWW(DrawLayer *initialL, const char* format, ... );
	DrawLayerGroup printFormattedTextCenter(DrawLayer *initialL, const char* format, ... );

private:
	int _wid, _hei;
};

#endif /* DRAWER_H_ */
