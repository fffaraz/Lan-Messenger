#include "dialogoptions.hpp"
#include "ui_dialogoptions.h"

DialogOptions::DialogOptions(Messenger* messenger, QWidget *parent) :
    QTabWidget(parent),
	ui(new Ui::DialogOptions), messenger(messenger)
{
    ui->setupUi(this);
	this->ui->leDomainName->setEnabled(false);
	connect(ui->rdDefaultHostname, SIGNAL(toggled(bool)), this, SLOT(defaultHostnameToggled(bool)));
	connect(ui->leDomainName, SIGNAL(returnPressed()), this, SLOT(nameChanged()));
}

DialogOptions::~DialogOptions()
{
    delete ui;
}

void DialogOptions::defaultHostnameToggled(bool value) {
	if (value) {
		this->ui->leDomainName->setEnabled(false);
	}
	else {
		this->ui->leDomainName->setEnabled(true);
	}
}

void DialogOptions::nameChanged() {

}
