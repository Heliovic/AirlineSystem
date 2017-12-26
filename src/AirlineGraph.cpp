#include "AirlineGraph.h"

AirlineGraph::AirlineGraph()
{
    LoadAirport();
    LoadAirline();
    ShowAirlineGraph();
    //WriteAirlineJson();
}

AirlineGraph::~AirlineGraph()
{
    //dtor
}
//���������Ϣ
void AirlineGraph::LoadAirport()
{
    Array AirportArray;
    ifstream infile;
    string s;
    infile.open("Airport.json");
    ostringstream tmp;
    tmp<<infile.rdbuf();
    s=tmp.str();
    AirportArray.parse(s);  //����json
    mAirportNumber=AirportArray.size();
    mAirportHeadArray=new Airport*[mAirportNumber];
    for(int i=0;i<mAirportNumber;i++)   //���ɶ����
    {
        mAirportHeadArray[i]=new Airport();
        mAirportHeadArray[i]->No=AirportArray.get<Object>(i).get<Number>("���");
        mAirportHeadArray[i]->mAirportName=AirportArray.get<Object>(i).get<String>("����");
        mAirportHeadArray[i]->mShortName=AirportArray.get<Object>(i).get<String>("��������");
        mAirportHeadArray[i]->mLocation=AirportArray.get<Object>(i).get<String>("����");
    }
    //cout<<AirportArray.json();
}
//���뺽����Ϣ
void AirlineGraph::LoadAirline()
{
    Array AirlineArray;
    ifstream infile;
    string s;
    infile.open("Airline.json");
    ostringstream tmp;
    tmp<<infile.rdbuf();
    s=tmp.str();
    AirlineArray.parse(s);  //����json
    mAirlineVector=new vector<Airline*>();
    for(int i=0;i<AirlineArray.size();i++)  //���溽�ߵ�vector
    {
        Airline* airline=new Airline();
        airline->mAirlineName=AirlineArray.get<Object>(i).get<String>("�����");
        airline->mCompany=AirlineArray.get<Object>(i).get<String>("��˾");
        airline->mDepartureAirport=AirlineArray.get<Object>(i).get<String>("��ɻ���");
        airline->mArrivalAirport=AirlineArray.get<Object>(i).get<String>("�������");
        airline->mDepartureTime=AirlineArray.get<Object>(i).get<String>("���ʱ��");
        airline->mArrivalTime=AirlineArray.get<Object>(i).get<String>("����ʱ��");
        airline->mAirplaneModel=AirlineArray.get<Object>(i).get<String>("����");
        airline->mDepartureCity=AirlineArray.get<Object>(i).get<String>("��ʼ����");
        airline->mArrivalCity=AirlineArray.get<Object>(i).get<String>("�������");
        airline->mPrice=AirlineArray.get<Object>(i).get<Number>("�۸�");
        airline->mIntDiscount=AirlineArray.get<Object>(i).get<Number>("����ۿ�");
        airline->mCapacity=AirlineArray.get<Object>(i).get<Number>("����");
        airline->mCurrentNumber=AirlineArray.get<Object>(i).get<Number>("��ǰ����");
        mAirlineVector->push_back(airline);

        Airport* airport=FindAirportByName(airline->mDepartureAirport);
        if(airport!=NULL)   //�жϻ����Ƿ����
        {
            InsertAirlineGraph(airport,airline);    //���뵽ͼ
        }
    }
    infile.close();
    //cout<<AirlineArray.json();
}
//ͨ������Ų�ѯ����
Airport* AirlineGraph::FindAirportByName(string name)
{
    for(int i=0;i<mAirportNumber;i++)
    {
        if(mAirportHeadArray[i]->mAirportName==name)
        {

          //  cout<<mAirportHeadArray[i]->mAirportName;
            return mAirportHeadArray[i];
        }
    }
    return NULL;
}

