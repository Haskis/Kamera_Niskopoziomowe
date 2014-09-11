#ifndef TRAININGSET_H
#define TRAININGSET_H

#include <QObject>
#include <QDir>
#include <QStringList>

#include "opencv2/core/core.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

class TrainingSet : public QObject
{
  Q_OBJECT
public:
  explicit TrainingSet(QObject *parent = 0);

  QStringList getAvailableFaces();
  bool addPerson(const QString &name);
  bool removePerson(const QString &name);
  bool addFace(const QString &person, const QImage &image);

  int getTrainingSet(cv::vector<cv::Mat> &images, cv::vector<int> &labels,cv::vector<QString> &names);
signals:

public slots:


private:
  QDir mainDirectory;

};

#endif // TRAININGSET_H
