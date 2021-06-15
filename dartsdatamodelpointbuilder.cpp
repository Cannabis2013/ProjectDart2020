#include "dartsdatamodelpointbuilder.h"

const DartsDataModelsContext::DartsDataModelPoint *DartsDataModelsContext::dartsdatamodelpointbuilder::buildModelByValues(const int &point, const int &score)
{
    auto pointModel = new DartsDataModelPoint;
    pointModel->setPoint(point);
    pointModel->setScore(score);
    return pointModel;
}

const DartsDataModelsContext::DartsDataModelPoint *DartsDataModelsContext::dartsdatamodelpointbuilder::buildDefaultPointModel(const int &defaultValue)
{
    auto pointModel = new DartsDataModelPoint;
    pointModel->setPoint(defaultValue);
    pointModel->setScore(defaultValue);
    return pointModel;
}
