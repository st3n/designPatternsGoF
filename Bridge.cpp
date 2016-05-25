#include <iostream>
#include <map>
#include <string>
#include <fstream>

using namespace std;


class ISmartHouseDeviseAPI
{
public:
	virtual void sendCommand(int channel, char* aBuffer) = 0;
	virtual int getStatus(int id) = 0;
	virtual int openChannel(int id) = 0;
	virtual int closeChannel(int channal) = 0;
	virtual ~ISmartHouseDeviseAPI();	
};

class IRelay
{
public:	
	virtual void on() = 0;
	virtual void off() = 0;
	virtual ~IRelay();	
};

class Relay : public IRelay
{
	ISmartHouseDeviseAPI *mImplApi;
	int mAddress;
public:
	Relay(int addr, ISmartHouseDeviseAPI *api);
	~Relay();
	void on();
	void off();
};

Relay::Relay(int address, ISmartHouseDeviseAPI *api) : mImplApi(api), mAddress(address)
{}

void Relay::on()
{
	int channel = mImplApi->openChannel(mAddress);
	mImplApi->sendCommand(channel, "AT 1");
	mImplApi->closeChannel(channel);
}

void Relay::off()
{
	int channel = mImplApi->openChannel(mAddress);
	if (mImplApi->getStatus(channel))
		mImplApi->sendCommand(channel, "AT 0");
	mImplApi->closeChannel(channel);
}

class LikeLinuxDevice : public ISmartHouseDeviseAPI
{
	map<int, fstream*> mDevice;
public:
	LikeLinuxDevice();
	~LikeLinuxDevice() { };
	void sendCommand(int channel, char* aBuffer);
	int getStatsendCommandus(int id);
	int openChannel(int id);
	int closeChannel(int channal);
};

LikeLinuxDevice::sendCommand(int channel, char* aBuffer)
{
	if (mDevice.find(channel) != mDevice.end())
	{
		fstream *device = mDevice.at(channel);
		*device << aBuffer;
	}
}

int LikeLinuxDevice::getStatsendCommandus(int id)
{	
	if (mDevice.find(channel) != mDevice.end())
	{
		fstream *device = mDevice.at(id);
		device->unget();
		int state;
		*device >> state;
		return state;
	}
	return -1;
}

int LikeLinuxDevice::openChannel(int id)
{
	if (mDevice.find(id) != mDevice.end())
	{	
		fstream *device = new fstream("dev-" + to_string(id), fstream::in | fstream::out | fstream::app);
		mDevice.insert(make_paire(id, device));
	}
	return id;
}

int LikeLinuxDevice::closeChannel(int channal)
{
	if (device.find(channal) != mDevice.end())
	{
		fstream *device = mDevice.at(channal);
		device->close();
		device.erase(channal);
	}
}

class DebugDevice : public ISmartHouseDeviseAPI
{
public:
	DebugDevice();
	~DebugDevice();
	void sendCommand(int channel, char* aBuffer);
	int getStatsendCommandus(int id);
	int openChannel(int id);
	int closeChannel(int channal);
};

void DebugDevice:: sendCommand(int channel, char* aBuffer)
{
	cout << "send command : " << channel << " " << aBuffer << endl;
}

int DebugDevice::getStatsendCommandus(int id)
{
	cout << "Get status for device # " << id << endl;
	return 1;
}

int DebugDevice::openChannel(int id)
{
	cout << "Open channal for device # " << id << endl;
	return id;
}
int DebugDevice::closeChannel(int channal)
{
	cout << "Close channal for # " << channal << endl;
}

int main(int argc, char const *argv[])
{
	//if debug include LikeLinuxDevice or DebugDevice.h
	ISmartHouseDeviseAPI *api;

//	#ifndef _DEBUG
		api = new LikeLinuxDevice;
//	#else
//		api = new DebugDevice;

	IRelay *relay = new Relay(2, api);
	relay->on();
	relay->off();

	delete relay;
	delete api;
	return 0;
}