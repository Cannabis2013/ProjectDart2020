#ifndef ICONTROLLERPOINTBUILDER_H
#define ICONTROLLERPOINTBUILDER_H


namespace DartsPointSingleAttemptContext {
    template<typename TModelInterface, typename TJsonFormat, typename  TUuid, typename TString>
    class IDartsControllerpointBuilder
    {
    public:
        typedef TModelInterface ModelsInterface;
        typedef TJsonFormat JsonFormat;
        typedef TString StringFormat;
        typedef TUuid IdFormat;
        virtual const ModelsInterface* buildControllerPointByJson(const JsonFormat& json) const = 0;
        virtual const ModelsInterface* buildControllerPointByValues(const int& point,
                                                                    const int& score,
                                                                    const int& modKeyCode,
                                                                    const IdFormat& playerId,
                                                                    const StringFormat& playerName) const = 0;
    };
}

#endif // ICONTROLLERPOINTBUILDER_H
