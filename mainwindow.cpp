#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "proyectil.h"
#include "Personaje.h"
#include <qdebug.h>
#include <QLabel>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) //La interfaz diseñada en Qt Designer
{
    ui->setupUi(this); //This hace referencia a la clase MainWindow, configura la interfaz de usuario definida en el Qt designer
    QGraphicsScene *scene = new QGraphicsScene(this); // se debe crear una escena para manejar elementos gráficos
    scene->setSceneRect(0, 0, 1280, 720);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFixedSize(1280 + 2 * ui->graphicsView->frameWidth(), 720 + 2 * ui->graphicsView->frameWidth());//manejar la relación de aspecto
    tiempoTrans = 0;

    QPixmap backgroundImage(":/backgrounds/background_1.jpg");

    QGraphicsPixmapItem *background = scene->addPixmap(backgroundImage);

    background->setPos(0,-400);

    timer = new QTimer;

    /*La función connect debe ser ajustada para conectar a la señal con el slot. La función hmov toma un puntero al objeto Particula como argumento
     * y no se puede conectar directamente al timeout del timer. Se puede utilizar una función lambda o una función auxiliar:
     *
     * private slots:
    void onTimeout(); // Declaration of the helper function

private:
    void connectTimer(); // Se crea una función para conectar el timer en el .h

Dentro del mainwindow.cpp:


void MainWindow::onTimeout() {
    hmov(bola);
}
Se define la función:
void MainWindow::connectTimer() {
    connect(timer, &QTimer::timeout, this, &MainWindow::onTimeout);

La función "helper" o auxiliar no acepta parámetros sino que simplemente llama al slot hmov. Luego, hay una función connectTimer que es responsable de conectar la
señal de timeout.

     */


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::hmov(Proyectil *bola)
{
    bola->movParabolico(&this->tiempoTrans);
    tiempoTrans+=0.01;
}

