#include "CCKConfigServiceImpl.h"
#include <fstream>

using namespace std;
using namespace cckconfig;

CCKConfigServiceImpl::CCKConfigServiceImpl()
{
}

CCKConfigServiceImpl::~CCKConfigServiceImpl()
{
}

Status CCKConfigServiceImpl::GetCfgMN401(ServerContext* context, const GetDeviceRq* request, MN401* reply)
{
    char position[20];
    struct CCKDeviceInfo CCKDev[FSM_CCKTreeSize];
    memset(position,CCKTypeDevice::DT_None,20);
    FSM_CCK_Get_Data(CCKDev);
    for(int i=0;i<FSM_CCKTreeSize;i++) {
        if(CCKDev[i].type != 0)
            position[CCKDev[i].Position] = CCKDev[i].type;
    }
    position[9] = (char)CCKTypeDevice::DT_MN401;
    for(int i=0;i<20;i++) {
       reply->add_devlist((fsm::CCKTypeDevice)position[i]); 
    }
     //0
  /*  reply->add_devlist(CCKTypeDevice::DT_MN921); //1
    reply->add_devlist(CCKTypeDevice::DT_MN825); //2
    reply->add_devlist(CCKTypeDevice::DT_MN825); //3
    reply->add_devlist(CCKTypeDevice::DT_None); //4
    reply->add_devlist(CCKTypeDevice::DT_None); //5
    reply->add_devlist(CCKTypeDevice::DT_None); //6
    reply->add_devlist(CCKTypeDevice::DT_None); //7
    reply->add_devlist(CCKTypeDevice::DT_MN524); //8
    reply->add_devlist(CCKTypeDevice::DT_MN401); //9
    
    reply->add_devlist(CCKTypeDevice::DT_PO06);  //10
    reply->add_devlist(CCKTypeDevice::DT_PO07); //11
    reply->add_devlist(CCKTypeDevice::DT_PO08); //12
    reply->add_devlist(CCKTypeDevice::DT_VirtPO); //13
    reply->add_devlist(CCKTypeDevice::DT_None); //14
    reply->add_devlist(CCKTypeDevice::DT_None); //15
    reply->add_devlist(CCKTypeDevice::DT_None); //16
    reply->add_devlist(CCKTypeDevice::DT_None); //17
    reply->add_devlist(CCKTypeDevice::DT_None); //18
    reply->add_devlist(CCKTypeDevice::DT_None); //19
    */
    return Status::OK;
}

Status CCKConfigServiceImpl::GetCfgMN(ServerContext* context, const GetDeviceRq* request, MN* reply)
{
    int imgid = request->id();
    fstream input(string("fsmcfg_") + std::to_string(imgid) + string("_mn"), ios::in | ios::binary);
    reply->ParseFromIstream(&input);
    return Status::OK;
}

Status CCKConfigServiceImpl::GetCfgPO(ServerContext* context, const GetDeviceRq* request, P0* reply)
{
    int imgid = request->id();
    fstream input(string("fsmcfg_") + std::to_string(imgid) + string("_po"), ios::in | ios::binary);
    reply->ParseFromIstream(&input);
    return Status::OK;
}

Status CCKConfigServiceImpl::GetCfgVirtPO(ServerContext* context, const GetDeviceRq* request, VirtP0* reply)
{
    int imgid = request->id();
    fstream input(string("fsmcfg_") + std::to_string(imgid) + string("_virtpo"), ios::in | ios::binary);
    reply->ParseFromIstream(&input);
    return Status::OK;
}

    
Status CCKConfigServiceImpl::SetCfgMN401(ServerContext* context, const MN401* request, SetDeviceResp* reply)
{
    return Status::OK;
}

Status CCKConfigServiceImpl::SetCfgMN(ServerContext* context, const MN* request, SetDeviceResp* reply)
{
    int imgid = request->client().id();
    fstream output(string("fsmcfg_") + std::to_string(imgid) + string("_mn"), ios::out | ios::trunc | ios::binary);
    request->SerializePartialToOstream(&output);
    reply->set_status(200);
    return Status::OK;
}


Status CCKConfigServiceImpl::SetCfgPO(ServerContext* context, const P0* request, SetDeviceResp* reply)
{
    int imgid = request->client().id();
    fstream output(string("fsmcfg_") + std::to_string(imgid) + string("_po"), ios::out | ios::trunc | ios::binary);
    request->SerializePartialToOstream(&output);
    reply->set_status(200);
    return Status::OK;
}

Status CCKConfigServiceImpl::SetCfgVirtPO(ServerContext* context, const VirtP0* request, SetDeviceResp* reply)
{
    int imgid = request->client().id();
    fstream output(string("fsmcfg_") + std::to_string(imgid) + string("_virtpo"), ios::out | ios::trunc | ios::binary);
    request->SerializePartialToOstream(&output);
    reply->set_status(200);
    return Status::OK;
}
