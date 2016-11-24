#ifndef CHILDDLG_H
#define CHILDDLG_H

#include <QDialog>

namespace Ui {
class childDlg;
}

class childDlg : public QDialog
{
    Q_OBJECT

public:
    explicit childDlg(QWidget *parent = 0);
    static QString _drivName;
    static QString _drivCarNumber;
    static QString _drivCarModel;
    ~childDlg();

private slots:
    void on_pushOkButton_clicked();

    void on_pushCloseButton_clicked();

private:
    Ui::childDlg *ui;
};

#endif // CHILDDLG_H
