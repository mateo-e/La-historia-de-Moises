#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) //La interfaz diseñada en Qt Designer
{
    ui->setupUi(this); //This hace referencia a la clase MainWindow, configura la interfaz de usuario definida en el Qt designer

    // se crea la escena 0 la cual corresponde al menu

    set_escena(0); // se inicializa la primera escena

    timer = new QTimer;

    connect(timer, SIGNAL(timeout()), this, SLOT(Actualizacion()));

    timer->start(25);


    ui->Informacion->hide();
    Apuntando = false;
    num_escena = 0;



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
        delete scene; // se elimina escena anterior

    scene = new QGraphicsScene(this); // se crea la nueva escena

    switch(num_escena)
    {
        case 0:
        {

            scene->setSceneRect(0, 0, 1280, 720);
            ui->graphicsView->setScene(scene);
            ui->graphicsView->setFixedSize(1280 + 2 * ui->graphicsView->frameWidth(), 720 + 2 * ui->graphicsView->frameWidth());//manejar la relación de aspecto

            break;
        }

        case 1:
        {
            scene->setSceneRect(0, 0, 1280, 720);
            ui->graphicsView->setScene(scene);
            ui->graphicsView->setFixedSize(1280 + 2 * ui->graphicsView->frameWidth(), 720 + 2 * ui->graphicsView->frameWidth());//manejar la relación de aspecto


            QPixmap backgroundImage(":/backgrounds/background_1.jpg");

            QGraphicsPixmapItem *background = scene->addPixmap(backgroundImage);

            moises = new Personaje(100,290);
            scene->addItem(moises);
            moises->num_proyectiles = 5; // se inicializa un numero de proyectiles para el personaje principal


            villano = new faraon(500,290);
            scene->addItem(villano);
            villano->num_proyectiles = 5;

            villano->setTransformOriginPoint(villano->boundingRect().center());
            villano->setRotation(45);

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

    //Proyectil p;

    if(num_escena == 0)
        return;

    moises->setSprite();

    for(int i = 0; i < 5 - moises->num_proyectiles; i++)
    {
        if((moises->piedras.at(i))->velIn < 1)
        {
            (moises->piedras.at(i))->pintar = false; // detiene la animacion
        }
        else
        {
            hmov(moises->piedras.at(i));
            moises->piedras.at(i)->tiempoTrans += 0.15;
        }

    }




}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    //Manejo del evento de tecla para cada mecanica del nivel actual (num_escena)



    if(num_escena == 1)
    {
        if(! Apuntando)
        {
            // primer nivel solo tiene movimiento lateral
            switch(event->key()) {
            case Qt::Key_A:
                if(moises->x > 5)
                {
                    moises->dir = 'a';
                    moises->moveBy(-vel_personaje, 0);
                }

                break;
            case Qt::Key_D:
                if(moises->x < 200)
                {
                    moises->dir = 'd';
                    moises->moveBy(vel_personaje, 0);
                }

                break;

            case Qt::Key_Q:
            { // entra en modo apuntado

                Apuntando = true; // variable que nos indica que el personaje esta en modo apuntar para lanzar el proyectil


                // necesario para que el sprite quede mirando haciea el enemigo
                moises->dir = 'd';
                moises->update();


                // se inicializa la sombra con puntos
                moises->sombra_apuntado = new pared(moises->x * 2 + 50,moises->y * 2 - 15,150,30,":/sprites/puntos_apuntado.png");

                scene->addItem(moises->sombra_apuntado);

                // se inicializa la rotacion de la sombra de tiro
                moises->sombra_apuntado->setTransformOriginPoint(moises->sombra_apuntado->boundingRect().left(),moises->sombra_apuntado->boundingRect().y()+15); // se ajusta el eje de giro
                moises->sombra_apuntado->setRotation(-angulo_tiro);


                // se muestra un label con la informacion del angulo de tiro
                ui->Informacion->setText((QString::number(angulo_tiro)).append("°"));
                ui->Informacion->setGeometry(moises->x * 2 - 10,moises->y * 2 - 7,180,20);
                ui->Informacion->show();

                break;
            }

            }
        }

        else if(! moises->getBandera()) // esta variable se hace verdadera cuando se quiere pasar a la mecanica de seleccion de potencia
        { // en caso de que el personaje esté apuntando

            switch(event->key()) {

            case Qt::Key_A:
                if(angulo_tiro + 2 < 90) // se limita el angulo
                {
                    angulo_tiro += 2;
                    moises->sombra_apuntado->setRotation(-angulo_tiro);
                }
                break;
            case Qt::Key_D:

                if(angulo_tiro - 2 > 0) // se limita el angulo
                {
                    angulo_tiro -= 2;
                    moises->sombra_apuntado->setRotation(-angulo_tiro);
                }
                break;

            case Qt::Key_Q:

                moises->setBandera(true); // bandera para pasar a la mecanica de seleccion de potencia
            }

            ui->Informacion->setText((QString::number(angulo_tiro)).append("°")); // label que muestra el angulo de tiro



        }

        else // una vez se ha calculado el angulo de tiro
        {
            // calculo de la potencia del proyectil
            switch(event->key()) {
            case Qt::Key_W:
                if(moises->sombra_apuntado->largoTotal < 140)
                {
                    moises->sombra_apuntado->largoTotal += 2;
                    moises->sombra_apuntado->update();
                    ui->Informacion->setText((QString::number(moises->sombra_apuntado->largoTotal - 50)).append("km/h")); // label que muestra la velocidad de tiro

                }
                break;
            case Qt::Key_S:

                if(moises->sombra_apuntado->largoTotal > 50)
                {
                    moises->sombra_apuntado->largoTotal -= 2;
                    moises->sombra_apuntado->update();
                    ui->Informacion->setText((QString::number(moises->sombra_apuntado->largoTotal -50)).append("km/h")); // label que muestra la velocidad de tiro

                }
                break;
            case Qt::Key_Q:
                //lanzar

                if(moises->num_proyectiles > 0)
                {
                    moises->piedras.append( new Proyectil(ui->graphicsView,moises->sombra_apuntado->largoTotal,moises->x,moises->y,angulo_tiro*(3.1415/180)));
                    moises->piedras.back()->setPos(moises->x,moises->y);
                    scene->addItem(moises->piedras.back());
                    moises->num_proyectiles --;
                }
                else
                {
                    ui->Informacion->show();
                    ui->Informacion->setText("¡TE HAZ QUEDADO SIN PROYECTILES!");

                    break;
                }

                Apuntando = false; // se sale del modo calcular angulo
                moises->setBandera(false); // se sale del modo calcular potencia
                delete moises->sombra_apuntado;
                ui->Informacion->hide();




                break;
            }


        }

    }

    else if(num_escena == 2)
    {

    }

    else if(num_escena == 3)
    {
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
}


void MainWindow::hmov(Proyectil *bola)
{
    bola->movParabolico(&bola->tiempoTrans);
}


void MainWindow::on_JugarBtn_clicked()
{
    set_escena(1); // se elimina escena anterior y se cambia a la siguiente

    // se esconden los elementos del menu
    delete ui->JugarBtn;

    num_escena = 1;

}

