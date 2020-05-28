#ifndef PROJECTDARTINTERFACE_H
#define PROJECTDARTINTERFACE_H

#include "idatacontext.h"
#include "iplayercontext.h"
#include <QtCore>

/*
 * This is the interface you will pass to the visual QML layer
 * Make sure that methods are marked with the Q_INVOKABLE macro and return types which are accepted by the QML engine
 *
 */

class AbstractDartInterface : public QObject
{
public:


};

#endif // PROJECTDARTINTERFACE_H
