#include "joingamewindow.h"
#include "ui_joingamewindow.h"
#include <vector>
#include <string>
#include <map>
#include <QMessageBox>


JoinWindow::JoinWindow(QWidget *parent) :
        QDialog(parent),
        //cl(std::move(cl)),
        ui(new Ui::JoinWindow)
{
    ui->setupUi(this);
}

JoinWindow::~JoinWindow()
{
    delete ui;
}

void JoinWindow::on_refreshButton_clicked()
{

}


void JoinWindow::on_joinButton_clicked()
{
    

}