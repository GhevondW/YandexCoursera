#ifndef _BASIC_EXAMPLE_H_
#define _BASIC_EXAMPLE_H_

/*the Command interface*/
class Command 
{
public:
	virtual void execute()=0;
};

/*Receiver class*/
class Light {

public:
	Light() {  }

	void turnOn() 
	{
		std::cout << "The light is on" << std::endl;
	}

	void turnOff() 
	{
		std::cout << "The light is off" << std::endl;
	}
};

/*the Command for turning on the light*/
class FlipUpCommand: public Command 
{
public:

	FlipUpCommand(Light& light):theLight(light)
	{

	}

	virtual void execute()
	{
		theLight.turnOn();
	}

private:
	Light& theLight;
};

/*the Command for turning off the light*/
class FlipDownCommand: public Command
{
public:   
	FlipDownCommand(Light& light) :theLight(light)
	{

	}
	virtual void execute() 
	{
		theLight.turnOff();
	}
private:
	Light& theLight;
};

class Switch {
public:
	Switch(Command& flipUpCmd, Command& flipDownCmd)
	:flipUpCommand(flipUpCmd),flipDownCommand(flipDownCmd)
	{

	}

	void flipUp() const
	{
		flipUpCommand.execute();
	}

	void flipDown() const
	{
		flipDownCommand.execute();
	}

private:
	Command& flipUpCommand;
	Command& flipDownCommand;
};

#endif