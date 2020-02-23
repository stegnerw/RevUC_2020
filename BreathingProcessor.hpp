#ifndef BREATHING_PROCESS_HPP
#define BREATHING_PROCESS_HPP

#include <iostream>
#include <vector>
#include <complex>
#include "lib/eigen/Eigen/Eigen"
#include "ProcessedFrame.hpp"

class BreathingProcess {
  public:
    // Public functions
    BreathingProcess();
    bool  Process(std::vector<float>, ProcessedFrame&);
    // Setters and Getters
    void  SetSweepAlpha(float);
    float GetSweepAlpha();
    void  SetPhaseWeightsAlpha(float);
    float GetPhaseWeightsAlpha();
    void  SetPeakLocAlpha(float);
    float GetPeakLocAlpha();
    void  SetEnvAlpha();
    float GetEnvAlpha();

  private:
    // Private functions
    void  ComplexMatrixLPF(Eigen::VectorXcf&, float);
    void  FloatMatrixLPF(Eigen::VectorXf&, float);
    void  FloatLPF(float&, float);
    // Private variables
    bool              firstSweep;
    float             sweepAlpha;
    float             phaseWeightsAplha;
    float             peakLocAlpha;
    float             envAlpha;
    Eigen::VectorXcf  lastLPSweep;
};

#endif
