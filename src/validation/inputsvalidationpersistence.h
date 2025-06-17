#ifndef INPUTSVALIDATIONPERSISTENCE_H
#define INPUTSVALIDATIONPERSISTENCE_H

#include <QHash>
#include "src/FileIO/filejsonio.h"

class InputsValidationPersistence
{
public:
    InputsValidationPersistence(const QString& fileName);

    QHash<QString, bool> readAllowances();
    QString readModifier();
    void save(const QHash<QString,bool>& allowances, const QString& openModifier);

private:
    FileJsonIO *_ioDevice;
};

#endif // INPUTSVALIDATIONPERSISTENCE_H
