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

        Airport* airport=GetAirportByName(airline->mDepartureAirport);
        if(airport!=NULL)   //�жϻ����Ƿ����
        {
            InsertAirlineGraph(airport,airline);    //���뵽ͼ
        }
    }
    infile.close();
    //cout<<AirlineArray.json();
}
//ͨ������Ų�ѯ����
Airport* AirlineGraph::GetAirportByName(string name)
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
    Airport* dAirport=GetAirportByName(airline->mDepartureAirport);
    Airport* aAirport=GetAirportByName(airline->mArrivalAirport);

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
        WriteAirlineJson(); //д�������º��������ļ�
    }
}

string AirlineGraph::GetAirportLocation(string airportName)
{
    return GetAirportByName(airportName)->mLocation;
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
    vector<Airline*> vec;
    Airport* airport=mAirportHeadArray[no];
    Airline* airline=airport->mAdjAirline;
    while(airline!=NULL)
    {
        vec.push_back(airline);
        airline=airline->mNextAirline;
    }
    for(int i=1;i<vec.size();i++)  //��������
    {
        Airline* airline=vec[i];
        int j;
        for(j=i-1;j>=0&&(airline->GetAirlineDepartureTimeStamp())<vec[j]->GetAirlineDepartureTimeStamp();j--)
        {
            vec[j+1]=vec[j];
        }
        vec[j+1]=airline;
    }
    cout.setf(ios::left);
    cout<<endl;
    cout<<"========================================================================================================================================================================"<<endl;
    /*Airport* airport=mAirportHeadArray[no];
    Airline* airline=airport->mAdjAirline;*/
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

    for(vector<Airline*>::iterator it=vec.begin();it!=vec.end();it++)
    {
        Airline* airline=*it;
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

vector<Airline*>* AirlineGraph::GetAirlineByDACity(string departure,string arrival)
{
    vector<Airline*>* vec=new vector<Airline*>();
    vector<int>* dAirportVec=new vector<int>();
    dAirportVec=GetAirportIdByLocation(departure);
    for(vector<int>::iterator dit=dAirportVec->begin();dit!=dAirportVec->end();dit++)
    {
        Airline* airline=mAirportHeadArray[*dit]->mAdjAirline;
        while(airline!=NULL)
        {
            if(airline->mArrivalCity==arrival)
            {
                vec->push_back(airline);
            }
            airline=airline->mNextAirline;
        }
    }
    return vec;
}

void AirlineGraph::ShowDACityAirlineByDiscountPrice(string departure,string arrival)
{
    vector<Airline*>* vec=GetAirlineByDACity(departure,arrival);

    for(int i=1;i<vec->size();i++)  //��������
    {
        Airline* airline=(*vec)[i];
        int j;
        for(j=i-1;j>=0&&(airline->GetPriceAfterDiscount())<(*vec)[j]->GetPriceAfterDiscount();j--)
        {
            (*vec)[j+1]=(*vec)[j];
        }
        (*vec)[j+1]=airline;
    }

    cout<<endl<<"========================================================================================================================================================================"<<endl;
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
    for(vector<Airline*>::iterator it=vec->begin();it!=vec->end();it++)
    {
        Airline* airline=*it;
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
    }
    cout<<endl<<"========================================================================================================================================================================"<<endl;
}

void AirlineGraph::ShowDACityAirlineByDepartureTime(string departure,string arrival)
{
    vector<Airline*>* vec=GetAirlineByDACity(departure,arrival);

    for(int i=1;i<vec->size();i++)
    {
        Airline* airline=(*vec)[i];
        int j;
        for(j=i-1;j>=0&&(airline->GetAirlineDepartureTimeStamp())<(*vec)[j]->GetAirlineDepartureTimeStamp();j--)
        {
            (*vec)[j+1]=(*vec)[j];
        }
        (*vec)[j+1]=airline;
    }

    cout<<endl<<"========================================================================================================================================================================"<<endl;
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
    for(vector<Airline*>::iterator it=vec->begin();it!=vec->end();it++)
    {
        Airline* airline=*it;
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
    }
    cout<<endl<<"========================================================================================================================================================================"<<endl;
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

void AirlineGraph::GetAdvisableRouteWithDFS(string departure,string arrival)
{
    int InD[mAirportNumber]={0};
    int visit[mAirportNumber]={0};
    for(int i=0;i<mAirportNumber;i++)
    {
        Airline* airline=mAirportHeadArray[i]->mAdjAirline;
        while(airline!=NULL)
        {
            InD[GetAirportByName(airline->mArrivalAirport)->No]+=1; //ͳ�ƻ������
            airline=airline->mNextAirline;
        }
    }


    //int d=GetAirportByName()
    //vector< vector<Airline*> >* mainVec=new vector< vector<Airline*> >();
    vector<Airline*> routeVec;
    vector<Route>* mainVec=new vector<Route>();
    //DFS(9,29,InD,visit,mainVec,routeVec);
    /*for(vector< vector<Airline*> >::iterator it=mainVec->begin();it!=mainVec->end();it++)
    {
        vector<Airline*> vec=*it;
        for(int i=0;i<vec.size();i++)
        {
            cout<<vec[i]->mAirlineName<<"->";
        }
        cout<<endl;
    }*/

    BFS(9,29,InD,visit,mainVec);
    cout<<mainVec->size();
    for(vector<Route>::iterator it=mainVec->begin();it!=mainVec->end();it++)
    {
        (*it).ShowRoute();
        cout<<endl;
    }
}

void AirlineGraph::BFS(int f,int a,int* InD,int* visit,vector<Route>* mainVec)
{
    int k=5;   //����k
    queue<Route> q;
    Route r;
    r.mPrevNo=f;
    q.push(r);
    while(!q.empty())
    {
        Route r0=q.front();
        q.pop();
        Airline* airline=mAirportHeadArray[r0.mPrevNo]->mAdjAirline;
        while(airline!=NULL)
        {
            if(!r0.CheckPass(airline->mArrivalAirport))
            {
                if((r0.mAirlineVec.size()>0&&r0.mAirlineVec[r0.mAirlineVec.size()-1]->GetAirlineArrivalTimeStamp()<airline->GetAirlineDepartureTimeStamp())
                        ||r0.mAirlineVec.size()==0) //������ʼ�����ߣ�����Ҫ�ж�ǰ�󺽰�ʱ���Ƿ�ϵ���
                {
                    int no=GetAirportByName(airline->mArrivalAirport)->No;
                    if(visit[no]<k*InD[no])    //��ȵ�k��������һ��������ȵ�10��������BFS���̶ܳȣ���������ʱ�������
                    {
                        Route rNew=r0;
                        rNew.mAirlineVec.push_back(airline);
                        rNew.mPrevNo=no;
                        visit[no]+=1;
                        if(no!=a)
                        {
                            q.push(rNew);
                        }
                        else
                        {
                            mainVec->push_back(rNew);
                        }
                    }
                }
            }
            airline=airline->mNextAirline;
        }
    }
}

void AirlineGraph::DFS(int v,int a,int* InD,int* visit,vector< vector<Airline*> >* mainVec,vector<Airline*> routeVec)
{
    if(v!=a)    //δ����Ŀ�ĵ�
    {

        /*for(int j=0;j<routeVec.size();j++)
        {
            cout<<routeVec[j]<<"  ";
        }
        cout<<endl;*/

        visit[v]+=1;
        //cout<<"visit: "<<visit[v]<<"ind: "<<InD[v]<<endl;
        Airline* airline=mAirportHeadArray[v]->mAdjAirline;
        //cout<<v<<endl;
        while(airline!=NULL)
        {
            //cout<<airline->mAirlineName<<endl;
            int no=GetAirportByName(airline->mArrivalAirport)->No;
            bool tag=0;
            for(int i=0;i<routeVec.size();i++)
            {
                if(routeVec[i]->mArrivalAirport==airline->mArrivalAirport)
                {
                    tag=1;
                    break;
                }
            }
            if(routeVec.size()==0)
            {
                if(visit[no]<InD[no]&&!tag)   //�ȽϷ��ʴ���������Ƿ�С�����
                {
                    vector<Airline*> newRoute;
                    for(vector<Airline*>::iterator it=routeVec.begin(); it!=routeVec.end(); it++)
                    {
                        newRoute.push_back(*it);
                    }
                    newRoute.push_back(airline);
                    DFS(no,a,InD,visit,mainVec,newRoute);
                }
                else
                {
                    //cout<<"�������"<<endl;
                }
            }
            else if(routeVec[routeVec.size()-1]->GetAirlineArrivalTimeStamp()<airline->GetAirlineDepartureTimeStamp()/*&&airline->GetAirlineDepartureTimeStamp()<airline->GetAirlineArrivalTimeStamp()*/)
            {
                if(visit[no]<InD[no]&&!tag)   //�ȽϷ��ʴ���������Ƿ�С�����
                {
                    vector<Airline*> newRoute;
                    for(vector<Airline*>::iterator it=routeVec.begin(); it!=routeVec.end(); it++)
                    {
                        newRoute.push_back(*it);
                    }
                    newRoute.push_back(airline);
                    DFS(no,a,InD,visit,mainVec,newRoute);
                }
                else
                {
                    //cout<<"�������"<<endl;
                }
            }
            airline=airline->mNextAirline;
        }
    }else   //����Ŀ�ĵأ���ֹDFS
    {
        visit[v]+=1;
        /*for(int i=0;i<routeVec.size();i++)
        {
            cout<<routeVec[i]->mArrivalAirport<<"->";
        }
        cout<<endl;*/
        mainVec->push_back(routeVec);   //��·�������� mainVec
        /*for(int j=0;j<routeVec.size();j++)
        {
            cout<<routeVec[j]<<"  ";
        }*/
        //cout<<endl;
    }

}
