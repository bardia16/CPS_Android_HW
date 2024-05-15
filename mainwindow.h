#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "accelerometer.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_StartRecording_clicked();
    void on_StartAttempt_clicked();
    void updateTextBrowser(const QString &output); // Added slot declaration

private:
    Ui::MainWindow *ui;
    Accelerometer *accelerometer;
};

#endif // MAINWINDOW_H
