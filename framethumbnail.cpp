#include "headers/framethumbnail.h"

// width = 50, height = 50
FrameThumbnail::FrameThumbnail(QPixmap image, int width, int height)
{
    this->setPixmap(image);
}

QSizeF FrameThumbnail::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const {
}


void FrameThumbnail::setGeometry(const QRectF& rect){
}
