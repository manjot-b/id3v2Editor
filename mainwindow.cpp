#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    albumCoverPixmap = new QPixmap();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_browseImgPushButton_clicked()
{
    albumCoverPixmap->load("C:/Users/Manjot/Documents/Qt/id3v2Editor/id3v2Editor/damn.jpg");
    int width = ui->albumCoverLabel->width();
    int height = ui->albumCoverLabel->height();
    ui->albumCoverLabel->setPixmap(albumCoverPixmap->scaled(width, height, Qt::KeepAspectRatio));
}

void MainWindow::on_deleteImgPushButton_clicked()
{
    albumCoverPixmap->load("");   // loads nothing which will delete the image
    ui->albumCoverLabel->setPixmap(*albumCoverPixmap);
}
