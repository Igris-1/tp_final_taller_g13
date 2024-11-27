#ifndef EDITOR_H
#define EDITOR_H

#include <QMainWindow>
#include <QAudioOutput>
#include <QMediaPlayer>
#include "structure.h"

QT_BEGIN_NAMESPACE

namespace Ui {
class Editor;
}

QT_END_NAMESPACE

class Editor: public QMainWindow {
    Q_OBJECT

public:
    explicit Editor(QWidget* parent = nullptr);
    ~Editor();

private slots:
    void on_exitButton_clicked();
    void on_musicButton_clicked();
    void on_saveButton_clicked();
    void on_cleanButton_clicked();

    // ITEMS
    void on_item_1_clicked();
    void on_item_2_clicked();
    void on_item_3_clicked();
    void on_item_4_clicked();
    void on_item_5_clicked();
    void on_item_6_clicked();

private:
    Ui::Editor* ui;
    QMediaPlayer* mediaPlayer;
    QAudioOutput* audioOutput;
    std::list<Structure*> items;

    void deleteItems();
};

#endif  // EDITOR_H
