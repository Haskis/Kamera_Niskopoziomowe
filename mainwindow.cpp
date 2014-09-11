#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <stylesheets.h>
extern const QString StyleSheetBadLineEdit;
extern const QString StyleSheetGoodLineEdit;
MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  frameTimer(new QTimer(this)),
  tolerance(50),
  isStreaming(false),
  isTrained(false)
{
  ui->setupUi(this);
  connect(&cameraDriver,SIGNAL(imageUpdated(QImage&)),
          this,SLOT(imageUpdated(QImage&)));

  connect(frameTimer,SIGNAL(timeout()),
          this,SLOT(on_pushButtonGetImage_clicked()));

  //Set's logo image on imageLabel
  QImage logoImage;
  logoImage.load("Pliki/VivotekLogo.jpeg");
  ui->labelImage->setPixmap(QPixmap::fromImage(logoImage));
  ui->labelImage->setScaledContents(true);

  //Fill people from database
  refreshPeople();
}

MainWindow::~MainWindow(){
  delete ui;
}

void MainWindow::imageUpdated(QImage &image )
{
  ui->ledIndicatorWidget->animateClick(20);
  ui->labelFramesCaptured->setText(QString::number(cameraDriver.getFramesCaptured()));
  imageSize = cv::Size(image.size().width(), image.size().height());
  imageProcessing.loadNewImage(image);
  imageProcessing.updateGray();

  if(imageProcessing.detectFaces()){
    faceImage = ImageProcessing::Mat2QImage(*imageProcessing.getGrayImage()).copy(imageProcessing.getFaceRectangle());
    faceImage = faceImage.scaled(QSize(100,100),Qt::IgnoreAspectRatio,Qt::FastTransformation);

    if(!isStreaming)
      ui->pushButtonAddFace->setEnabled(true);
    else{
      if(isTrained){
        int label;
        double confidence;
        recognizer->predict(ImageProcessing::QImage2Mat(faceImage),label,confidence);
        ui->labelActualPerson->setText(names.at(label));
      }
      moveToFace();
    }
  }
  else{
    ui->pushButtonAddFace->setDisabled(true);
    ui->labelActualPerson->setText("None");
    faceImage = QImage();  
  }
  imageProcessing.drawFaceRectangles(true,true);
  ui->labelImage->setPixmap(QPixmap::fromImage(ImageProcessing::Mat2QImage(*imageProcessing.getImage())));
}

void MainWindow::moveToFace(){
  if(imageProcessing.getFaceCentre().x()<imageSize.width/2-tolerance)
    cameraDriver.moveCamera(CameraDriver::Left);

  if(imageProcessing.getFaceCentre().x()>imageSize.width/2+tolerance)
    cameraDriver.moveCamera(CameraDriver::Right);

  if(imageProcessing.getFaceCentre().y()<imageSize.height/2-tolerance)
    cameraDriver.moveCamera(CameraDriver::Up);

  if(imageProcessing.getFaceCentre().y()>imageSize.height/2+tolerance)
    cameraDriver.moveCamera(CameraDriver::Down);
}

void MainWindow::refreshPeople(){
  ui->comboBoxAvailablePeople->clear();
  QStringList people = trainingSet.getAvailableFaces();
  foreach(QString person, people)
    ui->comboBoxAvailablePeople->addItem(person);

}

void MainWindow::on_pushButtonMoveUp_clicked(){
  if(ui->checkBoxEnableMovement->isChecked())
    cameraDriver.moveCamera(CameraDriver::Up);
}

void MainWindow::on_pushButtonMoveRight_clicked(){
  if(ui->checkBoxEnableMovement->isChecked())
    cameraDriver.moveCamera(CameraDriver::Right);
}

void MainWindow::on_pushButtonMoveDown_clicked(){
  if(ui->checkBoxEnableMovement->isChecked())
    cameraDriver.moveCamera(CameraDriver::Down);
}

void MainWindow::on_pushButtonMoveLeft_clicked(){
  if(ui->checkBoxEnableMovement->isChecked())
    cameraDriver.moveCamera(CameraDriver::Left);
}

void MainWindow::on_pushButtonGetImage_clicked(){
  cameraDriver.getImage();
}

void MainWindow::on_pushButtonAddPerson_clicked(){
  if(ui->lineEditNewPerson->text().isEmpty())
    ui->lineEditNewPerson->setStyleSheet(StyleSheetBadLineEdit);
  else
    if(trainingSet.getAvailableFaces().contains(ui->lineEditNewPerson->text()))
      ui->lineEditNewPerson->setStyleSheet(StyleSheetBadLineEdit);
    else{
      trainingSet.addPerson(ui->lineEditNewPerson->text());
      ui->lineEditNewPerson->clear();
      refreshPeople();
      ui->lineEditNewPerson->setStyleSheet(StyleSheetGoodLineEdit);
    }
}

void MainWindow::on_pushButtonRemovePerson_clicked(){
  if(trainingSet.removePerson(ui->comboBoxAvailablePeople->currentText()))
    refreshPeople();
}

void MainWindow::on_pushButtonAddFace_clicked(){
  if(faceImage.isNull())
    return;
  else{
    trainingSet.addFace(ui->comboBoxAvailablePeople->currentText(),faceImage);
  }
}

void MainWindow::on_pushButtonStart_clicked(){
  isStreaming = true;
  ui->checkBoxEnableMovement->setChecked(false);
  ui->checkBoxEnableMovement->setEnabled(false);

  ui->pushButtonGetImage->setDisabled(true);
  ui->pushButtonAddFace->setDisabled(true);
  ui->pushButtonStart->setDisabled(true);
  ui->pushButtonStop->setEnabled(true);
  ui->labelMode->setText("Stream");
  frameTimer->start(200);
}

void MainWindow::on_pushButtonStop_clicked()
{
  isStreaming = false;
  ui->checkBoxEnableMovement->setEnabled(true);
  ui->pushButtonGetImage->setEnabled(true);
  ui->pushButtonStop->setDisabled(true);
  ui->pushButtonStart->setEnabled(true);
  frameTimer->stop();
  ui->labelMode->setText("Stoped");
}

void MainWindow::on_checkBoxEnableMovement_toggled(bool checked)
{
   if(!checked){
     ui->pushButtonMoveDown->setDisabled(true);
     ui->pushButtonMoveUp->setDisabled(true);
     ui->pushButtonMoveLeft->setDisabled(true);
     ui->pushButtonMoveRight->setDisabled(true);
   } else{
     ui->pushButtonMoveDown->setEnabled(true);
     ui->pushButtonMoveUp->setEnabled(true);
     ui->pushButtonMoveLeft->setEnabled(true);
     ui->pushButtonMoveRight->setEnabled(true);
   }
}

void MainWindow::on_pushButtonTrain_clicked(){
  assert(imgs.size() == labels.size());
  //int numberOfPeople = 2
  trainingSet.getTrainingSet(imgs, labels,names);
  int numberOfPeople = names.size();
  //recognizer = cv::createFisherFaceRecognizer(numberOfPeople);
  //recognizer = cv::createLBPHFaceRecognizer();
  recognizer = cv::createEigenFaceRecognizer(numberOfPeople);
  recognizer->train(imgs,labels);
  isTrained = true;
}
