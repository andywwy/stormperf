
#ifndef _ENDPOINT_IMPL_H_
#define _ENDPOINT_IMPL_H_
#include <endpoint.h>
using namespace EndPointCtrl;

class itfEndPointCtrlInt: public EndPointCtrl::EndPointCtrlInt
{
public:
    virtual ::EndPointCtrl::QaddPairResult AddPairs(const ::EndPointCtrl::Qpair&, const ::Ice::Current& = ::Ice::Current());
    virtual void DelPairs(const ::EndPointCtrl::QGetResultUuid&, const ::Ice::Current& = ::Ice::Current());
    virtual ::EndPointCtrl::QpairStatsList GetResults(const ::EndPointCtrl::QGetResultUuid&, const ::Ice::Current& = ::Ice::Current());
    virtual ::EndPointCtrl::QaddPairResult Ep2AddPairs(const ::EndPointCtrl::Qpair&, const ::Ice::Current& = ::Ice::Current());
    virtual void Ep2DelPairs(const ::EndPointCtrl::QGetResultUuid&, const ::Ice::Current& = ::Ice::Current());
    virtual ::EndPointCtrl::QpairStatsList Ep2GetResults(const ::EndPointCtrl::QGetResultUuid&, const ::Ice::Current& = ::Ice::Current());
};

//iperf线程
class EndpointThread : public IceUtil::Thread{
public:
    int exit_flag;
    EndpointThread();
    ~EndpointThread();
    void run();
    void stop();
private:

};
typedef IceUtil::Handle<EndpointThread> EndpointThreadPtr;

//周期性获取统计信息用线程
class StatsThread : public IceUtil::Thread{
public:
    int exit_flag;
    StatsThread();
    ~StatsThread();
    void run();
    void stop();
private:

};
typedef IceUtil::Handle<StatsThread> StatsThreadPtr;


#endif

