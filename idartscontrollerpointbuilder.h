#ifndef ICONTROLLERPOINTBUILDER_H
#define ICONTROLLERPOINTBUILDER_H

#include <qvector.h>

namespace DartsPointControllerContext {
    template<typename TModelInterface, typename TJsonFormat, typename  TUuid, typename TString>
    class IDartsControllerpointBuilder
    {
    public:
        typedef TModelInterface ModelsInterface;
        typedef TJsonFormat JsonFormat;
        typedef TString StringFormat;
        typedef TUuid IdFormat;
        virtual const ModelsInterface* buildControllerPointByJson(const JsonFormat& json) const = 0;
        virtual const ModelsInterface* buildControllerPointByInputValues(const int& point,
                                                                         const int& score,
                                                                         const int& modKeyCode) const = 0;
        virtual QVector<const ModelsInterface*> buildControllerPointsByJson(const JsonFormat& json) const = 0;
    };
}

#endif // ICONTROLLERPOINTBUILDER_H
