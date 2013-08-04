#ifndef BASE_COMMAND_H
#define BASE_COMMAND_H
class BaseCommand
{
public:
	enum CommandType
	{
		NOTYPE=0,
		OSTU=1,
		WAVE_FILTER,
		DICE_PAINT
	};

	BaseCommand();
	~BaseCommand();
	virtual void RunCommand(){};
	CommandType GetType(){return type_;};
protected:
	CommandType type_;
	void CommandOver();
private:
	BaseCommand(BaseCommand&b);
	BaseCommand &operator=(const BaseCommand & b);
};

#endif