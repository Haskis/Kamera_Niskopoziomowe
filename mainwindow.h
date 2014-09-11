#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <cameradriver.h>
#include <imageprocessing.h>
#include <trainingset.h>
namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  void moveToFace();
  void refreshPeople();
private:
  Ui::MainWindow *ui;
  CameraDriver cameraDriver;
  ImageProcessing imageProcessing;
public slots:
  void imageUpdated(QImage &image);
private slots:
  void on_pushButtonMoveUp_clicked();
  void on_pushButtonMoveRight_clicked();
  void on_pushButtonMoveDown_clicked();
  void on_pushButtonMoveLeft_clicked();
  void on_pushButtonGetImage_clicked();
  void on_pushButtonAddPerson_clicked();

  void on_pushButtonRemovePerson_clicked();
  void on_pushButtonAddFace_clicked();
  void on_pushButtonStart_clicked();
  void on_pushButtonStop_clicked();

  void on_checkBoxEnableMovement_toggled(bool checked);

  void on_pushButtonTrain_clicked();

private:
  cv::Ptr<cv::FaceRecognizer> recognizer;
  bool isStreaming;
  bool isTrained;
  int tolerance;
  QImage faceImage;
  cv::Size imageSize;
  QTimer *frameTimer;
  QPalette p;
  TrainingSet trainingSet;
  cv::vector<cv::Mat> imgs;
  cv::vector<int> labels;
  cv::vector<QString> names;
};

#endif // MAINWINDOW_H
