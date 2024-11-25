#ifndef EDITOR_H
#define EDITOR_H

#include <QDialog>
#include <QMediaPlayer>

namespace Ui {
class Editor;
}

class Editor: public QDialog {
    Q_OBJECT

public:
    explicit Editor(QWidget* parent, QMediaPlayer* player);

    ~Editor();

private slots:

    void on_backButton_clicked();
    void on_musicButton_clicked();
    void on_saveButton_clicked();

    // ITEMS
    void on_item_1_clicked();
    void on_item_2_clicked();
    void on_item_3_clicked();
    void on_item_4_clicked();
    void on_item_5_clicked();
    void on_item_6_clicked();
    void on_item_7_clicked();
    void on_item_8_clicked();
    
private:
    Ui::Editor* ui;
    QMediaPlayer* player;
    int itemCounter;

    void deleteItems();
};

#endif  // EDITOR_H
