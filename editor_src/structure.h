#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <QMouseEvent>
#include <QPoint>
#include <QPushButton>

#include <yaml-cpp/yaml.h>

class Structure: public QPushButton {
    Q_OBJECT

public:
    explicit Structure(QWidget* parent = nullptr);
    QString type;
    bool alive;

    ~Structure() = default;

    void toYaml(YAML::Emitter& out) const;
    void setType(const QString& type);
    QString getType() const;

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

private:
    QPoint dragStartPosition;

    void deleteItem();
};

#endif  // STRUCTURE_H
