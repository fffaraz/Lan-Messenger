#include "roomwindow.h"
#include "ui_roomwindow.h"

RoomWindow::RoomWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RoomWindow)
{
    ui->setupUi(this);
    ui->txtInput->setFocus();
}

RoomWindow::~RoomWindow()
{
    delete ui;
}

void RoomWindow::on_btnSend_clicked()
{
    emit enteredText(ui->txtInput->text());
    ui->txtChat->append("Me: " + ui->txtInput->text());
    ui->txtInput->clear();
    ui->txtInput->setFocus();
}

void RoomWindow::receivedPM(QString from, QString text)
{
    QString f = from.count()>1? from + " : " : "";
    ui->txtChat->append(f + text);
}

void RoomWindow::on_txtInput_returnPressed()
{
    on_btnSend_clicked();
}

void RoomWindow::closeEvent(QCloseEvent *event)
{
    emit closedWindow();
    event->accept();
    this->deleteLater();
}

void RoomWindow::updateList(QList<QString> list)
{
    ui->listUsers->clear();
    for(int i=0; i<list.count(); i++)
        ui->listUsers->addItem(list[i]);
}


void RoomWindow::on_listUsers_doubleClicked(const QModelIndex &index)
{
    QString userid = ui->listUsers->currentItem()->text();
    emit startPM(userid);
}
