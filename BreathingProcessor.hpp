#ifndef BREATHING_PROCESS_HPP
#define BREATHING_PROCESS_HPP

#include <iostream>
#include <vector>
#include <complex>
#include "lib/eigen/Eigen/Eigen"
#include "ProcessedFrame.hpp"

class BreathingProcessor {
  public:
    // Public functions
    BreathingProcessor();
    bool  Process(std::vector<float>, ProcessedFrame&);
    // Setters and Getters
    void  SetSweepAlpha(float);
    float GetSweepAlpha();
    void  SetPhaseWeightsAlpha(float);
    float GetPhaseWeightsAlpha();
    void  SetPeakLocAlpha(float);
    float GetPeakLocAlpha();
    void  SetEnvAlpha(float);
    float GetEnvAlpha();
    void  SetMaxHistory(int);
    int   GetMaxHistory();
    

  private:
    // Private functions
    void  ComplexMatrixLPF(Eigen::VectorXcf&, float);
    void  FloatMatrixLPF(Eigen::VectorXf&, float);
    void  FloatLPF(float&, float);
    // Private variables
    bool              firstSweep;
    float             sweepAlpha;
    float             phaseWeightsAlpha;
    float             peakLocAlpha;
    float             envAlpha;
    int               maxHistory;
    Eigen::VectorXcf  lastLPSweep;
};

#endif
