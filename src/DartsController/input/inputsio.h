#ifndef INPUTSIO_H
#define INPUTSIO_H

#include "src/DartsController/input/DartsInternalInput.h"
#include <qstring.h>

class InputsIO
{
public:
        InputsIO(const QString &filePath);

        bool toFile(const QList<DartsInternalInput> &_inputs);
        QList<DartsInternalInput> fromFile() const;
private:
        const QString _filePath;
};

#endif // INPUTSIO_H
