#include "maindlg.h"
#include "ui_maindlg.h"
#include "stoplanedetect.h"
#include <QApplication>
#include <QtGui>
#include <QDebug>
#include <stdio.h>
#include <QTableWidget>
#include <QMediaPlayer>
#include <QVideoWidget>
extern QString childDlg::_drivName;
extern QString childDlg::_drivCarNumber;
extern QString childDlg::_drivCarModel;

Mat frame;	//원 프레임
Mat edges;	//처리된 이후의 프레임
Rect Area(0, 0, 500, 320);	//관심영역

stopLaneDetect finder;
using namespace cv;

int nKey = -1;

MainDlg::MainDlg(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainDlg)
{
    ui->setupUi(this);
}

MainDlg::~MainDlg()
{
    delete ui;
}

void MainDlg::on_pushSignButton_clicked()
{
    scndDlg = new childDlg(this);
    scndDlg->show();
}

void MainDlg::on_pushStartButton_clicked()
{
    // here, input driver's information
    // where, pull childDlg
    ui->drivName->setText(QString(childDlg::_drivName));
    ui->drivCarNum->setText(QString(childDlg::_drivCarNumber));
    ui->drivCarMod->setText(QString(childDlg::_drivCarModel));

    VideoCapture vidmat("/home/dogunkim/computerVision/video/birdView_1425.avi");
    vidmat.set(CAP_PROP_POS_FRAMES, 200);

    while (1)
    {
        if (nKey != -1)
        {
            nKey = waitKey(0);
            nKey = -1;
        }
        else
        {
            nKey = waitKey(10);

            vidmat >> frame;

            if (frame.empty())
                break;

            finder.preprocessing(frame, edges, Area);
            stopLaneDetect realfinder;
            realfinder.transformHough(edges, frame, 0);
            imshow("output", frame);
        }
    }
}
