#include "connectionwindow.h"

#include <QMessageBox>
#include <QPalette>
#include <QPixmap>
#include <iostream>
#include <ostream>
#include <utility>

#include "chooseoptionwindow.h"
#include "ui_connectionwindow.h"

ConnectionWindow::ConnectionWindow(QWidget* parent):
        QMainWindow(parent), ui(new Ui::ConnectionWindow) {
    ui->setupUi(this);
    chooseOptionWindow = NULL;
}

ConnectionWindow::~ConnectionWindow() {
    if (this->chooseOptionWindow != NULL)
        delete this->chooseOptionWindow;
    delete ui;
}


void ConnectionWindow::on_pushButton_clicked() {
    QString port = ui->portLineEdit->text();
    QString address = ui->addressLineEdit->text();
    
    if (port.isEmpty() || address.isEmpty()) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error");
        msgBox.setText("Please fill in all fields");
        msgBox.setStyleSheet("QMessageBox { background-color: gray; border: 1px solid gray; }");
        msgBox.exec();
        return;
    }

    QByteArray byteArrayPort = port.toUtf8();
    char* charPort = byteArrayPort.data();

    QByteArray byteArrayAddress = address.toUtf8();
    char* charAddress = byteArrayAddress.data();

    try {
        this->chooseOptionWindow = new ChooseOptionWindow(nullptr, charAddress, charPort);
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

void ConnectionWindow::on_exitGameButton_clicked() { QApplication::quit(); }