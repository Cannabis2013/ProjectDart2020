#ifndef IINDEXREPORT_H
#define IINDEXREPORT_H

class QByteArray;

class IIndexReport {
public:
        virtual QByteArray report() const = 0;
};

#endif // IINDEXREPORT_H
