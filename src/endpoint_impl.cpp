#include "endpoint_impl.h"
#include "readerwriterqueue.h"
#include "pair.h"
using namespace EndPointCtrl;


QaddPairResult itfEndPointCtrlInt::AddPairs(const ::EndPointCtrl::Qpair&pairlist, const ::Ice::Current&c)
{
    QaddPairResult templist;
    std::map<string,std::vector<PAIR_CLASS*>*> ctrladdr_pair_map;

    //生成pair所需数据结构
    ::EndPointCtrl::Qpair::iterator it;
    for(it=pairlist.begin();it!=pairlist.end();it++){
        PAIR_CLASS*pair=AddPair(*it);
        //保存到全局目的地址map中
        AddPairToCtrlAddrMap(pair,g_e2ctrladdr_pair_map);
        //保存到临时目的地址map中
        AddPairToCtrlAddrMap(pair,ctrladdr_pair_map);
    }

    //通知server侧批量添加iperf
    std::map<string,std::vector<PAIR_CLASS*>*>::iterator ctrladdr_it;
    for(ctrladdr_it=ctrladdr_pair_map.begin();ctrladdr_it!=ctrladdr_pair_map.end();ctrladdr_it++)
    {

        string host=ctrladdr_it->first;
        std::vector<PAIR_CLASS*>*pair_list=ctrladdr_it->second;
        if(pair_list==NULL)continue;
        
    }
    return templist;
}
void itfEndPointCtrlInt::DelPairs(const ::EndPointCtrl::QGetResultUuid&uuidlist, const ::Ice::Current&c)
{
    return ;
}
QpairStatsList itfEndPointCtrlInt::GetResults(const ::EndPointCtrl::QGetResultUuid&uuidlist, const ::Ice::Current&c)
{
    QpairStatsList templist;
    return templist;
}
QaddPairResult itfEndPointCtrlInt::Ep2AddPairs(const ::EndPointCtrl::Qpair&pairlist, const ::Ice::Current&c)
{
    QaddPairResult templist;
    return templist;
}
void itfEndPointCtrlInt::Ep2DelPairs(const ::EndPointCtrl::QGetResultUuid&uuidlist, const ::Ice::Current&c)
{
    return ;
}
QpairStatsList itfEndPointCtrlInt::Ep2GetResults(const ::EndPointCtrl::QGetResultUuid&uuidlist, const ::Ice::Current&c)
{
    QpairStatsList templist;
    return templist;
}

