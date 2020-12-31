#ifndef ICONTROLLERBUILDER_H
#define ICONTROLLERBUILDER_H

template<class TControllerInterface,class TParameters>
class IControllerBuilder
{
public:
    virtual TControllerInterface *buildController(const TParameters &mode, 
                                                  const TParameters &contextMode) = 0;
};

#endif // ICONTROLLERBUILDER_H
