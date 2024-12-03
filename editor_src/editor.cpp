#include "editor.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QLayout>
#include <QTimer>
#include <fstream>
#include <iostream>
#include <memory>

#include <yaml-cpp/yaml.h>

#include "structure.h"
#include "ui_editor.h"

Editor::Editor(QWidget* parent):
        QMainWindow(parent),
        ui(new Ui::Editor),
        items(),
        mediaPlayer(new QMediaPlayer(this)),
        audioOutput(new QAudioOutput(this)) {
    ui->setupUi(this);

    mediaPlayer->setAudioOutput(audioOutput);
    mediaPlayer->setSource(QUrl("qrc:/assets/music/editor_music.mp3"));
    this->mediaPlayer->setLoops(QMediaPlayer::Infinite);
    audioOutput->setVolume(0.2);
    mediaPlayer->play();
}

Editor::~Editor() { 
    if (mediaPlayer != nullptr)
        delete mediaPlayer;
    if (audioOutput != nullptr)
        delete audioOutput;
    delete ui; 
    }


void Editor::on_exitButton_clicked() {
    QMessageBox messageBox(this);
    messageBox.setWindowTitle("Salir");
    messageBox.setText("¿Estás seguro que deseas salir?");
    messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    messageBox.setStyleSheet("QMessageBox QLabel {"
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
                             "}");

    if (messageBox.exec() == QMessageBox::Yes) {
        this->close();
    }
}

void Editor::on_musicButton_clicked() {
    if (this->mediaPlayer->playbackState() == QMediaPlayer::PlayingState) {
        this->mediaPlayer->pause();
    } else {
        this->mediaPlayer->play();
    }
}

#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <iostream>
#include "yaml-cpp/yaml.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <iostream>
#include "yaml-cpp/yaml.h"

void Editor::on_saveButton_clicked() {
    QFileDialog saveDialog(this, "Guardar archivo");
    saveDialog.setAcceptMode(QFileDialog::AcceptSave);
    saveDialog.setDirectory("../maps/");
    saveDialog.setNameFilter("Archivos YAML (*.yaml)");
    saveDialog.setStyleSheet(
            "QFileDialog { "
            "   border-image: transparent;"
            "   border: 1px solid #000000; "
            "} "
            "QFileDialog QWidget { "
            "   border-image: transparent;"
            "} "
            "QFileDialog QLabel, "
            "QFileDialog QLineEdit, "
            "QFileDialog QPushButton, "
            "QFileDialog QComboBox { "
            "   border: 1px solid #ccc; "
            "   background: #4CAF50;"
            "   border-radius: 3px; "
            "} "
            "QFileDialog QPushButton { "
            "   border-image: transparent;"
            "   color: white; "
            "   border-radius: 5px; "
            "   padding: 5px; "
            "} "
            "QFileDialog QPushButton:hover { "
            "   background-color: #45a049; "
            "} "
    );

    if (!saveDialog.exec()) {
        QMessageBox cancelBox(this);
        cancelBox.setWindowTitle("Operación cancelada");
        cancelBox.setText("No se guardó ningún archivo.");
        cancelBox.setIcon(QMessageBox::Information);
        cancelBox.setStyleSheet("QMessageBox QLabel {"
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
                            "}");

        cancelBox.exec();
        return;
    }

    QString filePath = saveDialog.selectedFiles().first();

    YAML::Emitter out;
    out << YAML::BeginMap;

    // Información del mapa
    out << YAML::Key << "map" << YAML::Value << YAML::BeginMap 
        << YAML::Key << "map_width" << YAML::Value << this->width() 
        << YAML::Key << "map_height" << YAML::Value << this->height() 
        << YAML::EndMap;

    // Agrupaciones
    QMap<QString, QList<const Structure*>> groupedElements;
    for (const auto* item: items) {
        if (item->alive){
            groupedElements[item->getType()].append(item);
        }
    }

    // Guardar cada grupo
    for (auto it = groupedElements.cbegin(); it != groupedElements.cend(); ++it) {
        out << YAML::Key << it.key().toStdString() << YAML::Value << YAML::BeginSeq;
        for (const auto* element: it.value()) {
            element->toYaml(out);
        }
        out << YAML::EndSeq;
    }

    out << YAML::EndMap;

    // Escribir en archivo
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << out.c_str();
        file.close();

        QMessageBox successBox(this);
        successBox.setWindowTitle("Guardado exitoso");
        successBox.setText("El archivo se guardó correctamente en:\n" + filePath);
        successBox.setIcon(QMessageBox::Information);
        successBox.setStyleSheet("QMessageBox QLabel {"
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
                            "}");
        successBox.exec();
    } else {
        QMessageBox errorBox(this);
        errorBox.setWindowTitle("Error");
        errorBox.setText("No se pudo guardar el archivo.");
        errorBox.setIcon(QMessageBox::Critical);
        errorBox.setStyleSheet("QMessageBox QLabel {"
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
                            "}");
        errorBox.exec();
    }
}

