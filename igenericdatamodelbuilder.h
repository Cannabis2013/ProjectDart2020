#ifndef IDATAMODELBUILDER_H
#define IDATAMODELBUILDER_H

template<class TModel, class TModelArguments, class TModelBuilderOptions>
class IGenericDataModelBuilder
{
public:
    virtual TModel *buildModel(const TModelArguments &args, const TModelBuilderOptions &options) = 0;
};

#endif // IDATAMODELBUILDER_H
