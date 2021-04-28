#ifndef IPLAYEREXTRACTJSONSERVICE_H
#define IPLAYEREXTRACTJSONSERVICE_H

template<typename TJsonFormat, typename TModelInterface>
class IPlayerJsonExtractorService
{
public:
     virtual TModelInterface extractPlayerModelsFromJsonArray(const TJsonFormat&) = 0;
};

#endif // IPLAYEREXTRACTJSONSERVICE_H
