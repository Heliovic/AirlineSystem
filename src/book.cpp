#include "book.h"

book::book()
{
    //ctor
}

book::~book()
{
    //dtor
}
book::book(int leftticket_num)
{   //string mDepartureCity,mArrivalCity;

    cout<<"�������������"<<endl;
    cin>>mDepartureCity;
    cout<<"�����뵽�����"<<endl;
    cin>>mArrivalCity;
    if(1)
    {
        cout<<"�����"<<endl;
        cin>>mAirlineName;
        while(mAirlineName=="")
        {
            cout<<"����Ų���Ϊ��"<<endl;
        }
        while(mAirlineName!="")
        {


            cout<<"Ԥ������"<<endl;
            cin>>ticket_num;
            if(ticket_num>0&&ticket_num<leftticket_num) cout<<"Ԥ���ɹ�"<<endl;

        }
    }


}
