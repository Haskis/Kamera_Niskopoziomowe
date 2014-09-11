#include "trainingset.h"
#include <QImage>
#include <QDebug>
TrainingSet::TrainingSet(QObject *parent) :
  QObject(parent)
{
  mainDirectory.setPath("Pliki/Faces");
}

QStringList TrainingSet::getAvailableFaces(){
  return mainDirectory.entryList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name);
}

bool TrainingSet::addPerson(const QString &name){
  if(getAvailableFaces().contains(name))
    return false;
  else
    mainDirectory.mkdir(name);
}

bool TrainingSet::removePerson(const QString &name){

  if(getAvailableFaces().contains(name) == false)
    return false;
  else{
    mainDirectory.cd(name);
    qDebug()<<mainDirectory.removeRecursively();
    mainDirectory.cd("..");
  }
}

bool TrainingSet::addFace(const QString &person, const QImage &image)
{
  if(getAvailableFaces().contains(person) == false)
    return false;
  else{
    QString photoName;
    QDir faceDirectory;
    faceDirectory.setPath(mainDirectory.path() + "/" + person);
    photoName.sprintf("%06d", faceDirectory.entryList(QDir::Files).size() +1);
    image.save(faceDirectory.path() + "/" + photoName + ".jpg","jpg", 100);
  }
}

int TrainingSet::getTrainingSet(cv::vector<cv::Mat> &images, cv::vector<int> &labels, cv::vector<QString> &names){
  QStringList directoriesList = getAvailableFaces();

  labels.clear();
  images.clear();
  names.clear();
  for(int i=0; i<directoriesList.size(); i++){
    QString person = directoriesList.at(i);
    QDir faceDirectory;
    faceDirectory.setPath(mainDirectory.path() + "/" + person);
    QStringList photosList = faceDirectory.entryList(QDir::Files);
    foreach(QString photo, photosList){
      images.push_back(cv::imread(faceDirectory.path().toStdString() + "/" + photo.toStdString(), CV_LOAD_IMAGE_GRAYSCALE));
      labels.push_back(i);
    }
    names.push_back(person);
  }
  return directoriesList.size();

}
