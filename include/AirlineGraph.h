#ifndef AIRLINEGRAPH_H
#define AIRLINEGRAPH_H
#include "Airport.h"
#include "Airline.h"
#include "jsonxx.h"
#include <fstream>
#include <iomanip>
#include <vector>
#include<algorithm>

using std::setw;
using namespace jsonxx;

//����ͼ
class AirlineGraph
{
    public:
        AirlineGraph();
        virtual ~AirlineGraph();
        int mAirportNumber;                         //��������
        Airport** mAirportHeadArray;                //�����
        vector<Airline*>* mAirlineVector;           //���溽��
        Airport* FindAirportByName(string name);    //���һ�������ȡָ��
        int GetAirlineNumber();                     //���غ�����Ŀ
        void InsertAirline(Airline* airline);       //�ⲿ����ӿ�
        void ShowAllAirlineToUser();                //Ԥ���Ѿ�������ȫ�����ߵ������Ϣ
        void ShowAirlineByAirport(int no);           //Ԥ��ĳ�������ĺ���
        void ShowAirlineByCity(string city);                       //Ԥ��ĳ�����еĺ���
        void ShowAirlineGraph();                                   //��ӡ���������
        void WriteAirlineJson();                                    //дjson���ļ�
        vector<int>* GetAirportIdByLocation(string loc);
        string GetAirportLocation(string airportName);
        Airport* FindAirlineByName1(string name);                  //ͨ������Ų���
        Airline* FindAirlineByDepartureAirport(string name);
        void Search(string city1,string city2);
        void SortByPrice(string name1,string name2);            //���۸�����
        vector<Airline*>* FindAirlineByName(string name);       //ͨ������Ų���
        void SortByTime(string name1,string name2);             //��ʱ������
        void SearchByTime(string time1,string time2,string name1,string name2);//��ʱ�����
        void SearchByPrice(int price1,int price2,string name1,string name2);//��Ʊ�۲���
        int timetransform(string time);                 //ʱ��ת������
        void Properline(string city1,string city2);     //�Ƽ�����·��
        Airport* FindAirportByCity(string city);
        bool timecomp(string time1,string time2);
    protected:

    private:
        Array GenerateAirlineJson();    //����json
        void LoadAirport(); //�ӱ��������������
        void LoadAirline(); //�ӱ������뺽������
        void InsertAirlineGraph(Airport* airport,Airline* airline); //��ͼ�в���ߣ����뺽�ߣ�
};

#endif // AIRLINEGRAPH_H
