#ifndef PMWINDOW_H
#define PMWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QCloseEvent>

namespace Ui {
class PMWindow;
}

class PMWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit PMWindow(QWidget *parent = 0);
    ~PMWindow();
    
private:
    Ui::PMWindow *ui;
    void closeEvent (QCloseEvent * event) ;

public slots:
    void receivedPM(QString text);

signals:
    void enteredText(QString text);
    void closedWindow();

private slots:
    void on_btnSend_clicked();
    void on_txtInput_returnPressed();
};

#endif // PMWINDOW_H
