#ifndef IURLPARSER_H
#define IURLPARSER_H

template<class TUrl, class TString>
class IParserService
{
public:
    virtual ~IParserService() = default;
    // /{baseurl}/{method}/{url parameter}?{url query}
    virtual TUrl parseUrl(const TString &arg1,
                          const TString &arg2,
                          const TString &arg3,
                          const TString &arg4)=0;
};

#endif // IURLPARSER_H
