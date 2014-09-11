#ifndef CAMERADRIVER_H
#define CAMERADRIVER_H

#include <QObject>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <QImage>
#include <QImageReader>
class CameraDriver : public QObject
{
  Q_OBJECT
public:

  enum Direction{
    Up,
    Down,
    Left,
    Right
  };

  explicit CameraDriver(QObject *parent = 0);

  int inline getFramesCaptured()const {
    return framesCaptured;
  }

signals:
  void imageUpdated(QImage& image);
private slots:
  void replyFinished(QNetworkReply *reply);

public slots:
  void moveCamera(Direction direction);
  void getImage();
private:

  int framesCaptured;
  QImage image;
  QNetworkAccessManager *manager;
};

#endif // CAMERADRIVER_H
