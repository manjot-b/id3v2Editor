#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStringList>
#include <QFileDialog>
#include <QDir>
#include <QFileInfo>
#include <QDateTime>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    albumCoverPixmap = new QPixmap();
    audioFilesList = new QStringList();
    audioFilesModel = new QStringListModel();
    ui->audioFileListView->setModel(audioFilesModel);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_browseImgPushButton_clicked()
{
    albumCoverPixmap->load("C:/Users/Manjot/Documents/Qt/id3v2Editor/id3v2Editor/damn.jpg");
    int width = ui->albumCoverLabel->width() < albumCoverPixmap->width() ?
                ui->albumCoverLabel->width() : albumCoverPixmap->width();
    int height = ui->albumCoverLabel->height() < albumCoverPixmap->height() ?
                ui->albumCoverLabel->height() : albumCoverPixmap->height();
    ui->albumCoverLabel->setPixmap(albumCoverPixmap->scaled(width, height, Qt::KeepAspectRatio));
}

void MainWindow::on_deleteImgPushButton_clicked()
{
    albumCoverPixmap->load("");   // loads nothing which will delete the image
    ui->albumCoverLabel->setPixmap(*albumCoverPixmap);
}

void MainWindow::on_addDirPushButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(
                this, "Open Directory", QDir::homePath(), QFileDialog::ShowDirsOnly |  QFileDialog::DontResolveSymlinks);
    qDebug() << dir;

    QDir currentDir(dir);
    QStringList fileFilters;
    fileFilters << "*.mp3" << "*.m4a";
    QStringList files = currentDir.entryList(fileFilters);

    qDebug() << files;

    for (QString file : files)
    {
        QString absPath = dir + "/" + file;
        audioFilesList->append(absPath);
    }
    audioFilesModel->setStringList(*audioFilesList); // update model with updated list
}

void MainWindow::on_addFilePushButton_clicked()
{
    QStringList files = QFileDialog::getOpenFileNames(this, "Open Files", QDir::homePath(), "Audio Files(*.mp3 *.mp4 *.m4v *.m4a)");
    qDebug() << files;

    QFileInfo fInfo(files.front());

    qDebug() << fInfo.lastModified().toString("yyyy-MM-dd h:mm AP");

    audioFilesList->append(files);
    audioFilesModel->setStringList(*audioFilesList); // update model with updated list
}
