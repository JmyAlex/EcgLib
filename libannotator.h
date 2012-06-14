#ifndef LIBANNOTATOR_H
#define LIBANNOTATOR_H
#pragma once

#include "annotator.h"

class LibAnnotator : public Annotator
{
public:
	LibAnnotator();
	~LibAnnotator();

	virtual bool AnalyzeSignal(const SignalData &signal, std::vector<double> &samples, std::vector<int> &peak_type);

private:
	wchar_t* GetPath(); 
};

#endif // LIBANNOTATOR_H