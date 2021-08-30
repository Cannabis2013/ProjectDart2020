#ifndef CALCULATESCOREBYDARTSPOINTINPUT_H
#define CALCULATESCOREBYDARTSPOINTINPUT_H

#include "IPointCalculatorService.h"
#include "idpcmodel.h"
#include "quuid.h"

namespace DPCContext {
    class CalculateScoreByDartsPointInput : public IPointCalculatorService<IDPCModel>
    {
    public:
        enum PointKeyCodes{
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
        virtual int calculateScore(const ModelsInterface* model) const override
        {
            auto pointMultiplier = createPointMultiplier(model->modKeyCode());
            return calculateScore(model->point(),pointMultiplier);
        }
        void addScoreValuesToDartsPointModels(const QVector<ModelsInterface *> &models) const override
        {
            QVector<const ModelsInterface*> list;
            for (const auto& model : models)
                calculateScore(model);
        }
    private:
        int createPointMultiplier(const int &code) const
        {
            auto pointMultiplier = code == PointKeyCodes::TrippleModifier ? 3 :
                                   code == PointKeyCodes::DoubleModifier ? 2 :
                                   code == PointKeyCodes::SingleModifer ? 1 : 0;
            return pointMultiplier;
        }
        int calculateScore(const int &point, const int &multiplier) const
        {
            return point*multiplier;
        }
    };
}


#endif // POINTSCORECALCULATOR_H
