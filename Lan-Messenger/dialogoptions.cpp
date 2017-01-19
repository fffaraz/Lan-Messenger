// Lan Messenger
// Copyright (C) 2017 Sebastian Martin Dicke <sebastianmartindicke@gmx.de>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//


#include "dialogoptions.hpp"
#include "ui_dialogoptions.h"

DialogOptions::DialogOptions(Messenger &messenger, QWidget *parent) :
    QTabWidget(parent),
	ui(new Ui::DialogOptions), messenger(&messenger)
{
    ui->setupUi(this);
	this->ui->leDomainName->setEnabled(false);
	this->ui->rdDefaultHostname->setChecked(true);
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
