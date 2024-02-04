#ifndef IDARTINPUTS_H
#define IDARTINPUTS_H

#include "Input.h"

#include <QList>
#include <functional>

class QString;

class IDartsInputs {
public:
        virtual void init() = 0;
        virtual void initFromFile() = 0;
        virtual void setInputs(const QList<Input>& inputs) = 0;
        virtual Input save(Input input) = 0;
        virtual bool anyInputs(const QString& name, const int& throwIndex) const = 0;
        virtual QList<Input> inputs(const QString& name) const = 0;
        virtual QList<Input> inputs(const QString& name, const int& throwIndex) const = 0;
        virtual const QList<Input>& inputs() const = 0;
        virtual void remove(const std::function<bool(const Input&)>& predicate) = 0;
        virtual bool saveState() = 0;
};

#endif // IDARTINPUTS_H
