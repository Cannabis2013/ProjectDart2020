#ifndef IURLPARSER_H
#define IURLPARSER_H

template<typename TUrl,
         typename TString,
         typename TParameters,
         typename TQueries>
class IParserService
{
public:
    // /{baseurl}/{method}/{url parameter}?{url query}
    virtual TUrl parseUrl(const TString &baseUrl,
                          const TString &method,
                          const TParameters& parameters,
                          const TQueries& queries)=0;
};

#endif // IURLPARSER_H
