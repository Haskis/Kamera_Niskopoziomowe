
#include <QPainter>

#include "ledindicator.h"

const qreal LedIndicator::scaledSize = 1000; /* Visual Studio static const mess */

LedIndicator::LedIndicator(QWidget *parent) : QAbstractButton(parent)
{
  setMinimumSize(24,24);
  onColor1 =  QColor(0,255,0);
  onColor2 =  QColor(0,0,0);
  offColor1 = QColor(255,0,0);
  offColor2 = QColor(0,0,0);
}

bool LedIndicator::hitButton(const QPoint &pos) const
{
  return false;
}

void LedIndicator::resizeEvent(QResizeEvent *event) {
  update();
}

void LedIndicator::paintEvent(QPaintEvent *event) {
    qreal realSize = qMin(width(), height());

    QRadialGradient gradient;
    QPainter painter(this);
    QPen     pen(Qt::black);
             pen.setWidth(1);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width()/2, height()/2);
    painter.scale(realSize/scaledSize, realSize/scaledSize);

    gradient = QRadialGradient (QPointF(-500,-500), 1500, QPointF(-500,-500));
    gradient.setColorAt(0, QColor(224,224,224));
    gradient.setColorAt(1, QColor(28,28,28));
    painter.setPen(pen);
    painter.setBrush(QBrush(gradient));
    painter.drawEllipse(QPointF(0,0), 500, 500);

    gradient = QRadialGradient (QPointF(500,500), 1500, QPointF(500,500));
    gradient.setColorAt(0, QColor(224,224,224));
    gradient.setColorAt(1, QColor(28,28,28));
    painter.setPen(pen);
    painter.setBrush(QBrush(gradient));
    painter.drawEllipse(QPointF(0,0), 450, 450);

    painter.setPen(pen);
    if( isDown() ) {
        gradient = QRadialGradient (QPointF(-500,-500), 1500, QPointF(-500,-500));
        gradient.setColorAt(0, onColor1);
        gradient.setColorAt(1, onColor2);
    } else {
        gradient = QRadialGradient (QPointF(500,500), 1500, QPointF(500,500));
        gradient.setColorAt(0, offColor1);
        gradient.setColorAt(1, offColor2);
    }
    painter.setBrush(gradient);
    painter.drawEllipse(QPointF(0,0), 400, 400);
}

