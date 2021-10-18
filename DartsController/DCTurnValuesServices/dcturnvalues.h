#ifndef DCTURNVALUES_H
#define DCTURNVALUES_H

#include <qstring.h>
#include <qjsondocument.h>
#include <qjsonobject.h>

struct DCTurnValues
{
   bool canUndo;
   bool canRedo;
   int roundIndex;
   int setIndex;
   int attemptIndex;
   QString targetRow;
   QString playerName;
};

#endif // DARTSPOINTTURNVALUES_H
