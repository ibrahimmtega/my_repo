#include "include/utilities.h"
#include <QDebug>
#include <dummy.h>

QByteArray utilities::toVariant()
{

    Dummy dd;

    qDebug()<<"dd : "<<dd.x;

    return utilities::arr;
}
