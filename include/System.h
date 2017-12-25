#ifndef SYSTEM_H
#define SYSTEM_H
#include "AirlineGraph.h"
#include <fstream>

class System
{
    public:
        System();
        virtual ~System();
        AirlineGraph* mAirlineGraph;
        Array mBookArray;
        void InsertAirlineInfo();   //���뺽����Ϣ
        void ShowAllAirlineToUser();    //Ԥ���Ѿ�������ȫ�����ߵ������Ϣ
        void ShowAirlineByAirport(int no);  //Ԥ��ĳ�������ĺ���
        void ShowAirlineByCity(string city);    //Ԥ��ĳ�����еĺ���
        void SearchAirline(string name);    //ͨ������Ų鿴��ϸ��Ϣ
        void Book();    //��Ʊ
    protected:

    private:
};

#endif // SYSTEM_H
