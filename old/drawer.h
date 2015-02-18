#ifndef DRAWER_H
#define DRAWER_H

#include "stdafx.h"
#include "textbuffer.h"

enum LAYER_TYPE{
    LT_BACK,
    LT_FLOAT
};

class Layer{
public:
    Layer(QString nm="", LAYER_TYPE ty = LT_FLOAT, QChar spce = 'Q');

    LAYER_TYPE type;
    QString str;
    QString name;
    QChar cSpace;
private:
};

class Drawer
{
public:
    Drawer();

    void AddLayer(Layer l); // layers added in order of priority (background first ... top foreground last)
    void ClearLayers();

    QString ToText();

    std::vector<Layer> L;

    QString Encrypt(QString in);
    QString Decrypt(QString in);
private:

};

#endif // DRAWER_H
