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
    QTimer *timer, *cronometro;
    QList <obstaculo *> obstaculos;
    QList <villano *> enemigos;
    QList <Personaje *> hebreos;
    bool evaluarColision(Personaje * entidad,char dir);
    bool enemigoColisiona(villano * entidad,char dir);
    villano *faraon;
    Personaje *moises;
    float tiempo = 0;
    short int niv_max = 1,cont = 0,num_escena = 0,angulo_tiro = 45,bg_posx = 0;
    bool Apuntando;
    QGraphicsPixmapItem *background, *contexto;
    obstaculo *cactus,*casa,*marco,*brocha;

};
#endif // MAINWINDOW_H
