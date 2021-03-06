#include <iostream>
#include <cstdint>
#include <fstream>
#include <gflags/gflags.h>
#include <glog/logging.h>
#include <foo/Foo.hpp>

#include <zlib.h>
#include "msg.pb.h"

void AddMsg(msg::Msg* msgPtr, const std::string& key, std::int32_t value);

int main(int argc, char** argv) {
	FLAGS_logtostderr = true;
	gflags::ParseCommandLineFlags(&argc, &argv, true);
	// Initialize Google's logging library.
  google::InitGoogleLogging(argv[0]);
	foo::helloWorld();
	google::ShutdownGoogleLogging();

	GOOGLE_PROTOBUF_VERIFY_VERSION;
	// Write a Message
	{
		msg::MsgList msgList;
		AddMsg(msgList.add_msgs(), "bar", 3);
		AddMsg(msgList.add_msgs(), "baz", 5);
		AddMsg(msgList.add_msgs(), "bop", 7);
		// Write the new address book back to disk.
		std::fstream out("msg.txt", std::ios::out | std::ios::trunc | std::ios::binary);
		if (!msgList.SerializeToOstream(&out)) {
			std::cerr << "Failed to write /tmp/msg.txt." << std::endl;
			return -1;
		}
	}

	// Read a Message
	{
		msg::MsgList msgList;
		std::fstream in("msg.txt", std::ios::in | std::ios::binary);
		if (!msgList.ParseFromIstream(&in) || msgList.msgs_size() != 3) {
			std::cerr << "Failed to read /tmp/msg.txt." << std::endl;
			return -2;
		}

		for (std::size_t i=0; i < 3; ++i) {
			std::cout << "hello " << msgList.msgs(i).key()
				<< ":" << msgList.msgs(i).value() << std::endl;
		}
	}

	// Optional:  Delete all global objects allocated by libprotobuf.
	google::protobuf::ShutdownProtobufLibrary();

	return 0;
}

void AddMsg(msg::Msg* msgPtr, const std::string& key, std::int32_t value) {
	msgPtr->set_key(key.c_str());
	msgPtr->set_value(value);
}
