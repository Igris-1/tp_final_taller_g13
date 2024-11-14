#include "aboutwindow.h"

#include <QDesktopServices>
#include <QUrl>

#include "ui_aboutwindow.h"

AboutWindow::AboutWindow(QWidget* parent): QDialog(parent), ui(new Ui::AboutWindow) {
    ui->setupUi(this);
}

AboutWindow::~AboutWindow() { delete ui; }

void AboutWindow::on_gameRepoButton_clicked() {
    QUrl url("https://github.com/Igris-1/tp_final_taller_g13");  // Reemplaza con tu enlace
    QDesktopServices::openUrl(url);
}

void AboutWindow::on_fedeButton_clicked() {
    QUrl url("https://github.com/FedericoMPeralta");  // Reemplaza con tu enlace
    QDesktopServices::openUrl(url);
}

void AboutWindow::on_nicoButton_clicked() {
    QUrl url("https://github.com/Igris-1");  // Reemplaza con tu enlace
    QDesktopServices::openUrl(url);
}

void AboutWindow::on_franButton_clicked() {
    QUrl url("https://github.com/franzimbi");  // Reemplaza con tu enlace
    QDesktopServices::openUrl(url);
}

void AboutWindow::on_pedroButton_clicked() {
    QUrl url("https://github.com/PedroBubuli");  // Reemplaza con tu enlace
    QDesktopServices::openUrl(url);
}

void AboutWindow::on_backButton_clicked() { this->close(); }
