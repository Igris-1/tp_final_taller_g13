#include <QMovie>
#include "loadingscreen.h" // Include the header file for LoadingScreen
#include "ui_loadingscreen.h" // Include the header file for Ui::LoadingScreen

// Definition of LoadingScreen class
class LoadingScreen : public QMainWindow {
    Q_OBJECT

public:
    explicit LoadingScreen(QWidget *parent = nullptr);
    ~LoadingScreen();

private:
    Ui::LoadingScreen *ui;
};

// Constructor de tu ventana o widget
LoadingScreen::LoadingScreen(QWidget *parent) : QMainWindow(nullptr), ui(new Ui::LoadingScreen) {
    ui->setupUi(this);

    // Configurar el GIF como fondo
    QMovie *movie = new QMovie(":../assets/music/menu_song.mp3"); // Ruta al GIF
    ui->backgroundLabel->setMovie(movie);
    ui->backgroundLabel->setScaledContents(true); // Escala el contenido al tamaño del QLabel
    movie->start();
}