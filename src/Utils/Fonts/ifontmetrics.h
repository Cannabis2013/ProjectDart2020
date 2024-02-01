#ifndef IFONTMETRICS_H
#define IFONTMETRICS_H

class QString;

class IFontMetrics {
public:
        virtual double width(const QString& str, const int& size = 16, const int& weigh = 400) const = 0;
        virtual double height(const QString& str, const int& size = 16, const int& weigh = 400) const = 0;
};

#endif // IFONTMETRICS_H
