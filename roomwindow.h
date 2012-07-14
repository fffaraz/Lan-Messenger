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
