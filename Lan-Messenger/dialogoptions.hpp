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
