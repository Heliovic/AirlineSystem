#ifndef AIRLINE_H
#define AIRLINE_H
#include <iostream>
#include <stdlib.h>
using namespace std;

class Airline
{
    public:
        Airline();
        virtual ~Airline();
        string mAirlineName;        //�����
        string mCompany;            //���๫˾
        string mDepartureAirport;   //��ɻ���
        string mArrivalAirport;     //�������
        string mDepartureTime;      //���ʱ��
        string mArrivalTime;        //����ʱ��
        string mAirplaneModel;      //����
        string mDepartureCity;      //��ɳ���
        string mArrivalCity;        //�������
        int mAirportNo;
        int mPrice;                 //�۸�
        int mIntDiscount;           //�ۿ�
        int mCapacity;              //��������
        int mCurrentNumber;         //��ǰ����
        Airline* mNextAirline;      //��һ����
        int GetPriceAfterDiscount();
        int GetAirlineDepartureTimeStamp();
        int GetAirlineArrivalTimeStamp();
    protected:

    private:
};

#endif // AIRLINE_H
