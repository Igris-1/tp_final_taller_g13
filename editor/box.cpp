#include "box.h"

Box::Box(QWidget *parent)
    : QPushButton(parent) {}

void Box::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        dragStartPosition = event->pos(); // Guarda la posición del clic
    } else if (event->button() == Qt::RightButton) {
        deleteItem(); // Elimina el botón
    }
}

void Box::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        move(pos() + event->pos() - dragStartPosition); // Mueve el botón
    }
}

void Box::deleteItem() {
    this->hide();           
    this->deleteLater();    
    if (parentWidget()) {   
        parentWidget()->update(); 
    }
}
