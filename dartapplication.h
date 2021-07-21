#ifndef PROJECTDARTINTERFACE_H
#define PROJECTDARTINTERFACE_H

#include <AbstractApplicationInterface.h>
#include <dartapplicationservices.h>

#define printVariable(var) #var
#define STATUS_ERROR -1

class DartApplication :
        public AbstractApplicationInterface,
        public DartApplicationServices
{
    Q_OBJECT
public slots:
    void handleSendGameModesRequest() const override;
    //Handle request for tournament meta information
    void createDartsTournamentValues() override;
    //Set game controller methods
    void setDartsPointController(AbstractDartsController *controller) override;
    void setDartsScoreController(AbstractDartsController *controller) override;
private:
    // Clear controller..
    void clearGameController();
};
#endif // PROJECTDARTINTERFACE_H
