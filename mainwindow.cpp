#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) //La interfaz diseñada en Qt Designer
{
    ui->setupUi(this); //This hace referencia a la clase MainWindow, configura la interfaz de usuario definida en el Qt designer

    // manejo de cronometro dentro del juego
    cronometro = new QTimer;
    connect(cronometro, SIGNAL(timeout()), this, SLOT(aumentarCronometro()));

    // timer para manejo de eventos
    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(Actualizacion()));

    // se crea la escena 0 la cual corresponde al menu

    set_escena(3); // se inicializa la primera escena

    ui->dialogo_lbl->hide();
    ui->dialogo_lbl->setAlignment(Qt::AlignCenter);
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
/*
    if(NewNum_escena != 0)
        delete scene; // se elimina escena anterior
*/
    scene = new QGraphicsScene(this); // se crea la nuweva escena

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

            moises->dialogue = new QFile(":/textos/dialogos.txt"); // se abre el archivo de dialogos
            moises->dialogue->open(QIODevice::ReadOnly|QIODevice::Text);

            faraon = new villano(500,290);
            scene->addItem(faraon);
            faraon->num_proyectiles = 1;

            background->setPos(0,-400);
            break;
        }
        case 2:
        { // escena de nivel 2

            QPixmap backgroundImage(":/backgrounds/background_2.jpg");

            background = scene->addPixmap(backgroundImage);

            cronometro->stop();
            timer->stop();

            ui->dialogo_lbl->hide();
            ui->lbl_cronometro->hide();
            ui->vida_label->hide();

            ui->Informacion->setText("NUMERO DE PUERTAS PINTADAS: 0");
            ui->Informacion->setGeometry(490,620,310,30);
            ui->Informacion->setAlignment(Qt::AlignCenter);

            ui->lbl_cronometro->setText("0");
            tiempo = 0;

            background->setPos(bg_posx,-50);


            casa = new obstaculo(1500,175,350,300,":/sprites/casas.png");
            scene->addItem(casa);
            casa->cont = 4;

            brocha = new obstaculo(1500,195,80,80,":/sprites/brocha.png");
            scene->addItem(brocha);

            marco = new obstaculo(1500,175,350,300,":/sprites/marco_pintado.png");
            scene->addItem(marco);
            marco->hide();

            moises = new Personaje(320,280);
            scene->addItem(moises);

            cactus = new obstaculo(1000,245,150,150,":/sprites/cactus.png");
            scene->addItem(cactus);
            cactus->hide();

            break;
        }
        case 3:
        { // escena de nivel 3

            QPixmap backgroundImage(":/backgrounds/background_3.jpg");

            background = scene->addPixmap(backgroundImage);

            cronometro->stop();
            timer->stop();

            ui->lbl_cronometro->hide();

            tiempo = 0; // manejo de algunos eventos

            // aparecen los 10 hebreos
            hebreos.push_back(new Personaje(35,35,'2'));
            hebreos.push_back(new Personaje(800,35,'3'));
            hebreos.push_back(new Personaje(35,395,'2'));
            hebreos.push_back(new Personaje(800,395,'3'));
            hebreos.push_back(new Personaje(85,200,'2'));
            hebreos.push_back(new Personaje(745,200,'3'));
            hebreos.push_back(new Personaje(365,240,'2'));
            hebreos.push_back(new Personaje(465,240,'3'));
            hebreos.push_back(new Personaje(390,135,'2'));
            hebreos.push_back(new Personaje(440,135,'3'));

            for(short int i =0 ; i < hebreos.size(); i++)
            {
                hebreos.at(i)->setScale(0.515);
                hebreos.at(i)->dir = 's';
                scene->addItem(hebreos.at(i));
            }

            moises = new Personaje(420,270);
            scene->addItem(moises);


            moises->dir = 's';
            moises->setScale(0.5);

            background->setPos(0,-1310); // se posiciona el background

            crear_mapa();// creacion del mapa junto con personajes

            // aparece el faraon
            enemigos.push_back(new villano(415,445));
            enemigos.back()->setScale(0.515);
            enemigos.back()->dir = 'w';
            scene->addItem(enemigos.back());

            ui->Informacion->setGeometry(395,235,500,30);
            ui->Informacion->setText("Numero de hebreos salvados: 0/10");
            ui->Informacion->setAlignment(Qt::AlignCenter);
            ui->Informacion->setStyleSheet("color: red;");

            obstaculos.at(0)->hide();
            obstaculos.removeFirst(); // se elimina el obstaculo que da camino hacia el mar

            break;
        }

        case 4:
        { // escena de juego perdido
            ui->dialogo_lbl->hide();
            ui->lbl_cronometro->hide();
            ui->context_lbl->hide();
            ui->vida_label->hide();


            ui->Informacion->show(); // label que muestra la razon de perdida
            ui->Informacion->setGeometry(495,270,310,30);
            ui->Informacion->setAlignment(Qt::AlignCenter);
            ui->JugarBtn->setText("JUGAR DE NUEVO");
        }

        case 5:
        { // escena de juego ganado

        }
        }
}

