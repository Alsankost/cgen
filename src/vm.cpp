#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "./includes/vm.h";
#include "./includes/world.h"

const int DEFAULT_COMMANDS_COUNT = 10;
const int DEFAULT_PROG_SIZE = 64;

const int DEFAULT_MAX_ENERGY = 8000;
const int DEFAULT_START_ENERGY = 1000;

double normArgInt(double data) {
	return (int) data;
}

double normArgFloat(double data) {
	return data;
}

double normArgPrc(double data) {
	if (data < 0) {
		return 0;
	}
	if (data > 100) {
		return 100;
	}
	return data;
}

double normArgDir(double data) {
	if (data < 0) {
		return 0;
	}
	if (data > 7) {
		return 7;
	}
	return data;
}

/*Properties:
 0bit - is predator;
 1bit - is chlorophyll;
 2bit - is mineral;
 3bit - is toxic;
*/
void setProp(Bot* bot, int bit, bool state) {
	bot->prop += (2 ^ (bit + 1)) * (state)?1:-1;
}

bool getProp(Bot* bot, int bit) {
	return bot->prop & (2 ^ (bit + 1));
}

VM::VM() {
	this->commands = new Command[commandsCount];
}

VM::VM(int ps) {
	this->progSize = (ps > 0)?ps:DEFAULT_PROG_SIZE;
	VM();
}

VM::VM(int ps, int cc) {
	this->progSize = (ps > 0)?ps:DEFAULT_PROG_SIZE;
	this->commandsCount = (cc > 0)?cc:DEFAULT_COMMANDS_COUNT;
	VM();
}

void VM::setCommand(int id, Command com) {
	if (id < 0 || id >= this->commandsCount || com.execute == 0) return;
	this->commands[id] = com;
}

Command VM::getCommand(int id) {
	if (id < 0 || id >= this->commandsCount) return Command{0, 0, 0};
	return this->commands[id];
}

void VM::setMaxEnergy(int me) {
	this->maxEnergy = me;
}

void VM::setStartEnergy(int se) {
	this->startEnergy = se;
}
		
int VM::getCommandCount() {
	return this->commandsCount;
}

int VM::getProgSize() {
	return this->progSize;
}

void VM::executeBot(int x, int y, Bot* bot, World* world) {
	if (bot->pointer > this->progSize || bot->pointer < 0) bot->pointer = 0;
	CommandItem tmp = bot->prog[bot->pointer];
	commands[tmp.idCommand].execute(x, y, bot, this, world, tmp.args);
	if (bot->energy <= 0) world->set(x, y, 2, 10);
	if (bot->energy >= this->maxEnergy) {
		bool flag = true;
		for (int i = 0; i < 8; i++) {
			if (world->isEmptyToDir(x, y, i)) {
				Bot* tb = createChildBot(bot);
				world->setToDir(x, y, i, 1, (long) tb);
				bot->energy = bot->energy / 2;
				flag = false;
				break;
			}
		}
		if (flag) {
			world->setToPoint(x, y, 2, bot->energy / 4);
		}
	}
}

void VM::executeWorld(World* world) {
	for (int x = 0; x < world->getWidth(); x++) {
		for (int y = 0; y < world->getHeight(); y++) {
			WorldItem tmp = world->get(x, y);
			if (tmp.type == 1) {
				Bot* bot = (Bot*) tmp.proxyPointer;
				this->executeBot(x, y, bot, world);
			}
		}
	}
}

CommandItem VM::createRandomCommandItem(int id) {
	if (id < 0 || id >= this->commandsCount) return CommandItem{-1, 0};
	Command comm = this->commands[id];
	CommandItem tmp;
	tmp.idCommand = id;
	tmp.args = new double[comm.argsCount];
	for (int i = 0; i < comm.argsCount; i++) {
		tmp.args[i] = createRandomArg(comm.argTypes[i]);
	}
	return tmp;
}

double VM::createRandomArg(int type) {
	srand(time(NULL));
	switch (type) {
		case 0:
			return rand();
		case 1:
			return rand() / (rand() / 8.0);
		case 2:
			return rand() % 101;
		case 3:
			return rand() % this->progSize;
		case 4:
			return rand() % 8;
	}
	return 0;
}

Bot* VM::createNewBot() {
	srand(time(NULL));
	Bot* tmp = new Bot;
	tmp->prog = new CommandItem[this->progSize];
	for (int i = 0; i < this->progSize; i++) {
		tmp->prog[i] = this->createRandomCommandItem(rand() % commandsCount);
	}
	tmp->energy = this->startEnergy;
	return tmp;
}

Bot* VM::createChildBot(Bot* bot) {
	Bot* tmp = new Bot;
	for (int i = 0; i < this->progSize; i++) {
		tmp->prog[i] = bot->prog[i];
	}
	srand(time(NULL));
	int tp = rand() % this->progSize;
	tmp->prog[tp] = this->createRandomCommandItem(rand() % commandsCount);
	return tmp;
}