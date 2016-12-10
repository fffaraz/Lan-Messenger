// Lan Messenger
// Copyright (C) 2012 Faraz Fallahi <fffaraz@gmail.com>
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

#ifndef DIALOGABOUT_H
#define DIALOGABOUT_H

#include <QDialog>
#include <QUrl>
#include <QDesktopServices>

namespace Ui {
class DialogAbout;
}

class DialogAbout : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogAbout(QWidget *parent = 0);
    ~DialogAbout();
    
    private slots:
        void link0();
        void link1();
        void link2();

private:
    Ui::DialogAbout *ui;
};

#endif // DIALOGABOUT_H
