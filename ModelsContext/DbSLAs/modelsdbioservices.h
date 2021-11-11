#ifndef MODELSDBIOSERVICES_H
#define MODELSDBIOSERVICES_H

#include "FileOperationsContext/SLAs/ifilereader.h"
#include "FileOperationsContext/SLAs/ifilewriter.h"

class ModelsDbIOSLAs
{
public:
    typedef  IFileReader<QByteArray> FileReaderInterface;
    typedef IFileWriter<QByteArray> FileWriteInterface;
    IFileWriter<QByteArray> *saveJson() const
    {
        return _writeJsonToFile;
    }
    ModelsDbIOSLAs *setWriteJsonToFile(IFileWriter<QByteArray> *service)
    {
        _writeJsonToFile = service;
        return this;
    }
    IFileReader<QByteArray> *readJson() const
    {
        return _readJsonFromFile;
    }
    ModelsDbIOSLAs *setReadJsonFromFile(IFileReader<QByteArray> *service)
    {
        _readJsonFromFile = service;
        return this;
    }
private:
    FileWriteInterface *_writeJsonToFile;
    FileReaderInterface *_readJsonFromFile;
};

#endif // MODELSDBIOSERVICES_H
