#ifndef SIGNALDATA_H
#define SIGNALDATA_H
#pragma once

#include <vector>
//#include <iostream>

class SignalData
{
public:
	SignalData();
	SignalData(const SignalData &other);
	SignalData(const std::vector<double> &data, const int sample_rate);
	~SignalData();

	void set_size(const int size);
	void set_sample_rate(const int sample_rate);
	void set_data(const std::vector<double> &data);

	int size() const;
	int sample_rate() const;
	std::vector<double> data() const;

	//friend istream &operator >> (istream &in, SignalData &ecg_signal);
	//friend ostream &operator << (ostream &out, const SignalData &ecg_signal);

private:
	//int _id;
	int _size;
	int _sample_rate;
	std::vector<double> _data;

};

inline SignalData::SignalData() : _size(0), _sample_rate(1000)
{

}

inline SignalData::SignalData(const SignalData &other)
{
	_data = other.data();
	_sample_rate = other.sample_rate();
	_size = other.size();
}

inline SignalData::SignalData(const std::vector<double> &data, const int sample_rate)
{
	_data = data;
	_sample_rate = sample_rate;
}

inline SignalData::~SignalData()
{
	_data.clear();
}

inline void SignalData::set_size(const int size)
{
	_size = size;
}

inline void SignalData::set_sample_rate(const int sample_rate)
{
	_sample_rate = sample_rate;
}

inline void SignalData::set_data(const std::vector<double> &data)
{
	_data = data;
}

inline int SignalData::size() const
{
	return _size;
}

inline int SignalData::sample_rate() const
{
	return _sample_rate;
}

inline std::vector<double> SignalData::data() const
{
	return _data;
}

#endif // SIGNALDATA_H
