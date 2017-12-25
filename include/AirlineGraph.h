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
        void ShowAllAirlineToUser();    //Ԥ���Ѿ�������ȫ�����ߵ������Ϣ
        void ShowAirlineByAirport(int no);  //Ԥ��ĳ�������ĺ���
        void ShowAirlineByCity(string city);    //Ԥ��ĳ�����еĺ���
        void ShowAirlineGraph();    //��ӡ���������
        void WriteAirlineJson();    //дjson���ļ�
        vector<int>* GetAirportIdByLocation(string loc);
        string GetAirportLocation(string airportName);
        vector<Airline*>* FindAirlineByName(string name);//ͨ������Ų���
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
