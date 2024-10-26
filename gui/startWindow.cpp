#include "startWindow.h"

#include <QPalette>
#include <QPixmap>

#include "ui_startWindow.h"  // Archivo generado por uic

StartWindow::StartWindow(QWidget* parent): QMainWindow(parent), ui(new Ui::StartWindow) {
    ui->setupUi(this);

    // Configuración del fondo de la ventana
    QPixmap bkgnd(":/fondo");  // Carga el recurso usando la ruta interna de Qt
    if (bkgnd.isNull()) {
        qDebug() << "Error: No se pudo cargar la imagen de fondo desde el recurso";
    } else {
        bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
        QPalette palette;
        palette.setBrush(QPalette::Window, bkgnd);
        this->setPalette(palette);
    }
}

StartWindow::~StartWindow() { delete ui; }
