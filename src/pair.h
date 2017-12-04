#ifndef __PARI_H__
#define __PARI_H__
#include <Ice/Ice.h>
#include "endpoint.h"
#include "readerwriterqueue.h"
#include "iperf_wrapper.h"
#include "endpoint_impl.h"
#include <map>
#include<vector>

using namespace EndPointCtrl;
using namespace moodycamel;
using namespace std;

extern Ice::LoggerPtr g_logger;

class PAIR_CLASS{
public:
    PAIR_CLASS(EndPointCtrl::Pair info);
    ~PAIR_CLASS();
    EndPointCtrl::Pair pairinfo;

    int referenceCount; //引用计数
    
    int e1_status;  //取值为ENDPOINT_STATUS
    int e2_status;  //取值为ENDPOINT_STATUS
    
    ReaderWriterQueue<TmStatsItem> e1_stats_queue;  //ep1的统计队列,这是一个无锁队列，仅iperf线程和主线程可以访问
    ReaderWriterQueue<TmStatsItem> e2_stats_queue; //ep2的统计队列,这是一个无锁队列，仅iperf线程和主线程可以访问


    EndpointThreadPtr e1_perf_thread;
    EndpointThreadPtr e2_perf_thread;
};

extern std::map<string, PAIR_CLASS*> g_pair_map;  //key=uuid
extern std::map<string,std::vector<PAIR_CLASS*>*>  g_e2ctrladdr_pair_map; //key=ctrladdress

PAIR_CLASS* AddPair(EndPointCtrl::Pair pairinfo);
void DelPair(string uuid);

#endif
