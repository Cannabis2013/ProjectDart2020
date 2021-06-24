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
        virtual const ModelsInterface* createPointModel(const JsonFormat& json) const = 0;
        virtual const ModelsInterface* createPointModel(const int& point,
                                                        const int& score,
                                                        const int& modKeyCode) const = 0;
        virtual const ModelsInterface* createPointModelWithTotalScoreByModel(const ModelsInterface* model,const int &totalScore) const = 0;
        virtual QVector<const ModelsInterface*> createPointsByJson(const JsonFormat& json) const = 0;
    };
}

#endif // ICONTROLLERPOINTBUILDER_H
