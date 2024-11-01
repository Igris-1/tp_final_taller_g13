#include "connectionwindow.h"

#include <QPalette>
#include <QPixmap>
//#include "chooseoptionwindow.h"

#include <ostream>
#include <iostream>
#include <QMessageBox>
#include <utility>
#include "ui_connectionwindow.h"  // Archivo generado por uic

ConnectionWindow::ConnectionWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::ConnectionWindow)
{
    ui->setupUi(this);
    //this->chooseOptionWindow = NULL;

}

ConnectionWindow::~ConnectionWindow()
{
    // if (this->chooseOptionWindow != NULL)
    //     delete this->chooseOptionWindow;

    delete ui;
}


void ConnectionWindow::on_pushButton_clicked()
{

    // QString port = ui->portLineEdit->text();
    // QString address = ui->addressLineEdit->text();

    try {

        // aca hay que levantar el cliente ponele 
        // Client cl(address.toStdString(), port.toStdString());

        // Esta es la ventana que se abre despues de conectarse,
        // seria el menu que ve el cliente
        // this->chooseOptionWindow = new ChooseOptionWindow(nullptr);
        // hide();
        // this->chooseOptionWindow->show();

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error");
        msgBox.setText("Error joining server");
        msgBox.exec();
        msgBox.setStyleSheet("QMessageBox { background-color: gray; border: 1px solid gray; }");
    }
}
