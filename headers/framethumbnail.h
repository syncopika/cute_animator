#ifndef FRAMETHUMBNAIL_H
#define FRAMETHUMBNAIL_H

#include <QGraphicsLayoutItem>
#include <QGraphicsPixmapItem>
#include <QPen>
#include <QPainter>

class FrameThumbnail : public QGraphicsPixmapItem, public QGraphicsLayoutItem
{

public:
    FrameThumbnail(QPixmap image);
    virtual void setGeometry(const QRectF& rect);

protected:
    virtual QSizeF sizeHint(Qt::SizeHint which, const QSizeF& constraint = QSizeF()) const;

};

#endif // FRAMETHUMBNAIL_H
