#ifndef DCADDINPUT_H
#define DCADDINPUT_H

#include <DartsController/Routines/idcaddinput.h>


struct DCIndex;

class DCAddInput : public IDCAddInput
{
public:
    QByteArray add(const QByteArray &inputByteArray,DCServices *services) override;
private:
    enum ControllerState {
        Initialized,
        Running,
        WinnerDeclared,
        AwaitsInput
    };
    DCInput toInputModel(const QByteArray &byteArray, DCServices *services);
    void evaluateInput(DCInput &input, DCServices *services);
    void updateModelsContext(DCInput &input, DCServices *services);
    void updateControllerContext(DCInput &input, DCServices *services);
    QByteArray inputToByteArray(const DCInput &input, DCServices *services);
    QByteArray indexToByteArray(const DCIndex &index, DCServices *services);
};
#endif // DCADDTOMODELCONTEXT_H
