#ifndef IDATAMODELBUILDER_H
#define IDATAMODELBUILDER_H

template<class TModel, class TModelArguments, class TModelBuilderOptions>
class IDataModelBuilder
{
public:
    virtual TModel *buildModel(const TModelArguments &params,
                               const TModelBuilderOptions &options) = 0;
};

#endif // IDATAMODELBUILDER_H
