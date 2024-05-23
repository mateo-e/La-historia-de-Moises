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
    float tiempoTrans;
    void set_escena(short num_escena);
    QGraphicsScene *scene;

private slots:
    void hmov(Proyectil *bola);
    void Actualizacion();
    void keyPressEvent(QKeyEvent *event);


    void on_JugarBtn_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    faraon *villano;
    Personaje *moises;
    short int vel_personaje = 5;
    short int num_escena = 0;
    bool Apuntando = false;
    short int angulo_tiro = 45;
};
#endif // MAINWINDOW_H
