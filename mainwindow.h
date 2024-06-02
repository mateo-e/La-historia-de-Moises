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
#include <QFile>
#include <QList>

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
    void crear_mapa();
    QGraphicsScene *scene;
    void hmov(Proyectil *bola);

private slots:

    void Actualizacion();
    void aumentarCronometro();
    void keyPressEvent(QKeyEvent *event);
    void on_JugarBtn_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QTimer *cronometro;
    QList <pared *> paredes;
    QList <faraon *> enemigos;
    faraon *villano;
    Personaje *moises;
    float tiempo = 0;
    short int num_escena = 0;
    bool Apuntando;
    short int angulo_tiro = 45;
    short int bg_posx = 0;
    QGraphicsPixmapItem *background;
    pared *cactus;
    pared *casa;
    pared *marco;
    pared *brocha;


};
#endif // MAINWINDOW_H
