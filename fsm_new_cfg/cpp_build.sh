protoc -I=. --cpp_out=./cpp ./fsm_cckconfig_clientinfo.proto
protoc -I=. --cpp_out=./cpp ./fsm_cckconfig_MN.proto
protoc -I=. --cpp_out=./cpp ./fsm_cckconfig_MN401.proto
protoc -I=. --cpp_out=./cpp ./fsm_cckconfig_PO.proto
protoc -I=. --cpp_out=./cpp ./fsm_cckconfig_VirtPO.proto
protoc -I=. --cpp_out=./cpp ./fsm_cckconfig_service.proto
protoc -I=. --cpp_out=./cpp ./nanopb.proto
protoc -I=. --grpc_out=./cpp --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` ./fsm_cckconfig_service.proto