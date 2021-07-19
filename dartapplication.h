#ifndef PROJECTDARTINTERFACE_H
#define PROJECTDARTINTERFACE_H

#include <AbstractApplicationInterface.h>
#include "dartapplicationservices.h"

#define printVariable(var) #var
#define STATUS_ERROR -1

class DartApplication :
        public AbstractApplicationInterface,
        protected DartApplicationServices
{
    Q_OBJECT
public slots:
    void handleSendGameModesRequest() const override;
    //Handle request for tournament meta information
    void createDartsTournamentValues() override;
    //Set game controller methods
    void setDartsPointController(AbstractDartsController *controller) override;
    void setDartsScoreController(AbstractDartsController *controller) override;
protected:
    AbstractModelsService* _modelsService;
private:
    // Clear controller..
    void clearGameController();
    // Builders related..
    AbstractGameController *gameController() const;
    // Controller services
    AbstractGameController *_gameController = nullptr;
};
#endif // PROJECTDARTINTERFACE_H
