#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QVector3D>
#include "movement.h"
#include "accelerometer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void addMovement(const QVector3D &acceleration);
    void addAcceleration(const QVector3D &acceleration);
    void updateTextBrowser(const QString &output); // Added slot declaration

private slots:
    void on_StartRecording_clicked();
    void on_StartAttempt_clicked();

private:
    Ui::MainWindow *ui;
    QList<Movement*> movements;
    Accelerometer *accelerometer;
    Movement *currentMovement;
};

#endif // MAINWINDOW_H
