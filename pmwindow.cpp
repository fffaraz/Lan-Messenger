#include "pmwindow.h"
#include "ui_pmwindow.h"

PMWindow::PMWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PMWindow)
{
    ui->setupUi(this);
    ui->txtInput->setFocus();
}

PMWindow::~PMWindow()
{
    delete ui;
}

void PMWindow::on_btnSend_clicked()
{
    emit enteredText(ui->txtInput->text());
    ui->txtChat->append("Me: " + ui->txtInput->text());
    ui->txtInput->clear();
    ui->txtInput->setFocus();
}

void PMWindow::receivedPM(QString text)
{
    ui->txtChat->append(this->windowTitle() + " : " + text);
}

void PMWindow::on_txtInput_returnPressed()
{
    on_btnSend_clicked();
}

void PMWindow::closeEvent(QCloseEvent *event)
{
    emit closedWindow();
    event->accept();
    this->deleteLater();
}
