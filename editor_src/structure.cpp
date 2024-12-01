#include "structure.h"

#include <iostream>

#include <yaml-cpp/yaml.h>

Structure::Structure(QWidget* parent): QPushButton(parent), type("Structure"), alive(true) {}


void Structure::toYaml(YAML::Emitter& out) const {
    out << YAML::Flow << YAML::BeginMap << YAML::Key << "x" << YAML::Value << this->x() << YAML::Key
        << "y" << YAML::Value << this->y() << YAML::Key << "width" << YAML::Value << this->width()
        << YAML::Key << "height" << YAML::Value << this->height() << YAML::EndMap;
}

void Structure::setType(const QString& type) { this->type = type; }

QString Structure::getType() const { return this->type; }

void Structure::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        dragStartPosition = event->pos();
    } else if (event->button() == Qt::RightButton) {
        this->alive = false;
        deleteItem();
    }
}

void Structure::mouseMoveEvent(QMouseEvent* event) {
    if (event->buttons() & Qt::LeftButton) {
        move(pos() + event->pos() - dragStartPosition);
    }
}

void Structure::deleteItem() {
    this->hide();
    if (parentWidget()) {
        parentWidget()->update();
    }
}
