#ifndef IDCCREATETURNVALUES_H
#define IDCCREATETURNVALUES_H
struct DCTurnValues;
class IDCCreateTurnValues
{
public:
    virtual DCTurnValues create() const = 0;
};
#endif // IBUILDTURNVALUES_H
