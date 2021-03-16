#include <string>
#include "QtGuiApplication1.h"
#include <QtWidgets/QApplication>

using namespace std;

int main(int argc, char *argv[])
{
		QApplication a(argc, argv);
		QtGuiApplication1 w;
		//string str = argv[1];

		
		w.show();
		return a.exec();
	
}

