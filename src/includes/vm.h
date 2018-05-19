#define ARG_INT   0;
#define ARG_FLOAT 1;
#define ARG_PRC   2;
#define ARG_COM   3;
#define ARG_DIR   4;

class World;
struct WorldItem;

double normArgInt(double data);
double normArgFloat(double data);
double normArgPrc(double data);
double normArgDir(double data);

struct CommandItem {
	int idCommand;
	double* args;
};

struct Bot {
	CommandItem* prog;
	int pointer;
	int energy;
	int prop;
};

/*Properties:
 0bit - is predator;
 1bit - is chlorophyll;
 2bit - is mineral;
 3bit - is toxic;
*/
void setProp(Bot* bot, int bit, bool state);
bool getProp(Bot* bot, int bit);

struct Command {
	void (*execute)(int, int, Bot*, VM*, World*, double*);
	int argsCount;
	int* argTypes;
};

class VM {
	private:
		Command* commands;
		int commandsCount;
		int progSize;
		int maxEnergy;
		int startEnergy;

	public:
		VM();
		VM(int);
		VM(int, int);

		void    setCommand(int id, Command com);
		Command getCommand(int id);
		
		void setMaxEnergy(int me);
		void setStartEnergy(int se);

		int getCommandCount();
		int getProgSize();

		void executeBot(int x, int y, Bot* bot, World* world);
		void executeWorld(World* world);

		CommandItem createRandomCommandItem(int id);
		double createRandomArg(int type);

		Bot* createNewBot();
		Bot* createChildBot(Bot* bot);
};