void Editor::on_openButton_clicked() {
    this->deleteItems();

    QFileDialog openDialog(this, "Abrir archivo");
    openDialog.setAcceptMode(QFileDialog::AcceptOpen);
    openDialog.setFileMode(QFileDialog::ExistingFile);
    openDialog.setDirectory("../maps/");
    openDialog.setNameFilter("Archivos YAML (*.yaml)");
    openDialog.setStyleSheet(
            "QFileDialog { "
            "   border-image: transparent;"
            "   border: 1px solid #000000; "
            "} "
            "QFileDialog QWidget { "
            "   border-image: transparent;"
            "} "
            "QFileDialog QLabel, "
            "QFileDialog QLineEdit, "
            "QFileDialog QPushButton, "
            "QFileDialog QComboBox { "
            "   border: 1px solid #ccc; "
            "   background: #4CAF50;"
            "   border-radius: 3px; "
            "} "
            "QFileDialog QPushButton { "
            "   border-image: transparent;"
            "   color: white; "
            "   border-radius: 5px; "
            "   padding: 5px; "
            "} "
            "QFileDialog QPushButton:hover { "
            "   background-color: #45a049; "
            "} "
    );

    if (!openDialog.exec()) {
        QMessageBox cancelBox(this);
        cancelBox.setWindowTitle("Operación cancelada");
        cancelBox.setText("No se seleccionó ningún archivo.");
        cancelBox.setIcon(QMessageBox::Information);
        cancelBox.setStyleSheet("QMessageBox QLabel {"
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
                            "}");

        cancelBox.exec();
        return;
    }

    QString filePath = openDialog.selectedFiles().first();

    // parser
    try {
        YAML::Node config = YAML::LoadFile(filePath.toStdString());

        int mapWidth = config["map"]["map_width"].as<int>();
        int mapHeight = config["map"]["map_height"].as<int>();

        // lo que hay que hacer para que funcione qt...
        this->resize(mapWidth, mapHeight);
        this->showFullScreen();
        this->setWindowFlags(Qt::Window);
        this->showNormal();

        if (config["boxes"]) {
            for (const auto& box : config["boxes"]) {
                int x = box["x"].as<int>();
                int y = box["y"].as<int>();
                int width = box["width"].as<int>();
                int height = box["height"].as<int>();

                Structure* structure = new Structure(this);
                structure->setType("boxes");
                structure->setGeometry(x, y, width, height);
                structure->setStyleSheet("border-image: url(:/assets/images/box.png);");
                structure->show();
                this->items.push_back(structure);
            }
        }

        if (config["ducks"]) {
            for (const auto& duck : config["ducks"]) {
                int x = duck["x"].as<int>();
                int y = duck["y"].as<int>();
                int width = duck["width"].as<int>();
                int height = duck["height"].as<int>();

                Structure* structure = new Structure(this);
                structure->setType("ducks");
                structure->setGeometry(x, y, width, height); 
                structure->setStyleSheet("border-image: url(:/assets/images/respawn.png);");
                structure->show();
                this->items.push_back(structure);
            }
        }

        if (config["platforms"]) {
            for (const auto& platform : config["platforms"]) {
                int x = platform["x"].as<int>();
                int y = platform["y"].as<int>();
                int width = platform["width"].as<int>();
                int height = platform["height"].as<int>();

                Structure* structure = new Structure(this);
                structure->setType("platforms");
                if (width > height) {
                    structure->setGeometry(x, y, width, height); 
                    structure->setStyleSheet("border-image: url(:/assets/images/horizontal_wood.png);");
                } else {
                    structure->setGeometry(x, y, width, height);
                    structure->setStyleSheet("border-image: url(:/assets/images/vertical_wood.png);");
                }
                this->items.push_back(structure);
                structure->show();
            }

            if (config["weapons"]) {
                for (const auto& weapon : config["weapons"]) {
                    int x = weapon["x"].as<int>();
                    int y = weapon["y"].as<int>();
                    int width = weapon["width"].as<int>();
                    int height = weapon["height"].as<int>();

                    Structure* structure = new Structure(this);
                    structure->setType("weapons");
                    structure->setGeometry(x, y, width, height);
                    structure->setStyleSheet("border-image: url(:/assets/images/gunSpawner.png);");
                    structure->show();
                    this->items.push_back(structure);
                }
            }
        }
    } catch (const YAML::Exception& e) {
        QMessageBox::critical(this, "Error", QString("Error al leer el archivo YAML: %1").arg(e.what()));
        std::cerr << "Error al leer el archivo YAML: " << e.what() << std::endl;
    }
}

