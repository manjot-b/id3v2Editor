#include "audiofilemodel.h"
#include "mp3file.h"

#include <QDateTime>
#include <QList>
#include <QDir>
#include <QDebug>

AudioFileModel::AudioFileModel(QObject *parent)
    : QAbstractTableModel(parent), cols(4),
      audioFiles(), fileFilters()
{
    fileFilters << "*mp3" << "*.m4a";
}

AudioFileModel::~AudioFileModel()
{
    for (AudioFile *f : audioFiles)
        delete f;
}

bool AudioFileModel::addFile(const QString &filePath)
{
    //AudioFile f(filePath);
    QStringList extension = filePath.split(".");
    if (!extension.isEmpty() && extension.last() == "mp3")
    {
        MP3File *mp3 = new MP3File(filePath);
        if (mp3 != nullptr) // will not open if used by another process or currently open
            return addFile(mp3);
    }
    return false;
}

bool AudioFileModel::addFile(AudioFile *file)
{
    if (file->isFile())
    {
        if (!isInAudioFilesList(*file))
        {
            beginInsertRows(QModelIndex(), audioFiles.size()+1, audioFiles.size()+1);
            audioFiles.append(file);
            endInsertRows();
            return true;    // success
        }
    }

    return false;   // file wasn't a file or was a duplicate
}

bool AudioFileModel::addFiles(const QStringList &filePaths)
{
    QVector<AudioFile *> temp;
    for (QString path : filePaths)
    {
        QStringList extension = path.split(".");
        if (extension.last() == "mp3")
        {
            MP3File *file = new MP3File(path);
            if (file != nullptr)
                temp.append(file);
        }
    }
    return addFiles(temp);
}

bool AudioFileModel::addFiles(QVector<AudioFile *> &files)
{
    QVector<AudioFile *>::const_reverse_iterator rit = files.rbegin();
    for (; rit != files.rend(); rit++)
    {
        if (!((*rit)->isFile()))
            return false;   // failure

        if (isInAudioFilesList( **rit ))
            files.removeAll(*rit);
    }

    if (files.isEmpty())
        return true;

    int firstRow = audioFiles.size() + 1;
    int lastRow = audioFiles.size() + files.size();
    beginInsertRows(QModelIndex(), firstRow, lastRow);
    audioFiles.append(files);
    endInsertRows();

    return true;
}

bool AudioFileModel::addFilesFromDirectory(const QString &dir)
{
    QDir currentDir(dir);
    QList<QFileInfo> tempList = currentDir.entryInfoList(fileFilters);
    QVector<AudioFile *> tempVec;
    for (auto const &file : tempList)
    {
        if (file.suffix() == "mp3")
        {
            MP3File *mp3File = new MP3File(file);
            if (mp3File != nullptr)
                tempVec.append(mp3File);
        }
    }

    return addFiles(tempVec);
}

bool AudioFileModel::isInAudioFilesList(AudioFile &file)
{
    if (audioFiles.isEmpty())
        return false;

    for (auto ptr : audioFiles)
    {
        if (ptr->absoluteFilePath() == file.absoluteFilePath())
            return true;
    }
    return false;
}

int AudioFileModel::rowCount(const QModelIndex & /*parent*/) const
{
    return audioFiles.size();
}

int AudioFileModel::columnCount(const QModelIndex & /*parent*/) const
{
    return cols;
}

QVariant AudioFileModel::data(const QModelIndex &index, int role) const
{
    switch(role)
    {
    case Qt::DisplayRole:
        if (!audioFiles.isEmpty())
        {
            QFileInfo *f = audioFiles.at(index.row());
            switch(index.column())
            {
            case ColumnName::FILENAME:
                return f->fileName();
            case ColumnName::FILEPATH:
                return f->absoluteFilePath();
            case ColumnName::FILESIZE:
                return QString::number(f->size() / (float)1048576, 'f', 2);   // bytes to megabytes
            case ColumnName::LASTMODIFIED:
                return f->lastModified().toString("yyyy-MM-dd h:mm AP");
            }
        }
        break;

    case Qt::TextAlignmentRole:
        switch(index.column())
        {
        case ColumnName::FILESIZE:
        case ColumnName::LASTMODIFIED:
            return Qt::AlignRight; break;
        }
        break;
    }
    return QVariant();
}

QVariant AudioFileModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
    {
        switch(role)
        {
        case Qt::DisplayRole:
            switch(section)
            {
            case ColumnName::FILENAME:
                return "Filename"; break;
            case ColumnName::FILEPATH:
                return "Filepath"; break;
            case ColumnName::FILESIZE:
                return "Size (MB)"; break;
            case ColumnName::LASTMODIFIED:
                return "Last Modified"; break;
            }
            break;
        }
    }
    return QVariant();
}

QString AudioFileModel::getArtist(const QModelIndex &index) const
{
    return audioFiles[index.row()]->getArtist();
}

QString AudioFileModel::getAlbumArtist(const QModelIndex &index) const
{
    return audioFiles[index.row()]->getAlbumArtist();
}

QString AudioFileModel::getAlbum(const QModelIndex &index) const
{
    return audioFiles[index.row()]->getAlbum();
}

QString AudioFileModel::getComments(const QModelIndex &index) const
{
    return audioFiles[index.row()]->getComments();
}

QString AudioFileModel::getComposer(const QModelIndex &index) const
{
    return audioFiles[index.row()]->getComposer();
}

QString AudioFileModel::getDiscNumber(const QModelIndex &index) const
{
    QString discField= audioFiles[index.row()]->getDiscNumber();
    QString discNumber = discField.split('/').first();
    return discNumber;
}

QString AudioFileModel::getDiscTotal(const QModelIndex &index) const
{
    QString discField = audioFiles[index.row()]->getDiscNumber();
    QString discTotal;
    QStringList split = discField.split('/');

    if (split.size() > 1) discTotal = split.at(1);
    return discTotal;
}

QString AudioFileModel::getFileName(const QModelIndex &index) const
{
    return audioFiles[index.row()]->fileName();
}

QString AudioFileModel::getLyrics(const QModelIndex &index) const
{
    return audioFiles[index.row()]->getLyrics();
}

QString AudioFileModel::getTitle(const QModelIndex &index) const
{
    return audioFiles[index.row()]->getTitle();
}

QString AudioFileModel::getTrackNumber(const QModelIndex &index) const
{
    QString trackField = audioFiles[index.row()]->getTrackNumber();
    QString trackNumber = trackField.split('/').first();
    return trackNumber;
}

QString AudioFileModel::getTrackTotal(const QModelIndex &index) const
{
    QString trackField = audioFiles[index.row()]->getTrackNumber();
    QString trackTotal;
    QStringList split = trackField.split('/');

    if (split.size() > 1) trackTotal = split.at(1);
    return trackTotal;
}

QString AudioFileModel::getYear(const QModelIndex &index) const
{
    QString year = QString::number(audioFiles[index.row()]->getYear());
    return year;
}
