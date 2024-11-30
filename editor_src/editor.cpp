#include "editor.h"

#include <QFileDialog>
#include <QMessageBox>
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

    // Config mediaPlayer
    mediaPlayer->setAudioOutput(audioOutput);
    mediaPlayer->setSource(QUrl("qrc:/assets/music/editor_music.mp3"));
    this->mediaPlayer->setLoops(QMediaPlayer::Infinite);
    audioOutput->setVolume(0.2);
    mediaPlayer->play();
}

Editor::~Editor() { delete ui; }


void Editor::on_exitButton_clicked() {
    std::cout << "exitButton clicked" << std::endl;

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
    std::cout << "musicButton clicked" << std::endl;

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
    std::cout << "saveButton clicked" << std::endl;

    // Crear QFileDialog con estilos
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
        // Crear QMessageBox con estilos si el usuario cancela
        QMessageBox cancelBox(this);
        cancelBox.setWindowTitle("Operación cancelada");
        cancelBox.setText("No se guardó ningún archivo.");
        cancelBox.setIcon(QMessageBox::Information);

        // Aplicar estilos
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
    // Inicia el YAML
    out << YAML::BeginMap;

    // Información del mapa
    out << YAML::Key << "map" << YAML::Value << YAML::BeginMap 
        << YAML::Key << "map_width" << YAML::Value << this->width() 
        << YAML::Key << "map_height" << YAML::Value << this->height() 
        << YAML::EndMap;

    // Agrupaciones
    QMap<QString, QList<const Structure*>> groupedElements;
    for (const auto* item: items) {  // `items` es tu lista de estructuras
        groupedElements[item->getType()].append(item);
    }

    std::cout << "groupedElements.size(): " << groupedElements.size() << std::endl;

    // Guardar cada grupo
    for (auto it = groupedElements.cbegin(); it != groupedElements.cend(); ++it) {
        out << YAML::Key << it.key().toStdString() << YAML::Value << YAML::BeginSeq;
        for (const auto* element: it.value()) {
            element->toYaml(out);
        }
        out << YAML::EndSeq;
    }

    // Termina el YAML
    out << YAML::EndMap;

    // Escribir en archivo
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << out.c_str();
        file.close();

        // Crear QMessageBox con estilos para éxito
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
        // Crear QMessageBox con estilos para error
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
    std::cout << "openButton clicked" << std::endl;

    // Crear QFileDialog para abrir archivo
    QFileDialog openDialog(this, "Abrir archivo");
    openDialog.setAcceptMode(QFileDialog::AcceptOpen);
    openDialog.setFileMode(QFileDialog::ExistingFile);
    openDialog.setDirectory("../configuration_yamls/");
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
        // Crear QMessageBox con estilos si el usuario cancela
        QMessageBox cancelBox(this);
        cancelBox.setWindowTitle("Operación cancelada");
        cancelBox.setText("No se seleccionó ningún archivo.");
        cancelBox.setIcon(QMessageBox::Information);

        // Aplicar estilos
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

    // Obtener la ruta del archivo seleccionado
    QString filePath = openDialog.selectedFiles().first();
    std::cout << "Archivo seleccionado: " << filePath.toStdString() << std::endl;

    // parser

    try {
        // Parsear el archivo YAML
        YAML::Node config = YAML::LoadFile(filePath.toStdString());

        // Leer las dimensiones del mapa
        int mapWidth = config["map"]["map_width"].as<int>();
        int mapHeight = config["map"]["map_height"].as<int>();

        // Cambiar las dimensiones del editor
        this->setMinimumSize(mapWidth, mapHeight);
        std::cout << "Dimensiones del mapa: " << mapWidth << "x" << mapHeight << std::endl;

        // Crear objetos: cajas (boxes)
        if (config["boxes"]) {
            for (const auto& box : config["boxes"]) {
                int x = box["x"].as<int>();
                int y = box["y"].as<int>();
                int width = box["width"].as<int>();
                int height = box["height"].as<int>();

                Structure* structure = new Structure(this);
                this->items.push_back(structure);
                structure->setType("boxes");
                structure->setGeometry(x, y, width, height);  // Toma la posición original del botón
                structure->setStyleSheet("border-image: url(:/assets/images/box.png);");
                structure->show();
                std::cout << "Caja creada en (" << x << ", " << y << ") con tamaño " << width << "x" << height << std::endl;
            }
        }

        // Crear objetos: patos (ducks)
        if (config["ducks"]) {
            for (const auto& duck : config["ducks"]) {
                int x = duck["x"].as<int>();
                int y = duck["y"].as<int>();
                int width = duck["width"].as<int>();
                int height = duck["height"].as<int>();

                Structure* structure = new Structure(this);
                this->items.push_back(structure);
                structure->setType("boxes");
                structure->setGeometry(x, y, width, height);  // Toma la posición original del botón
                structure->setStyleSheet("border-image: url(:/assets/images/respawn.png);");
                structure->show();
                std::cout << "Pato creado en (" << x << ", " << y << ") con tamaño " << width << "x" << height << std::endl;
            }
        }

        // Crear objetos: plataformas (platforms)
        if (config["platforms"]) {
            for (const auto& platform : config["platforms"]) {
                int x = platform["x"].as<int>();
                int y = platform["y"].as<int>();
                int width = platform["width"].as<int>();
                int height = platform["height"].as<int>();

                Structure* structure = new Structure(this);
                    structure->setType("platforms");
                if (width > height) {
                    structure->setGeometry(x, y, width, height);  // Toma la posición original del botón
                    structure->setStyleSheet("border-image: url(:/assets/images/horizontal_wood.png);");
                } else {
                    structure->setGeometry(x, y, width, height);  // Toma la posición original del botón
                    structure->setStyleSheet("border-image: url(:/assets/images/vertical_wood.png);");
                }
                this->items.push_back(structure);
                structure->show();
                std::cout << "Plataforma creada en (" << x << ", " << y << ") con tamaño " << width << "x" << height << std::endl;
            }

        // Crear objetos: armas (weapons)
            if (config["weapons"]) {
                for (const auto& weapon : config["weapons"]) {
                    int x = weapon["x"].as<int>();
                    int y = weapon["y"].as<int>();
                    int width = weapon["width"].as<int>();
                    int height = weapon["height"].as<int>();

                    Structure* structure = new Structure(this);
                    this->items.push_back(structure);
                    structure->setType("platforms");
                    structure->setGeometry(x, y, width, height);  // Toma la posición original del botón
                    structure->setStyleSheet("border-image: url(:/assets/images/gunSpawner.png);");
                    structure->show();
                    std::cout << "Arma creada en (" << x << ", " << y << ") con tamaño " << width << "x" << height << std::endl;
                }
            }
        }

    } catch (const YAML::Exception& e) {
        QMessageBox::critical(this, "Error", QString("Error al leer el archivo YAML: %1").arg(e.what()));
        std::cerr << "Error al leer el archivo YAML: " << e.what() << std::endl;
    }
}



