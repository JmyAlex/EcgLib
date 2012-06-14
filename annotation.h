#ifndef ANNOTATION_H
#define ANNOTATION_H
#pragma once

#include <vector>
#include <iostream>
#include "annotator.h"
#include "signaldata.h"
#include "point.h"

//class Point;

/*
 * Добавить лог
 */ 

class Annotation
{
public:
	explicit Annotation(Annotator *annotator);
	~Annotation();

	void set_signal_data(const SignalData &signal_data);
	SignalData signal_data() const;
	
	std::vector<Point> annotation() const;
	void AnnotateSignal();

private:
	Annotator *_annotator;
	SignalData *_signal_data;
	std::vector<double> _samples;  //wtf ??
	std::vector<int> _peak_type;
	std::vector<Point> _points;

	enum PeakType 
	{
		q = 15,
		Q = 17,
		P = 24,
		T = 27,
		U = 29,
		NORMAL = 1,
		BEGIN = 39,
		END = 40,
		ECT = 46,
		pBegin = 42,
		pEnd = 43,
		tBegin = 44,
		tEnd = 45,
		r = 47,
		R = 48,
		s = 49,
		S = 50
	};

};

inline Annotation::Annotation(Annotator *annotator)
{
	_signal_data = new SignalData;
	if (annotator != NULL)
		_annotator = annotator;
	else 
		std::cerr << "Erorr: null pointer as argument!" << std::endl;
}

inline void Annotation::set_signal_data(const SignalData &signal_data)
{
	*_signal_data = signal_data;
}

inline std::vector<Point> Annotation::annotation() const
{
	return _points;
}

#endif // ANNOTATION_H