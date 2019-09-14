#include "headers/framethumbnail.h"

// width = 50, height = 50
FrameThumbnail::FrameThumbnail(QPixmap image)
{
    setPixmap(image);
}

QSizeF FrameThumbnail::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const {
    Q_UNUSED(which);
    Q_UNUSED(constraint);
    return boundingRect().size();
}

void FrameThumbnail::setGeometry(const QRectF& rect){
    setPos(rect.topLeft());
}
