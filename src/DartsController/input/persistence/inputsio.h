#ifndef INPUTSIO_H
#define INPUTSIO_H

#include <qstring.h>

class Input;

class InputsIO
{
public:
        bool toFile(const QList<Input> &_inputs);
        QList<Input> fromFile() const;
private:
        const QString _filePath = "dartsInputs.dat";
};

#endif // INPUTSIO_H
