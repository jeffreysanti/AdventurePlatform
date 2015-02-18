#include "textbuffer.h"

#include "mainwindow.h"
#include "textgame.h"
#include "ui_mainwindow.h"
#include "QDesktopWidget"
#include <QFile>
#include <QDebug>

int TextBuffer::TEXT_COLS = 72;

void TextBuffer::AddText(QString str)
{
	buf += str;
}

TextBuffer::TextBuffer(TextAdventureGame *g)
{
    buf = "";
    in = "";
    waitForInput = false;
    hPos = -1;
    TEXT_COLS = 72;
    bQuit = false;
    numOnly = false;
    game = g;
    game->win->showFullScreen();
    //win->setPalette(QPalette(Qt::white));
    RecalculateFont();
    qsrand(QTime::currentTime().msec());
}


TextBuffer::~TextBuffer()
{
    waitForInput = false;
    bQuit = true;
}

void TextBuffer::RecalculateFont()
{
    if(game->win == NULL)
	return;

    game->win->ui->in->setFont(QFont("Lucida Console", 16));
    game->win->ui->text->setWordWrapMode(QTextOption::NoWrap);
    int sz = 48;
    int px, wid;
    wid = game->win->ui->text->width() -100;
    while(sz > 0)
    {
	QFont f("Lucida Console", sz);
	// find out the max char width
	QFontMetrics fm(f, game->win->ui->text);
	px = fm.width(" ");
	TEXT_COLS = floor((float)wid / (float)px) - 2;
	if(TEXT_COLS >= 120)
	{
	    game->win->ui->text->setFont(f);
	    return;
	}
	sz --;
    }
    game->win->ui->in->setFont(QFont("Lucida Console", 16));
}

QColor TextBuffer::Color(QChar code)
{
    /*
	    0 = Black       8 = Gray
	    1 = Blue        9 = Light Blue
	    2 = Green       A = Light Green
	    3 = Aqua        B = Light Aqua
	    4 = Red         C = Light Red
	    5 = Purple      D = Light Purple
	    6 = Yellow      E = Light Yellow
	    7 = White       F = Bright White
*/
    /*if(S[i].b == '0') b = "#000000";
    if(S[i].b == '1') b = "#0000FF";
    if(S[i].b == '2') b = "#006600";
    if(S[i].b == '3') b = "#66CCCC";
    if(S[i].b == '4') b = "#FF0000";
    if(S[i].b == '5') b = "#9900CC";
    if(S[i].b == '6') b = "#CC9900";
    if(S[i].b == '7') b = "#CCCCCC";
    if(S[i].b == '8') b = "#666666";
    if(S[i].b == '9') b = "#3399FF";
    if(S[i].b == 'A') b = "#00FF00";
    if(S[i].b == 'B') b = "#00CCFF";
    if(S[i].b == 'C') b = "#FF9966";
    if(S[i].b == 'D') b = "#666699";
    if(S[i].b == 'E') b = "#FFFF00";
    if(S[i].b == 'F') b = "#FFFFFF";*/
    if(code == '0') return Qt::black;
    if(code == '1') return Qt::darkBlue;
    if(code == '2') return Qt::darkGreen;
    if(code == '3') return Qt::darkCyan;
    if(code == '4') return Qt::darkRed;
    if(code == '5') return Qt::darkMagenta;
    if(code == '6') return Qt::darkYellow;
    if(code == '7') return Qt::lightGray;
    if(code == '8') return Qt::darkGray;
    if(code == '9') return Qt::blue;
    if(code == 'A') return Qt::green;
    if(code == 'B') return Qt::cyan;
    if(code == 'C') return Qt::red;
    if(code == 'D') return Qt::magenta;
    if(code == 'E') return Qt::yellow;
    if(code == 'F') return Qt::white;

    return Qt::white;
}

QString TextBuffer::Random(int len)
{
    QString out;
    int min = 97;
    int max = 122;
    for(int i=0; i<len; i++)
    {
	int v = ((qrand()%(max-min+1))+min);
	QChar c = QChar(v);
	out += c;
    }
    return out;
}

