#include "audiofilemodel.h"
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

AudioFileModel::~AudioFileModel() {}

void AudioFileModel::addFile(const QString &filePath)
{
    QFileInfo f(filePath);
    addFile(f);
}

void AudioFileModel::addFile(QFileInfo file)
{
    beginInsertRows(QModelIndex(), audioFiles.size()+1, audioFiles.size()+1);
    audioFiles.append(file);
    endInsertRows();

}

void AudioFileModel::addFiles(const QStringList &filePaths)
{
    QVector<QFileInfo> temp;
    for (QString path : filePaths)
    {
        QFileInfo f(path);
        temp.append(f);
    }
    addFiles(temp);
}

void AudioFileModel::addFiles(const QVector<QFileInfo> &files)
{
    if (files.isEmpty()) return;
    int firstRow = audioFiles.size() + 1;
    int lastRow = audioFiles.size() + files.size();
    beginInsertRows(QModelIndex(), firstRow, lastRow);
    audioFiles.append(files);
    endInsertRows();
}

void AudioFileModel::addFilesFromDirectory(const QString &dir)
{
    QDir currentDir(dir);
    QList<QFileInfo> tempList = currentDir.entryInfoList(fileFilters);
    qDebug() << dir;
    addFiles(QVector<QFileInfo>::fromList(tempList));
}

int AudioFileModel::rowCount(const QModelIndex &parent) const
{
    return audioFiles.size();
}

int AudioFileModel::columnCount(const QModelIndex &parent) const
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
            QFileInfo f = audioFiles.at(index.row());
            switch(index.column())
            {
            case ColumnName::FILENAME:
                return f.fileName();
            case ColumnName::FILEPATH:
                return f.absoluteFilePath();
            case ColumnName::FILESIZE:
                return QString::number(f.size() / (float)1048576, 'f', 2);   // bytes to megabytes
            case ColumnName::LASTMODIFIED:
                return f.lastModified().toString("yyyy-MM-dd h:mm AP");
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
