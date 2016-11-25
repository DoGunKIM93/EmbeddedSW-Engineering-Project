#include "childdlg.h"
#include "ui_childdlg.h"

//QString childDlg::_name;

childDlg::childDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::childDlg)
{
    ui->setupUi(this);
    ui->chdrivName->setText(QString(_drivName));
    ui->chdrivCarMod->setText(QString(_drivCarModel));
    ui->chdrivCarNum->setText(QString(_drivCarNumber));
}

childDlg::~childDlg()
{
    delete ui;
}
void childDlg::on_pushOkButton_clicked()
{
    _drivName = ui->chdrivName->text();
    _drivCarModel = ui->chdrivCarMod->text();
    _drivCarNumber = ui->chdrivCarNum->text();
}

void childDlg::on_pushCloseButton_clicked()
{
    this->close();
}
