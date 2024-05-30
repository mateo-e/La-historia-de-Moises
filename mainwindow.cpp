#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) //La interfaz diseñada en Qt Designer
{
    ui->setupUi(this); //This hace referencia a la clase MainWindow, configura la interfaz de usuario definida en el Qt designer

    // se crea la escena 0 la cual corresponde al menu

    set_escena(0); // se inicializa la primera escena

    // manejo de cronometro dentro del juego
    cronometro = new QTimer;
    connect(cronometro, SIGNAL(timeout()), this, SLOT(aumentarCronometro()));



    // timer para manejo de eventos
    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(Actualizacion()));

    ui->lbl_cronometro->hide();
    ui->vida_label->hide();
    ui->Informacion->hide();
    Apuntando = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::set_escena(short int NewNum_escena)
{
    ui->JugarBtn->show(); // se muestra el boton
    ui->context_lbl->show(); // se muestra el contexto historico del nivel

    switch(NewNum_escena)
    { // se cambia el contexto dependiendo de la escena
    case 1: ui->context_lbl->setText("CONTEXTO HISTORICO: \nExistía un bebe, que fue llevado por la corriente de un rio, \neste es encontrado por la esposa del faraón \ny le ponen por nombre Moisés. \nPasados los años este se da cuenta de que viene de un pueblo \nHebreo y ahora quiere que su pueblo sea liberado. \nUsa las teclas A y D para moverte y Q para lanzar \nTienes 5 oportunidade \n HAZ QUE EL FARAON CAIGA!");break;
    case 2: ui->context_lbl->setText("CONTEXTO HISTORICO: \nAl ver que el faraón no desea liberar al pueblo hebreo, \nDios desata 10 plagas en Egipto, \nEn la ultima Moisés le dice al pueblo Hebreo \nque pinte el marco superior de la puerta con sangre de cordero \nUsa la tecla W para saltar. \nDeberas pintar todas las casas que aparezcan en tu camino. \nPROTEGE A TU PUEBLO DE LA PLAGA!");break;
    case 3: ui->context_lbl->setText("CONTEXTO HISTORICO: \n  ");break;
    }

    ui->context_lbl->setAlignment(Qt::AlignCenter);


    num_escena = NewNum_escena;

    if(NewNum_escena != 0)
        delete scene; // se elimina escena anterior



    scene = new QGraphicsScene(this); // se crea la nueva escena

    scene->setSceneRect(0, 0, 1280, 720);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFixedSize(1280 + 2 * ui->graphicsView->frameWidth(), 720 + 2 * ui->graphicsView->frameWidth());//manejar la relación de aspecto

    switch(NewNum_escena)
    {
        case 0:
        { // escena de inicio
            break;
        }

        case 1:
        { // escena de nivel 1

            timer->stop(); // se activa cuando el usuario presiona el boton para iniciar
            cronometro->stop();

            ui->vida_label->hide();
            ui->vida_label->setText("3 - 3"); // se actualiza el contador de vidas
            ui->vida_label->setAlignment(Qt::AlignCenter);

            ui->lbl_cronometro->hide();
            ui->lbl_cronometro->setText("70");

            QPixmap backgroundImage(":/backgrounds/background_1.jpg");

            background = scene->addPixmap(backgroundImage);


            moises = new Personaje(100,290);
            scene->addItem(moises);
            moises->num_proyectiles = 5; // se inicializa un numero de proyectiles para el personaje principal

            villano = new faraon(500,290);
            scene->addItem(villano);
            villano->num_proyectiles = 1;

            background->setPos(0,-400);
            break;
        }
        case 2:
        { // escena de nivel 2

            QPixmap backgroundImage(":/backgrounds/background_2.jpg");

            background = scene->addPixmap(backgroundImage);

            cronometro->stop();
            timer->stop();

            ui->lbl_cronometro->hide();
            ui->vida_label->hide();

            ui->Informacion->setText("NUMERO DE PUERTAS PINTADAS: 0");
            ui->Informacion->setGeometry(490,620,310,30);
            ui->Informacion->setAlignment(Qt::AlignCenter);

            ui->lbl_cronometro->setText("70");
            tiempo = 0;

            background->setPos(bg_posx,-50);


            casa = new pared(1500,175,350,300,":/sprites/casas.png");
            scene->addItem(casa);
            casa->cont = 4;

            brocha = new pared(1500,195,80,80,":/sprites/brocha.png");
            scene->addItem(brocha);

            marco = new pared(1500,175,350,300,":/sprites/marco_pintado.png");
            scene->addItem(marco);
            marco->hide();

            moises = new Personaje(320,280);
            scene->addItem(moises);

            cactus = new pared(1000,245,150,150,":/sprites/cactus.png");
            scene->addItem(cactus);
            cactus->hide();

            break;
        }
        case 3:
        { // escena de nivel 3

            break;
        }

        case 4:
        { // escena de juego perdido
            ui->lbl_cronometro->hide();
            ui->Informacion->hide();
            ui->context_lbl->hide();
            ui->JugarBtn->hide();
            ui->vida_label->hide();

        }

        case 5:
        { // escena de juego ganado

        }
        }
}


