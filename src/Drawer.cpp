/*
 *  Jeffrey Santi
 *  AdventurePlatform
 *
 *  Drawer.cpp
 *
 *
 */

#include <Drawer.h>
#include <cstdarg>
#include <cstdio>
#include <cstring>

Drawer::Drawer(int wid, int hei, Color bg) {
	_wid = wid;
	_hei = hei;
	_needsRefresh = false;
	DrawLayer *layer = newLayer();
	layer->setColor(bg);
	layer->solidFill(' ');
}

Drawer::~Drawer() {
	// TODO Auto-generated destructor stub
}


DrawLayer *Drawer::newLayer()
{
	return newLayer(_wid, _hei);
}

DrawLayer *Drawer::newLayer(int wid, int hei)
{
	DrawLayer *layer = new DrawLayer(this, wid, hei);
	_L.push_back(layer);
	return layer;
}

int Drawer::getWidth(){
	return _wid;
}
int Drawer::getHeight(){
	return _hei;
}

inline Color charToColor(char c){
	if(c == '0') return BLACK;
	else if(c == '1') return RED;
	else if(c == '2') return GREEN;
	else if(c == '3') return BROWN;
	else if(c == '4') return BLUE;
	else if(c == '5') return MAGENTA;
	else if(c == '6') return CYAN;
	else if(c == '7') return GRAY;
	else if(c == 'A') return DARKGRAY;
	else if(c == 'B') return LIGHTRED;
	else if(c == 'C') return LIGHTGREEN;
	else if(c == 'D') return YELLOW;
	else if(c == 'E') return LIGHTBLUE;
	else if(c == 'F') return LIGHTMAGENTA;
	else if(c == 'G') return LIGHTCYAN;
	else return WHITE;
}

DrawLayerGroup Drawer::printFormattedTextWW(DrawLayer *layer, const char* format, ... ){
	std::vector<DrawLayer *> ls;
	ls.push_back(layer);
	char buffer[MAX_STRING];
	char bufferNew[MAX_STRING];
	memset(buffer, 0, sizeof(char)*MAX_STRING);
	memset(bufferNew, 0, sizeof(char)*MAX_STRING);

	va_list args;
	va_start(args, format);
	vsprintf(buffer, format, args);
	va_end(args);

	int x = 0;
	int i = -1;
	while(i<MAX_STRING-5){
		i ++;
		if(buffer[i] == '<'){
			if(buffer[i+2] == '>'){
				if((i > 0) && buffer[i-1] == '\\')
				{
					bufferNew[x-1] = '<';
					continue;
				}
				else
				{
					layer->printTextWW("%s", bufferNew);
					// new layer for new color
					DrawLayer *lnew = newLayer();
					lnew->setOffset(layer->getOffsetX(), layer->getOffsetY());
					Color f = charToColor(buffer[i+1]);
					lnew->setColor(f);
					i = i+2; // at >, we'll move again on continue

					// now blank each active letter from previous layer
					for(int y=0; y<x; y++){
						if(bufferNew[y] != ' '){
							bufferNew[y] = '\a'; // bell character
						}
					}
					layer = lnew;
					ls.push_back(layer);
					continue;
				}
			}
		}
		// normal character
		bufferNew[x] = buffer[i];
		x++;
	}
	layer->printTextWW("%s", bufferNew);
	return DrawLayerGroup(ls);
}

DrawLayerGroup Drawer::printFormattedTextCenter(DrawLayer *layer, const char* format, ... ){
	std::vector<DrawLayer *> ls;
	ls.push_back(layer);
	char buffer[MAX_STRING];
	char bufferNew[MAX_STRING];
	memset(buffer, 0, sizeof(char)*MAX_STRING);
	memset(bufferNew, 0, sizeof(char)*MAX_STRING);

	va_list args;
	va_start(args, format);
	vsprintf(buffer, format, args);
	va_end(args);

	// make sure length is same for each pass
	int x = 0;
	int i = -1;
	while(i<MAX_STRING-5){
		i ++;
		if(buffer[i] == 0)
			break;
		if(buffer[i] == '<'){
			if(buffer[i+2] == '>'){
				if((i > 0) && buffer[i-1] == '\\')
				{
					continue;
				}
				else
				{
					i = i+2; // at >, we'll move again on continue
					continue;
				}
			}
		}
		// normal character
		bufferNew[x] = '\a';
		x++;
	}

	x = 0;
	i = -1;
	while(i<MAX_STRING-5){
		i ++;
		if(buffer[i] == '<'){
			if(buffer[i+2] == '>'){
				if((i > 0) && buffer[i-1] == '\\')
				{
					bufferNew[x-1] = '<';
					continue;
				}
				else
				{
					layer->printTextCenter("%s", bufferNew);
					// new layer for new color
					DrawLayer *lnew = newLayer();
					lnew->setOffset(layer->getOffsetX(), layer->getOffsetY());
					Color f = charToColor(buffer[i+1]);
					lnew->setColor(f);
					i = i+2; // at >, we'll move again on continue

					// now blank each active letter from previous layer
					for(int y=0; y<x; y++){
						if(bufferNew[y] != ' '){
							bufferNew[y] = '\a'; // bell character
						}
					}
					layer = lnew;
					ls.push_back(layer);
					continue;
				}
			}
		}
		// normal character
		bufferNew[x] = buffer[i];
		x++;
	}
	layer->printTextCenter("%s", bufferNew);
	return DrawLayerGroup(ls);
}

void Drawer::onLayerModified(){
	_needsRefresh = true;
}

bool Drawer::needsPaint(){
	bool ret = _needsRefresh;
	_needsRefresh = false;
	return ret;
}

