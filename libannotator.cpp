#include "libannotator.h"
#include "signaldata.h"

#include "lib\lib.h"

#include <windows.h>
#include <string>
#include <iostream>
#include "Shlwapi.h"

LibAnnotator::LibAnnotator()
{
}

LibAnnotator::~LibAnnotator()
{
}

bool LibAnnotator::AnalyzeSignal(const SignalData &signal, std::vector<double> &samples, std::vector<int> &peak_type)
{
	EcgAnnotation ann;
	int** qrsAnn;
    int** ANN;
	int annNum = 0;

	std::vector<double> vector_data = signal.data();
	int size = signal.size();
	double *data = new double[size];
	for (int i = 0; i < size; i++)
		data[i] = vector_data[i];
	int sample_rate = signal.sample_rate();
	//std::cout << sample_rate << '\t' << size << std::endl;
	wchar_t *path = GetPath();
	//for (int i = 0; i < 10; i++)
	//	std::cout << path[i] << '\t'; 

	qrsAnn = ann.GetQRS(data, size, sample_rate, L"filters");
	if (qrsAnn)
    {
        ann.GetEctopics(qrsAnn, ann.GetQrsNumber(), sample_rate);
        ANN = ann.GetPTU(data, size, sample_rate, L"filters", qrsAnn, ann.GetQrsNumber());
        if (ANN)
        {
            annNum = ann.GetEcgAnnotationSize();
		}
        else
        {
            ANN = qrsAnn;
            annNum = 2 * ann.GetQrsNumber();
		}
		for (int i = 0; i < annNum; i++)
        {
			samples.push_back(ANN[i][0]);
			peak_type.push_back(ANN[i][1]);
		}
		delete [] data;
		return true;
	}
	else
	{
		std::cerr << "Error: could not get QRS complexes. make sure you have got \"filters\" directory in the ecg application dir." << std::endl;
		return false;
	}
}

wchar_t* LibAnnotator::GetPath()     //Получить путь директории с исполняемым файлом. Нужно для папки с фильтрами
{
	wstring path, filterDir;
	filterDir = L"\\filters";
	TCHAR pBuf [MAX_PATH]; 
	GetModuleFileName(NULL, pBuf, MAX_PATH);
	PathRemoveFileSpec(pBuf);
	wstring sBuf(pBuf);
	path = sBuf + filterDir;
	wchar_t* cPath = const_cast<wchar_t*>(path.c_str());
	return cPath;
}