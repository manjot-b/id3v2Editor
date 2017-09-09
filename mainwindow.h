#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QItemSelection>
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

    void on_audioFilesTableView_selectionChanged(const QItemSelection &,
                                                 const QItemSelection &);

private:
    Ui::MainWindow *ui;
    QPixmap *albumCoverPixmap;
    AudioFileModel *model;
};

#endif // MAINWINDOW_H
