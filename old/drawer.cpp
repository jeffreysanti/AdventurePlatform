#include "drawer.h"

Layer::Layer(QString nm, LAYER_TYPE ty, QChar spce)
{
    name = nm;
    type = ty;
    cSpace = spce;
}


Drawer::Drawer()
{
}

void Drawer::AddLayer(Layer l)
{
    L.push_back(l);
}

void Drawer::ClearLayers()
{
    L.clear();
}

QString Drawer::Encrypt(QString in)
{
    QString out;
    int i=0;
    QChar f,b;
    f = b = 'X';
    while(i < in.length())
    {
	if(in[i] == '<')
	{
	    if((i+3 < in.length()) && (in[i+3] == '>'))
	    {
		if((i > 0) && in[i-1] == '\\')
		{
		    out[out.length()-1] = b;
		    out = out + f + '<';
		}
		else
		{
		    b = in[i+1];
		    f = in[i+2];
		    i = i+3;
		}
	    }
	    else
	    {
		out = out + b + f + in[i];
	    }
	}
	else
	{
	    out = out + b + f + in[i];
	}
	i++;
    }
    return out;
}
QString Drawer::Decrypt(QString in)
{
    QString out = "<XX>";
    int i=0;
    QChar f,b;
    f = b = 'X';
    while(i < in.length() / 3)
    {
	if(in[i*3] != b || in[i*3+1] != f)
	{
	    b = in[i*3];
	    f = in[i*3+1];
	    out = out + '<' + b + f + '>' + in[i*3+2];
	}
	else
	{
	    out = out + in[i*3+2];
	}
	i++;
    }
    return out;
}

QString Drawer::ToText()
{
    int x=0; // character position
    int y=0; // vertical position
    std::vector<QString> S;
    for(int i=0; i<(int)L.size(); i++)
    {
	Layer l = L[i];
	l.str = Encrypt(l.str);
	x = y = 0;

	    int e=0;
	    while(e < l.str.length() / 3)
	    {
		if(l.str[e*3+2] == '\n')
		{
		    y ++;
		    x = 0;
		    if(y+1 > (int)S.size())
		    {
			S.push_back("");
		    }
		}
		else
		{
		    if(y+1 > (int)S.size())
		    {
			S.push_back("");
		    }
		    if(x*3 +1 > S[y].length())
		    {
			S[y] += "   ";
		    }

		    if(l.type == LT_BACK ||
		       (l.type == LT_FLOAT && l.str[e*3+2] != ' '))
		    {
			if(l.type == LT_FLOAT && l.str[e*3+2] == l.cSpace)
			{
			    S[y][x*3] = l.str[e*3];
			    S[y][x*3+1] = l.str[e*3+1];
			    S[y][x*3+2] = ' ';
			}
			else
			{
			    S[y][x*3] = l.str[e*3];
			    S[y][x*3+1] = l.str[e*3+1];
			    S[y][x*3+2] = l.str[e*3+2];
			}
		    }
		    x++;
		}
		e++;
	    }
    }

    QString fnl = "";
    for(int i=0; i<(int)S.size(); i++)
    {
	if(i != 0)
	    fnl = fnl + "\n";
	fnl = fnl + Decrypt(S[i]);
    }
    return fnl;
}
