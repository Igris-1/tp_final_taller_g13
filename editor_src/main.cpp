#include <QApplication>

#include "editor.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    Editor w;
    w.show();
    return a.exec();
}
