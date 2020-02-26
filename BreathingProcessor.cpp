#include "BreathingProcessor.hpp"
#include <algorithm>
#include <cmath>

#define DEBUG
#define MAX_HISTORY 500

// Public functions
BreathingProcessor::BreathingProcessor(int sweepLength) :
  firstSweep(true),
  secondSweep(true),
  sweepAlpha(0.7),
  phaseWeightsAlpha(0.9),
  peakLocAlpha(0.95),
  envAlpha(0.95),
  maxHistory(MAX_HISTORY),
  breathHistory(MAX_HISTORY),
  lastSweep(sweepLength),
  lastEnv(sweepLength),
  lastPeakLoc(sweepLength),
  lastPhaseWeights(sweepLength)
{
  // intentionally blank
}

bool  BreathingProcessor::Process(std::vector<std::complex<float>> sweep, ProcessedFrame& outFrame){
  if (firstSweep) {
    lastSweep   = sweep;
    ComplexVectorAbs(lastSweep, lastEnv);
    lastPeakLoc = (float)std::distance(lastEnv.begin(), std::max_element(lastEnv.begin(), lastEnv.end()));
    firstSweep = false;
    return false;
  }

  sweep = ComplexVecLPF(sweep, lastSweep, sweepAlpha);
  std::vector<float> env;
  ComplexVectorAbs(sweep, env);
  lastEnv = FloatVecLPF(env, lastEnv, envAlpha);
  float peakLoc = (float)std::distance(lastEnv.begin(), std::max_element(lastEnv.begin(), lastEnv.end()));
  lastPeakLoc = peakLocAlpha * lastPeakLoc + (1 - peakLocAlpha) * peakLoc;
  int peakLocInt = (int)(lastPeakLoc + 0.5);
  int peakMin = std::max(0, peakLocInt-50);
  int peakMax = std::min(peakLocInt+50, sweep.size()-1);
  
  std::complex<float> peak = std::accumulate(sweep.begin()+peakMin, sweep.begin()+peakMax, 0.0) / sweep.size();

  std::vector<std::complex<float>> delta();
  for (std::size_t i = 0; i < sweep.size(); i++) {
    delta[i] = sweep[i] * lastSweep[i];
  }

  std::vector<float> phaseWeights;
  for (std::size_t i = 0; i < delta.size(); i++)
    phaseWeights[i] = delta[i].imag();
  if (secondSweep) {
    lastPhaseWeights = phaseWeights;
    secondSweep = false;
  } else {
    lastPhaseWeights = FloatVecLPF(phaseWeights, lastPhaseWeights, phaseWeightsAlpha);
  }


  return true;
}

void BreathingProcessor::ComplexVectorAbs(std::vector<std::complex<float>> orig, std::vector<float>& abs){
  for (std::size_t i = 0; i < orig.size(); i++) {
    abs[i] = sqrt(orig[i].real()*orig[i].real() + orig[i].imag()*orig[i].imag()) ;
  }
}

std::vector<std::complex<float>> ComplexVecLPF(std::vector<std::complex<float>> old_v, std::vector<std::complex<float>> new_v, float alpha) {
  std::vector<std::complex<float>> filtered;
  for (std::size_t i = 0; i < new_v.size(); i++) {
    filtered[i] = alpha * old_v[i] + (1-alpha) * new_v[i];
  }
  return filtered;
}

std::vector<float> FloatVecLPF(std::vector<float> old_v, std::vector<float> new_v, float alpha) {
  std::vector<float> filtered;
  for (std::size_t i = 0; i < new_v.size(); i++) {
    filtered[i] = alpha * old_v[i] + (1-alpha) * new_v[i];
  }
  return filtered;
}

#ifdef DEBUG
int main() {
  int sweep_len = 5;
  std::vector<std::complex<float>> sweep = 
    {std::complex<float>(10,0),
     std::complex<float>(11,1),
     std::complex<float>(12,2),
     std::complex<float>(13,3),
     std::complex<float>(14,4)};
  ProcessedFrame frame;
  BreathingProcessor bp(sweep_len);
  bp.Process(sweep, frame);
  std::vector<std::complex<float>> sweep2 =
    {std::complex<float>(10,10),
     std::complex<float>(11,11),
     std::complex<float>(12,12),
     std::complex<float>(13,13),
     std::complex<float>(14,14)};
  ProcessedFrame frame2;
  bp.Process(sweep2, frame2);
  return 0;
}
#endif

