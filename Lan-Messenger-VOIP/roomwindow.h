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

#ifndef ROOMWINDOW_H
#define ROOMWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QCloseEvent>
#include <QModelIndex>

namespace Ui {
class RoomWindow;
}

class RoomWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit RoomWindow(QWidget *parent = 0);
    void updateList(QList<QString> list);
    ~RoomWindow();
    
private:
    Ui::RoomWindow *ui;
    void closeEvent (QCloseEvent * event) ;

public slots:
    void receivedPM(QString from, QString text);

signals:
    void enteredText(QString text);
    void closedWindow();
    void roomAdd();
    void startPM(QString id);

private slots:
    void on_btnSend_clicked();
    void on_txtInput_returnPressed();
    void on_listUsers_doubleClicked(const QModelIndex &index);
};

#endif // ROOMWINDOW_H
