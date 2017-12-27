#ifndef SYSTEM_H
#define SYSTEM_H
#include "AirlineGraph.h"
#include "BookOrder.h"
#include "TimeUtil.h"
#include <fstream>

class System
{
    public:
        System();
        virtual ~System();
        AirlineGraph* mAirlineGraph;
        vector<BookOrder*>* mBookOrderVector;
        void InsertAirlineInfo();   //���뺽����Ϣ
        void ShowAllAirlineToUser();    //Ԥ���Ѿ�������ȫ�����ߵ������Ϣ
        void ShowAirlineByAirport(int no);  //Ԥ��ĳ�������ĺ���
        void ShowAirlineByCity(string city);    //Ԥ��ĳ�����еĺ���
        void SearchAirlineByName(string name);    //ͨ������Ų鿴��ϸ��Ϣ
        void LoadBookOrder();
        int GetBookOrderNum();
        void Book();    //��Ʊ
        void ShowBookList();
        void Unsubscribe(); //��Ʊ
        void UnsubscribeByName(string name); //ͨ��������Ʊ
        void UnsubscribeByIdNum(string Id); //ͨ��֤������Ʊ
        void UnsubscribeByNo(int no); //ͨ�������Ʊ
        void MenuDaemon();
        void ShowAdvisableRoute(string departureCity,string arrivalCity,string departureTime,string arrivalTime);
        void ShowBestAirlineNetwork(string departureCity);
        void RecommandBestRoute(string departureCity,string arrivalCity);
    protected:

    private:
        Array GenerateBookJson();    //����json
        void ShowMenu(int i);
};

#endif // SYSTEM_H