void Editor::on_cleanButton_clicked() {
    std::cout << "cleanButton clicked" << std::endl;
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
    std::cout << "item_1 clicked" << std::endl;

    Structure* structure = new Structure(this);
    this->items.push_back(structure);
    structure->setType("boxes");
    structure->setGeometry(ui->item_1->geometry());  // Toma la posición original del botón
    structure->setStyleSheet("border-image: url(:/assets/images/box.png);");
    structure->show();
}

void Editor::on_item_2_clicked() {
    std::cout << "item_2 clicked" << std::endl;

    Structure* structure = new Structure(this);
    structure->setType("platforms");
    this->items.push_back(structure);
    structure->setGeometry(ui->item_2->geometry());  // Toma la posición original del botón
    structure->setStyleSheet("border-image: url(:/assets/images/one_block.png);");
    structure->show();
}

void Editor::on_item_3_clicked() {
    std::cout << "item_3 clicked" << std::endl;

    Structure* structure = new Structure(this);
    structure->setType("platforms");
    this->items.push_back(structure);
    structure->setGeometry(ui->item_3->geometry());  // Toma la posición original del botón
    structure->setStyleSheet("border-image: url(:/assets/images/horizontal_wood.png);");
    structure->show();
}

void Editor::on_item_4_clicked() {
    std::cout << "item_4 clicked" << std::endl;

    Structure* structure = new Structure(this);
    structure->setType("platforms");
    this->items.push_back(structure);
    structure->setGeometry(ui->item_4->geometry());  // Toma la posición original del botón
    structure->setStyleSheet("border-image: url(:/assets/images/vertical_wood.png);");
    structure->show();
}

void Editor::on_item_5_clicked() {
    std::cout << "item_5 clicked" << std::endl;

    Structure* structure = new Structure(this);
    structure->setType("ducks");
    this->items.push_back(structure);
    structure->setGeometry(ui->item_5->geometry());  // Toma la posición original del botón
    structure->setStyleSheet("border-image: url(:/assets/images/respawn.png);");
    structure->show();
}

void Editor::on_item_6_clicked() {
    std::cout << "item_6 clicked" << std::endl;

    Structure* structure = new Structure(this);
    structure->setType("weapons");
    this->items.push_back(structure);
    structure->setGeometry(ui->item_6->geometry());  // Toma la posición original del botón
    structure->setStyleSheet("border-image: url(:/assets/images/gunSpawner.png);");
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

    std::cout << this->items.size() << std::endl;
}
