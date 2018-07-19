#include "stdafx.h"

#include <iostream>
#include <map>
#include <string>
#include <iostream>


//
// supporting tools and software
//
// Validate and test your json commands
// https://jsonlint.com/

// RapidJSON : lots and lots of examples to help you use it properly
// https://github.com/Tencent/rapidjson
//

// std::function
// std::bind
// std::placeholders
// std::map
// std::make_pair

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace rapidjson;
using namespace std;

bool g_done = false;


//
// TEST COMMANDS 
//

// I used these as prebuilts to simplify sending the payloads
auto help_command = R"(
 {
  "command":"help",
  "payload": {
    "usage":"Enter json command in 'command':'<command>','payload': { // json payload of arguments }"
  }
 }
)";					//There was a comma at the end of the usage that made it invalid json

auto exit_command = R"(
 {
  "command":"exit",
  "payload": {
     "reason":"Exiting program on user request."
  }
 }
)";

auto sendstring_command = R"(
 {
  "command":"sendstring",
  "payload": {
     "string":"Teststring"
  }
 }
)";

auto sendbool_command = R"(
 {
  "command":"sendbool",
  "payload": {
     "bool":"true"
  }
 }
)";

auto sendnumber_command = R"(
 {
  "command":"sendnumber",
  "payload": {
     "number":"12345"
  }
 }
)";

auto sendarray_command = R"(
 {
  "command":"sendarray",
  "payload": {
     "array":"[0,1,2,3,4]"
  }
 }
)";
class Controller {
public:
	bool help(rapidjson::Value &payload)
	{
		cout << "Controller::help: command: ";

		rapidjson::Document doc;						//initalize Document
		doc.Parse(help_command);
														//We do not adjust the help payload

		rapidjson::StringBuffer buffer;					//initalize writer
		rapidjson::Writer<StringBuffer> w(buffer);
		doc.Accept(w);

		std::cout << buffer.GetString() << std::endl;  //send json in this case to the terminal

        return true;
    }

    bool exit(rapidjson::Value &payload)
    {
        cout << "Controller::exit: command: \n";

		assert(payload.IsString());						//check for correct payload

		rapidjson::Document doc;						//initalize Document
		doc.Parse(exit_command);
														//do not modify payload

		rapidjson::StringBuffer buffer;					//initalize writer
		rapidjson::Writer<StringBuffer> w(buffer);
		doc.Accept(w);

		std::cout << buffer.GetString() << std::endl;  //send json in this case to the terminal

		g_done = true;									// set g_done to exit the program

        return true;
    }

	bool sendstring(rapidjson::Value &payload)
	{
		cout << "Controller::sendstring: command: \n";

		assert(payload.IsString());						//check for correct payload

		rapidjson::Document doc;						//initalize Document
		doc.Parse(sendstring_command);

		Value& v = doc["payload"];						//load the payload
		v["string"] = payload;

		rapidjson::StringBuffer buffer;					//initalize writer
		rapidjson::Writer<StringBuffer> w(buffer);
		doc.Accept(w);

		std::cout << buffer.GetString() << std::endl;  //send json in this case to the terminal

		return true;
	}

	bool sendbool(rapidjson::Value &payload)
	{
		cout << "Controller::sendbool: command: \n";

		assert(payload.IsBool());						//check for correct payload

		rapidjson::Document doc;						//initalize Document
		doc.Parse(sendbool_command);

		Value& v = doc["payload"];						//load the payload
		v["bool"] = payload;

		rapidjson::StringBuffer buffer;					//initalize writer
		rapidjson::Writer<StringBuffer> w(buffer);
		doc.Accept(w);

		std::cout << buffer.GetString() << std::endl;  //send json in this case to the terminal
	
		return true;
	}

	bool sendnumber(rapidjson::Value &payload)
	{
		cout << "Controller::sendnumber: command: \n";

		assert(payload.IsNumber());						//check for correct payload

		rapidjson::Document doc;						//initalize Document
		doc.Parse(sendnumber_command);

		Value& v = doc["payload"];						//load the payload
		v["number"] = payload;

		rapidjson::StringBuffer buffer;					//initalize writer
		rapidjson::Writer<StringBuffer> w(buffer);
		doc.Accept(w);

		std::cout << buffer.GetString() << std::endl;  //send json in this case to the terminal

		return true;
	}

