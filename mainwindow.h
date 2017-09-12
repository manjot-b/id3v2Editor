#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QItemSelection>
#include <QModelIndexList>
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

    enum ComboBoxType
    {
        FILENAME,
        TITLE,
        ARTIST,
        ALBUMARTIST,
        ALBUM,
        YEAR,
        COMPOSER,
        COMMENTS,
        TRACK,
        TRACKTOTAL,
        DISC,
        DISCTOTAL
    };

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
    QString unchanged;

    void setComboBoxText(const QModelIndexList &selections, ComboBoxType comboBoxType);
};

#endif // MAINWINDOW_H
