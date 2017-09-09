#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "audiofilemodel.h"
#include "mp3file.h"

#include <QStringList>
#include <QFileDialog>
#include <QDir>
#include <QFileInfo>
#include <QDateTime>
#include <QItemSelectionModel>
#include <QModelIndexList>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    albumCoverPixmap = new QPixmap();

    model = new AudioFileModel(0);
    ui->audioFilesTableView->setModel(model);
    ui->audioFilesTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QItemSelectionModel *selectionModel = ui->audioFilesTableView->selectionModel();
    connect(selectionModel, SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
                                   this, SLOT(on_audioFilesTableView_selectionChanged(QItemSelection, QItemSelection)));

    /*MP3File f("doctor.mp3");
    qDebug() << "Artist " << f.getArtist();
    qDebug() << "Album Artist " << f.getAlbumArtist();
    qDebug() << "Comments " << f.getComments();
    qDebug() << "DiscNumber " << f.getDiscNumber();
    qDebug() << "Lyrics " << f.getLyrics();
    qDebug() << "Title " << f.getTitle();
    qDebug() << "Track " << f.getTrackNumber();
    qDebug() << "Year " << f.getYear();*/
}

MainWindow::~MainWindow()
{
    delete ui;
    delete model;
    delete albumCoverPixmap;
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
                this, "Open Directory", QDir::homePath(),
                QFileDialog::ShowDirsOnly |  QFileDialog::DontResolveSymlinks);
    qDebug() << model->addFilesFromDirectory(dir);

}

void MainWindow::on_addFilePushButton_clicked()
{
    QStringList files = QFileDialog::getOpenFileNames(this, "Open Files",
                                                      QDir::homePath(),
                                                      "Audio Files(*.mp3 *.mp4 *.m4v *.m4a)");
    qDebug() << files;

    qDebug() << model->addFiles(files);

}

void MainWindow::on_audioFilesTableView_selectionChanged(const QItemSelection &,
                                                         const QItemSelection &)
{
    QModelIndexList selection = ui->audioFilesTableView->selectionModel()->selectedRows();

    QString artist = model->getArtist(selection.front());
    ui->artistLineEdit->setText(artist);
}
