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
	DrawLayer *newLayer(Color c);
	DrawLayer *newLayer(int wid, int hei);

	std::vector<DrawLayer *> _L;

	int getWidth();
	int getHeight();

	DrawLayerGroup printFormattedTextWW(DrawLayer *initialL, const char* format, ... );
	DrawLayerGroup printFormattedTextWW(DrawLayer *initialL, std::string s);
	DrawLayerGroup printFormattedTextCenter(DrawLayer *initialL, const char* format, ... );
	DrawLayerGroup printFormattedTextCenter(DrawLayer *initialL, std::string s);

	void resetScreen(Color bg=BLACK);

	void onLayerModified();
	bool needsPaint();

private:
	int _wid, _hei;
	bool _needsRefresh;
};

#endif /* DRAWER_H_ */
