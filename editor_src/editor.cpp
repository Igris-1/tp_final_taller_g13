#include "editor.h"

#include "ui_editor.h"
#include <iostream>
#include <QMessageBox>
#include <memory>
#include <QFileDialog>
#include "structure.h"

Editor::Editor(QWidget* parent):
        QMainWindow(parent), 
        ui(new Ui::Editor),
        itemCounter(0),
        mediaPlayer(new QMediaPlayer(this)),
        audioOutput(new QAudioOutput(this)) {
    ui->setupUi(this);
    
    // Config mediaPlayer
    mediaPlayer->setAudioOutput(audioOutput);
    mediaPlayer->setSource(QUrl("qrc:/assets/music/menu_song.mp3"));
    this->mediaPlayer->setLoops(QMediaPlayer::Infinite);
    audioOutput->setVolume(0.4);
    mediaPlayer->play();
}

Editor::~Editor() { 
        delete ui; 
    }


void Editor::on_exitButton_clicked() {
    std::cout << "exitButton clicked" << std::endl;

    QMessageBox messageBox(this);
    messageBox.setWindowTitle("Salir");
    messageBox.setText("¿Estás seguro que deseas salir?");
    messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

    messageBox.setStyleSheet(
        "QMessageBox QLabel {"
        "   background-image: transparent;"
        "   border-image: transparent;"
        "   color: #000000;"
        "}"
        "QMessageBox {"
        "   background-image: transparent;"
        "   border-image: transparent;"
        "   background-color: #f0f0f0;"
        "   border: 2px solid #000000;" 
        "   color: #000000;"           
        "}"
        "QPushButton {"
        "   background-image: transparent;"
        "   border-image: transparent;"
        "   background-color: #d9d9d9;"
        "   color: #000000;"
        "   border: 1px solid #000000;"
        "   border-radius: 5px;"
        "   padding: 5px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #e6e6e6;"
        "}"
    );

    if (messageBox.exec() == QMessageBox::Yes) {
        this->close();
    }
}

void Editor::on_musicButton_clicked() {
    std::cout << "musicButton clicked" << std::endl;

    if (this->mediaPlayer->playbackState() == QMediaPlayer::PlayingState) {
        this->mediaPlayer->pause();
    } else {
        this->mediaPlayer->play();
    }
}

void Editor::on_saveButton_clicked() {
    // hacer cosas falopas con el editor
}

void Editor::on_item_1_clicked() {
    std::cout << "item_1 clicked" << std::endl;
    Structure *structure = new Structure(this);
    structure->setGeometry(ui->item_1->geometry()); // Toma la posición original del botón
    structure->setStyleSheet("border-image: url(:/assets/images/box.png);");
    structure->show();
}

void Editor::on_item_2_clicked() {
    std::cout << "item_2 clicked" << std::endl;
    Structure *structure = new Structure(this);
    structure->setGeometry(ui->item_2->geometry()); // Toma la posición original del botón
    structure->setStyleSheet("border-image: url(:/assets/images/one_block.png);");
    structure->show();
}

void Editor::on_item_3_clicked() {
    std::cout << "item_3 clicked" << std::endl;
    Structure *structure = new Structure(this);
    structure->setGeometry(ui->item_3->geometry()); // Toma la posición original del botón
    structure->setStyleSheet("border-image: url(:/assets/images/horizontal_wood.png);");
    structure->show();
}

void Editor::on_item_4_clicked() {
    std::cout << "item_4 clicked" << std::endl;
    Structure *structure = new Structure(this);
    structure->setGeometry(ui->item_4->geometry()); // Toma la posición original del botón
    structure->setStyleSheet("border-image: url(:/assets/images/vertical_wood.png);");
    structure->show();
}


void Editor::deleteItems() {
    // Elimina todos los items del editor

}
