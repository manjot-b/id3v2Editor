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

private:
    void extractData();
};

#endif // MP3FILE_H
