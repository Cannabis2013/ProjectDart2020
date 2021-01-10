#ifndef ICONTROLLERBUILDER_H
#define ICONTROLLERBUILDER_H

template<class TControllerInterface,
         class TParameter,
         class TUserIds,
         class TUserNames,
         class TScores>
class IControllerBuilder
{
public:
    virtual TControllerInterface *assembleFTPGameController(const TParameter &parameters,
                                                            const TUserIds& userIds,
                                                            const TUserNames& userNames,
                                                            const TScores& scores,
                                                            const int &contextMode) = 0;
};

#endif // ICONTROLLERBUILDER_H
