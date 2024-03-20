#ifndef IINPUTSTATISTICS_H
#define IINPUTSTATISTICS_H

class QString;

class IInputStatistics {
public:
        virtual double middle(const QString& name) const = 0;
        virtual int lowest(const QString& name) const = 0;
        virtual int highest(const QString& name) const = 0;
};

#endif // IINPUTSTATISTICS_H