void MainWindow::crear_mapa()
{
    QFile mapa(":/textos/mapa.txt");
    mapa.open(QIODevice::ReadOnly|QIODevice::Text);

    if(!mapa.isOpen())
        return;

    QString linea = " ";

    while(linea != "") // obtengo cada una de las lienas
    {
        linea = mapa.readLine();

        int actual_pos = 0,ant_pos = 0,x,y,w,h;
        for(int i = 1; linea.indexOf(",",actual_pos+1) != -1; i++) // busco el separador
        {
            QString coord_str;

            actual_pos = linea.indexOf(",",actual_pos +1);


            for(int u = ant_pos; u < actual_pos ; u++)
                coord_str.push_back(linea[u]);


            switch(i)
            {
                // se rellena cada coordenada
            case 1:x = coord_str.toInt(); break;
            case 2:y = coord_str.toInt(); break;
            case 3:w = coord_str.toInt(); break;
            case 4:h = coord_str.toInt(); break;
            }

            ant_pos = actual_pos + 1;
        }
        obstaculos.push_back(new obstaculo(x,y,w,h));
        scene->addItem(obstaculos.back());
    }
    mapa.close();
}

void MainWindow::perseguirJugador(villano *entidad)
{

    short int num_ran = QRandomGenerator::global()->bounded(0,1); // da un comportamiento diferente a cada enemigo para evitar superposicion de personajes

    switch(num_ran)
    {
    case 0:
    {
        if(moises->y > entidad->y and !enemigoColisiona(entidad,'s') and entidad->dir != 'w')
            entidad->dir = 's';

        else if(moises->x > entidad->x and !enemigoColisiona(entidad,'d') and entidad->dir != 'a')
            entidad->dir = 'd';

        else if(moises->y < entidad->y and !enemigoColisiona(entidad,'w') and entidad->dir != 's')
            entidad->dir = 'w';

        else if(moises->x < entidad->x and !enemigoColisiona(entidad,'a') and entidad->dir != 'd')
            entidad->dir = 'a';

        else if(!enemigoColisiona(entidad,'w') and entidad->dir != 's')
            entidad->dir = 'w';

        else if(!enemigoColisiona(entidad,'d') and entidad->dir != 'a')
            entidad->dir = 'd';

        else if(!enemigoColisiona(entidad,'s') and entidad->dir != 'w')
            entidad->dir = 's';

        else if(!enemigoColisiona(entidad,'a') and entidad->dir != 'd')
            entidad->dir = 'a';

        else if(!enemigoColisiona(entidad,'w'))
            entidad->dir = 'w';

        else if(!enemigoColisiona(entidad,'s'))
            entidad->dir = 's';

        else if(!enemigoColisiona(entidad,'d'))
            entidad->dir = 'd';

        else if(!enemigoColisiona(entidad,'a'))
            entidad->dir = 'a';
        break;
    }
    case 1:
    {
        if(!enemigoColisiona(entidad,'s') and entidad->dir != 'w')
            entidad->dir = 's';

        else if(!enemigoColisiona(entidad,'a') and entidad->dir != 'd')
            entidad->dir = 'a';

        else if(!enemigoColisiona(entidad,'w') and entidad->dir != 's')
            entidad->dir = 'w';

        else if(!enemigoColisiona(entidad,'d') and entidad->dir != 'a')
            entidad->dir = 'd';

        else if(!enemigoColisiona(entidad,'w'))
            entidad->dir = 'w';

        else if(!enemigoColisiona(entidad,'d'))
            entidad->dir = 'd';

        else if(!enemigoColisiona(entidad,'s'))
            entidad->dir = 's';

        else if(!enemigoColisiona(entidad,'a'))
            entidad->dir = 'a';
        break;
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
            if(faraon->collidesWithItem(moises->piedras.at(i),Qt::IntersectsItemBoundingRect) and moises->piedras.at(i)->isVisible()) // se evalua colision de cada uno de los proyectiles del jugador con el faraon
            {
                faraon->vidas --;

                ui->vida_label->setText(QString::number(moises->vidas) + " - " + QString::number(faraon->vidas)); // se actualiza el contador de vidas

                moises->piedras.at(i)->posX = 1000;
                moises->piedras.at(i)->posY = 1000;
                moises->piedras.at(i)->setPos(1000,1000);

                if(faraon->vidas == 0) // si se acaba la vida del faraon
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
                moises->piedras.at(i)->posX = 1000;
                moises->piedras.at(i)->posY = 1000;
                moises->piedras.at(i)->setPos(1000,1000);
            }
            else
            {
                hmov(moises->piedras.at(i));
                moises->piedras.at(i)->tiempoTrans += 0.15;
            }
        }


        // accion y movimiento del faraon
        std::srand(static_cast<unsigned>(std::time(nullptr)));

        short int numeroAleatorio = std::rand() % 4 + 1;

        faraon->setTransformOriginPoint(faraon->boundingRect().center());

        switch(numeroAleatorio)
        {
            case 1:
            case 2:
            {// atacar jugador

                if(! faraon->proy_lanzado) // si el faraon ya tiene un proyectil lanzado no se le permite lanzar mas hasta que se destruya el actual
                {
                    // se crea lanza del faraon y se añade a la escena
                    faraon->proy_lanzado = true;
                    faraon->lanza = new Proyectil(nullptr,-65,faraon->x,faraon->y,-45);
                    faraon->lanza->setRotation(-45);
                    faraon->lanza->setPos(faraon->x,faraon->y);
                    scene->addItem(faraon->lanza);
                    break;
                }
            }
            default: faraon->despl_x(); break;
        }

        if(faraon->proy_lanzado)
        {
            // verificacion de nivel perdido
            if(moises->collidesWithItem(faraon->lanza,Qt::IntersectsItemBoundingRect))
            {
                moises->vidas --;

                delete faraon->lanza;
                faraon->proy_lanzado = false;

                ui->vida_label->setText(QString::number(moises->vidas) + " - " + QString::number(faraon->vidas)); // se actualiza el contador de vidas

                if(moises->vidas == 0)
                {
                    set_escena(4); // escena de juego perdido
                    ui->Informacion->setText("TE HAZ QUEDADO SIN VIDAS!");
                }
                return;
            }

            if(faraon->lanza->velIn > -1)
            {
                delete faraon->lanza; // se elimina el proyectil en caso de que se detenga
                faraon->proy_lanzado = false;
            }
            else
            {
                hmov(faraon->lanza);
                faraon->lanza->tiempoTrans += 0.15;
            }
        }

        if(ui->dialogo_lbl->isVisible())
            ui->dialogo_lbl->setGeometry((moises->x * 2) - 160, (moises->y * 2) - 30,390,30); // el cuadro de dialogo persigue al jugador
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

        if(marco->posx < -30)
        {
            marco->posx = 1000;
            marco->setPos(1000,marco->posy);
            marco->hide();

            if(brocha->isVisible())
            {
                set_escena(4);
                ui->Informacion->setText("DEJASTE UNA CASA SIN PINTAR!");
                return;
            }
        }

        switch(casa->cont)// se ajusta su posicion del marco dependiendo de la casa
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

        if(moises->collidesWithItem(brocha,Qt::IntersectsItemBoundingRect) and brocha->isVisible()) // si se agarra la brocha
        {
            marco->show();
            brocha->hide();
            moises->cont_casas++;
            ui->Informacion->setText("NUMERO DE PUERTAS PINTADAS: " + QString::number(moises->cont_casas));
        }

        if(brocha->isVisible())
        {
            brocha->posx = marco->posx + 5; // se coloca la brocha en el medio de la casa
            brocha->setPos(brocha->posx,brocha->posy);
        }
        else if(casa->posx <= 640 and casa->posx > 0 and !marco->isVisible()) // si la casa se comienza a ver y el marco no esta puesto, aparece la brocha
        {
            brocha->posx = 10000;
            brocha->show();
        }

        if(marco->isVisible())
        {
            marco->posx-= 3;
            marco->setPos(marco->posx,marco->posy); // se teletransporta el marco a la casa
        }

        if(moises->x < -10) //mecanica de perdida: moises se queda atras de la pantalla
        {
            set_escena(4);
            ui->Informacion->setText("LA PLAGA TE HA ALCANZADO!");
            return;
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


        for(int i = 0; i < enemigos.size() and enemigos.at(i)->mover; i++) // se actualiza cada uno de los enemigos
        {
            perseguirJugador(enemigos.at(i)); // algoritmo de persecusion

            switch(enemigos.at(i)->dir)
            {
            case 'w': enemigos.at(i)->setPos(enemigos.at(i)->x,enemigos.at(i)->y -= 2); break;
            case 's': enemigos.at(i)->setPos(enemigos.at(i)->x,enemigos.at(i)->y += 2); break;
            case 'a': enemigos.at(i)->setPos(enemigos.at(i)->x -= 2,enemigos.at(i)->y); break;
            case 'd': enemigos.at(i)->setPos(enemigos.at(i)->x += 2,enemigos.at(i)->y); break;
            }
            enemigos.at(i)->setSprite();
        }

        if(!enemigos.at(0)->mover and background->y() < -650)
        {
            background->setPos(background->x(),background->y() + 10);
            moises->y += 19;
            for(short int i = 0; i < obstaculos.size(); i++)
                obstaculos.at(i)->posy += 10; // se mueve cada una de las obstaculos
            for(short int i = 0; i < enemigos.size(); i++)
                enemigos.at(i)->y += 19;
        }



    }
}

void MainWindow::aumentarCronometro()
{
    tiempo++;

    switch(num_escena) // seleccion de cada uno de los comportamientos del cronometro dependiendo la escena
    {

    case 1:
    {
        ui->lbl_cronometro->setText(QString::number(70 - tiempo)); // se coloca el nuevo tiempo

        // se evalua perdida

        if(tiempo == 70)
        {
            ui->lbl_cronometro->hide();
            set_escena(4); // escena de juego perdido
            ui->Informacion->setText("TE HAZ QUEDADO SIN TIEMPO!");
        }
        break;
    }
    case 2:
    {
        ui->lbl_cronometro->setText(QString::number(tiempo/100 * 80) + " %"); // se coloca el nuevo tiempo

        if(tiempo == 80)
        {
            ui->lbl_cronometro->hide();
            set_escena(3); // se pasa al siguiente nivel
        }
        break;
    }

    case 3:
    {
        ui->lbl_cronometro->setText(QString::number(tiempo));

        if((int)tiempo % 10  == 0 and enemigos.size() < 7) // aparece un nuevo soldado cada 10 segundos mientras haya menos de 6
        {
            enemigos.push_back(new villano(415,445));
            enemigos.back()->spriteX = 800;
            enemigos.back()->es_faraon = false;
            enemigos.back()->setScale(0.515);
            enemigos.back()->dir = 'w';
            scene->addItem(enemigos.back());
        }

        for(short int i = 0; i < hebreos.size(); i++)
        {
            hebreos.at(i)->setSprite(); // actualizacion de sprite
            hebreos.at(i)->update();
        }
    }
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
                ui->dialogo_lbl->hide();


                // necesario para que el sprite quede mirando haciea el enemigo
                moises->dir = 'd';
                moises->update();


                // se inicializa la sombra con puntos
                moises->sombra_apuntado = new obstaculo(moises->x * 2 + 50,moises->y * 2 - 15,150,30,":/sprites/puntos_apuntado.png");

                scene->addItem(moises->sombra_apuntado);

                // se inicializa la rotacion de la sombra de tiro
                moises->sombra_apuntado->setTransformOriginPoint(moises->sombra_apuntado->boundingRect().left(),moises->sombra_apuntado->boundingRect().y()+15); // se ajusta el eje de giro
                moises->sombra_apuntado->setRotation(-angulo_tiro);


                // se muestra un label con la informacion del angulo de tiro
                ui->Informacion->setText((QString::number(angulo_tiro)).append("°"));
                ui->Informacion->setGeometry(moises->x * 2 - 10,moises->y * 2 - 7,170,20);
                ui->Informacion->show();

                break;
            }
            }
        }

        else
        { // en caso de que el personaje esté apuntando

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

            case Qt::Key_A:
                if(angulo_tiro + 2 < 90) // se limita el angulo
                {
                    angulo_tiro += 2;
                    moises->sombra_apuntado->setRotation(-angulo_tiro);
                    ui->Informacion->setText((QString::number(angulo_tiro)).append("°")); // label que muestra el angulo de tiro
                }
                break;
            case Qt::Key_D:

                if(angulo_tiro - 2 > 45) // se limita el angulo
                {
                    angulo_tiro -= 2;
                    moises->sombra_apuntado->setRotation(-angulo_tiro);
                    ui->Informacion->setText((QString::number(angulo_tiro)).append("°")); // label que muestra el angulo de tiro
                }
                break;

            case Qt::Key_Q:
                //lanzar

                // se muestra dialogo
                ui->dialogo_lbl->show();
                ui->dialogo_lbl->setText(moises->dialogue->readLine());


                if(moises->num_proyectiles > 0)
                {
                    moises->piedras.append( new Proyectil(ui->graphicsView,moises->sombra_apuntado->largoTotal,moises->x,moises->y,angulo_tiro*(3.1415/180)));
                    moises->piedras.back()->setPos(moises->x,moises->y);
                    scene->addItem(moises->piedras.back());
                    moises->num_proyectiles --;
                }
                else
                {
                    ui->Informacion->setText("TE HAZ QUEDADO SIN PROYECTILES!");
                    set_escena(4); // juego perdido por falta de proyectiles

                    break;
                }

                Apuntando = false; // se sale del modo calcular angulo
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
            if(moises->x - 5 > 0 and ! evaluarColision(moises,'a'))
                moises->moveBy(-5, 0);
            break;

        case Qt::Key_D:
            moises->dir = 'd';
            if(moises->x + 5 < 830 and ! evaluarColision(moises,'d'))
                moises->moveBy(5, 0);
            break;

        case Qt::Key_W:
            moises->dir = 'w';
            if(moises->y - 5 > 0 and !evaluarColision(moises,'w'))
                moises->moveBy(0, -5);
            break;

        case Qt::Key_S:
            moises->dir = 's';
            if(moises->y + 5 < 430 and ! evaluarColision(moises,'s'))
                moises->moveBy(0, 5);


            break;
        }

        //movimiento de camara
        if(moises->y <20 and background->y() < 0)
        {
            for(short int i = 0; i < enemigos.size(); i++)
                enemigos.at(i)->mover = false;

            ui->Informacion->hide();
        }

        // se evalua colision con hebreos

        QPointF center1 = moises->mapToScene(moises->boundingRect().center());
        qreal collisionThreshold = 10;
        for(int i = 0; i < hebreos.size(); i++)
        {
            // Verificar la colisión después de aplicar transformaciones

            QPointF center2 = hebreos.at(i)->mapToScene(hebreos.at(i)->boundingRect().center());
            qreal distance = QLineF(center1, center2).length();


            if (distance < collisionThreshold)
            {
                hebreos.at(i)->hide();
                hebreos.removeAt(i);
                if(hebreos.size() == 0) // se abre puerta cuando
                {
                    ui->Informacion->setText("HAZ SALVADO A TODOS LOS HEBREOS ¡AHORA HUYE!");
                    obstaculos.at(0)->hide();
                    obstaculos.removeFirst(); // se elimina el obstaculo que da camino hacia el mar
                }
                else
                    ui->Informacion->setText("Numero de hebreos salvados:" + QString::number(10 - hebreos.size()) + "/10");
            }
        }

        moises->setSprite();
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(num_escena == 3)
    {
        for(short int i = 0; i < obstaculos.size();i++) //se evalua colision con cada una de las obstaculos
        {
            if(moises->collidesWithItem(obstaculos.at(i),Qt::IntersectsItemBoundingRect))
            {
                switch(event->key())
                { // se evalua la tecla que se soltó y se ubica al personaje lejos del objeto con el que está colisionando
                case Qt::Key_A:
                    moises->moveBy(5, 0);
                    break;

                case Qt::Key_D:
                    moises->moveBy(-5, 0);
                    break;

                case Qt::Key_W:
                    moises->moveBy(0, 5);
                    break;

                case Qt::Key_S:
                    moises->moveBy(0, -5);
                    break;
                }
            }
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

    switch(num_escena) // definicion de diferentes comportamientos del boton de inicio dependiendo de la escena
    {
    case 1:
    {
        ui->vida_label->show();
        ui->lbl_cronometro->show();
        break;
    }
    case 2:
    {
        ui->Informacion->show();
        cactus->show();
        ui->lbl_cronometro->show();
        break;
    }
    case 3:
    {
        ui->Informacion->show();
        break;
    }
    case 4:
    {
        set_escena(1); // se manda al nivel 1
        ui->Informacion->hide();
        ui->JugarBtn->setText("INICIAR NIVEL");
        Apuntando = false;
        tiempo = 0;
        return;
    }
    case 5: // escena de juego ganado
    {

        break;
    }
    }


    ui->context_lbl->hide();

    if(num_escena != 0)
        ui->JugarBtn->hide(); // se esconde

    else // si es la primera escena este boton funciona como inicializador del juego
        set_escena(num_escena+1); // se elimina escena anterior y se cambia a la siguiente

    ui->JugarBtn->setText("INICIAR NIVEL");
}

bool MainWindow::evaluarColision(Personaje *entidad, char dir)
{

    switch(dir) // se mueve la entidad a la posicion deseada con el fin de probar si colisiona en ese lugar
    {
    case 'w': entidad->setPos(entidad->x,entidad->y - 5); break;

    case 's': entidad->setPos(entidad->x,entidad->y + 5);break;

    case 'd': entidad->setPos(entidad->x + 5,entidad->y);break;

    case 'a': entidad->setPos(entidad->x - 5,entidad->y);break;
    }

    for(short int i = 0; i < obstaculos.size();i++) //se evalua colision con cada una de las obstaculos
    {
        if(entidad->collidesWithItem(obstaculos.at(i),Qt::IntersectsItemBoundingRect))
        {
            entidad->setPos(entidad->x,entidad->y);
            return true;
        }
    }

    entidad->setPos(entidad->x,entidad->y);
    return false;
}

bool MainWindow::enemigoColisiona(villano *entidad, char dir)
{
    switch(dir) // se mueve la entidad a la posicion deseada con el fin de probar si colisiona en ese lugar
    {
    case 'w': entidad->setPos(entidad->x,entidad->y - 5); break;

    case 's': entidad->setPos(entidad->x,entidad->y + 5);break;

    case 'd': entidad->setPos(entidad->x + 3,entidad->y);break;

    case 'a': entidad->setPos(entidad->x - 3,entidad->y);break;
    }

    for(short int i = 0; i < obstaculos.size();i++) //se evalua colision con cada una de las obstaculos
    {
        if(entidad->collidesWithItem(obstaculos.at(i),Qt::IntersectsItemBoundingRect))
        {
            entidad->setPos(entidad->x,entidad->y);
            return true;
        }
    }

    entidad->setPos(entidad->x,entidad->y);
    return false;
}

