#include "maindlg.h"
#include "ui_maindlg.h"

extern QString childDlg::_drivName;
extern QString childDlg::_drivCarNumber;
extern QString childDlg::_drivCarModel;

MainDlg::MainDlg(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainDlg)
{
    ui->setupUi(this);
    model = new QStandardItemModel (this);

    model->setRowCount(1);          // can expand length
    model->setColumnCount(3);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("name")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("date")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("score")));

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
}
