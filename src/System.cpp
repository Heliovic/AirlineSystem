#include "System.h"

System::System()
{
    mAirlineGraph=new AirlineGraph();
    ifstream infile;
    string s;
    infile.open("Book.json");
    ostringstream tmp;
    tmp<<infile.rdbuf();
    s=tmp.str();
    mBookArray.parse(s);  //����json
    /*ofstream outfile;
    outfile.open("Airline.json");
    Array jsonArray=GenerateAirlineJson();
    cout<<jsonArray.json();
    outfile<<jsonArray.json();
    outfile.close();*/
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
    if(mAirlineGraph->FindAirlineByName(airline->mAirlineName)!=NULL)
    {
        cout<<"�Ѵ��ڸú��࣡"<<endl;
        return;
    }
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

void System::ShowAllAirlineToUser()
{
    mAirlineGraph->ShowAllAirlineToUser();
}

void System::ShowAirlineByAirport(int no)
{
    mAirlineGraph->ShowAirlineByAirport(no);
    cout<<endl<<"========================================================================================================================================================================"<<endl;
}

void System::ShowAirlineByCity(string city)
{
    cout<<city;
    mAirlineGraph->ShowAirlineByCity(city);
}

void System::SearchAirline(string name)
{
    vector<Airline*>* vec=mAirlineGraph->FindAirlineByName(name);
    if(vec->size()==0)
    {
        cout<<endl<<"�޼�¼��"<<endl;
    }
    else
    {
        cout<<endl<<"========================================================================================================================================================================"<<endl;
        cout<<"����"<<vec->size()<<"�����:"<<endl;
        for(vector<Airline*>::iterator it=vec->begin();it!=vec->end();it++)
        {
            Airline* airline=(*it);
            cout<<endl;
            cout<<setw(12)<<"�����:"<<airline->mAirlineName<<endl;
            cout<<setw(12)<<"���չ�˾:"<<airline->mCompany<<endl;
            cout<<setw(12)<<"������:"<<airline->mDepartureCity<<endl;
            cout<<setw(12)<<"��ɻ���:"<<airline->mDepartureAirport<<endl;
            cout<<setw(12)<<"Ŀ�ĵ�:"<<airline->mArrivalCity<<endl;
            cout<<setw(12)<<"��½����:"<<airline->mArrivalAirport<<endl;
            cout<<setw(12)<<"���ʱ��:"<<airline->mDepartureTime<<endl;
            cout<<setw(12)<<"�ִ�ʱ��:"<<airline->mArrivalTime<<endl;
            cout<<setw(12)<<"����:"<<airline->mAirplaneModel<<endl;
            cout<<setw(12)<<"Ʊ��:"<<airline->mPrice<<endl;
            cout<<setw(12)<<"�ۿ�:"<<airline->mIntDiscount/1000.0<<endl;
            cout<<setw(12)<<"�ۺ�Ʊ��:"<<airline->mPrice*(1-airline->mIntDiscount/1000.0)<<endl;
            cout<<setw(12)<<"�ؿ���:"<<airline->mCapacity<<endl;
            cout<<setw(12)<<"����:"<<airline->mCurrentNumber<<endl;
            cout<<setw(12)<<"��Ʊ:"<<airline->mCapacity-airline->mCurrentNumber<<endl;
            cout<<endl;
            cout<<"==========================================="<<endl;
        }
    }
}

void System::Book()
{
    /*cout<<jsonArray.json();
    outfile<<jsonArray.json();
    outfile.close();*/

    string name;
    cout<<endl<<"�����뺽��ţ�"<<endl;
    cin>>name;

    vector<Airline*>* vec=mAirlineGraph->FindAirlineByName(name);
    if(vec->size()==0)
    {
        cout<<endl<<"�޼�¼��"<<endl;
        return;
    }
    else if(vec->size()==1)
    {
        Airline* airline=(*vec)[0];

        cout<<"==========================================="<<endl;
        cout<<endl;
        cout<<setw(12)<<"�����:"<<airline->mAirlineName<<endl;
        cout<<setw(12)<<"���չ�˾:"<<airline->mCompany<<endl;
        cout<<setw(12)<<"������:"<<airline->mDepartureCity<<endl;
        cout<<setw(12)<<"��ɻ���:"<<airline->mDepartureAirport<<endl;
        cout<<setw(12)<<"Ŀ�ĵ�:"<<airline->mArrivalCity<<endl;
        cout<<setw(12)<<"��½����:"<<airline->mArrivalAirport<<endl;
        cout<<setw(12)<<"���ʱ��:"<<airline->mDepartureTime<<endl;
        cout<<setw(12)<<"�ִ�ʱ��:"<<airline->mArrivalTime<<endl;
        cout<<setw(12)<<"����:"<<airline->mAirplaneModel<<endl;
        cout<<setw(12)<<"Ʊ��:"<<airline->mPrice<<endl;
        cout<<setw(12)<<"�ۿ�:"<<airline->mIntDiscount/1000.0<<endl;
        cout<<setw(12)<<"�ۺ�Ʊ��:"<<airline->mPrice*(1-airline->mIntDiscount/1000.0)<<endl;
        cout<<setw(12)<<"�ؿ���:"<<airline->mCapacity<<endl;
        cout<<setw(12)<<"����:"<<airline->mCurrentNumber<<endl;
        cout<<setw(12)<<"��Ʊ:"<<airline->mCapacity-airline->mCurrentNumber<<endl;
        cout<<endl;
        cout<<"==========================================="<<endl;


        if(airline->mCapacity==airline->mCurrentNumber)
        {
            cout<<endl<<"���ۿգ�"<<endl;
            return;
        }
        Object jsonObj;
        string s1,s2;
        cout<<endl<<"������������"<<endl;
        cin>>s1;
        jsonObj<<"����"<<s1;
        cout<<endl<<"������֤���ţ�"<<endl;
        cin>>s2;
        jsonObj<<"֤����"<<s2;

        jsonObj<<"��˾"<<airline->mCompany;
        jsonObj<<"�����"<<airline->mAirlineName;
        jsonObj<<"��ʼ����"<<airline->mDepartureCity;
        jsonObj<<"��ɻ���"<<airline->mDepartureAirport;
        jsonObj<<"�������"<<airline->mArrivalCity;
        jsonObj<<"�������"<<airline->mArrivalAirport;
        jsonObj<<"���ʱ��"<<airline->mDepartureTime;
        jsonObj<<"����ʱ��"<<airline->mArrivalTime;
        jsonObj<<"����"<<airline->mAirplaneModel;
        jsonObj<<"����۸�"<<int(airline->mPrice*(1-airline->mIntDiscount/1000.0));

        mBookArray<<jsonObj;
        cout<<mBookArray.json();

        ofstream outfile;
        outfile.open("Book.json");

        outfile<<mBookArray.json();
        outfile.close();

        mAirlineGraph->Book(airline);

        cout<<"==========================================="<<endl;
        cout<<endl;
        cout<<"================ Ԥ���ɹ� ================="<<endl;
        cout<<endl;
        cout<<setw(12)<<"����:"<<s1<<endl;
        cout<<setw(12)<<"֤����:"<<s2<<endl;
        cout<<setw(12)<<"�����:"<<airline->mAirlineName<<endl;
        cout<<setw(12)<<"���չ�˾:"<<airline->mCompany<<endl;
        cout<<setw(12)<<"������:"<<airline->mDepartureCity<<endl;
        cout<<setw(12)<<"��ɻ���:"<<airline->mDepartureAirport<<endl;
        cout<<setw(12)<<"Ŀ�ĵ�:"<<airline->mArrivalCity<<endl;
        cout<<setw(12)<<"��½����:"<<airline->mArrivalAirport<<endl;
        cout<<setw(12)<<"���ʱ��:"<<airline->mDepartureTime<<endl;
        cout<<setw(12)<<"�ִ�ʱ��:"<<airline->mArrivalTime<<endl;
        cout<<setw(12)<<"����:"<<airline->mAirplaneModel<<endl;
        cout<<setw(12)<<"����۸�"<<int(airline->mPrice*(1-airline->mIntDiscount/1000.0))<<endl;
        cout<<endl;
        cout<<"==========================================="<<endl;
    }
    else if(vec->size()>1)
    {
        cout<<"����"<<vec->size()<<"�����:"<<endl;
        cout<<"==========================================="<<endl;
        for(int i=0;i<vec->size();i++)
        {
            Airline* airline=(*vec)[i];
            cout<<"��"<<i+1<<"��"<<endl;
            cout<<endl;
            cout<<setw(12)<<"�����:"<<airline->mAirlineName<<endl;
            cout<<setw(12)<<"���չ�˾:"<<airline->mCompany<<endl;
            cout<<setw(12)<<"������:"<<airline->mDepartureCity<<endl;
            cout<<setw(12)<<"��ɻ���:"<<airline->mDepartureAirport<<endl;
            cout<<setw(12)<<"Ŀ�ĵ�:"<<airline->mArrivalCity<<endl;
            cout<<setw(12)<<"��½����:"<<airline->mArrivalAirport<<endl;
            cout<<setw(12)<<"���ʱ��:"<<airline->mDepartureTime<<endl;
            cout<<setw(12)<<"�ִ�ʱ��:"<<airline->mArrivalTime<<endl;
            cout<<setw(12)<<"����:"<<airline->mAirplaneModel<<endl;
            cout<<setw(12)<<"Ʊ��:"<<airline->mPrice<<endl;
            cout<<setw(12)<<"�ۿ�:"<<airline->mIntDiscount/1000.0<<endl;
            cout<<setw(12)<<"�ۺ�Ʊ��:"<<airline->mPrice*(1-airline->mIntDiscount/1000.0)<<endl;
            cout<<setw(12)<<"�ؿ���:"<<airline->mCapacity<<endl;
            cout<<setw(12)<<"����:"<<airline->mCurrentNumber<<endl;
            cout<<setw(12)<<"��Ʊ:"<<airline->mCapacity-airline->mCurrentNumber<<endl;
            cout<<endl;
            cout<<"==========================================="<<endl;
        }

        cout<<"������Ԥ���������������֣�"<<endl;
        int i;
        cin>>i;
        while(i>vec->size()||i<=0)
        {
            cout<<endl<<"���벻�Ϸ������������룡"<<endl;
            cin>>i;
        }
        Airline* airline=(*vec)[i-1];

        if(airline->mCapacity==airline->mCurrentNumber)
        {
            cout<<endl<<"���ۿգ�"<<endl;
            return;
        }
        Object jsonObj;
        string s1,s2;
        cout<<endl<<"������������"<<endl;
        cin>>s1;
        jsonObj<<"����"<<s1;
        cout<<endl<<"������֤���ţ�"<<endl;
        cin>>s2;
        jsonObj<<"֤����"<<s2;

        jsonObj<<"��˾"<<airline->mCompany;
        jsonObj<<"�����"<<airline->mAirlineName;
        jsonObj<<"��ʼ����"<<airline->mDepartureCity;
        jsonObj<<"��ɻ���"<<airline->mDepartureAirport;
        jsonObj<<"�������"<<airline->mArrivalCity;
        jsonObj<<"�������"<<airline->mArrivalAirport;
        jsonObj<<"���ʱ��"<<airline->mDepartureTime;
        jsonObj<<"����ʱ��"<<airline->mArrivalTime;
        jsonObj<<"����"<<airline->mAirplaneModel;
        jsonObj<<"����۸�"<<int(airline->mPrice*(1-airline->mIntDiscount/1000.0));

        mBookArray<<jsonObj;
        cout<<mBookArray.json();

        ofstream outfile;
        outfile.open("Book.json");

        outfile<<mBookArray.json();
        outfile.close();

        mAirlineGraph->Book(airline);

        cout<<"==========================================="<<endl;
        cout<<endl;
        cout<<"================ Ԥ���ɹ� ================="<<endl;
        cout<<endl;
        cout<<setw(12)<<"����:"<<s1<<endl;
        cout<<setw(12)<<"֤����:"<<s2<<endl;
        cout<<setw(12)<<"�����:"<<airline->mAirlineName<<endl;
        cout<<setw(12)<<"���չ�˾:"<<airline->mCompany<<endl;
        cout<<setw(12)<<"������:"<<airline->mDepartureCity<<endl;
        cout<<setw(12)<<"��ɻ���:"<<airline->mDepartureAirport<<endl;
        cout<<setw(12)<<"Ŀ�ĵ�:"<<airline->mArrivalCity<<endl;
        cout<<setw(12)<<"��½����:"<<airline->mArrivalAirport<<endl;
        cout<<setw(12)<<"���ʱ��:"<<airline->mDepartureTime<<endl;
        cout<<setw(12)<<"�ִ�ʱ��:"<<airline->mArrivalTime<<endl;
        cout<<setw(12)<<"����:"<<airline->mAirplaneModel<<endl;
        cout<<setw(12)<<"����۸�"<<int(airline->mPrice*(1-airline->mIntDiscount/1000.0))<<endl;
        cout<<endl;
        cout<<"==========================================="<<endl;
    }
}
