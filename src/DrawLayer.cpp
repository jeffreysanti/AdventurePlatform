/*
 *  Jeffrey Santi
 *  AdventurePlatform
 *
 *  DrawLayer.cpp
 *
 *
 */

#include <DrawLayer.h>
#include <Drawer.h>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

DrawLayer::DrawLayer(Drawer* drawer, int wid, int hei) {
	_wid = wid;
	_hei = hei;
	_color = GRAY;
	_offx = 0;
	_offy = 0;
	_drawer = drawer;
	_buffer = new char*[_hei];
	for(int i=0; i<_hei; i++){
		_buffer[i] = new char[_wid];
		memset(_buffer[i], 0, sizeof(char) * _wid);
	}
}

DrawLayer::~DrawLayer() {
	for(int i=0; i<_hei; i++){
		delete [] _buffer[i];
	}
	delete [] _buffer;
}

void DrawLayer::solidFill(char c)
{
	for(int y=0; y<_hei; y++){
		for(int x=0; x<_wid; x++){
			setChar(x, y, c);
		}
	}
}

void DrawLayer::fillRect(int x0, int y0, int x1, int y1, char c){
	for(int y=y0; y<=y1; y++){
		for(int x=x0; x<=x1; x++){
			setChar(x, y, c);
		}
	}
}
void DrawLayer::setChar(int x, int y, char c){
	if(x >= 0 && x < _wid && y >= 0 && y < _hei){
		_buffer[y][x] = c;
		_drawer->onLayerModified();
	}
}

void DrawLayer::printTextWW(const char* format, ... ){
	char buffer[MAX_STRING];
	memset(buffer, 0, sizeof(char)*MAX_STRING);

	va_list args;
	va_start(args, format);
	vsprintf(buffer, format, args);
	va_end(args);

	// now word wrap it
	int posLastSpace = 0;
	int x = 0;
	int i = -1;
	while(i<MAX_STRING-1){
		i ++;
		if(buffer[i] == 0)
			break;
		if(buffer[i] == '\n')
			continue;
		if(buffer[i] == ' ')
			posLastSpace = i;
		if(x == _wid - 1){ // last character possible in this row
			if(buffer[i+1] == ' '){
				buffer[i+1] = '\n';
				x = 0;
				continue;
			}
			buffer[posLastSpace] = '\n';
			i = posLastSpace;
			x = 0;
			continue;
		}
		x++;
	}

	// now dump it to the buffer
	x = 0;
	int y = 0;
	for(int i=0; i<MAX_STRING-1; i++){
		if(buffer[i] == 0)
			break;
		if(buffer[i] == '\n'){
			y++;
			x = 0;
			continue;
		}if(buffer[i] == ' '){
			x++;
			continue;
		}
		if(buffer[i] != '\a')
			setChar(x, y, buffer[i]);
		x ++;
	}
}

void DrawLayer::printTextCenter(const char* format, ... ){
	char buffer[MAX_STRING];
	memset(buffer, 0, sizeof(char)*MAX_STRING);

	va_list args;
	va_start(args, format);
	vsprintf(buffer, format, args);
	va_end(args);

	// now dump it to the buffer
	int len = 0;
	for(int i=0; i<MAX_STRING-1; i++){
		if(buffer[i] == 0)
			break;
		len ++;
	}

	int x = 0;
	int spare = _wid - len;
	x += int(spare/2);
	for(int i=0; i<len; i++){
		if(buffer[i] == ' '){
			x++;
			continue;
		}
		if(buffer[i] != '\a')
			setChar(x, 0, buffer[i]);
		x ++;
	}
}

void DrawLayer::setColor(Color c){
	_color = c;
	_drawer->onLayerModified();
}
Color DrawLayer::getColor(){
	return _color;
}

void DrawLayer::setOffset(int offx, int offy){
	_offx = offx;
	_offy = offy;
	_drawer->onLayerModified();
}
int DrawLayer::getOffsetX(){
	return _offx;
}
int DrawLayer::getOffsetY(){
	return _offy;
}

char DrawLayer::getCell(int termX, int termY)
{
	int x = termX - _offx;
	int y = termY - _offy;
	if(x >= _wid || y >= _hei || x < 0 || y < 0)
		return 0;
	return _buffer[y][x];
}


int DrawLayer::getEffectiveWidth(){
	return _wid;
}
int DrawLayer::getEffectiveHeight(){
	return _hei;
}

DrawLayerGroup::DrawLayerGroup(std::vector<DrawLayer*> l){
	_L = l;
}

DrawLayerGroup::~DrawLayerGroup(){
	_L.clear();
}

void DrawLayerGroup::applyTransformation(int x, int y){
	for(int i=0; i<_L.size(); i++){
		_L[i]->setOffset(_L[i]->getOffsetX()+x, _L[i]->getOffsetY()+y);
	}
}

void DrawLayerGroup::colorMap(std::map<Color, Color> m){
	for(int i=0; i<_L.size(); i++){
		std::map<Color, Color>::iterator it = m.find(_L[i]->getColor());
		if(it != m.end()){
			_L[i]->setColor((*it).second);
		}
	}
}




