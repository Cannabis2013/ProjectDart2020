#ifndef IDARTSINPUTBUILDER_H
#define IDARTSINPUTBUILDER_H
class IDartsInput;
class QUuid;
class IDartsInputBuilder
{
public:
    virtual IDartsInput *create() const = 0;
};
#endif // IDARTSINPUTBUILDER_H
