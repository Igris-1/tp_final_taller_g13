#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <QPushButton>
#include <QMouseEvent>
#include <QPoint>

class Structure : public QPushButton {
    Q_OBJECT

public:
    explicit Structure(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QPoint dragStartPosition;

    // destructor
    ~Structure() = default;

    void deleteItem();
};

#endif // STRUCTURE_H
