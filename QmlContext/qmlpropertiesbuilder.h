#ifndef QMLPROPERTIESBUILDER_H
#define QMLPROPERTIESBUILDER_H

#include <qqmlcontext.h>

template<typename T> class QVector;

class QmlPropertiesBuilder
{
public:
    typedef QQmlContext::PropertyPair Property;
    typedef QVector<Property> Properties;
    QmlPropertiesBuilder();
    Properties contextProperties() const;
private:
    class Imp;
    Imp *d;
};
#endif // QMLAPPLICATIONPROPERTIES_H