void TextBuffer::OutputBuffer(bool waitEnter)
{
	std::vector<StringPart> S;
	StringPart cur;
	cur.b = DEF_B;
	cur.f = DEF_F;
	for(int i=0; i<buf.length(); i++)
	{
		if(buf[i] == '<')
		{
			if((i+3 < buf.length()) && (buf[i+3] == '>'))
			{
			    if((i > 0) && buf[i-1] == '\\')
			    {
				    cur.s[cur.s.length()-1] = '<';
			    }
			    else
			    {
				    S.push_back(cur);
				    cur.s = "";
				    cur.b = buf.at(i+1).toAscii();
				    cur.f = buf.at(i+2).toAscii();
				    i = i+3;
			    }
			}
			else
			{
			    cur.s = cur.s + buf[i];
			}
		}
		else if(buf[i] == '\n')
		{
		    S.push_back(cur);
		    cur.s = "\n";
		    S.push_back(cur);
		    cur.s = "";
		}
		else
		{
			cur.s = cur.s + buf[i];
		}
	}
	S.push_back(cur);

	ClearScreen();
	int curWidth = TEXT_COLS;
	for(int i=0; i<(int)S.size(); i++)
	{
		if(S[i].s == "\n")
		{
		    game->win->ui->text->insertPlainText("\n");
		    curWidth = TEXT_COLS;
		    continue;
		}
		QColor f, b;
		if(S[i].f == 'X') S[i].f = DEF_F;
		if(S[i].b == 'X') S[i].b = DEF_B;
		f = Color(S[i].f);
		b = Color(S[i].b);

		// now print
		game->win->ui->text->setTextColor(f);
		game->win->ui->text->setTextBackgroundColor(b);
		if(curWidth >= S[i].s.length())
		{
			curWidth -= S[i].s.length();
		}
		else
		{
		    while( curWidth < S[i].s.length() ) {
			    int spacePos = S[i].s.lastIndexOf(' ', curWidth);
			    if( spacePos == -1 )
				    spacePos = S[i].s.indexOf( ' ', curWidth );
			    if( spacePos != -1 ) {
				    S[i].s[spacePos] = '\n';
				    curWidth = spacePos + TEXT_COLS + 1;
			    }
		    }
		}
		game->win->ui->text->insertPlainText(S[i].s);
	}
	ClearBuffer();
	if(waitEnter)
		WaitForEnter();
}

void TextBuffer::ClearBuffer()
{
	buf = "";
}

void TextBuffer::ClearScreen()
{
	game->win->ui->text->setHtml("");
	RecalculateFont();
}

void TextBuffer::WaitForEnter()
{
    if(bQuit)
	return;
    // normal color
    game->win->ui->text->setTextColor(Color(DEF_F));
    game->win->ui->text->setTextBackgroundColor(Color(DEF_B));

    game->win->ui->text->insertPlainText("\n\n"+Center("[Hit Enter To Continue]") + "\n");
    waitForInput = true;
    game->win->ui->in->setPlainText(""); // calls InputChanged to set color
    while(waitForInput && !bQuit)
    {
	QCoreApplication::processEvents();
    }
    return;
}

QString TextBuffer::GetLine()
{
    waitForInput = true;
    game->win->ui->in->setPlainText(""); // calls InputChanged to set color
    hPos = -1;
    while(waitForInput && !bQuit)
    {
	QCoreApplication::processEvents();
    }
    if(in != "")
	H.push_back(in);
    return in;
}

int TextBuffer::GetNumber()
{
    waitForInput = true;
    numOnly = true;
    game->win->ui->in->setPlainText(""); // calls InputChanged to set color
    hPos = -1;
    while(waitForInput && !bQuit)
    {
	QCoreApplication::processEvents();
    }
    if(in != "")
	H.push_back(in);
    numOnly = false;
    if(in == "")
	return -1;
    return in.toInt();
}

