#include "GUI.h"
#include <QtWidgets/QApplication>
#include "UnitTests.h"

using namespace tic_tac_toe;

int main(int argc, char *argv[])
{

	UnitTests::testAll();

	QApplication app(argc, argv);
	Gui window;
	window.show();

	return app.exec();
}
