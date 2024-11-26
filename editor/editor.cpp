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
        mediaPlayer(new QMediaPlayer(this)) {
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
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Salir", "¿Estás seguro que deseas salir?",
                                                              QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
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
    structure->setStyleSheet("border-image: url(:/assets/images/editor/box.png);");
    structure->show();
}

void Editor::on_item_2_clicked() {
    std::cout << "item_2 clicked" << std::endl;
    Structure *structure = new Structure(this);
    structure->setGeometry(ui->item_2->geometry()); // Toma la posición original del botón
    structure->setStyleSheet("border-image: url(:/assets/images/editor/one_bock.png);");
    structure->show();
}

void Editor::on_item_3_clicked() {
    std::cout << "item_3 clicked" << std::endl;
    Structure *structure = new Structure(this);
    structure->setGeometry(ui->item_3->geometry()); // Toma la posición original del botón
    structure->setStyleSheet("border-image: url(:/assets/images/editor/vertical_wood.png);");
    structure->show();
}

void Editor::on_item_4_clicked() {
    std::cout << "item_4 clicked" << std::endl;
    Structure *structure = new Structure(this);
    structure->setGeometry(ui->item_4->geometry()); // Toma la posición original del botón
    structure->setStyleSheet("border-image: url(:/assets/images/editor/horizontal_wood.png);");
    structure->show();
}


void Editor::deleteItems() {
    // Elimina todos los items del editor

}
