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

#ifndef DIALOGROOM_H
#define DIALOGROOM_H

#include <QDialog>

namespace Ui {
class DialogRoom;
}

class DialogRoom : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogRoom(QWidget *parent = 0);
    ~DialogRoom();
    
private:
    Ui::DialogRoom *ui;

signals:
    void joinRoom(QString room);
private slots:
    void on_btnJoin_clicked();
};

#endif // DIALOGROOM_H
