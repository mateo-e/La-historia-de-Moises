#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "proyectil.h"
#include "Personaje.h"
#include <QKeyEvent>
#include <QLabel>
#include <QPixmap>
#include <villano.h>
#include <obstaculo.h>
#include <QFile>
#include <vector>
#include <QList>
#include <QRandomGenerator>


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
    void perseguirJugador(villano * entidad);
    QGraphicsScene *scene;
    void hmov(Proyectil *bola);

private slots:

    void Actualizacion();
    void aumentarCronometro();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void on_JugarBtn_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QTimer *cronometro;
    QList <obstaculo *> obstaculos;
    QList <villano *> enemigos;
    QList <Personaje *> hebreos;
    bool evaluarColision(Personaje * entidad,char dir);
    bool enemigoColisiona(villano * entidad,char dir);
    villano *faraon;
    Personaje *moises;
    float tiempo = 0;
    short int cont = 0;
    short int num_escena = 0;
    bool Apuntando;
    short int angulo_tiro = 45;
    short int bg_posx = 0;
    QGraphicsPixmapItem *background;
    obstaculo *cactus;
    obstaculo *casa;
    obstaculo *marco;
    obstaculo *brocha;
};
#endif // MAINWINDOW_H
