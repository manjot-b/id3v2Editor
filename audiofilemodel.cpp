#include "audiofilemodel.h"
#include <QDateTime>
#include <QDebug>

AudioFileModel::AudioFileModel(QObject *parent)
    : QAbstractTableModel(parent), rows(0), cols(4),
      audioFiles()
{
    //audioFiles = new QVector<QFileInfo>();

}

AudioFileModel::~AudioFileModel()
{

}

void AudioFileModel::addFile(QString filePath)
{
    QFileInfo f(filePath);
    addFile(f);
}

void AudioFileModel::addFile(QFileInfo file)
{
    //QFileInfo f = file;
    audioFiles.append(file);
    rows = audioFiles.size();

    QModelIndex topLeft = createIndex(0, 0);
    QModelIndex bottomRight = createIndex(rows - 1, cols - 1);
    emit dataChanged(topLeft, bottomRight);
}

int AudioFileModel::rowCount(const QModelIndex &parent) const
{
    return rows;
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
            QFileInfo f = audioFiles.at(index.row());
            if (index.column() == ColumnName::FILENAME)
                return f.fileName();
            if (index.column() == ColumnName::FILEPATH)
                return f.absoluteFilePath();
            if (index.column() == ColumnName::FILESIZE)
                return f.size();
            if (index.column() == ColumnName::LASTMODIFIED)
                return f.lastModified().toString("yyyy-MM-dd h:mm AP");
            break;

    }
    return QVariant();
}
