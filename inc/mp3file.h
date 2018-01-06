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

<<<<<<< HEAD:inc/mp3file.h
    void setArtist(QString artist);
    void setAlbumArtist(QString albumArtist);
    void setAlbum(QString album);
    void setComments(QString comments);
    void setComposer(QString composer);
    void setDiscNumber(QString discNumber);
    void setLyrics(QString lyrics);
    void setTitle(QString title);
    void setTrackNumber(QString trackNumber);
    void setYear(int year);
=======
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
>>>>>>> 27bd3ff88ae7f694f03cbf5648ceeef1b78666ff:inc/mp3file.h

    bool save();

private:
    void extractData();
};

#endif // MP3FILE_H