void MainWindow::Actualizacion()
{
    if(num_escena == 0)
        return;

    else if(num_escena == 1)
    {
        // movimiento del jugador
        moises->setSprite();

        for(int i = 0; i < 5 - moises->num_proyectiles; i++)
        {
            if(villano->collidesWithItem(moises->piedras.at(i),Qt::IntersectsItemBoundingRect) and moises->piedras.at(i)->isVisible()) // se evalua colision de cada uno de los proyectiles del jugador con el villano
            {
                villano->vidas --;

                ui->vida_label->setText(QString::number(moises->vidas) + " - " + QString::number(villano->vidas)); // se actualiza el contador de vidas

                moises->piedras.at(i)->posX = 1000;
                moises->piedras.at(i)->posY = 1000;
                moises->piedras.at(i)->setPos(1000,1000);

                if(villano->vidas == 0) // si se acaba la vida del faraon
                {
                    ui->vida_label->hide();
                    timer->stop();
                    set_escena(2); // se pasa al siguiente nivel
                }
                return;
            }

            if((moises->piedras.at(i))->velIn < 1 or moises->piedras.at(i)->posX == 1000)
            {
                (moises->piedras.at(i))->pintar = false; // detiene la animacion
            }
            else
            {
                hmov(moises->piedras.at(i));
                moises->piedras.at(i)->tiempoTrans += 0.15;
            }
        }


        // accion y movimiento del faraon
        std::srand(static_cast<unsigned>(std::time(nullptr)));

        short int numeroAleatorio = std::rand() % 3 + 1;

        villano->setTransformOriginPoint(villano->boundingRect().center());

        switch(numeroAleatorio)
        {
            case 1:
            {// atacar jugador

                if(! villano->proy_lanzado) // si el faraon ya tiene un proyectil lanzado no se le permite lanzar mas hasta que se destruya el actual
                {
                    // se crea lanza del faraon y se añade a la escena
                    villano->proy_lanzado = true;
                    villano->lanza = new Proyectil(nullptr,-65,villano->x,villano->y,-45);
                    villano->lanza->setRotation(-45);
                    villano->lanza->setPos(villano->x,villano->y);
                    scene->addItem(villano->lanza);
                    break;
                }
            }
            default: villano->despl_x(); break;
        }

        if(villano->proy_lanzado)
        {
            // verificacion de nivel perdido
            if(moises->collidesWithItem(villano->lanza,Qt::IntersectsItemBoundingRect))
            {
                moises->vidas --;

                delete villano->lanza;
                villano->proy_lanzado = false;

                ui->vida_label->setText(QString::number(moises->vidas) + " - " + QString::number(villano->vidas)); // se actualiza el contador de vidas

                if(moises->vidas == 0)
                    set_escena(4); // escena de juego perdido
                return;
            }

            if(villano->lanza->velIn > -1)
            {
                delete villano->lanza; // se elimina el proyectil en caso de que se detenga
                villano->proy_lanzado = false;
            }
            else
            {
                hmov(villano->lanza);
                villano->lanza->tiempoTrans += 0.15;
            }
        }
    }

    else if(num_escena == 2)
    {
        // actualizacion del background

        bg_posx -= (tiempo /10 + 3)*2; // se desplaza el background


        if(bg_posx < -2810)
            bg_posx = 0; // se reinicia


        background->setPos(bg_posx,-50);

        // se actualiza el sprite del personaje

        if(bg_posx % 13 == 0)
            moises->setSprite();



        cactus->setPos(cactus->posx-= tiempo /10 + 3,cactus->posy); // movimiento de los cactus

        if(cactus->posx < -200) // si pasa del borde se teletransporta el mismo objeto hacia mas adelante
        {
            cactus->setPos(1000,cactus->posy);
            cactus->posx = 1000;
            cactus->cont ++; // manejo de diferente aspecto
            if(cactus->cont == 6)
                cactus->cont = 0;
        }


        casa->setPos(casa->posx -= tiempo /10 + 3,casa->posy); // movimiento de las casas


        if(casa->posx < -400) // si pasa del borde se teletransporta el mismo objeto hacia mas adelante
        {
            casa->setPos(1000,casa->posy);
            casa->posx = 1000;
            casa->cont ++; // manejo de diferente aspecto

            if(casa->cont == 7)
                casa->cont = 0;
        }

        if(marco->posx < -150)
        {
            marco->setPos(1000,marco->posy);
            marco->hide();
            brocha->show();
        }

        switch(casa->cont)// se ajusta su posicion dependiendo de la casa
        {
        case 0:
            marco->posy = casa->posy + 87;
            marco->posx = casa->posx + 55;
            marco->w = 110;
            marco->h = 110;
            break;
        case 1:
            marco->posy = casa->posy + 90;
            marco->posx = casa->posx + 45;
            marco->w = 110;
            marco->h = 110;

            break;
        case 2:
            marco->posy = casa->posy + 82;
            marco->posx = casa->posx + 25;
            marco->w = 135;
            marco->h = 135;

            break;
        case 3:
            marco->posy = casa->posy + 80;
            marco->posx = casa->posx + 10;
            marco->w = 140;
            marco->h = 140;

            break;
        case 4:
            marco->posy = casa->posy + 80;
            marco->posx = casa->posx + 94;
            marco->w = 100;
            marco->h = 140;

            break;
        case 5:
            marco->posy = casa->posy + 89;
            marco->posx = casa->posx + 76;
            marco->w = 90;
            marco->h = 100;

            break;
        case 6:
            marco->posy = casa->posy + 85;
            marco->posx = casa->posx + 85;
            marco->w = 100;
            marco->h = 70;

            break;
        }


        if(moises->collidesWithItem(brocha,Qt::IntersectsItemBoundingRect) || marco->isVisible()) // si se agarra la brocha
        {
            marco->show();
            brocha->hide();
            moises->cont_casas++;


            ui->Informacion->setText("NUMERO DE PUERTAS PINTADAS: " + QString::number(moises->cont_casas));


            marco->setPos(marco->posx,marco->posy); // se teletransporta el marco a la casa
        }


        if(brocha->isVisible())
        {
            brocha->posx = marco->posx + 5; // se coloca la brocha en el medio de la casa
            brocha->setPos(brocha->posx,brocha->posy);
        }


        if(moises->collidesWithItem(cactus,Qt::ContainsItemBoundingRect)) // se evalua colision con cactus
        {
            moises->x -= tiempo / 10 + 2; // se frena en caso de chocar contra un cactus
            moises->setPos(moises->x,moises->posY_in);


            if(moises->tiempoTrans > 0)
            {
                moises->tiempoTrans = 0;
                moises->y = moises->posY_in;
            }


        }

        // se evalua si el personaje está saltando para ejecutar su movimiento
        else if(moises->tiempoTrans > 0)
        { // si el personaje está saltando
            moises->tiempoTrans += 0.15;
            moises->saltar();

            if(moises->y >= moises->posY_in)
                moises->tiempoTrans = 0; // se verifica cuando ha llegado a su posicion inicial
        }



    }
    else if(num_escena == 3)
    {

    }
}

