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
