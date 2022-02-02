#ifndef REPORTSERVICES_H
#define REPORTSERVICES_H
#include "icreatereport.h"
class ReportServices
{
public:
    ICreateReport *createReport() const {return _createReport;}
    void setCreateReport(ICreateReport *newCreateReport) {_createReport = newCreateReport;}
private:
    ICreateReport *_createReport;
};
#endif // REPORTSERVICES_H
