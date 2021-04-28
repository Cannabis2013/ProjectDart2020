#ifndef IPLAYERJSONASSEMBLERSERVICE_H
#define IPLAYERJSONASSEMBLERSERVICE_H

template <typename TJsonFormat, typename TModelInterfaces>
class IPlayerJsonAssemblerService
{
public:
    virtual TJsonFormat assembleJsonArrayFromModels(const TModelInterfaces&) = 0;

};

#endif // IPLAYERJSONASSEMBLERSERVICE_H
