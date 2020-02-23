#include "BreathingProcessor.hpp"

#define DEBUG
#define INIT_MAX_HISTORY

// Public functions
BreathingProcessor::BreathingProcessor() :
  firstSweep(false),
  sweepAlpha(0.7),
  phaseWeightsAlpha(0.9),
  peakLocAlpha(0.95),
  envAlpha(0.95),
  maxHistory(INIT_MAX_HISTORY),
  lastLPSweep(INIT_MAX_HISTORY)
{
  // intentionally blank
}

bool  BreathingProcessor::Process(std::vector<float> sweep, ProcessedFrame& outFrame){
  return true;
}

// Setters and Getters
void  BreathingProcessor::SetSweepAlpha(float a){
  
}

float BreathingProcessor::GetSweepAlpha(){
  return 0.0;
}

void  BreathingProcessor::SetPhaseWeightsAlpha(float a){
  
}

float BreathingProcessor::GetPhaseWeightsAlpha(){
  return 0.0;
}

void  BreathingProcessor::SetPeakLocAlpha(float a){
  
}

float BreathingProcessor::GetPeakLocAlpha(){
  return 0.0;
}

void  BreathingProcessor::SetEnvAlpha(float a){
  
}

float BreathingProcessor::GetEnvAlpha(){
  return 0.0;
}

// Private functions
void  BreathingProcessor::ComplexMatrixLPF(Eigen::VectorXcf& mat, float alpha){
  
}

void  BreathingProcessor::FloatMatrixLPF(Eigen::VectorXf& mat, float alpha){
  
}

void  BreathingProcessor::FloatLPF(float& num, float alpha){
  
}

#ifdef DEBUG
int main() {
  return 0;
}
#endif

