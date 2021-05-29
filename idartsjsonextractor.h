#ifndef IDARTSJSONEXTRACTOR_H
#define IDARTSJSONEXTRACTOR_H

template<typename TJsonFormat, typename TString>
class IDartsJsonExtractor
{
public:
    typedef TString StringFormat;
    typedef TJsonFormat JsonFormat;
    virtual StringFormat getWinnerNameByJson(const JsonFormat& json) const = 0;
    virtual int getPlayerScoreByJson(const JsonFormat& json) const = 0;
};
#endif // IDARTSJSONEXTRACTOR_H
