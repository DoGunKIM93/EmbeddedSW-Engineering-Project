#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <QFileDialog>
#include <QTimer>
#include <QVector>
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_startButton_clicked();
    void on_stopButton_clicked();
    //void on_timer_count();
private:
    Ui::MainWindow *ui;
    QTimer *m_timer;
};

#endif // MAINWINDOW_H
