#ifndef INPUTSIO_H
#define INPUTSIO_H

#include "src/DartsController/input/dartInput.h"
#include <qstring.h>

class InputsIO
{
public:
        InputsIO(const QString &filePath);

        bool toFile(const QList<DartInput> &_inputs);
        QList<DartInput> fromFile() const;
private:
        const QString _filePath;
};

#endif // INPUTSIO_H
