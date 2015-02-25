/*
 *  Jeffrey Santi
 *  AdventurePlatform
 *
 *  DrawLayer.h
 *
 *
 */

#ifndef DRAWLAYER_H_
#define DRAWLAYER_H_

#include <string>
#include <vector>
#include <map>

#define MAX_STRING 8192

enum Color{
	BLACK,
	RED,
	GREEN,
	BROWN,
	BLUE,
	MAGENTA,
	CYAN,
	GRAY,
	DARKGRAY,
	LIGHTRED,
	LIGHTGREEN,
	YELLOW,
	LIGHTBLUE,
	LIGHTMAGENTA,
	LIGHTCYAN,
	WHITE
};

class Drawer;

class DrawLayer {
public:
	DrawLayer(Drawer *drawer, int wid, int hei);
	virtual ~DrawLayer();

	void solidFill(char c = ' ');
	void fillRect(int x0, int y0, int x1, int y1, char c = ' ');
	void setChar(int x, int y, char c);
	void printTextWW(const char* format, ... );
	void printTextWW(std::string s);
	void printTextCenter(const char* format, ... );
	void printTextCenter(std::string s);


	void setColor(Color c);
	Color getColor();

	void setOffset(int offx, int offy);
	int getOffsetX();
	int getOffsetY();

	char getCell(int termX, int termY);

	int getEffectiveWidth();
	int getEffectiveHeight();

private:
	Color _color;
	int _offx, _offy;
	int _wid, _hei;

	char **_buffer;
	Drawer *_drawer;
};

class DrawLayerGroup{

public:

	DrawLayerGroup(std::vector<DrawLayer*>);
	~DrawLayerGroup();

	void applyTransformation(int x, int y);
	void colorMap(std::map<Color, Color> m);

private:
	std::vector<DrawLayer*> _L;
};

#endif /* DRAWLAYER_H_ */
