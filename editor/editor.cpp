#include "editor.h"

#include "ui_editor.h"
#include <iostream>
#include <QMessageBox>
#include <memory>
#include <QFileDialog>
#include "box.h"

Editor::Editor(QWidget* parent, QMediaPlayer* player) : 
    QDialog(parent), 
    ui(new Ui::Editor),
    player(player),
    itemCounter(0) { 
        ui->setupUi(this);
    }

Editor::~Editor() { 
        delete ui; 
    }


void Editor::on_musicButton_clicked() {
    std::cout << "musicButton clicked" << std::endl;

    if (this->player->playbackState() == QMediaPlayer::PlayingState) {
        this->player->pause();
    } else {
        this->player->play();
    }
}

void Editor::on_saveButton_clicked() {
    // hacer cosas falopas con el editor
}

void Editor::on_item_1_clicked() {
    std::cout << "item_1 clicked" << std::endl;
    Box *box = new Box(this);
    box->setGeometry(ui->item_1->geometry()); // Toma la posición original del botón
    box->setStyleSheet("border-image: url(:/assets/images/editor/box.png);");
    box->show();
}

void Editor::on_item_2_clicked() {
    std::cout << "item_2 clicked" << std::endl;
    Box *box = new Box(this);
    box->setGeometry(ui->item_2->geometry()); // Toma la posición original del botón
    box->setStyleSheet("border-image: url(:/assets/images/editor/land_rock.png);");
    box->show();
}

void Editor::on_item_3_clicked() {
    std::cout << "item_3 clicked" << std::endl;
    Box *box = new Box(this);
    box->setGeometry(ui->item_3->geometry()); // Toma la posición original del botón
    box->setStyleSheet("border-image: url(:/assets/images/editor/horizontal_rock_2.png);");
    box->show();
}

void Editor::on_item_4_clicked() {
    std::cout << "item_4 clicked" << std::endl;
    Box *box = new Box(this);
    box->setGeometry(ui->item_4->geometry()); // Toma la posición original del botón
    box->setStyleSheet("border-image: url(:/assets/images/editor/horizontal_rock.png);");
    box->show();
}


void Editor::deleteItems() {
    // Elimina todos los items del editor

}
