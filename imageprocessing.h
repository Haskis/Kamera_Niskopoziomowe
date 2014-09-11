#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <QObject>
#include <QImage>

#include "opencv2/core/core.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"

#include <cstdio>
class ImageProcessing : public QObject
{
  Q_OBJECT
public:
  explicit ImageProcessing(QObject *parent = 0);

  const cv::Mat* getGrayImage(){return &grayImage;}
  const cv::Mat* getImage(){return &image;}
  void loadNewImage(QImage const &image);
  void updateGray();


  //Qt <--> OpenCv conversion functions
  static QImage Mat2QImage(const cv::Mat & cvmat);
  static cv::Mat QImage2Mat(const QImage & img);

  //Face detection
  bool detectFaces();
  void drawFaceRectangles(bool normalImageFlag, bool grayImageFlag);

  QPoint getFaceCentre();
  QRect getFaceRectangle();
signals:

public slots:

private:

  //Image processing
  cv::Mat grayImage;
  cv::Mat image;

  //Face detection
  cv::CascadeClassifier haarCascadeFrontOne;
  cv::CascadeClassifier haarCascadeFrontTwo;
  cv::CascadeClassifier haarCascadeFrontThree;
  cv::CascadeClassifier haarCascadeFrontDefault;
  cv::CascadeClassifier haarCascadeProfil;

  cv::vector< cv::Rect_<int> > faces;
};

#endif // IMAGEPROCESSING_H
