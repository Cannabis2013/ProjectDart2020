#ifndef IBUILDSINGLEATTEMPTPOINTCONTROLLER_H
#define IBUILDSINGLEATTEMPTPOINTCONTROLLER_H


template<typename TControllerInterface, typename TControllerDetails>
class IBuildControllerService
{
public:
    typedef TControllerInterface ControllerInterface;
    typedef TControllerDetails ControllerDetails;

    virtual ControllerInterface buildSingleAttemptPointController(ControllerDetails details) const = 0;

};

#endif // IBUILDSINGLEATTEMPTPOINTCONTROLLER_H
