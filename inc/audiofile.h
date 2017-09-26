#ifndef AUDIOFILE_H
#define AUDIOFILE_H

#include <QFileInfo>

#include <taglib/toolkit/tfile.h>

class AudioFile : public QFileInfo
{
public:
    AudioFile(QString absPath);
    AudioFile(QFileInfo file);
    virtual ~AudioFile();

    virtual QString getArtist() const = 0;
    virtual QString getAlbumArtist() const = 0;
    virtual QString getAlbum() const = 0;
    virtual QString getComments() const = 0;
    virtual QString getComposer() const = 0;
    virtual QString getDiscNumber() const = 0;
    virtual QString getLyrics() const = 0;
    virtual QString getTitle() const = 0;
    virtual QString getTrackNumber() const = 0;
    virtual int getYear() const = 0;

    virtual void setArtist() const = 0;
    virtual void setAlbumArtist() const = 0;
    virtual void setAlbum() const = 0;
    virtual void setComments() const = 0;
    virtual void setComposer() const = 0;
    virtual void setDiscNumber() const = 0;
    virtual void setLyrics() const = 0;
    virtual void setTitle() const = 0;
    virtual void setTrackNumber() const = 0;
    virtual void setYear() const = 0;


protected:
    TagLib::File *tagLibFile;    // TagLib::File is an abstract class

    QString artist;
    QString albumArtist;
    QString album;
    QString comments;
    QString composer;
    QString discNumber;
    QString lyrics;
    QString title;
    QString trackNumber;
    int year;
};

#endif // AUDIOFILE_H
