  #ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "proyectil.h"
#include "Personaje.h"
#include <QKeyEvent>
#include <QLabel>
#include <QPixmap>
#include <faraon.h>
#include <pared.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void set_escena(short num_escena);
    void update_proyectil();
    QGraphicsScene *scene;
    void hmov(Proyectil *bola);

private slots:

    void Actualizacion();
    void keyPressEvent(QKeyEvent *event);
    void on_JugarBtn_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    faraon *villano;
    Personaje *moises;
    short int num_escena;
    bool Apuntando;
    short int angulo_tiro = 45;
    QGraphicsPixmapItem *background;
    short int bg_posx = 0;

};
#endif // MAINWINDOW_H
