#ifndef SYSTEM_H
#define SYSTEM_H
#include "AirlineGraph.h"
#include "BookOrder.h"
#include "TimeUtil.h"
#include <fstream>
#include <time.h>

class System
{
    public:
        System();
        virtual ~System();
        void InsertAirlineInfo();   //���뺽����Ϣ
        void ShowWelcome();
        void ShowAllAirlineToUser();    //Ԥ���Ѿ�������ȫ�����ߵ������Ϣ
        void ShowAirlineByAirport(int no);  //Ԥ��ĳ�������ĺ���
        void ShowAirlineByCity(string city);    //Ԥ��ĳ�����еĺ���
        void SearchAirlineByName(string name);    //ͨ������Ų鿴��ϸ��Ϣ
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
        AirlineGraph* mAirlineGraph;
        vector<BookOrder*>* mBookOrderVector;
        void LoadBookOrder();
        int GetBookOrderNum();
        Array GenerateBookJson();    //����json
        void ShowMenu(int i);
};

#endif // SYSTEM_H
