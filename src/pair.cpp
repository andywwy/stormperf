#include "pair.h"
std::map<string, PAIR_CLASS*> g_pair_map;  //key=uuid
std::map<string,std::vector<PAIR_CLASS*>*>  g_e2ctrladdr_pair_map; //key=ctrladdress
std::map<string,std::vector<PAIR_CLASS*>*>  g_e2ctrladdr_pair_map; //key=ctrladdress

//清空所有资源
void FreeAllPairs()
{
    std::map<string,std::vector<PAIR_CLASS*>*>::iterator ctrladdr_pair_map_it;
    for(ctrladdr_pair_map_it=g_e2ctrladdr_pair_map.begin();ctrladdr_pair_map_it!=g_e2ctrladdr_pair_map.end();ctrladdr_pair_map_it++)
    {

        std::vector<PAIR_CLASS*>*pair_list=ctrladdr_pair_map_it->second;
        delete pair_list;
    }
    g_e2ctrladdr_pair_map.clear();

    std::map<string, PAIR_CLASS*>::iterator pair_map_it;
    for(pair_map_it=g_pair_map.begin();pair_map_it!=g_pair_map.end();pair_map_it++)
    {
        PAIR_CLASS*pair=pair_map_it->second;
        delete pair;
    }
    g_pair_map.clear();
}

//在client上创建pair时使用
void AddPairToCtrlAddrMap(PAIR_CLASS* pair, std::map<string,std::vector<PAIR_CLASS*>*>&ctrladdr_pair_map)
{
    std::map<string,std::vector<PAIR_CLASS*>*>::iterator ctrladdr_pair_map_it;
    std::vector<PAIR_CLASS*>* pair_list=NULL;

    ctrladdr_pair_map_it=ctrladdr_pair_map.find(pair->pairinfo.ep2.ctrlAddr);
    if(ctrladdr_pair_map_it==ctrladdr_pair_map.end())
    {
        pair_list=new std::vector<PAIR_CLASS*>();
        ctrladdr_pair_map.insert(map<string, std::vector<PAIR_CLASS*>*> ::value_type(pair->pairinfo.ep2.ctrlAddr,pair_list));
    }
    else
    {
        pair_list=ctrladdr_pair_map_it->second;
    }
    pair_list->push_back(pair);
    
}

PAIR_CLASS* AddPair(EndPointCtrl::Pair pairinfo)
{
     std::map<string, PAIR_CLASS*>::iterator pair_map_it;
     PAIR_CLASS* pair=NULL;
     
     //判断pair是否已经存在了，如果已经存在，那么找到它，直接返回即可
    pair_map_it=g_pair_map.find(pairinfo.uuid);
    if(pair_map_it!=g_pair_map.end())
    {
        pair=pair_map_it->second;
        pair->referenceCount++;
        return pair;
    }
    
    pair=new PAIR_CLASS(pairinfo);
    g_pair_map.insert(map<string, PAIR_CLASS*>::value_type(pairinfo.uuid,pair));

    return pair;
}
void DelPair(string uuid)
{
     std::map<std::string, PAIR_CLASS*>::iterator pair_map_it;
     std::map<std::string,std::vector<PAIR_CLASS*>*>::iterator ctrladdr_pair_map_it;
     PAIR_CLASS* pair=NULL;
     std::vector<PAIR_CLASS*>* pair_list=NULL;
    //找到该pair
    pair_map_it=g_pair_map.find(uuid);
    if(pair_map_it==g_pair_map.end())
    {
        g_logger->print("DelPair:can not found the pair of uuid="+uuid);
        return ;
    }
    pair=pair_map_it->second;
    pair->referenceCount--;
    if(pair->referenceCount>0)return;
    
    //删除其对应的g_e2ctrladdr_pair_map中的数据
    ctrladdr_pair_map_it=g_e2ctrladdr_pair_map.find(pair->pairinfo.ep2.ctrlAddr);
    if(ctrladdr_pair_map_it!=g_e2ctrladdr_pair_map.end())
    {
        pair_list=ctrladdr_pair_map_it->second;
        if(NULL!=pair_list)
        {
            //找到对应的pair,删除
            for(std::vector<PAIR_CLASS*>::iterator list_it=pair_list->begin();list_it!=pair_list->end();list_it++){
                PAIR_CLASS*  temp_pair=*list_it;
                if(temp_pair->pairinfo.uuid==pair->pairinfo.uuid){
					pair_list->erase(list_it);
                    break;
                }
            }
        }
    }

    //删除其对应的g_pair_map中的数据
    g_pair_map.erase(pair_map_it);
    //删除pair
    delete pair;
}

PAIR_CLASS::PAIR_CLASS(EndPointCtrl::Pair info)
{
    this->pairinfo=info;
    referenceCount=0;
    e1_status=ENDPOINT_STATUS_IDLE;
    e2_status=ENDPOINT_STATUS_IDLE;
    e1_perf_thread=NULL;
    e2_perf_thread=NULL;
}
PAIR_CLASS::~PAIR_CLASS()
{
}