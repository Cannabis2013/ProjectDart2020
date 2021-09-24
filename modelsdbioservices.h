#ifndef MODELSDBIOSERVICES_H
#define MODELSDBIOSERVICES_H

#include <ifilereader.h>
#include <ifilewriter.h>


class ModelsDbIOSLAs
{
public:
    IFileWriter<QByteArray> *writeJsonToFile() const
    {
        return _writeJsonToFile;
    }
    void setWriteJsonToFile(IFileWriter<QByteArray> *newWriteJsonToFile)
    {
        _writeJsonToFile = newWriteJsonToFile;
    }
    IFileReader<QByteArray> *readJsonFromFile() const
    {
        return _readJsonFromFile;
    }
    void setReadJsonFromFile(IFileReader<QByteArray> *newReadJsonFromFile)
    {
        _readJsonFromFile = newReadJsonFromFile;
    }
private:
    IFileWriter<QByteArray> *_writeJsonToFile;
    IFileReader<QByteArray> *_readJsonFromFile;
};

#endif // MODELSDBIOSERVICES_H
