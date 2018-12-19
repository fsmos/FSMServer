#ifndef CCKCONFIGSERVICEIMPL_H
#define CCKCONFIGSERVICEIMPL_H
#include <grpcpp/grpcpp.h>
#include "cpp/fsm_cckconfig_service.grpc.pb.h"
extern "C" {
    #include "FSM/FSMDevice/FSM_DeviceProcess.h"
}

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using fsm::CCKConfig;
using fsm::GetDeviceRq;
using fsm::SetDeviceResp;
using fsm::MN401;
using fsm::MN;
using fsm::P0;
using fsm::VirtP0;
using fsm::CCKTypeDevice;
namespace cckconfig
{

class CCKConfigServiceImpl final : public CCKConfig::Service
{
    public:
    CCKConfigServiceImpl();
    ~CCKConfigServiceImpl();
    
    Status GetCfgMN401(ServerContext* context, const GetDeviceRq* request, MN401* reply);
    Status GetCfgMN(ServerContext* context, const GetDeviceRq* request, MN* reply);
    Status GetCfgPO(ServerContext* context, const GetDeviceRq* request, P0* reply);
    Status GetCfgVirtPO(ServerContext* context, const GetDeviceRq* request, VirtP0* reply);
    
    Status SetCfgMN401(ServerContext* context, const MN401* request, SetDeviceResp* reply);
    Status SetCfgMN(ServerContext* context, const MN* request, SetDeviceResp* reply);
    Status SetCfgPO(ServerContext* context, const P0* request, SetDeviceResp* reply);
    Status SetCfgVirtPO(ServerContext* context, const VirtP0* request, SetDeviceResp* reply);
    
    
    

};

}

#endif // CCKCONFIGSERVICEIMPL_H
