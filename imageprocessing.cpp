#include "imageprocessing.h"
#include <QDebug>
#include <QDir>
static bool s_greyTableInit = false;
static QVector<QRgb> s_greyTable;


ImageProcessing::ImageProcessing(QObject *parent) :
  QObject(parent)
{
  haarCascadeFrontDefault.load("../Kamera_Niskopoziomowe/Pliki/haarcascade_frontalface_default.xml");
  haarCascadeFrontOne.load("../Kamera_Niskopoziomowe/Pliki/haarcascade_frontalface_alt.xml");
  haarCascadeFrontTwo.load("../Kamera_Niskopoziomowe/Pliki/haarcascade_frontalface_alt2.xml");
  haarCascadeFrontThree.load("../Kamera_Niskopoziomowe/Pliki/haarcascade_frontalface_alt_tree.xml");
  haarCascadeProfil.load("../Kamera_Niskopoziomowe/Pliki/haarcascade_profileface.xml");
}

void ImageProcessing::loadNewImage(QImage const&image){
  this->image = QImage2Mat(image);
}

void ImageProcessing::updateGray(){
  cv::cvtColor(this->image,this->grayImage,CV_BGR2GRAY);
  cv::equalizeHist( this->grayImage, this->grayImage );
}

QImage ImageProcessing::Mat2QImage(const cv::Mat & cvmat)
{
  int height = cvmat.rows;
  int width = cvmat.cols;

  if (cvmat.depth() == CV_8U && cvmat.channels() == 3) {
      QImage img((const uchar*)cvmat.data, width, height, cvmat.step.p[0], QImage::Format_RGB888);
      return img.rgbSwapped();
  }
  else if (cvmat.depth() == CV_8U && cvmat.channels() == 1) {
    if (!s_greyTableInit) {
        for (int i = 0; i < 256; i++){
            s_greyTable.push_back(qRgb(i, i, i));
        }
    }
    QImage img((const uchar*)cvmat.data, width, height, cvmat.step.p[0], QImage::Format_Indexed8);
    img.setColorTable(s_greyTable);
    return img;
  }
  else if (cvmat.depth() == CV_8U && cvmat.channels() == 4) {
    QImage img((const uchar*)cvmat.data, width, height, cvmat.step.p[0], QImage::Format_RGB32);
    return img.rgbSwapped();
}
  else {
      qWarning() << "Image cannot be converted.";
      return QImage();
  }

}

cv::Mat ImageProcessing::QImage2Mat(const QImage &img)
{
  int cvType;

  switch (img.format()) {
  case QImage::Format_Indexed8:
    cvType = CV_8UC1;
    break;
  case QImage::Format_RGB888:
    cvType = CV_8UC3;
    break;
  case QImage::Format_RGB32:
    cvType = CV_8UC4;
    break;
  default:
    qCritical() << "Error: unsupported conversion from QImage to cv::Mat";
    return cv::Mat();
  }

  //We need to copy data, becouse we nedd to switch colors from rgb to brg
  cv::Mat mat(img.height(), img.width(), cvType, (void*)img.bits(), img.bytesPerLine());
  cv::Mat result;
  if(cvType != CV_8UC1){
    cv::cvtColor(mat, result, CV_RGB2BGR);
    return result;
  } else{
    return mat;
  }
}

bool ImageProcessing::detectFaces()
{
  haarCascadeFrontOne.detectMultiScale(grayImage, faces);
  return faces.size()>0;
}

void ImageProcessing::drawFaceRectangles(bool normalImageFlag, bool grayImageFlag)
{
  if(normalImageFlag){
    for(int i=0; i<faces.size(); i++){
      cv::rectangle(image,faces.at(i),cv::Scalar(255,0,0),2);
      }
  }
  if(grayImageFlag){
    for(int i=0; i<faces.size(); i++)
      cv::rectangle(grayImage,faces.at(i),cv::Scalar(255,0,0),2);
    }
}

QPoint ImageProcessing::getFaceCentre(){
  assert(faces.size()>0);

  QPoint centre(faces.at(0).x+faces.at(0).width/2,faces.at(0).y+faces.at(0).height/2);
  return centre;
}
QRect ImageProcessing::getFaceRectangle(){
  assert(faces.size()>0);

  return QRect(faces.at(0).x, faces.at(0).y, faces.at(0).width, faces.at(0).height);

}
