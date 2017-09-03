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
    QString getDiscNumber() const;
    QString getLyrics() const;
    QString getTitle() const;
    QString getTrackNumber() const;
    int getYear() const;

private:
    void extractData();
};

#endif // MP3FILE_H
