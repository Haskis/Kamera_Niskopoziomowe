#ifndef LEDINDICATOR_H
#define LEDINDICATOR_H

#include <QAbstractButton>
#include <QResizeEvent>
#include <QColor>
#include <QDebug>
#include <QTimer>

class LedIndicator : public QAbstractButton
{
  Q_PROPERTY(QColor onColor1      WRITE setOnColor1     READ getOnColor1   )
  Q_PROPERTY(QColor onColor2      WRITE setOnColor2     READ getOnColor2   )
  Q_PROPERTY(QColor offColor1     WRITE setOffColor1    READ getOffColor1  )
  Q_PROPERTY(QColor offColor2     WRITE setOffColor2    READ getOffColor2  )
  Q_OBJECT
public:
  LedIndicator(QWidget *parent);

  void setOnColor1(QColor c)  { onColor1  = c;    }
  void setOffColor1(QColor c) { offColor1 = c;    }
  void setOnColor2(QColor c)  { onColor2  = c;    }
  void setOffColor2(QColor c) { offColor2 = c;    }

  QColor getOnColor1(void)    { return onColor1;  }
  QColor getOffColor1(void)   { return offColor1; }
  QColor getOnColor2(void)    { return onColor2;  }
  QColor getOffColor2(void)   { return offColor2; }

protected:
  virtual bool hitButton(const QPoint &pos) const;
  virtual void paintEvent (QPaintEvent *event);
  virtual void resizeEvent(QResizeEvent *event);
private:
  QTimer *timer;
  static const qreal scaledSize;  /* init in cpp */
  QColor  onColor1, offColor1;
  QColor  onColor2, offColor2;
  QPixmap ledBuffer;
};

#endif // LEDINDICATOR_H
