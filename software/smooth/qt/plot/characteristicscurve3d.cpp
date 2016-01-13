#include "plot/characteristicscurve3d.h"
#include "models/pvarray.h"

// ----------------------------------------------------------------------------
CharacteristicsCurve3D::CharacteristicsCurve3D(Qwt3D::SurfacePlot* pw,
                                               QSharedPointer<PVArray> pvarray) :
    Function(pw),
    PVModelFunctionBase(pvarray),
    m_IVFunction(new IVCharacteristicsCurve(pvarray))
{
}

// ----------------------------------------------------------------------------
double CharacteristicsCurve3D::operator()(double current, double exposure)
{
    double exposureTemp = m_PVArray->getExposure();
    m_PVArray->setExposure(exposure * 0.01); // convert percent to absolute
    double voltage = m_PVArray->calculateVoltage(current);
    m_PVArray->setExposure(exposureTemp);
    return voltage;
}

// ----------------------------------------------------------------------------
void CharacteristicsCurve3D::updateBoundingBox()
{
    m_IVFunction->updateBoundingBox();
    m_BoundingBox = m_IVFunction->getBoundingRect();
}
