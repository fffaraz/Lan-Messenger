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

#ifndef DIALOGNICKNAME_H
#define DIALOGNICKNAME_H

#include <QDialog>
#include <QString>

namespace Ui {
class DialogNickName;
}

class DialogNickName : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogNickName(QWidget *parent = 0);
    ~DialogNickName();
    
private slots:
    void on_btnOk_clicked();

signals:
    void setName(QString name);

private:
    Ui::DialogNickName *ui;
};

#endif // DIALOGNICKNAME_H