void TextBuffer::InputChanged()
{
    game->win->ui->in->moveCursor(QTextCursor::End);
    if(!waitForInput)
    {
	if(game->win->ui->in->toPlainText() != ">  ")
	{
	    game->win->ui->in->setTextColor(Qt::black);
	    game->win->ui->in->setPlainText(">  ");
	}
	return;
    }
    else if(game->win->ui->in->toPlainText().length() < 3)
    {
	game->win->ui->in->setTextColor(Qt::lightGray);
	game->win->ui->in->setPlainText(">  ");
	return;
    }
    if(game->win->ui->in->toPlainText().length() > 3)
    {
	in = game->win->ui->in->toPlainText().mid(3); // remove ">  "
	if(numOnly)
	{
	    for(int i=0; i<in.length(); i++)
	    {
		if(in[i] != '0' && in[i] != '1' &&
		   in[i] != '2' && in[i] != '3' &&
		   in[i] != '4' && in[i] != '5' &&
		   in[i] != '6' && in[i] != '7' &&
		   in[i] != '8' && in[i] != '9' &&
		   in[i] != '\n' && in[i] != '\r')
		{
		    in = StrReplace(in, QString(in[i]), "");
		    game->win->ui->in->setPlainText(">  "+in);
		    return;
		}
	    }
	}
	if(hPos == -1)
	    hStr = in;
	if(in[in.length()-1] == '\r' || in[in.length()-1] == '\n')
	{
	    in = StrReplace(StrReplace(in, "\n", ""), "\r", "");
	    waitForInput = false;
	    game->win->ui->in->setPlainText(""); // recalls this to gray out input
	    hPos = -1;
	    return;
	}
    }
    else
    {
	in = "";
    }
}

QString TextBuffer::Int(int i)
{
    return QString::number(i);
}

QString TextBuffer::Float(float f)
{
    return QString::number(f);
}

QString TextBuffer::Lower(QString str)
{
    return str.toLower();
}

QString TextBuffer::Upper(QString str)
{
    return str.toUpper();
}

QString TextBuffer::Center(QString str, int max)
{
	if(max <= 0)
	{
	    max = TEXT_COLS;
	}
	QString tmp;
	int spare = max - str.length();
	if(spare % 2 == 0)
	{
		for(int i=0; i<int(spare/2); i++)
		{
			tmp = tmp + " ";
		}
	}
	else
	{
		for(int i=0; i<int((spare+1)/2); i++)
		{
			tmp = tmp + " ";
		}
	}
	tmp = tmp + str;
	return tmp;
}

QString TextBuffer::Left(QString str, int i, QChar c)
{
    str = str.left(i);
    i -= str.length();
    for(int x=0; x<i; x++)
    {
	str = str + c;
    }
    return str;
}

QString TextBuffer::Right(QString str, int i, QChar c)
{
    str = str.right(i);
    i -= str.length();
    for(int x=0; x<i; x++)
    {
	str = c + str;
    }
    return str;
}

QString TextBuffer::Times(QString str, int num)
{
    QString tmp;
    for(int i=0; i<num; i++)
    {
	tmp += str;
    }
    return tmp;
}

void TextBuffer::Wait(int ms)
{
    QTime t;
    t.start();
    QEventLoop loop;
    while(t.elapsed() < ms)
    {
	loop.processEvents();
    }
}

void TextBuffer::ScrollBuffer(bool up)
{
    /*   if(up)
	hPos ++;
    else
	hPos --;
    if(hPos == -1)
    {
	win->ui->in->setPlainText(">  "+hStr);
	return;
    }
    if(hPos < 0)
    {
	hPos = H.size() -1;
	if(hPos == -1)
	{
	    game->win->ui->in->setPlainText(">  "+hStr);
	    return;
	}
    }
    else if(hPos > H.size() -1)
    {
	hPos = -1;
	win->ui->in->setPlainText(">  "+hStr);
	return;
    }
    game->win->ui->in->setPlainText(">  "+H[hPos]);*/
}