//���뺽�� ����ʱ����
void AirlineGraph::InsertAirlineGraph(Airport* airport,Airline* airline)
{
    Airline* line=airport->mAdjAirline;
    if(line==NULL)
    {
        airport->mAdjAirline=airline;
    }else
    {
        //cout<<line->mAirlineName;
        while(line->mNextAirline!=NULL)
        {
            line=line->mNextAirline;
        }
        line->mNextAirline=airline;
    }
}
//չʾ����
void AirlineGraph::ShowAirlineGraph()
{
    cout.setf(ios::left);
    cout<<endl;

    for(int i=0;i<mAirportNumber;i++)
    {
        cout<<endl;
        cout<<"======================================================================================================================";
        Airport* airport=mAirportHeadArray[i];
        Airline* airline=airport->mAdjAirline;
        cout<<endl<<"��"<<airport->mLocation<<" - "<<airport->mAirportName<<"��"<<"\t"<<endl<<endl;
        while(airline!=NULL)
        {
            cout<<airline->mAirlineName<<"\t";
            airline=airline->mNextAirline;
        }
    }
    cout<<endl<<"======================================================================================================================"<<endl;
}
//����json
Array AirlineGraph::GenerateAirlineJson()
{
    Array jsonArray;
    for(int i=0;i<mAirportNumber;i++)
    {
        Airport* airport=mAirportHeadArray[i];
        Airline* airline=airport->mAdjAirline;
        while(airline!=NULL)
        {
            Object jsonObj;
            jsonObj<<"��˾"<<airline->mCompany;
            jsonObj<<"�����"<<airline->mAirlineName;
            jsonObj<<"��ʼ����"<<airline->mDepartureCity;
            jsonObj<<"��ɻ���"<<airline->mDepartureAirport;
            jsonObj<<"�������"<<airline->mArrivalCity;
            jsonObj<<"�������"<<airline->mArrivalAirport;
            jsonObj<<"���ʱ��"<<airline->mDepartureTime;
            jsonObj<<"����ʱ��"<<airline->mArrivalTime;
            jsonObj<<"����"<<airline->mAirplaneModel;
            jsonObj<<"�۸�"<<airline->mPrice;
            jsonObj<<"����ۿ�"<<airline->mIntDiscount;
            jsonObj<<"����"<<airline->mCapacity;
            jsonObj<<"��ǰ����"<<airline->mCurrentNumber;

            jsonArray<<jsonObj;
            airline=airline->mNextAirline;
        }
    }
    return jsonArray;
}

void AirlineGraph::WriteAirlineJson()
{
    ofstream outfile;
    outfile.open("Airline.json");
    Array jsonArray=GenerateAirlineJson();
    //cout<<jsonArray.json();
    outfile<<jsonArray.json();
    outfile.close();
}

int AirlineGraph::GetAirlineNumber()
{
    return mAirlineVector->size();
}

void AirlineGraph::InsertAirline(Airline* airline)
{
    Airport* dAirport=FindAirportByName(airline->mDepartureAirport);
    Airport* aAirport=FindAirportByName(airline->mArrivalAirport);

    if(dAirport==NULL||aAirport==NULL)
    {
        cout<<endl<<"���������ڣ�";
        return;
    }else if(dAirport->mLocation!=airline->mDepartureCity||aAirport->mLocation!=airline->mArrivalCity)
    {
        cout<<endl<<"����λ����Ϣ��ƥ�䣡";
        return;
    }else
    {
        mAirlineVector->push_back(airline);
        InsertAirlineGraph(dAirport,airline);    //���뵽ͼ
    }
}

string AirlineGraph::GetAirportLocation(string airportName)
{
    return FindAirportByName(airportName)->mLocation;
}

//���뺽��Ż�ȡ���п��ܵĺ���
vector<Airline*>* AirlineGraph::FindAirlineByName(string name)
{
    vector<Airline*>* vec=new vector<Airline*>();
    for(int i=0;i<mAirportNumber;i++)
    {
        Airport* airport=mAirportHeadArray[i];
        Airline* airline=airport->mAdjAirline;
        while(airline!=NULL)
        {
            if(airline->mAirlineName==name)
            {
                vec->push_back(airline);
            }
            airline=airline->mNextAirline;
        }
    }
    return vec;
}

void AirlineGraph::ShowAllAirlineToUser()
{
    cout.setf(ios::left);
    cout<<endl;

    for(int i=0;i<mAirportNumber;i++)
    {
        ShowAirlineByAirport(i);
    }
    cout<<endl<<"========================================================================================================================================================================"<<endl;
}


