#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_timer = new QTimer;
    connect(m_timer, SIGNAL(timeout()), this, SLOT(on_timer_count()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    // using prev tool
    QString qsfileName=QFileDialog::getOpenFileName(this, tr("Open Image"),"../",tr("Image Files(*.png *.jpg *.bmp"));
    cv::Mat image = cv::imread(qsfileName.toStdString());

    //cv::Mat image = cv::imread("/home/sunwung/Desktop/QtTest/gunners.jpg");
    cv::imshow("testImshow", image);
    cv::waitKey(0);
}

void MainWindow::on_stopButton_clicked()
{
    m_timer->start(100);
}
