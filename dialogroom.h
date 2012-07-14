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
