#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include "audiofilemodel.h"

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
    void on_browseImgPushButton_clicked();

    void on_deleteImgPushButton_clicked();

    void on_addDirPushButton_clicked();

    void on_addFilePushButton_clicked();

private:
    Ui::MainWindow *ui;
    QPixmap *albumCoverPixmap;
    AudioFileModel *model;
};

#endif // MAINWINDOW_H
