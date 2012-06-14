#ifndef ANNOTATOR_H
#define ANNOTATOR_H
#pragma once

#include <vector>

class SignalData;

class Annotator
{
public:
	virtual bool AnalyzeSignal(const SignalData &signal, std::vector<double> &samples, std::vector<int> &peak_type) = 0;

protected:
	Annotator();

};

#endif // ANNOTATOR_H