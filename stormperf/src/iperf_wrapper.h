#ifndef __IPERF_WRAPPER_H__
#define __IPERF_WRAPPER_H__

//¶¨Òåendpoint×´Ì¬
typedef enum _ENDPOINT_STATUS{
    ENDPOINT_STATUS_IDLE=0,
    ENDPOINT_STATUS_INIT,
    ENDPOINT_STATUS_RUNNING,
    ENDPOINT_STATUS_TERMINAL,
    ENDPOINT_STATUS_FINISH
}ENDPOINT_STATUS;

typedef struct _TmStatsItem{
    double timestamp;
    
}TmStatsItem;
#endif
