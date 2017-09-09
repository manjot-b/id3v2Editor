#ifndef AUDIOFILEMODEL_H
#define AUDIOFILEMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include <QFileInfo>
#include <QStringList>
#include <QVariant>
#include <QModelIndex>
#include "audiofile.h"

class AudioFileModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    AudioFileModel(QObject *parent);
    virtual ~AudioFileModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    bool addFile(AudioFile *);
    bool addFile(const QString &);
    bool addFiles(const QStringList &);
    bool addFiles(QVector<AudioFile *> &);
    bool addFilesFromDirectory(const QString &);

    QString getArtist(QModelIndex &) const;
    QString getAlbumArtist(QModelIndex &) const;
    QString getAlbum(QModelIndex &) const;
    QString getComments(QModelIndex &) const;
    QString getDiscNumber(QModelIndex &) const;
    QString getLyrics(QModelIndex &) const;
    QString getTitle(QModelIndex &) const;
    QString getTrackNumber(QModelIndex &) const;
    int getYear(QModelIndex &) const;

    enum ColumnName
    {
        FILENAME = 0,
        FILEPATH = 1,
        FILESIZE = 2,
        LASTMODIFIED = 3
    };
private:
    QVector<AudioFile *> audioFiles;
    const int cols;
    QStringList fileFilters;

    bool isInAudioFilesList(AudioFile &file);
};

#endif // AUDIOFILEMODEL_H