	bool sendarray(rapidjson::Value &payload)
	{
		cout << "Controller::sendarray: command: \n";

		assert(payload.IsArray());						//check for correct payload

		rapidjson::Document doc;						//initalize Document
		doc.Parse(sendstring_command);

		Value& v = doc["payload"];						//load the payload
		v["array"] = payload;

		rapidjson::StringBuffer buffer;					//initalize writer
		rapidjson::Writer<StringBuffer> w(buffer);
		doc.Accept(w);

		std::cout << buffer.GetString() << std::endl;  //send json in this case to the terminal

		return true;
	}

    // implement 3-4 more commands
};

// gimme ... this is actually tricky
// Bonus Question: why did I type cast this? 
//To attempt this the CommandHandler type is a pointer to a function that returns the bool and
// takes in a value &. I expect this is so that the controller function commands get turned into 
// CommandHandler types

//Apparently Visual studios does not support this feature or at least I can't find how to turn it on. Which is very annoying
//I can't compile this and don't have time to switch enviroments
typedef std::function<bool(rapidjson::Value &)> CommandHandler;


class CommandDispatcher {
public:
    // ctor - need impl
    CommandDispatcher()
    {
		command_handlers_ = new std::map<std::string, CommandHandler>;
    }

    // dtor - need impl
    virtual ~CommandDispatcher()
    {
        // question why is it virtual? Is it needed in this case?
		// With the dtor being virtual it suggests that commandDispatcher will undergo polymorpism.
		// It being virtual will allow calling whatever dtor that it morphed into.
		delete &command_handlers_;
    }

    bool addCommandHandler(std::string command, CommandHandler handler)
    {
        cout << "CommandDispatcher: addCommandHandler: " << command << std::endl;

		command_handlers_.insert_or_assign(command, handler);

        return true;
    }

	bool dispatchCommand(std::string command_json, rapidjson::Value &payload)
	{
		cout << "COMMAND: " << command_json << endl;

		auto item = command_handlers_.find(command_json);
		if (item != command_handlers_.end())  //check if command was found
		{
			if (!item->second(payload)) //if the command fails return false
				return false;
		}
		else
			return false;				//command not found

        return true;					//command sent
    }

private:

    // gimme ...
    std::map<std::string, CommandHandler> command_handlers_;

    // another gimme ...
    // Question: why delete these?

	//To prevent anything from reasigning or coyping the Command dispatcher. To insure that each instance of the object is unique

    // delete unused constructors
    CommandDispatcher (const CommandDispatcher&) = delete;
    CommandDispatcher& operator= (const CommandDispatcher&) = delete;

};

int main()
{
    std::cout << "COMMAND DISPATCHER: STARTED" << std::endl;

    CommandDispatcher command_dispatcher;
    Controller controller;                 // controller class of functions to "dispatch" from Command Dispatcher

    // Implement
    // add command handlers in Controller class to CommandDispatcher using addCommandHandler
	CommandHandler hand1 = std::bind(controller.help, std::placeholders::_1);				//I have no way to check if that is the correct way to assign the handlers as I can't compile
	command_dispatcher.addCommandHandler("help", hand1);

	CommandHandler hand2 = std::bind(controller.exit, std::placeholders::_1);
	command_dispatcher.addCommandHandler("exit", hand2);

	CommandHandler hand3 = std::bind(controller.sendstring, std::placeholders::_1);
	command_dispatcher.addCommandHandler("sendstring", hand3);

	CommandHandler hand4 = std::bind(controller.sendbool, std::placeholders::_1);
	command_dispatcher.addCommandHandler("sendbool", hand4);

	CommandHandler hand5 = std::bind(controller.sendnumber, std::placeholders::_1);
	command_dispatcher.addCommandHandler("sendnumber", hand5);

	CommandHandler hand6 = std::bind(controller.sendarray, std::placeholders::_1);
	command_dispatcher.addCommandHandler("sendarray", hand6);



    // gimme ...
    // command line interface
    string command;
	string payload;
	rapidjson::Document doc;

    while( ! g_done ) {
        cout << "COMMANDS: {\"help\":\"exit\":\"sendstring\":\"sendbool\":\"sendnumber\":\"sendarray\"}\n";
        cout << "\tenter command : ";
        getline(cin, command);
		cout << "payload\":{\"reason\":\"User requested exit.\"}:{\"string\":\"TestString.\"}";
		cout << ":{\"bool\":\"true\"}:{\"number\":\"12345.\"}:{\"array\":\"[0,1,2,3,4,5]\"}}\n";
		cout << "\n\tenter payload : ";
		getline(cin, payload);
		doc.Parse(payload.c_str());
		
        command_dispatcher.dispatchCommand(command, doc[0] );
    }

    std::cout << "COMMAND DISPATCHER: ENDED" << std::endl;
    return 0;
}