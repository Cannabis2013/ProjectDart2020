#ifndef ICONTROLLERBUILDER_H
#define ICONTROLLERBUILDER_H

template<class TControllerInterface,class TParameter>
class IControllerBuilder
{
public:
    virtual TControllerInterface *buildGameController(const TParameter &mode,
                                                      const TParameter &type,
                                                      const TParameter &contextMode) = 0;
};

#endif // ICONTROLLERBUILDER_H
