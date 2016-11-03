#include <node.h>
#include <node_buffer.h>
#include <v8.h>
#include "FSM/FSMDevice/FSMSysCtl.h"
#include "FSM/FSMDevice/FSM_DeviceProcess.h"

struct FSM_SendCmdUserspace fsmdat;
//#include <ArrayBuffer.h>

using namespace v8;

Handle<Value> GetCtl(const Arguments& args) {
 HandleScope scope;
 Handle<Object> ret = Object::New();
 node::Buffer *buf;
 FSM_SendCtlCmd(&fsmdat);
 buf = node::Buffer::New((char *)&fsmdat, sizeof(struct FSM_SendCmdUserspace));
 ret->Set(String::NewSymbol("msg"),buf->handle_);
 return scope.Close(ret);
}


void init(Handle<Object> target) {
  target->Set(String::NewSymbol("GetCtl"), FunctionTemplate::New(GetCtl)->GetFunction());
}

NODE_MODULE(fsmctl, init)