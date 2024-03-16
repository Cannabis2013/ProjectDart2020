#ifndef ISCORESREPORT_H
#define ISCORESREPORT_H

class QString;
class QByteArray;

class IScoresReport {
public:
        virtual QString initialScore() const = 0;
        virtual int playerOne() const = 0;
        virtual int playerTwo() const = 0;
        virtual QString finishRow() const = 0;
        virtual QString delta() const = 0;
};

#endif // ISCORESREPORT_H
