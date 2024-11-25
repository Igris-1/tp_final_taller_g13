#ifndef BOX_H
#define BOX_H

#include <QPushButton>
#include <QMouseEvent>
#include <QPoint>

class Box : public QPushButton {
    Q_OBJECT

public:
    explicit Box(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QPoint dragStartPosition;

    // destructor
    ~Box() = default;

    void deleteItem();
};

#endif // BOX_H
