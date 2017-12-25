#ifndef SYSTEM_H
#define SYSTEM_H
#include "AirlineGraph.h"

class System
{
    public:
        System();
        virtual ~System();
        AirlineGraph* mAirlineGraph;
        void InsertAirlineInfo();   //���뺽����Ϣ
        void ShowAllAirlineToUser();    //Ԥ���Ѿ�������ȫ�����ߵ������Ϣ
        void ShowAirlineByAirport(int no);  //Ԥ��ĳ�������ĺ���
        void ShowAirlineByCity(string city);    //Ԥ��ĳ�����еĺ���
    protected:

    private:
};

#endif // SYSTEM_H
