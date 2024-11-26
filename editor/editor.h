#ifndef EDITOR_H
#define EDITOR_H

#include <QMainWindow>
#include <QMediaPlayer>

namespace Ui {
class Editor;
}

class Editor: public QMainWindow {
    Q_OBJECT

public:
    explicit Editor(QWidget* parent = nullptr, QMediaPlayer* player);

    ~Editor();

private slots:
    void on_exitButton_clicked();
    void on_musicButton_clicked();
    void on_saveButton_clicked();

    // ITEMS
    void on_item_1_clicked();
    void on_item_2_clicked();
    void on_item_3_clicked();
    void on_item_4_clicked();
    
private:
    Ui::Editor* ui;
    QMediaPlayer* mediaPlayer;
    int itemCounter;

    void deleteItems();
};

#endif  // EDITOR_H
