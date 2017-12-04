#ifndef _ENDPOINT_ICE_
#define _ENDPOINT_ICE_

module EndPointCtrl{
//定义传输类型
enum TransType{
    tcp,
    udp,
    sctp
};

struct Endpoint{
    string ctrlAddr; //控制ip地址
    string svcAddr;  //业务ip地址
};

//定义pair结构
struct Pair{
    string uuid;  //pair的唯一标识
    TransType type; //传输类型
    int ipver; //ip版本号，4 or 6
    Endpoint ep1;  //endpoint1 
    Endpoint ep2;  //endpoint2 
};

//定义获取统计信息的请求item结构
struct GetResultItem{
    string uuid;
    bool needStop; //是否需要停止线程
};
sequence<Pair> Qpair;
sequence<GetResultItem> QGetResultUuid;

//定义add pair的result结构
struct AddPairResult{
    string uuid; //pair的唯一标识
    short port; //server监听的端口号,返回0表示创建失败
};
sequence<AddPairResult> QaddPairResult;

//定义统计类型
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
//定义统计信息
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

//定义pair当前状态
enum PairStatus{
    idle,
    init,
    running
};

struct PairStats{
    string uuid;
    PairStatus status; //状态
    QstatsTimeList statstimelist;
};
sequence<PairStats> QpairStatsList;

interface EndPointCtrlInt{
  //创建pair列表
	QaddPairResult AddPairs(Qpair pairlist);
	//强制删除pair列表
	void DelPairs(QGetResultUuid uuidlist);
	//获得统计信息
	QpairStatsList GetResults(QGetResultUuid uuidlist);
	//

  //创建ep2上的pair列表
	QaddPairResult Ep2AddPairs(Qpair pairlist);
	//强制删除ep2上的pair列表
	void Ep2DelPairs(QGetResultUuid uuidlist);
	//获得ep2上的统计信息
	QpairStatsList Ep2GetResults(QGetResultUuid uuidlist);
};
};

#endif