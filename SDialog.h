#ifndef SDIALOG_H
#define SDIALOG_H
#include <QDialog>
#include "ui_sdialog.h"

class SDialog:public QDialog,public Ui::SDialog{
	Q_OBJECT
	public:
		SDialog(QWidget* parent=0);
	private slots:
		void solve_button_press();
};
#endif
