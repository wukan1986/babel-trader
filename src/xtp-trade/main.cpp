#include <iostream>
#include <functional>
#include <thread>
#include <chrono>

#include "glog/logging.h"

#include "conf.h"
#include "xtp_trade_handler.h"

#if WIN32
#include <windows.h>
#else
#include <sys/stat.h>
#include <sys/types.h>
#endif

#include "common/converter.h"

int main(int argc, char *argv[])
{
	// init glog
	fLI::FLAGS_max_log_size = 100;
	fLI::FLAGS_logbufsecs = 0;
	fLS::FLAGS_log_dir = "./log";
#if WIN32
	CreateDirectoryA("./log/", NULL);
#else
	mkdir("./log/", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif
	google::SetLogDestination(google::GLOG_INFO, "./log/BabelTrader-XTP-Trade.INFO.");
	google::SetLogDestination(google::GLOG_WARNING, "./log/BabelTrader-XTP-Trade.WARNING.");
	google::SetLogDestination(google::GLOG_ERROR, "./log/BabelTrader-XTP-Trade.ERROR.");
	google::InitGoogleLogging(argv[0]);

	// load config
	XTPTradeConf conf;
	auto ret = LoadConfig("./config/xtp_conf.json", conf);
	if (!ret) {
		return -1;
	}

	// run xtp handler
	XTPTradeHandler handler(conf);
	handler.run();

	return 0;
}
