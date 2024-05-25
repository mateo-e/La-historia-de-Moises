#include "proyectil.h"

Proyectil::Proyectil(QGraphicsView *view, float velIn,  qreal xIn, qreal yIn, float theta,QGraphicsItem *parent)
    : QGraphicsItem(parent), velIn(velIn), theta(theta), xIn(xIn), yIn(yIn)
{
    setFlag(QGraphicsItem::ItemIsFocusable); //Inicialización opcional para decir que tiene el foco para eventos del teclado
    viewRect = view ->size();
    dir=1;
    aspecto = new QPixmap(":/sprites/piedra.png");
    tiempoTrans = 0;



}

QRectF Proyectil::boundingRect() const
{
    return QRectF(posX, posY, 30, 30); // Xoordenadas iniciales del rect (sobre el origen del punto), unidades a la derecha y unidades abajo
}

void Proyectil::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(posX,posY,30,30,*aspecto);
    if(pintar)
    {
        setTransformOriginPoint(boundingRect().center()); // se ajusta el eje de giro
        rotacion += 0.01;
        setRotation(rotacion);
    }
}



void Proyectil::moveBy(int dx, int dy)
{
    posX += dx;
    posY += dy;
    setPos(posX, posY);
}

void Proyectil::movParabolico(float *dt)
{
    if(pintar)
    {
        posX = xIn + (velIn*cos(theta) * *dt)*dir;
        posY = yIn - (velIn *sin(theta) * *dt) + (0.5*9.8 * *dt * *dt);

        if(posY>310){
            if(theta > 45 and theta + 12 < 90)
                theta +=12;
            else
                theta +=5;

            theta = -atan((velIn*sin(theta)-9.8 * *dt)/velIn*cos(theta));
            velIn = 0.4 * sqrt(pow(velIn*sin(theta)-9.8 * *dt,2)+pow(velIn*cos(theta),2));
            *dt = 0;
            yIn = posY;
            xIn = posX;
        }



        setPos(posX,posY);
    }
}
