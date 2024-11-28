#include "editor.h"

#include "ui_editor.h"
#include <iostream>
#include <QMessageBox>
#include <memory>
#include <QFileDialog>
#include "structure.h"
#include <yaml-cpp/yaml.h>
#include <fstream>

Editor::Editor(QWidget* parent):
        QMainWindow(parent), 
        ui(new Ui::Editor),
        items(),
        mediaPlayer(new QMediaPlayer(this)),
        audioOutput(new QAudioOutput(this)) {
    ui->setupUi(this);
    
    // Config mediaPlayer
    mediaPlayer->setAudioOutput(audioOutput);
    mediaPlayer->setSource(QUrl("qrc:/assets/music/editor_music.mp3"));
    this->mediaPlayer->setLoops(QMediaPlayer::Infinite);
    audioOutput->setVolume(0.2);
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
    std::cout << "saveButton clicked" << std::endl;
    YAML::Emitter out;

    // Inicia el YAML
    out << YAML::BeginMap;

    // Información del mapa
    out << YAML::Key << "map" << YAML::Value << YAML::BeginMap
        << YAML::Key << "map_width" << YAML::Value << this->width()
        << YAML::Key << "map_height" << YAML::Value << this->height()
        << YAML::EndMap;
    
    // Agrupaciones
    QMap<QString, QList<const Structure*>> groupedElements;
    for (const auto* item : items) {  // `items` es tu lista de estructuras
        groupedElements[item->getType()].append(item);
    }

    std::cout << "groupedElements.size(): " << groupedElements.size() << std::endl;
    // Guardar cada grupo
    for (auto it = groupedElements.cbegin(); it != groupedElements.cend(); ++it) {
        out << YAML::Key << it.key().toStdString() << YAML::Value << YAML::BeginSeq;
        for (const auto* element : it.value()) {
            element->toYaml(out);
        }
        out << YAML::EndSeq;
    }

    // Termina el YAML
    out << YAML::EndMap;

    // Escribir en archivo
    QFile file("../configuration_yamls/custom_map.yaml");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << out.c_str();
        file.close();
    }
}

void Editor::on_cleanButton_clicked() {
    std::cout << "cleanButton clicked" << std::endl;
    if (this->items.size() != 0) {

        QMessageBox messageBox(this);
        messageBox.setWindowTitle("Limpiar");
        messageBox.setText("¿Estás seguro que deseas limpiar el editor?");
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
            this->deleteItems();
        }
    }
}

void Editor::on_item_1_clicked() {
    std::cout << "item_1 clicked" << std::endl;

    Structure *structure = new Structure(this);
    this->items.push_back(structure);
    structure->setType("boxes");
    structure->setGeometry(ui->item_1->geometry()); // Toma la posición original del botón
    structure->setStyleSheet("border-image: url(:/assets/images/box.png);");
    structure->show();
}

void Editor::on_item_2_clicked() {
    std::cout << "item_2 clicked" << std::endl;

    Structure *structure = new Structure(this);
    structure->setType("platforms");
    this->items.push_back(structure);
    structure->setGeometry(ui->item_2->geometry()); // Toma la posición original del botón
    structure->setStyleSheet("border-image: url(:/assets/images/one_block.png);");
    structure->show();
}

void Editor::on_item_3_clicked() {
    std::cout << "item_3 clicked" << std::endl;

    Structure *structure = new Structure(this);
    structure->setType("platforms");
    this->items.push_back(structure);
    structure->setGeometry(ui->item_3->geometry()); // Toma la posición original del botón
    structure->setStyleSheet("border-image: url(:/assets/images/horizontal_wood.png);");
    structure->show();
}

void Editor::on_item_4_clicked() {
    std::cout << "item_4 clicked" << std::endl;
    
    Structure *structure = new Structure(this);
    structure->setType("platforms");
    this->items.push_back(structure);
    structure->setGeometry(ui->item_4->geometry()); // Toma la posición original del botón
    structure->setStyleSheet("border-image: url(:/assets/images/vertical_wood.png);");
    structure->show();
}

void Editor::on_item_5_clicked() {
    std::cout << "item_5 clicked" << std::endl;
    
    Structure *structure = new Structure(this);
    structure->setType("ducks");
    this->items.push_back(structure);
    structure->setGeometry(ui->item_5->geometry()); // Toma la posición original del botón
    structure->setStyleSheet("border-image: url(:/assets/images/respawn.png);");
    structure->show();
}

void Editor::on_item_6_clicked() {
    std::cout << "item_6 clicked" << std::endl;
    
    Structure *structure = new Structure(this);
    structure->setType("weapons");
    this->items.push_back(structure);
    structure->setGeometry(ui->item_6->geometry()); // Toma la posición original del botón
    structure->setStyleSheet("border-image: url(:/assets/images/gunSpawner.png);");
    structure->show();
}


void Editor::deleteItems() {
    for (auto &item : this->items) {
        if (item != nullptr) {
            item->hide();
            item->deleteLater();
        }
    }
    this->items.clear();

    std::cout << this->items.size() << std::endl;
}
