#ifndef AIRLINEGRAPH_H
#define AIRLINEGRAPH_H
#include "Airport.h"
#include "Airline.h"
#include "jsonxx.h"
#include <fstream>
#include <iomanip>
#include <vector>

using std::setw;
using namespace jsonxx;

//����ͼ
class AirlineGraph
{
    public:
        AirlineGraph();
        virtual ~AirlineGraph();
        int mAirportNumber; //��������
        Airport** mAirportHeadArray;    //�����
        vector<Airline*>* mAirlineVector;   //���溽��
        Airport* FindAirportByName(string name);    //���һ�������ȡָ��
        int GetAirlineNumber(); //���غ�����Ŀ
        void InsertAirline(Airline* airline);   //�ⲿ����ӿ�
        void ShowAirlineGraph();    //��ӡ���������
        void WriteAirlineJson();    //дjson���ļ�
        string GetAirportLocation(string airportName);
		
		
        void FindByAirlineName(string name);//ͨ������Ų���
        void SortByPrize(string name1,string name2);//��ʱ������
        void SortByTime(string name1,string name2);//��ʱ������
    protected:

    private:
        Array GenerateAirlineJson();    //����json
        void LoadAirport(); //�ӱ��������������
        void LoadAirline(); //�ӱ������뺽������
        void InsertAirlineGraph(Airport* airport,Airline* airline); //��ͼ�в���ߣ����뺽�ߣ�
};

#endif // AIRLINEGRAPH_H
