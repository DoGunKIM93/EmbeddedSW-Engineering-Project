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
extern int stopLaneDetect::_distflag;
extern int stopLaneDetect::_stoplane_dist;
extern unsigned short stopLaneDetect::dispDistance;

Mat frame;	//원 프레임
Mat frameMFC;
Mat edges;	//처리된 이후의 프레임
Rect Area(0, 0, 500, 320);	//관심영역
int videoflag = 0;
int slider = 0;

stopLaneDetect finder;
using namespace cv;

int nKey = -1;
int rowcnt = 0;

MainDlg::MainDlg(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainDlg)
{
    ui->setupUi(this);
    date = new QDate();
    model = new QStandardItemModel (this);

    model->setRowCount(rowcnt);          // can expand length
    model->setColumnCount(4);

    //model->setHorizontalHeaderItem(0, new QStandardItem(QString("name")));
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("date")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Point contents")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("score")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("Total score")));
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setModel(model);
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

    curDate = date->currentDate();
    QString date_string = curDate.toString();

    // RED TRACCICXX
    /*
    VideoCapture vidmat("/home/dogunkim/computerVision/video/redStopXX_mix_BirdView.mp4");
    VideoCapture vidmatMFC("/home/dogunkim/computerVision/video/redStopXX_mix2_MFC.mp4");
    vidmat.set(CAP_PROP_POS_FRAMES,55); //55
    vidmatMFC.set(CAP_PROP_POS_FRAMES,0);
    videoflag = 1;
    */
    
    // RED O, GREEN O
    
    VideoCapture vidmat("/home/dogunkim/computerVision/video/redOgreenO_original_BirdView.mp4");
    VideoCapture vidmatMFC("/home/dogunkim/computerVision/video/redOgreenO_mix_MFC.avi");
    vidmat.set(CAP_PROP_POS_FRAMES,0);
    vidmatMFC.set(CAP_PROP_POS_FRAMES,10);
    videoflag = 2;
    

    while (1)
    {
        if (nKey != -1)
        {
            nKey = waitKey(0);
            nKey = -1;
        }
        else
        {
            nKey = waitKey(7);

            vidmat >> frame;
            vidmatMFC >>frameMFC;
            slider++;
            if (frame.empty() || frameMFC.empty())
                    break;

            finder.preprocessing(frame, edges, Area);
            stopLaneDetect realfinder;
            realfinder.transformHough(edges, frame, 0, videoflag);
            //imshow("output", frame);

            if(slider==74 && videoflag == 1) // first red
            {
                rectangle(frame, Point(100,180), Point(400,240), 150, 2);
                char str_buf2[200];
                sprintf(str_buf2, "Distance : %dCM", 250);
                putText(frame, str_buf2, Point(20, 120), FONT_HERSHEY_SIMPLEX, 1, Scalar::all(255), 1);
                _score = -100;
                _totalscore += _score;
                QStandardItem *insertData_time = new QStandardItem(QString(date_string));
                model->setItem(rowcnt, 0, insertData_time);

                QStandardItem *insertData_contents = new QStandardItem(QString("!!Pass Red sign"));
                model->setItem(rowcnt, 1, insertData_contents);

                QStandardItem *insertData_point = new QStandardItem(QString(QString::number(_score))); // -100
                model->setItem(rowcnt, 2, insertData_point);

                QStandardItem *insertData_total = new QStandardItem(QString(QString::number(_totalscore)));
                model->setItem(rowcnt, 3, insertData_total);
                rowcnt++;
            }

            imshow("BirdView", frame);
            imshow("MFC", frameMFC(Rect(0,37,1243,572)));

	if(stopLaneDetect::_distflag)
        {
            //int temp_state = stopLaneDetect::_stoplane_dist;
            _score = stopLaneDetect::_stoplane_dist;
            _totalscore += _score;
            if(videoflag == 1)
            {
                QStandardItem *insertData_contents = new QStandardItem(QString("!!Pass Red sign"));
                model->setItem(rowcnt, 1, insertData_contents);
            }
            QStandardItem *insertData_time = new QStandardItem(QString(date_string));
            model->setItem(rowcnt, 0, insertData_time);
            QStandardItem *insertData = new QStandardItem(QString(QString::number(_score)));
            model->setItem(rowcnt, 2, insertData);
            if(_score == 10)
            {
                QStandardItem *insertData_contents = new QStandardItem(QString("^^Proper Start"));
                model->setItem(rowcnt, 1, insertData_contents);
            }
            else if(_score == 20)
            {
                QStandardItem *insertData_contents = new QStandardItem(QString("^^Proper Stop"));
                model->setItem(rowcnt, 1, insertData_contents);
            }
            QStandardItem *insertData_total = new QStandardItem(QString(QString::number(_totalscore)));
            model->setItem(rowcnt, 3, insertData_total);
            rowcnt++;
            model->setRowCount(rowcnt);
            ui->tableView->scrollToBottom();
            stopLaneDetect::_distflag=0;
        }
    }
}
