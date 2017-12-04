#include <Ice/Ice.h>
#include <memory>
#include "endpoint_impl.h"

Ice::LoggerPtr g_logger;
class StormPerfService : public Ice::Service 
{
protected:
    virtual bool start(int, char*[], int&) override;
private:
	Ice::ObjectAdapterPtr _adapter;
};
 
bool
StormPerfService::start(int argc, char* argv[], int& status)
{
    g_logger=communicator()->getLogger();
    _adapter = communicator()->createObjectAdapterWithEndpoints("StormPerfService","tcp -p 2051");
    //EndPointCtrl::EndPointCtrlIntPtr coreEpObj = new itfEndPointCtrlInt;
    _adapter->addWithUUID(new itfEndPointCtrlInt);
    _adapter->activate();
    g_logger->print("the service started!");
    status = EXIT_SUCCESS;
    return true;
}
 
int
main(int argc, char* argv[])
{
    StormPerfService svc;
    return svc.main(argc, argv);
}
