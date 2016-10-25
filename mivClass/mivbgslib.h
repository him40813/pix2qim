#ifndef MIVBGSLIB
#define MIVBGSLIB

//CV LIB
#include <opencv/opencv.hpp>

// External LIB
    #include "package_bgs/IBGS.h"
    #include "package_bgs/FrameDifferenceBGS.h"
#include "package_bgs/StaticFrameDifferenceBGS.h"
#include "package_bgs/WeightedMovingMeanBGS.h"
#include "package_bgs/WeightedMovingVarianceBGS.h"
#include "package_bgs/MixtureOfGaussianV2BGS.h"
#include "package_bgs/AdaptiveBackgroundLearning.h"
#include "package_bgs/AdaptiveSelectiveBackgroundLearning.h"
#include "package_bgs/KNNBGS.h"

#if CV_MAJOR_VERSION >= 2 && CV_MINOR_VERSION >= 4 && CV_SUBMINOR_VERSION >= 3
#include "package_bgs/GMG.h"		// Unavailable in opencv3.0+
#endif

#include "package_bgs/dp/DPAdaptiveMedianBGS.h"
    #include "package_bgs/dp/DPGrimsonGMMBGS.h"     //Multiple gaussians based methods:
#include "package_bgs/dp/DPZivkovicAGMMBGS.h"
    #include "package_bgs/dp/DPMeanBGS.h"           //Temporal Median
#include "package_bgs/dp/DPWrenGABGS.h"
#include "package_bgs/dp/DPPratiMediodBGS.h"
#include "package_bgs/dp/DPEigenbackgroundBGS.h"
    #include "package_bgs/dp/DPTextureBGS.h"        // LBP

    #include "package_bgs/tb/T2FGMM_UM.h"           // Type-2 Fuzzy based methods:
#include "package_bgs/tb/T2FGMM_UV.h"
#include "package_bgs/tb/T2FMRF_UM.h"
#include "package_bgs/tb/T2FMRF_UV.h"
#include "package_bgs/tb/FuzzySugenoIntegral.h"
#include "package_bgs/tb/FuzzyChoquetIntegral.h"

    #include "package_bgs/lb/LBSimpleGaussian.h"    //Single gaussian based methods
#include "package_bgs/lb/LBFuzzyGaussian.h"
#include "package_bgs/lb/LBMixtureOfGaussians.h"
#include "package_bgs/lb/LBAdaptiveSOM.h"
#include "package_bgs/lb/LBFuzzyAdaptiveSOM.h"

#include "package_bgs/ck/LbpMrf.h"
#include "package_bgs/av/VuMeter.h"
    #include "package_bgs/ae/KDE.h"
    #include "package_bgs/db/IndependentMultimodalBGS.h" //IMBS
    #include "package_bgs/sjn/SJN_MultiCueBGS.h"
#include "package_bgs/bl/SigmaDeltaBGS.h"

    #include "package_bgs/pl/SuBSENSE.h"
    #include "package_bgs/pl/LOBSTER.h"

    #include "package_bgs/PBAS.h"


#include "mivuttil.h"

void static methodSelector()
{
    //// Respect Methods
    qRegisterMetaType<FrameDifferenceBGS>("FrameDifferenceBGS");
    qRegisterMetaType<DPGrimsonGMMBGS>("DPGrimsonGMMBGS");
    qRegisterMetaType<DPMeanBGS>("DPMeanBGS");
    qRegisterMetaType<DPTextureBGS>("DPTextureBGS");
    qRegisterMetaType<T2FGMM_UM>("T2FGMM_UM");
    qRegisterMetaType<LBSimpleGaussian>("LBSimpleGaussian");
    qRegisterMetaType<KDE>("KDE");
    qRegisterMetaType<IndependentMultimodalBGS>("IndependentMultimodalBGS");
    qRegisterMetaType<SJN_MultiCueBGS>("SJN_MultiCueBGS");
    qRegisterMetaType<SuBSENSEBGS>("SuBSENSEBGS");
    qRegisterMetaType<LOBSTERBGS>("LOBSTERBGS");
    qRegisterMetaType<PBAS>("PBAS");

    //// Another Methods
    qRegisterMetaType< StaticFrameDifferenceBGS >(" StaticFrameDifferenceBGS ");
    qRegisterMetaType< WeightedMovingMeanBGS >(" WeightedMovingMeanBGS ");
    qRegisterMetaType< WeightedMovingVarianceBGS >(" WeightedMovingVarianceBGS ");
    qRegisterMetaType< MixtureOfGaussianV2BGS >(" MixtureOfGaussianV2BGS ");
    qRegisterMetaType< AdaptiveBackgroundLearning >(" AdaptiveBackgroundLearning ");
    qRegisterMetaType< AdaptiveSelectiveBackgroundLearning >(" AdaptiveSelectiveBackgroundLearning ");
    qRegisterMetaType< KNNBGS >(" KNNBGS ");
    //qRegisterMetaType< GMG >(" GMG ");
    qRegisterMetaType< DPAdaptiveMedianBGS >(" DPAdaptiveMedianBGS ");
    qRegisterMetaType< DPZivkovicAGMMBGS >(" DPZivkovicAGMMBGS ");
    qRegisterMetaType< DPWrenGABGS >(" DPWrenGABGS ");
    qRegisterMetaType< DPPratiMediodBGS >(" DPPratiMediodBGS ");
    qRegisterMetaType< DPEigenbackgroundBGS >(" DPEigenbackgroundBGS ");
    qRegisterMetaType< T2FGMM_UV >(" T2FGMM_UV ");
    qRegisterMetaType< T2FMRF_UM >(" T2FMRF_UM ");
    qRegisterMetaType< T2FMRF_UV >(" T2FMRF_UV ");
    qRegisterMetaType< FuzzySugenoIntegral >(" FuzzySugenoIntegral ");
    qRegisterMetaType< FuzzyChoquetIntegral >(" FuzzyChoquetIntegral ");
    qRegisterMetaType< LBFuzzyGaussian >(" LBFuzzyGaussian ");
    qRegisterMetaType< LBMixtureOfGaussians >(" LBMixtureOfGaussians ");
    qRegisterMetaType< LBAdaptiveSOM >(" LBAdaptiveSOM ");
    qRegisterMetaType< LBFuzzyAdaptiveSOM >(" LBFuzzyAdaptiveSOM ");
    qRegisterMetaType< LbpMrf >(" LbpMrf ");
    qRegisterMetaType< VuMeter >(" VuMeter ");
    qRegisterMetaType< SigmaDeltaBGS >(" SigmaDeltaBGS ");

    std::clog<<"-. Alogorithms Class are Registered Complete."<<endl;

}


#endif // MIVBGSLIB