void MainWindow::aumentarCronometro()
{
    tiempo++;
    ui->lbl_cronometro->setText(QString::number(70 - tiempo)); // se coloca el nuevo tiempo

    // se evalua perdida
    if(tiempo == 70)
    {
        ui->lbl_cronometro->hide();
        set_escena(4); // escena de juego perdido
    }

}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(!timer->isActive()) // si el timer no está activado no permite el movimiento del jugador
        return;

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
                    moises->moveBy(-5, 0);
                }

                break;
            case Qt::Key_D:
                if(moises->x < 200)
                {
                    moises->dir = 'd';
                    moises->moveBy(5, 0);
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

                if(angulo_tiro - 2 > 45) // se limita el angulo
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
                    set_escena(4); // juego perdido por falta de proyectiles

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
        if(event->key() == Qt::Key_W)
        {
            if(! moises->collidesWithItem(cactus,Qt::ContainsItemBoundingRect)) // si no está colisionando con cactus
            {
                moises->tiempoTrans += 0.15;
                moises->saltar();
            }
        }
    }

    else if(num_escena == 3)
    {
        switch(event->key()) {
        case Qt::Key_A:
            moises->dir = 'a';
            moises->moveBy(-5, 0);
            break;
        case Qt::Key_D:
            moises->dir = 'd';
            moises->moveBy(5, 0);
            break;
        case Qt::Key_W:
            moises->dir = 'w';
            moises->moveBy(0, -5);
            break;
        case Qt::Key_S:
            moises->dir = 's';
            moises->moveBy(0, 5);
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
    timer->start(20);
    cronometro->start(1000);


    if(num_escena== 1 || num_escena== 3) // solo en las escenas 1 y 3 se muestra el label de vida
        ui->vida_label->show();
    else if(num_escena == 2)
    {
        ui->Informacion->show();
        cactus->show();
    }

    ui->lbl_cronometro->show();
    ui->context_lbl->hide();

    if(num_escena != 0)
        ui->JugarBtn->hide(); // se esconde

    else // si es la primera escena este boton funciona como inicializador del juego
        set_escena(num_escena+1); // se elimina escena anterior y se cambia a la siguiente

    ui->JugarBtn->setText("INICIAR NIVEL");
}

