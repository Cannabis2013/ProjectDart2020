#ifndef ISCORESCONTROLLER_H
#define ISCORESCONTROLLER_H

class QString;
class IScoresController {
public:
        virtual int playerOne() const = 0;
        virtual int playerTwo() const = 0;
        virtual QString finishRow() const = 0;
        virtual int delta() const = 0;
};

#endif // ISCORESCONTROLLER_H
