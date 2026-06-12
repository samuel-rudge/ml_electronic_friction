// source/utils/typing.h

# pragma once

#include <string>

namespace ml_ef::utils{

    enum PotentialType {
        harmonic,
        anharmonic 
    };

    enum UnitsType {
        dimensionless,
        atomic 
    };

    enum InitCondType{
        fixed,
        wigner
    };

    enum DataType{
        cl,
        qu
    };
    
}

