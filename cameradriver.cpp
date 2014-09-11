#include "cameradriver.h"

CameraDriver::CameraDriver(QObject *parent) :
  QObject(parent)
{
  framesCaptured = 0;

  manager = new QNetworkAccessManager(this);
  manager->get(QNetworkRequest(QUrl("http://192.168.1.99/cgi-bin/camctrl.cgi?focus=auto&iris=auto")));

  connect(manager, SIGNAL(finished(QNetworkReply*)),
          this, SLOT(replyFinished(QNetworkReply*)));
}

void CameraDriver::moveCamera(CameraDriver::Direction direction){

  switch(direction){

    case Up:{
      manager->get(QNetworkRequest(QUrl("http://192.168.1.99/cgi-bin/camctrl.cgi?move=up")));
      break;
    }
    case Down:{
      manager->get(QNetworkRequest(QUrl("http://192.168.1.99/cgi-bin/camctrl.cgi?move=down")));
      break;
    }
    case Left:{
      manager->get(QNetworkRequest(QUrl("http://192.168.1.99/cgi-bin/camctrl.cgi?move=left")));
      break;
    }
    case Right:{
       manager->get(QNetworkRequest(QUrl("http://192.168.1.99/cgi-bin/camctrl.cgi?move=right")));
      break;
    }
  }
}

void CameraDriver::getImage(){
  manager->get(QNetworkRequest(QUrl("http://192.168.1.99/cgi-bin/video.jpg")));
}
void CameraDriver::replyFinished(QNetworkReply * reply)
{
  QImageReader reader(reply);
  reader.setFormat("jpg");
  image = reader.read();
  reply->deleteLater();
  if(image.isNull())
    return;
  image = image.convertToFormat(QImage::Format_RGB888);
  framesCaptured++;
  emit imageUpdated(image);
}
