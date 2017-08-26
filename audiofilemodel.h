#ifndef AUDIOFILEMODEL_H
#define AUDIOFILEMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include <QFileInfo>
#include <QStringList>
#include <QVariant>

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

    void addFile(QFileInfo);
    void addFile(const QString&);
    void addFiles(const QStringList&);
    void addFiles(const QVector<QFileInfo>&);
    void addFilesFromDirectory(const QString&);

    enum ColumnName
    {
        FILENAME = 0,
        FILEPATH = 1,
        FILESIZE = 2,
        LASTMODIFIED = 3
    };
private:
    QVector<QFileInfo> audioFiles;
    const int cols;
    QStringList fileFilters;
};

#endif // AUDIOFILEMODEL_H