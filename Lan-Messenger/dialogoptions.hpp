// Lan Messenger
// Copyright (C) 2016 Sebastian Martin Dicke <sebastianmartindicke@gmx.de>
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


#ifndef DIALOGOPTIONS_HPP
#define DIALOGOPTIONS_HPP

#include <QTabWidget>

namespace Ui {
    class DialogOptions;
}

class DialogOptions : public QTabWidget
{
        Q_OBJECT

    public:
        explicit DialogOptions(QWidget *parent = 0);
        ~DialogOptions();

    private:
        Ui::DialogOptions *ui;
};

#endif // DIALOGOPTIONS_HPP