void AirlineGraph::ShowAirlineByAirport(int no)
{
    cout.setf(ios::left);
    cout<<endl;
    cout<<"========================================================================================================================================================================"<<endl;
    Airport* airport=mAirportHeadArray[no];
    Airline* airline=airport->mAdjAirline;
    cout<<endl<<"��"<<airport->mLocation<<" - "<<airport->mAirportName<<"��"<<"\t"<<endl<<endl;

    cout<<setw(10)<<"�����";
    cout<<setw(25)<<"���չ�˾";
    cout<<setw(10)<<"������";
    cout<<setw(20)<<"��ɻ���";
    cout<<setw(10)<<"Ŀ�ĵ�";
    cout<<setw(20)<<"��½����";
    cout<<setw(10)<<"���ʱ��";
    cout<<setw(10)<<"�ִ�ʱ��";
    cout<<setw(8)<<"����";
    cout<<setw(8)<<"Ʊ��";
    cout<<setw(8)<<"�ۿ�";
    cout<<setw(9)<<"�ۺ�Ʊ��";
    cout<<setw(8)<<"�ؿ���";
    cout<<setw(8)<<"����";
    cout<<setw(8)<<"��Ʊ";
    cout<<endl<<endl;

    while(airline!=NULL)
    {
        cout<<setw(10)<<airline->mAirlineName;
        cout<<setw(25)<<airline->mCompany;
        cout<<setw(10)<<airline->mDepartureCity;
        cout<<setw(20)<<airline->mDepartureAirport;
        cout<<setw(10)<<airline->mArrivalCity;
        cout<<setw(20)<<airline->mArrivalAirport;
        cout<<setw(10)<<airline->mDepartureTime;
        cout<<setw(10)<<airline->mArrivalTime;
        cout<<setw(8)<<airline->mAirplaneModel;
        cout<<setw(8)<<airline->mPrice;
        cout<<setw(8)<<airline->mIntDiscount/1000.0;
        cout<<setw(9)<<airline->mPrice*(1-airline->mIntDiscount/1000.0);
        cout<<setw(8)<<airline->mCapacity;
        cout<<setw(8)<<airline->mCurrentNumber;
        cout<<setw(8)<<airline->mCapacity-airline->mCurrentNumber;
        cout<<endl;
        airline=airline->mNextAirline;
    }
}

vector<int>* AirlineGraph::GetAirportIdByLocation(string loc)
{
    vector<int>* vec=new vector<int>();
    for(int i=0;i<mAirportNumber;i++)
    {
        if(mAirportHeadArray[i]->mLocation==loc)
        {
            vec->push_back(i);
        }
    }
    return vec;
}

void AirlineGraph::ShowAirlineByCity(string city)
{
    vector<int>* vec=GetAirportIdByLocation(city);
    for(int i=0;i<vec->size();i++)
    {
        ShowAirlineByAirport((*vec)[i]);
    }
    if(vec->size()>0)
    {
        cout<<endl<<"========================================================================================================================================================================"<<endl;
    }else
    {
        cout<<endl<<"�޺�����Ϣ��"<<endl;
    }
}

void AirlineGraph::Book(Airline* airline)
{
    airline->mCurrentNumber=airline->mCurrentNumber+1;  //�Ѷ�����+1
    WriteAirlineJson(); //д�������±�������
}

void AirlineGraph::Unsubscribe(BookOrder* bookOrder)
{
    vector<Airline*>* vec=FindAirlineByName(bookOrder->mAirlineName);
    for(vector<Airline*>::iterator it=vec->begin();it!=vec->end();it++)
    {
        if((*it)->mDepartureAirport==bookOrder->mDepartureAirport&&(*it)->mArrivalAirport==bookOrder->mArrivalAirport)
        {
            (*it)->mCurrentNumber=(*it)->mCurrentNumber-1;  //�Ѷ�����-1
            WriteAirlineJson(); //д�������±�������
            break;
        }
    }
    cout<<"==========================================="<<endl;
    cout<<endl;
    cout<<"================ ��Ʊ�ɹ� ================="<<endl;
    cout<<endl;
    cout<<setw(12)<<"����:"<<bookOrder->mName<<endl;
    cout<<setw(12)<<"֤����:"<<bookOrder->mIdNumber<<endl;
    cout<<setw(12)<<"�����:"<<bookOrder->mAirlineName<<endl;
    cout<<setw(12)<<"���չ�˾:"<<bookOrder->mCompany<<endl;
    cout<<setw(12)<<"������:"<<bookOrder->mDepartureCity<<endl;
    cout<<setw(12)<<"Ŀ�ĵ�:"<<bookOrder->mArrivalCity<<endl;
    cout<<setw(12)<<"����۸�:"<<bookOrder->mPrice<<endl;
    cout<<endl;
    cout<<"==========================================="<<endl;
}

