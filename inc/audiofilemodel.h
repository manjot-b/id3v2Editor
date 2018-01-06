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

    void setArtist(const QModelIndex &index, const QString &artist);
    void setAlbumArtist(const QModelIndex &index, const QString &albumArtist);
    void setAlbum(const QModelIndex &index, const QString &album);
    void setComments(const QModelIndex &index, const QString &comments);
    void setComposer(const QModelIndex &index, const QString &composer);
    void setDiscNumber(const QModelIndex &index, const QString &discNumber);
    void setDiscTotal(const QModelIndex &index, const QString &discTotal);
    void setLyrics(const QModelIndex &index, const QString &lyrics);
    void setTitle(const QModelIndex &index, const QString &title);
    void setTrackNumber(const QModelIndex &index, const QString &trackNumber);
    void setTrackTotal(const QModelIndex &index, const QString &trackTotal);
    void setYear(const QModelIndex &index, const unsigned int &year);

    void save(const QModelIndex &index);

    enum ColumnName
    {
        FILENAME = 0,
        FILEPATH = 1,
        FILESIZE = 2,
        LASTMODIFIED = 3
    };
private:
    const int cols;
    QVector<AudioFile *> audioFiles;
    QStringList fileFilters;

    bool isInAudioFilesList(AudioFile &file);
};

#endif // AUDIOFILEMODEL_H
