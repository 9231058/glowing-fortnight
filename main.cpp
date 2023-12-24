#include <QApplication>
#include "SDialog.h"

int main(int argc,char* argv[]){
	QApplication app(argc,argv);
	SDialog dialog;
	dialog.show();
	app.exec();
}
