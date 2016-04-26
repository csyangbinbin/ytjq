#include "stdafx.h"
#include "ytjq.h"
#include <QtGui/QApplication>
#include <iostream>
#include "utility.h"


#ifdef _DEBUG
#pragma comment(lib,"libtesseract302-static-debug.lib")
#else
#pragma comment(lib,"libtesseract302-static.lib")
#endif
#pragma comment(lib,"liblept168-static-mtdll.lib")
#pragma comment(lib,"giflib416-static-mtdll.lib")
#pragma comment(lib,"libjpeg8c-static-mtdll.lib")
#pragma comment(lib,"libpng143-static-mtdll.lib")
#pragma comment(lib,"zlib125-static-mtdll.lib")
#pragma comment(lib,"libtiff394-static-mtdll.lib")
#pragma comment(lib,"ws2_32.lib")

#pragma comment(lib,"Magick/lib/CORE_RL_magick_.lib")
#pragma comment(lib,"Magick/lib/CORE_RL_Magick++_.lib")


int main(int argc, char *argv[])
{
	InitializeMagick(NULL);

	QApplication a(argc, argv);
	ytjq w;
	w.show();
	return a.exec();
}
