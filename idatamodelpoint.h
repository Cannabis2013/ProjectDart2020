#ifndef IDATAMODELPOINT_H
#define IDATAMODELPOINT_H

namespace DartsDataModelsContext
{
    class IDataModelPoint
    {
    public:
        virtual int point() const = 0;
        virtual int score() const = 0;
    };
}

#endif // IDATAMODELPOINT_H
