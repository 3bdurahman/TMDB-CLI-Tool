#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/URI.h>
#include <Poco/StreamCopier.h>
#include <Poco/JSON/Array.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>
#include <iostream>
#include <fmt/core.h>
#include <fmt/color.h>
#include <fmt/format.h>
#include <fstream>

using namespace std;
using namespace Poco;
using namespace Poco::JSON;
using namespace Poco::Net;


extern string ParserJson(const string&& response);
extern string GetResponse(const char* type);