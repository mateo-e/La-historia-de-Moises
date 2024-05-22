#include "proyectil.h"

Proyectil::Proyectil(QGraphicsView *view, float velIn,  qreal xIn, qreal yIn, float theta,QGraphicsItem *parent)
    : QGraphicsItem(parent), velIn(velIn), theta(theta), xIn(xIn), yIn(yIn)
{
    setFlag(QGraphicsItem::ItemIsFocusable); //Inicialización opcional para decir que tiene el foco para eventos del teclado
    viewRect = view ->size();
    dir=1;

}

QRectF Proyectil::boundingRect() const
{
    return QRectF(55, 55, 10, 10); // Xoordenadas iniciales del rect (sobre el origen del punto), unidades a la derecha y unidades abajo
}

void Proyectil::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::red);
    painter->drawEllipse(55, 55, 10, 10); // Adjust as needed
}



void Proyectil::moveBy(int dx, int dy)
{
    posX += dx;
    posY += dy;
    setPos(posX, posY);
}

void Proyectil::movParabolico(float *dt)
{
    posX = xIn + (velIn*cos(theta) * *dt)*dir;
    posY = yIn - (velIn *sin(theta) * *dt) + (0.5*9.8 * *dt * *dt);
    if(posX>viewRect.width() - 5 || posX<0){
        velIn = 0.8*velIn;
        dir = -1*dir;
        xIn = posX + 10*dir;
        *dt = 0;
        yIn = posY;
        theta= 0;// -atan(velIn*cos(theta)/velIn*sin(theta) * *dt);

    }
    if(posY>viewRect.height()){
        theta = -atan((velIn*sin(theta)-9.8 * *dt)/velIn*cos(theta));
        velIn = 0.8 * sqrt(pow(velIn*sin(theta)-9.8 * *dt,2)+pow(velIn*cos(theta),2));
        *dt = 0;
        posY = posY-5;
        yIn = posY;
        xIn = posX;
    }


    setPos(posX,posY);
}
