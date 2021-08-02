#ifndef IFONTMETRICCONTEXT_H
#define IFONTMETRICCONTEXT_H

template<typename TString>
class IFontMetricContext
{
public:
    virtual double stringWidth(const TString &string, const TString &family, const int &pointSize = -1) const = 0;
    virtual double stringHeight(const TString &string, const TString &family, const int &pointSize = -1) const = 0;
    virtual double scale() const = 0;
    virtual void setScale(const double &scale) = 0;
};
#endif // IFONTMETRICCONTEXT_H
