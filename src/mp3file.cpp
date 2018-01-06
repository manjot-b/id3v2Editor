#include "mp3file.h"

#include <mpegfile.h>
#include <id3v2tag.h>
#include <id3v2frame.h>
#include <textidentificationframe.h>
#include <unsynchronizedlyricsframe.h>

#include <QDebug>

typedef TagLib::MPEG::File TagLibMp3File;

MP3File::MP3File(QString absPath) : AudioFile(absPath)
{
   tagLibFile = new TagLibMp3File(absPath.toStdString().c_str());
   extractData();
}

MP3File::MP3File(QFileInfo file) : AudioFile(file)
{
    tagLibFile = new TagLibMp3File(file.absoluteFilePath().toStdString().c_str());
    extractData();
}

QString MP3File::getArtist() const { return artist; }
QString MP3File::getAlbumArtist() const { return albumArtist; }
QString MP3File::getAlbum() const { return album; }
QString MP3File::getComments() const { return comments; }
QString MP3File::getComposer() const { return composer; }
QString MP3File::getDiscNumber() const { return discNumber; }
QString MP3File::getLyrics() const { return lyrics; }
QString MP3File::getTitle() const { return title; }
QString MP3File::getTrackNumber() const { return trackNumber; }
int MP3File::getYear() const { return year; }

void MP3File::setArtist(const QString &artist)
{
    TagLibMp3File *f = dynamic_cast<TagLibMp3File *>(tagLibFile);
    f->ID3v2Tag()->setArtist(artist.toStdString());
    this->artist = artist;
}

void MP3File::setAlbumArtist(const QString &albumArtist)
{
    TagLibMp3File *f = dynamic_cast<TagLibMp3File *>(tagLibFile);
    if (f->ID3v2Tag()->frameList("TPE2").isEmpty())
    {
        TagLib::ID3v2::TextIdentificationFrame *frame = new TagLib::ID3v2::TextIdentificationFrame("TPE2");
        frame->setText(albumArtist.toStdString());
        f->ID3v2Tag()->addFrame(frame);
    }
    else
    {
        f->ID3v2Tag()->frameList("TPE2").front()->setText(albumArtist.toStdString());
    }
    this->albumArtist = albumArtist;
}

void MP3File::setAlbum(const QString &album)
{
    TagLibMp3File *f = dynamic_cast<TagLibMp3File *>(tagLibFile);
    f->ID3v2Tag()->setAlbum(album.toStdString());
    this->album= album;
}

void MP3File::setComments(const QString &comments)
{
    TagLibMp3File *f = dynamic_cast<TagLibMp3File *>(tagLibFile);
    f->ID3v2Tag()->setComment(comments.toStdString());
    this->comments = comments;
}

void MP3File::setComposer(const QString &composer)
{
    TagLibMp3File *f = dynamic_cast<TagLibMp3File *>(tagLibFile);
    if (f->ID3v2Tag()->frameList("TCOM").isEmpty())
    {
        TagLib::ID3v2::TextIdentificationFrame *frame = new TagLib::ID3v2::TextIdentificationFrame("TCOM");
        frame->setText(composer.toStdString());
        f->ID3v2Tag()->addFrame(frame);
    }
    else
    {
        f->ID3v2Tag()->frameList("TCOM").front()->setText(composer.toStdString());
    }
    this->composer = composer;
}

void MP3File::setDiscNumber(const QString &discNumber)
{
    TagLibMp3File *f = dynamic_cast<TagLibMp3File *>(tagLibFile);
    if (f->ID3v2Tag()->frameList("TPOS").isEmpty())
    {
        TagLib::ID3v2::TextIdentificationFrame *frame = new TagLib::ID3v2::TextIdentificationFrame("TPOS");
        frame->setText(discNumber.toStdString());
        f->ID3v2Tag()->addFrame(frame);
    }
    else
    {
        f->ID3v2Tag()->frameList("TPOS").front()->setText(discNumber.toStdString());
    }
    this->discNumber = discNumber;
}

void MP3File::setLyrics(const QString &lyrics)
{
    TagLibMp3File *f = dynamic_cast<TagLibMp3File *>(tagLibFile);
    if (f->ID3v2Tag()->frameList("USLT").isEmpty())
    {
        TagLib::ID3v2::UnsynchronizedLyricsFrame *frame = new TagLib::ID3v2::UnsynchronizedLyricsFrame();
        frame->setText(lyrics.toStdString());
        f->ID3v2Tag()->addFrame(frame);
    }
    else
    {
        f->ID3v2Tag()->frameList("USLT").front()->setText(lyrics.toStdString());
    }
    this->lyrics = lyrics;
}

void MP3File::setTitle(const QString &title)
{
    TagLibMp3File *f = dynamic_cast<TagLibMp3File *>(tagLibFile);
    f->ID3v2Tag()->setTitle(title.toStdString());
    this->title= title;
}

void MP3File::setTrackNumber(const QString &trackNumber)
{
    TagLibMp3File *f = dynamic_cast<TagLibMp3File *>(tagLibFile);
    if (f->ID3v2Tag()->frameList("TRCK").isEmpty())
    {
        TagLib::ID3v2::TextIdentificationFrame *frame = new TagLib::ID3v2::TextIdentificationFrame("TRCK");
        frame->setText(trackNumber.toStdString());
        f->ID3v2Tag()->addFrame(frame);
    }
    else
    {
        f->ID3v2Tag()->frameList("TRCK").front()->setText(trackNumber.toStdString());
    }
    this->trackNumber = trackNumber;
}

void MP3File::setYear(const unsigned int &year)
{
    TagLibMp3File *f = dynamic_cast<TagLibMp3File *>(tagLibFile);
    f->ID3v2Tag()->setYear(year);
    this->year = year;
}

void MP3File::extractData()
{
    TagLibMp3File *f = dynamic_cast<TagLibMp3File *>(tagLibFile);
    if (f->hasID3v2Tag())
    {
        TagLib::ID3v2::Tag *tag = f->ID3v2Tag();

        artist = QString(tag->artist().toCString());
        album = QString(tag->album().toCString());
        comments = QString(tag->comment().toCString());
        title = QString(tag->title().toCString());
        year = tag->year();

        TagLib::ID3v2::FrameList frames = tag->frameList("TPE2");   // album artist
        if (!frames.isEmpty())
            albumArtist = QString(tag->frameList("TPE2").front()->toString().toCString());

        frames = tag->frameList("TPOS");    // disc number
        if(!frames.isEmpty())
            discNumber = QString(tag->frameList("TPOS").front()->toString().toCString());

        frames = tag->frameList("USLT");    // lyrics
        if(!frames.isEmpty())
            lyrics = QString(tag->frameList("USLT").front()->toString().toCString());

        frames = tag->frameList("TRCK");    // track number
        if(!frames.isEmpty())
            trackNumber = QString(tag->frameList("TRCK").front()->toString().toCString());

        frames = tag->frameList("TCOM"); // composer
        if (!frames.isEmpty())
            composer = QString(tag->frameList("TCOM").front()->toString().toCString());
    }
}

bool MP3File::save()
{
    TagLibMp3File *f = dynamic_cast<TagLibMp3File *>(tagLibFile);
    return f->save();
}
