#include "kernel_element.hpp"


kernelElement::kernelElement()
{
  numberOfParameters=3;
}

int kernelElement::returnNumberOfParameters()
{
  return numberOfParameters;
}

void kernelElement::initialize(arma::vec & parameters,
                               double initialValue,
                               int ninput,
                               arma::vec ranks)
{
  parameters(0)=initialValue;
  for (int ii=1;ii<parameters.size();ii++)
  {
    switch(ii%numberOfParameters)
    {
      case 0:
        parameters(ii)=1.;
        break;
      case 1:
        parameters(ii)=0.;
        break;
      case 2:
        parameters(ii)=1.;
        break;
    }
  }
}

double kernelElement::evalElement(arma::vec param,double input)
{
  return param(0)*std::exp(-(input-param(1))/param(2));
}

double kernelElement::evaldElement(arma::vec param,double input)
{
  return -2*param(0)*(input/param(2))*std::exp(-(input-param(1))/param(2));;
}

void kernelElement::getParametersForGrad(arma::vec & parameters,
                                         int currentParam,
                                         int startIndex,
                                         int lastIndex,
                                         double input)
{

  arma::vec parametersSave=parameters;

  for (int ii=startIndex;ii<=lastIndex;ii++)
    parameters(ii)=0.;

  switch(currentParam%numberOfParameters)
  {
    case 0:
      parameters(currentParam)=1.;
      parameters(currentParam+1)=parametersSave(currentParam+1);
      parameters(currentParam+2)=parametersSave(currentParam+2);
      break;
    case 1:
      parameters(currentParam-1)=2*parametersSave(currentParam-1)*(input-parametersSave(currentParam))/parametersSave(currentParam+1);
      parameters(currentParam)=parametersSave(currentParam);
      parameters(currentParam+1)=parametersSave(currentParam+1);
      break;
    case 2:
      parameters(currentParam-2)=parametersSave(currentParam-2)*std::pow(input-parametersSave(currentParam-1)/parametersSave(currentParam),2);
      parameters(currentParam-1)=parametersSave(currentParam-1);
      parameters(currentParam)=parametersSave(currentParam);
      break;
  }
}

double kernelElement::evalGradwrtParamElement(arma::vec param,double input)
{
  return param(0)*std::exp(-(input-param(1))/param(2));;
}
