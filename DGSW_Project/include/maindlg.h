#ifndef MAINDLG_H
#define MAINDLG_H

#include <QMainWindow>
#include <QtGui>
#include "childdlg.h"

namespace Ui {
class MainDlg;
}

class MainDlg : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainDlg(QWidget *parent = 0);
    ~MainDlg();

private slots:
    void on_pushSignButton_clicked();

    void on_pushStartButton_clicked();

private:
    Ui::MainDlg *ui;
    childDlg *scndDlg;
    QStandardItemModel *model;
    QDate *date;
    QDate curDate;

    int _score;
    int _totalscore;
};

#endif // MAINDLG_H
