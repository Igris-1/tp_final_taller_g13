#include "connectionwindow.h"

#include <QPalette>
#include <QPixmap>
#include "chooseoptionwindow.h"

#include <ostream>
#include <iostream>
#include <QMessageBox>
#include <utility>
#include "ui_connectionwindow.h"

ConnectionWindow::ConnectionWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::ConnectionWindow)
{
    ui->setupUi(this);
    chooseOptionWindow = NULL;
}

ConnectionWindow::~ConnectionWindow()
{
    if (this->chooseOptionWindow != NULL)
        delete this->chooseOptionWindow;
    delete ui;
}


void ConnectionWindow::on_pushButton_clicked()
{
    QString port = ui->portLineEdit->text();
    QString address = ui->addressLineEdit->text();

    try {
        // Levantar el cliente, si es necesario.
        // Client cl(address.toStdString(), port.toStdString());

        this->chooseOptionWindow = new ChooseOptionWindow(nullptr);
        hide();
        this->chooseOptionWindow->show();
        this->chooseOptionWindow->playMusic();

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error");
        msgBox.setText("Error joining server");
        msgBox.setStyleSheet("QMessageBox { background-color: gray; border: 1px solid gray; }");
        msgBox.exec();
    }
}

void ConnectionWindow::on_exitGameButton_clicked()
{
    QApplication::quit();
}