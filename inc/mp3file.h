#ifndef MP3FILE_H
#define MP3FILE_H

#include "audiofile.h"


class MP3File : public AudioFile
{
public:
    MP3File(QString absPath);
    MP3File(QFileInfo file);

    QString getArtist() const;
    QString getAlbumArtist() const;
    QString getAlbum() const;
    QString getComments() const;
    QString getComposer() const;
    QString getDiscNumber() const;
    QString getLyrics() const;
    QString getTitle() const;
    QString getTrackNumber() const;
    int getYear() const;

    void setArtist(const QString &artist);
    void setAlbumArtist(const QString &albumArtist);
    void setAlbum(const QString &album);
    void setComments(const QString &comments);
    void setComposer(const QString &composer);
    void setDiscNumber(const QString &discNumber);
    void setLyrics(const QString &lyrics);
    void setTitle(const QString &title);
    void setTrackNumber(const QString &trackNumber);
    void setYear(const unsigned int &year);

    bool save();

private:
    void extractData();
};

#endif // MP3FILE_H
