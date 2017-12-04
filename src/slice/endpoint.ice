#ifndef _ENDPOINT_ICE_
#define _ENDPOINT_ICE_

module EndPointCtrl{
//���崫������
enum TransType{
    tcp,
    udp,
    sctp
};

struct Endpoint{
    string ctrlAddr; //����ip��ַ
    string svcAddr;  //ҵ��ip��ַ
};

//����pair�ṹ
struct Pair{
    string uuid;  //pair��Ψһ��ʶ
    TransType type; //��������
    int ipver; //ip�汾�ţ�4 or 6
    Endpoint ep1;  //endpoint1 
    Endpoint ep2;  //endpoint2 
};

//�����ȡͳ����Ϣ������item�ṹ
struct GetResultItem{
    string uuid;
    bool needStop; //�Ƿ���Ҫֹͣ�߳�
};
sequence<Pair> Qpair;
sequence<GetResultItem> QGetResultUuid;

//����add pair��result�ṹ
struct AddPairResult{
    string uuid; //pair��Ψһ��ʶ
    short port; //server�����Ķ˿ں�,����0��ʾ����ʧ��
};
sequence<AddPairResult> QaddPairResult;

//����ͳ������
enum StatsType{
    sendbytes,
    sendbps,
    recvbytes,
    recvbps,
    retransmits,
    omitted,
    jitterms,
    lostpackets,
    packets,
    lostpercent
};
//����ͳ����Ϣ
struct StatsItem{
    StatsType type;
    double value;
};
sequence<StatsItem> QstatsList;

struct StatsTimeItem{
    long timestamp;
    QstatsList statslist;
};
sequence<StatsTimeItem> QstatsTimeList;

//����pair��ǰ״̬
enum PairStatus{
    idle,
    init,
    running
};

struct PairStats{
    string uuid;
    PairStatus status; //״̬
    QstatsTimeList statstimelist;
};
sequence<PairStats> QpairStatsList;

interface EndPointCtrlInt{
  //����pair�б�
	QaddPairResult AddPairs(Qpair pairlist);
	//ǿ��ɾ��pair�б�
	void DelPairs(QGetResultUuid uuidlist);
	//���ͳ����Ϣ
	QpairStatsList GetResults(QGetResultUuid uuidlist);
	//

  //����ep2�ϵ�pair�б�
	QaddPairResult Ep2AddPairs(Qpair pairlist);
	//ǿ��ɾ��ep2�ϵ�pair�б�
	void Ep2DelPairs(QGetResultUuid uuidlist);
	//���ep2�ϵ�ͳ����Ϣ
	QpairStatsList Ep2GetResults(QGetResultUuid uuidlist);
};
};

#endif