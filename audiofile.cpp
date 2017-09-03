#include "audiofile.h"

#include <taglib/mpeg/mpegfile.h>
#include <taglib/mpeg/id3v2/id3v2tag.h>
#include <taglib/mpeg/id3v2/id3v2frame.h>

AudioFile::AudioFile(QString absPath) : QFileInfo(absPath)
{
}

AudioFile::AudioFile(QFileInfo file) : QFileInfo(file)
{
}

AudioFile::~AudioFile()
{
    delete tagLibFile;
}
