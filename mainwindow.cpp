#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) //La interfaz diseñada en Qt Designer
{
    ui->setupUi(this); //This hace referencia a la clase MainWindow, configura la interfaz de usuario definida en el Qt designer

    // se crea la escena 0 la cual corresponde al menu

    set_escena(0);

    timer = new QTimer;

    connect(timer, SIGNAL(timeout()), this, SLOT(Actualizacion()));

    timer->start(70);

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

void MainWindow::set_escena(short int num_escena)
{

    if(num_escena != 0)
        delete scene;

    scene = new QGraphicsScene(this);

    switch(num_escena)
    {
        case 0:
        {
            scene->add
            break;
        }
        case 1:
        {
            scene->setSceneRect(0, 0, 1280, 720);
            ui->graphicsView->setScene(scene);
            ui->graphicsView->setFixedSize(1280 + 2 * ui->graphicsView->frameWidth(), 720 + 2 * ui->graphicsView->frameWidth());//manejar la relación de aspecto
            tiempoTrans = 0;

            QPixmap backgroundImage(":/backgrounds/background_1.jpg");

            QGraphicsPixmapItem *background = scene->addPixmap(backgroundImage);

            moises = new Personaje(100,290);
            scene->addItem(moises);
            moises->num_proyectiles = 5; // se inicializa un numero de proyectiles para el personaje principal

            villano = new faraon(500,290);
            scene->addItem(villano);
            villano->num_proyectiles = 5;


            background->setPos(0,-400);
            break;
        }
        case 2:
        {

            break;
        }
        case 3:
        {

            break;
        }
    }
}

void MainWindow::Actualizacion()
{
    moises->setSprite();

}
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    //Manejo del evento de tecla
    switch(event->key()) {
    case Qt::Key_A:
        moises->dir = 'a';
        moises->moveBy(-vel_personaje, 0);
        break;
    case Qt::Key_D:
        moises->dir = 'd';
        moises->moveBy(vel_personaje, 0);
        break;
    case Qt::Key_W:
        moises->dir = 'w';
        moises->moveBy(0, -vel_personaje);
        break;
    case Qt::Key_S:
        moises->dir = 's';
        moises->moveBy(0, vel_personaje);
        break;
    }
}


void MainWindow::hmov(Proyectil *bola)
{
    bola->movParabolico(&this->tiempoTrans);
    tiempoTrans+=0.01;
}

