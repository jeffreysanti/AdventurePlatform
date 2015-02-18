#include "stdafx.h"

#ifndef TXTUTILS
#define TXTUTILS

#define DEF_B '0' // white on black
#define DEF_F '7'


// list of unicode symbols
const QString UC_POUND = QString(QChar(0xA3));
const QString UC_BLOCK = QString(QChar(0x2588));
const QString UC_TL_CNR = QString(QChar(0x250c));
const QString UC_TR_CNR = QString(QChar(0x2510));
const QString UC_BL_CNR = QString(QChar(0x2514));
const QString UC_BR_CNR = QString(QChar(0x2518));
const QString UC_HORIZ = QString(QChar(0x2500));
const QString UC_VERT = QString(QChar(0x2502));

// Ke'Vr number system •--=?¦†‡+? (0-9)
const QString UC_KR_0 = QString(QChar(0x2022)); // •
const QString UC_KR_1 = QString(QChar('-'));    // -
const QString UC_KR_2 = QString(QChar(0x2550)); // -
const QString UC_KR_3 = QString(QChar(0x2261)); // =
const QString UC_KR_4 = QString(QChar(0x040F)); // ?
const QString UC_KR_5 = QString(QChar(0x2302)); // ¦
const QString UC_KR_6 = QString(QChar(0x2020)); // †
const QString UC_KR_7 = QString(QChar(0x2021)); // ‡
const QString UC_KR_8 = QString(QChar(0x256C)); // +
const QString UC_KR_9 = QString(QChar(0x0444)); // ?

class TextAdventureGame;

struct StringPart{
	QString s;
	QChar b, f;
};

class TextBuffer{
public:
	TextBuffer(TextAdventureGame *g);
	~TextBuffer();

	void AddText(QString str);
	void OutputBuffer(bool waitEnter=true); // auto-clears screen, writes buffer, clears buffer, waits for input (if waitEnter)
	void ClearScreen();
	void ClearBuffer();

	void WaitForEnter();
	QString GetLine();
	int GetNumber();

	void InputChanged();

	// text utility functions
	static QString Int(int i);
	static QString Float(float f);

	static QString Lower(QString str);
	static QString Upper(QString str);
	static QString Center(QString str, int max=-1);

	static QString Times(QString str, int num);

	static QString Left(QString str, int i, QChar c=' ');
	static QString Right(QString str, int i, QChar c=' ');

	static QString Random(int len);

	QColor Color(QChar code);

	void ScrollBuffer(bool up);

	void RecalculateFont();

	static void Wait(int ms);


	static int TEXT_COLS;

	bool bQuit;

private:

	QString buf;

	TextAdventureGame *game;

	QString in;
	bool waitForInput;

	std::vector<QString> H;
	int hPos;
	QString hStr;
	bool numOnly;
};


inline bool StrContains(QString str, QString find)
{
	if(str.indexOf(find) < 0) return false;
	else			  return true;
}

inline QString StrReplace(QString str, QString find, QString replaceWith)
{
    int pos;
    do
    {
	pos = str.toStdWString().find(find.toStdWString());
	if (pos!=-1)  str = QString::fromStdWString(str.toStdWString().replace(pos, find.toStdWString().length(), replaceWith.toStdWString()));
    }
    while (pos!=-1);
    return str;
}
/*
inline wostream& write_word( wostream& outs, int value )
  {
	  outs.write((wchar_t*)&value, sizeof(int));
    return outs;
  }

inline wistream& read_word( wistream& ins, int &value )
  {
	  ins.read((wchar_t*)&value, sizeof(int));
  return ins;
  }

inline wstring read_str(wistream& ins)
{
	wstring tmp;
	wchar_t *c;
	int i=0;
	read_word(ins, i);
	c = new wchar_t[i+1];
	ins.read((wchar_t*)c, i*sizeof(wchar_t));
	c[i] = '\0';
	tmp = wstring(c);
	delete [] c;
	return tmp;
}
*/
/*inline int GetInt()
{
	int in;
	wstring sin;
	wcin >> sin;
	size_t pos = sin.find_first_not_of(L"1234567890");
	if(pos != wstring::npos)
	{
		return -1;
	}
	in = _wtoi(sin.c_str());
	return in;
}
*/

inline int getdir (QString dir, QList<QString> &files)
{
   /*WIN32_FIND_DATA FindFileData;
   HANDLE hFind = INVALID_HANDLE_VALUE;
   LPSTR DirSpec;

   DirSpec = (LPSTR) malloc (MAX_PATH);

   // Find the first file in the directory.
   hFind = FindFirstFile(dir.toStdWString().c_str(), &FindFileData);

   if (hFind == INVALID_HANDLE_VALUE)
   {
      return -1;
   }
   else
   {
       files.push_back(QString::fromWCharArray(FindFileData.cFileName));
	  // List all the other files in the directory.
      while (FindNextFile(hFind, &FindFileData) != 0)
      {
		  files.push_back(QString::fromStdWString(std::wstring(FindFileData.cFileName)));
      }
      FindClose(hFind);
   }
   free(DirSpec);
   return 0;*/
}


#endif
