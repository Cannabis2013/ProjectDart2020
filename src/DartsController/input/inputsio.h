#ifndef INPUTSIO_H
#define INPUTSIO_H

#include "src/DartsController/input/Input.h"
#include <qstring.h>

class InputsIO
{
public:
        InputsIO(const QString &filePath);

        bool toFile(const QList<Input> &_inputs);
        QList<Input> fromFile() const;
private:
        const QString _filePath;
};

#endif // INPUTSIO_H
