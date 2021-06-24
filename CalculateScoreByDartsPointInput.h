#ifndef CALCULATESCOREBYDARTSPOINTINPUT_H
#define CALCULATESCOREBYDARTSPOINTINPUT_H

#include "IPointCalculatorService.h"
#include "idartscontrollerpoint.h"
#include "quuid.h"

namespace DartsPointControllerContext {
    class CalculateScoreByDartsPointInput : public IPointCalculatorService<IDartsControllerPoint<QUuid,QString,QByteArray>>
    {
    public:
        enum KeyMappings{
            SingleModifer = 0x2A,
            DoubleModifier = 0x2B,
            TrippleModifier = 0x2C,
            BullModifier,
            BullsEyeModifier
        };
        static CalculateScoreByDartsPointInput* createInstance()
        {
            return new CalculateScoreByDartsPointInput();
        }
        virtual void addScoreValueToDartsPointModel(const ModelsInterface* model) const override
        {
            // Initialize pointmultiplier
            auto keyCode = model->modKeyCode();
            auto point = model->point();
            auto pointMultiplier = keyCode == KeyMappings::TrippleModifier ? 3 :
                                   keyCode == KeyMappings::DoubleModifier ? 2 :
                                   keyCode == KeyMappings::SingleModifer ? 1 : 0;
            // Calculate point
            auto score = point*pointMultiplier;
            auto mutableModel = const_cast<ModelsInterface*>(model);
            mutableModel->setScore(score);
        }
        void addScoreValuesToDartsPointModels(const QVector<const ModelsInterface *> &models) const override
        {
            QVector<const ModelsInterface*> list;
            for (const auto& model : models)
                addScoreValueToDartsPointModel(model);
        }
    };
}


#endif // POINTSCORECALCULATOR_H
