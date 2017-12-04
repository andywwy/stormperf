#include "pair.h"
std::map<string, PAIR_CLASS*> g_pair_map;  //key=uuid
std::map<string,std::vector<PAIR_CLASS*>*>  g_e2ctrladdr_pair_map; //key=ctrladdress
std::map<string,std::vector<PAIR_CLASS*>*>  g_e2ctrladdr_pair_map; //key=ctrladdress

//���������Դ
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

//��client�ϴ���pairʱʹ��
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
     
     //�ж�pair�Ƿ��Ѿ������ˣ�����Ѿ����ڣ���ô�ҵ�����ֱ�ӷ��ؼ���
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
    //�ҵ���pair
    pair_map_it=g_pair_map.find(uuid);
    if(pair_map_it==g_pair_map.end())
    {
        g_logger->print("DelPair:can not found the pair of uuid="+uuid);
        return ;
    }
    pair=pair_map_it->second;
    pair->referenceCount--;
    if(pair->referenceCount>0)return;
    
    //ɾ�����Ӧ��g_e2ctrladdr_pair_map�е�����
    ctrladdr_pair_map_it=g_e2ctrladdr_pair_map.find(pair->pairinfo.ep2.ctrlAddr);
    if(ctrladdr_pair_map_it!=g_e2ctrladdr_pair_map.end())
    {
        pair_list=ctrladdr_pair_map_it->second;
        if(NULL!=pair_list)
        {
            //�ҵ���Ӧ��pair,ɾ��
            for(std::vector<PAIR_CLASS*>::iterator list_it=pair_list->begin();list_it!=pair_list->end();list_it++){
                PAIR_CLASS*  temp_pair=*list_it;
                if(temp_pair->pairinfo.uuid==pair->pairinfo.uuid){
					pair_list->erase(list_it);
                    break;
                }
            }
        }
    }

    //ɾ�����Ӧ��g_pair_map�е�����
    g_pair_map.erase(pair_map_it);
    //ɾ��pair
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