void Editor::on_cleanButton_clicked() {
    if (this->items.size() != 0) {
        QMessageBox messageBox(this);
        messageBox.setWindowTitle("Limpiar");
        messageBox.setText("¿Estás seguro que deseas limpiar el editor?");
        messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        messageBox.setStyleSheet("QMessageBox QLabel {"
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
                                 "}");
        if (messageBox.exec() == QMessageBox::Yes) {
            this->deleteItems();
        }
    }
}

void Editor::on_item_1_clicked() {
    setStructure(1);
}

void Editor::on_item_2_clicked() {
    setStructure(2);
}

void Editor::on_item_3_clicked() {
    setStructure(3);
}

void Editor::on_item_4_clicked() {
    setStructure(4);
}

void Editor::on_item_5_clicked() {
    setStructure(5);
}

void Editor::on_item_6_clicked() {
    setStructure(6);
}

void Editor::setStructure(int item) {
    Structure *structure = new Structure(this);

    if (item == 1) {
        structure->setType("boxes");
        structure->setGeometry(ui->item_1->geometry());
        structure->setStyleSheet("border-image: url(:/assets/images/box.png);");
    } else if (item == 2) {
        structure->setType("platforms");
        structure->setGeometry(ui->item_2->geometry());
        structure->setStyleSheet("border-image: url(:/assets/images/one_block.png);");
    } else if (item == 3) {
        structure->setType("platforms");
        structure->setGeometry(ui->item_3->geometry());
        structure->setStyleSheet("border-image: url(:/assets/images/horizontal_wood.png);");
    } else if (item == 4) {
        structure->setType("platforms");
        structure->setGeometry(ui->item_4->geometry());
        structure->setStyleSheet("border-image: url(:/assets/images/vertical_wood.png);");
    } else if (item == 5) {
        structure->setType("ducks");
        structure->setGeometry(ui->item_5->geometry());
        structure->setStyleSheet("border-image: url(:/assets/images/respawn.png);");
    } else if (item == 6) {
        structure->setType("weapons");
        structure->setGeometry(ui->item_6->geometry());
        structure->setStyleSheet("border-image: url(:/assets/images/gunSpawner.png);");
    }
    this->items.push_back(structure);
    structure->show();
}

void Editor::deleteItems() {
    for (auto& item: this->items) {
        if (item != nullptr) {
            item->hide();
            item->deleteLater();
        }
    }
    this->items.clear();
}
