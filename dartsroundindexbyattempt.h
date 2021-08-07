#ifndef DARTSROUNDINDEXBYATTEMPT_H
#define DARTSROUNDINDEXBYATTEMPT_H

#include <qobject.h>

class DartsRoundIndexByAttempt :public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(int numberOfAttempts READ numberOfAttempts WRITE setNumberOfAttempts NOTIFY numberOfAttemptsChanged);
    Q_PROPERTY(int InitialRound READ initialRound WRITE setInitialRound NOTIFY initialRoundChanged);
    Q_INVOKABLE int roundByAttempt(const int &index) const;
signals:
    void dataChanged();
    void numberOfAttemptsChanged();
    void initialRoundChanged();
private:
    int numberOfAttempts() const;
    void setNumberOfAttempts(int newNumberOfAttempts);
    int initialRound() const;
    void setInitialRound(int newInitialRound);
    int _numberOfAttempts;
    int _initialRound = 0;
};

#endif // DARTSMULTIPLEROUNDSLABELS_H
