#include "System.h"

System::System()
{
    mAirlineGraph=new AirlineGraph();
}

System::~System()
{
    //dtor
}


void System::InsertAirlineInfo()
{
    Airline* airline=new Airline();
    cout<<endl;
    cout<<"�����뺽�չ�˾��"<<endl;
    cin>>airline->mCompany;
    cout<<"�����뺽��ţ�"<<endl;
    cin>>airline->mAirlineName;
    cout<<"���������ʱ�䣺"<<endl;
    cin>>airline->mDepartureTime;
    cout<<"�����뵽��ʱ�䣺"<<endl;
    cin>>airline->mArrivalTime;
    cout<<"��������ɻ�����"<<endl;
    cin>>airline->mDepartureAirport;
    airline->mDepartureCity=mAirlineGraph->GetAirportLocation(airline->mDepartureAirport);
    cout<<"�����뵽�������"<<endl;
    cin>>airline->mArrivalAirport;
    airline->mArrivalCity=mAirlineGraph->GetAirportLocation(airline->mArrivalAirport);
    cout<<"��������ͣ�"<<endl;
    cin>>airline->mAirplaneModel;
    cout<<"������������"<<endl;
    cin>>airline->mCapacity;
    cout<<"�����뵱ǰ�˿�������"<<endl;
    cin>>airline->mCapacity;
    if(airline->mCapacity<airline->mCurrentNumber)
    {
        cout<<"�Ƿ����룡����С�ڵ�ǰ�˿�������"<<endl;
        return;
    }
    cout<<"������Ʊ�ۣ�"<<endl;
    cin>>airline->mPrice;
    cout<<"�������ۿۣ�1000%����"<<endl;
    cin>>airline->mIntDiscount;
    mAirlineGraph->InsertAirline(airline);
}
