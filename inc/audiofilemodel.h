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

    QString getArtist(const QModelIndex &) const;
    QString getAlbumArtist(const QModelIndex &) const;
    QString getAlbum(const QModelIndex &) const;
    QString getComments(const QModelIndex &) const;
    QString getComposer(const QModelIndex &) const;
    QString getDiscNumber(const QModelIndex &) const;
    QString getDiscTotal(const QModelIndex &) const;
    QString getFileName(const QModelIndex &) const;
    QString getLyrics(const QModelIndex &) const;
    QString getTitle(const QModelIndex &) const;
    QString getTrackNumber(const QModelIndex &) const;
    QString getTrackTotal(const QModelIndex &) const;
    QString getYear(const QModelIndex &) const;

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
