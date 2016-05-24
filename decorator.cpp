#include <iostream>
using namespace std;

class IRelay
{
public:
	virtual void On() = 0;
	virtual void Off() = 0;
};

class Relay : public IRelay
{
public:
   Relay() { cout << "Constructor of Relay" << endl; };
	virtual void On();
	virtual void Off();
};

void Relay::On()
{
	cout << "Turn On relay" << endl;
}

void Relay::Off()
{
	cout << "Turn Off relay" << endl;
}

class RelayDecorator : public IRelay
{
	IRelay *next;
public:
   RelayDecorator () {};
   ~RelayDecorator () {};
	RelayDecorator(IRelay *anext) : next(anext) { cout << "Constructor of Relay Decorator" << endl; };
	void On();
	void Off();
};

void RelayDecorator::On()
{
	next->On();
}

void RelayDecorator::Off()
{
	next->Off();
}

class ManagenKitchenWithRelay : public RelayDecorator
{
public:
	ManagenKitchenWithRelay(IRelay *anext) : RelayDecorator(anext) { cout << "Constructor of Kitchen Decorator" << endl; };
	void On();
	void Off();
};

void ManagenKitchenWithRelay::On()
{
	RelayDecorator::On();
	cout << "Turn on the light on the kithen" << endl;
}

void ManagenKitchenWithRelay::Off()
{
	RelayDecorator::Off();
	cout << "Turn off the light on the kithen" << endl;
}

class ManageWCWithRelay : public RelayDecorator
{
public:
	ManageWCWithRelay(IRelay *anext) : RelayDecorator(anext) { cout << "Constructor of WC Decorator" << endl; };
	void On();
	void Off();
};

void ManageWCWithRelay::On()
{
	RelayDecorator::On();
	cout << "Turn on the light in WC" << endl;
}

void ManageWCWithRelay::Off()
{
	RelayDecorator::Off();
	cout << "Turn off the light in WC" << endl;
}

void scenario(IRelay *relay)
{
	relay->On();
	relay->Off();
}

int main(int argc, char const *argv[])
{
	Relay myRoomLight;

//	scenario(&myRoomLight);

	ManagenKitchenWithRelay myKitchenLight(&myRoomLight);
//	scenario(&myKitchenLight);

	ManageWCWithRelay myWCLight(&myKitchenLight);
	scenario(&myWCLight);

	return 0;
}
