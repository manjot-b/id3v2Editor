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
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow), unchanged("*unchanged*")
{
    ui->setupUi(this);
    albumCoverPixmap = new QPixmap();

    model = new AudioFileModel(0);
    ui->audioFilesTableView->setModel(model);
    ui->audioFilesTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QItemSelectionModel *selectionModel = ui->audioFilesTableView->selectionModel();
    connect(selectionModel, SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
                                   this, SLOT(on_audioFilesTableView_selectionChanged(QItemSelection, QItemSelection)));

    ui->fileNameComboBox->addItem(unchanged);
    ui->fileNameComboBox->setEditText("");
    ui->artistComboBox->addItem(unchanged);
    ui->artistComboBox->setEditText("");
    ui->yearComboBox->addItem(unchanged);
    ui->yearComboBox->setEditText("");
    ui->commentsComboBox->addItem(unchanged);
    ui->commentsComboBox->setEditText("");
    ui->titleComboBox->addItem(unchanged);
    ui->titleComboBox->setEditText("");
    ui->albumArtistComboBox->addItem(unchanged);
    ui->albumArtistComboBox->setEditText("");
    ui->composerComboBox->addItem(unchanged);
    ui->composerComboBox->setEditText("");
    ui->trackComboBox->addItem(unchanged);
    ui->trackComboBox->setEditText("");
    ui->trackTotalComboBox->addItem(unchanged);
    ui->trackTotalComboBox->setEditText("");
    ui->discComboBox->addItem(unchanged);
    ui->discComboBox->setEditText("");
    ui->discTotalComboBox->addItem(unchanged);
    ui->discTotalComboBox->setEditText("");
    ui->albumComboBox->addItem(unchanged);
    ui->albumComboBox->setEditText("");

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
    QModelIndexList selections = ui->audioFilesTableView->selectionModel()->selectedRows();
    setComboBoxText(selections, ComboBoxType::ARTIST);
    setComboBoxText(selections, ComboBoxType::ALBUMARTIST);
    setComboBoxText(selections, ComboBoxType::ALBUM);
    setComboBoxText(selections, ComboBoxType::COMMENTS);
    setComboBoxText(selections, ComboBoxType::DISC);
    setComboBoxText(selections, ComboBoxType::DISCTOTAL);
    setComboBoxText(selections, ComboBoxType::FILENAME);
    setComboBoxText(selections, ComboBoxType::TITLE);
    setComboBoxText(selections, ComboBoxType::TRACK);
    setComboBoxText(selections, ComboBoxType::TRACKTOTAL);
    setComboBoxText(selections, ComboBoxType::YEAR);
    setComboBoxText(selections, ComboBoxType::COMPOSER);
}

void MainWindow::setComboBoxText(const QModelIndexList &selections, ComboBoxType comboBoxType)
{
    QString field;
    // there is only 1 of each file loaded
    // so no need to check if the file names match
    // for multiple selections
    if (comboBoxType == ComboBoxType::FILENAME)
    {
        if (selections.size() == 0)
            field = "";
        else if (selections.size() == 1)
            field = model->getFileName(selections.front());
        else
            field = unchanged;
        ui->fileNameComboBox->setEditText(field);
        return;
    }

    QComboBox *comboBox;

    switch(comboBoxType)
    {
    case ComboBoxType::TITLE:
        comboBox = ui->titleComboBox; break;
    case ComboBoxType::ARTIST:
        comboBox = ui->artistComboBox; break;
    case ComboBoxType::ALBUMARTIST:
        comboBox = ui->albumArtistComboBox; break;
    case ComboBoxType::ALBUM:
        comboBox = ui->albumComboBox; break;
    case ComboBoxType::YEAR:
        comboBox = ui->yearComboBox; break;
    case ComboBoxType::COMPOSER:
        comboBox = ui->composerComboBox; break;
    case ComboBoxType::COMMENTS:
        comboBox = ui->commentsComboBox; break;
    case ComboBoxType::TRACK:
        comboBox = ui->trackComboBox; break;
    case ComboBoxType::TRACKTOTAL:
        comboBox = ui->trackTotalComboBox; break;
    case ComboBoxType::DISC:
        comboBox = ui->discComboBox; break;
    case ComboBoxType::DISCTOTAL:
        comboBox = ui->discTotalComboBox; break;
    default: return;
    }

    if (!selections.isEmpty())
    {
        switch (comboBoxType)
        {
        case ComboBoxType::TITLE:
            field = model->getTitle(selections.front()); break;
        case ComboBoxType::ARTIST:
            field = model->getArtist(selections.front()); break;
        case ComboBoxType::ALBUMARTIST:
            field = model->getAlbumArtist(selections.front()); break;
        case ComboBoxType::ALBUM:
            field = model->getAlbum(selections.front()); break;
        case ComboBoxType::YEAR:
            field = model->getYear(selections.front()); break;
        case ComboBoxType::COMPOSER:
            //field = model->getComposer(selections.front());
            break;
        case ComboBoxType::COMMENTS:
            field = model->getComments(selections.front()); break;
        case ComboBoxType::TRACK:
            field = model->getTrackNumber(selections.front()); break;
        case ComboBoxType::TRACKTOTAL:
            field = model->getTrackTotal(selections.front()); break;
        case ComboBoxType::DISC:
            field = model->getDiscNumber(selections.front()); break;
        case ComboBoxType::DISCTOTAL:
            field = model->getDiscTotal(selections.front()); break;
        }
    }
    else field = "";

    QString currField;
    bool allSame = true;
    int i = 0;

    while (i < selections.size() && allSame)
    {
        switch (comboBoxType)
        {
        case ComboBoxType::TITLE:
            currField = model->getTitle(selections.at(i)); break;
        case ComboBoxType::ARTIST:
            currField = model->getArtist(selections.at(i)); break;
        case ComboBoxType::ALBUMARTIST:
            currField = model->getAlbumArtist(selections.at(i)); break;
        case ComboBoxType::ALBUM:
            currField = model->getAlbum(selections.at(i)); break;
        case ComboBoxType::YEAR:
            currField = model->getYear(selections.at(i)); break;
        case ComboBoxType::COMPOSER:
            //currField = model->getComposer(selections.at(i));
            break;
        case ComboBoxType::COMMENTS:
            currField = model->getComments(selections.at(i)); break;
        case ComboBoxType::TRACK:
            currField = model->getTrackNumber(selections.at(i)); break;
        case ComboBoxType::TRACKTOTAL:
            currField = model->getTrackTotal(selections.at(i)); break;
        case ComboBoxType::DISC:
            currField = model->getDiscNumber(selections.at(i)); break;
        case ComboBoxType::DISCTOTAL:
            currField = model->getDiscTotal(selections.at(i)); break;
        }

        if (field != currField)
            allSame = false;
        i++;
    }

    if (comboBoxType != ComboBoxType::FILENAME)
    {
        if (!allSame)
            comboBox->setCurrentIndex(0); // makes the combo box show *unchanged*
        else
            comboBox->setEditText(field);    // will make it blank if selections list is empty
    }
}
