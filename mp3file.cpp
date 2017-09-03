#include "mp3file.h"

#include <taglib/mpeg/mpegfile.h>
#include <taglib/mpeg/id3v2/id3v2tag.h>
#include <taglib/mpeg/id3v2/id3v2frame.h>

#include <QDebug>

MP3File::MP3File(QString absPath) : AudioFile(absPath)
{
   tagLibFile = new TagLib::MPEG::File(absPath.toStdString().c_str());
   extractData();
}

MP3File::MP3File(QFileInfo file) : AudioFile(file)
{
    tagLibFile = new TagLib::MPEG::File(file.absoluteFilePath().toStdString().c_str());
    extractData();
}

QString MP3File::getArtist() const { return artist; }
QString MP3File::getAlbumArtist() const { return albumArtist; }
QString MP3File::getAlbum() const { return album; }
QString MP3File::getComments() const { return comments; }
QString MP3File::getDiscNumber() const { return discNumber; }
QString MP3File::getLyrics() const { return lyrics; }
QString MP3File::getTitle() const { return title; }
QString MP3File::getTrackNumber() const { return trackNumber; }
int MP3File::getYear() const { return year; }

void MP3File::extractData()
{
    TagLib::MPEG::File *f = dynamic_cast<TagLib::MPEG::File *>(tagLibFile);
    if (f->hasID3v2Tag())
    {
        TagLib::ID3v2::Tag *tag = f->ID3v2Tag();

        artist = QString(tag->artist().toCString());
        album = QString(tag->album().toCString());
        comments = QString(tag->comment().toCString());
        title = QString(tag->title().toCString());
        year = tag->year();

        TagLib::ID3v2::FrameList frames = tag->frameList("TPE2");
        if (!frames.isEmpty())
            albumArtist = QString(tag->frameList("TPE2").front()->toString().toCString());

        frames = tag->frameList("TPOS");
        if(!frames.isEmpty())
            discNumber = QString(tag->frameList("TPOS").front()->toString().toCString());

        frames = tag->frameList("USLT");
        if(!frames.isEmpty())
            lyrics = QString(tag->frameList("USLT").front()->toString().toCString());

        frames = tag->frameList("TRCK");
        if(!frames.isEmpty())
            trackNumber = QString(tag->frameList("TRCK").front()->toString().toCString());
    }
}
