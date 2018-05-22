#include "./includes/testVM.h"
#include "./includes/vm.h"
#include "./includes/world.h"
#include "./includes/utils.h"

#include <stdio.h>
#include <iostream>

using namespace std;

void comTest_sun(int x, int y, Bot* bot, VM* vm, World* world, double* args) {
	bot->energy += 10;
	setProp(bot, 1, true);
}

void comTest_move(int x, int y, Bot* bot, VM* vm, World* world, double* args) {
	world->moveToDir(x, y, args[0]);
	bot->energy -= 10;
}

void comTest_eatCompl(int x, int y, Bot* bot, VM* vm, World* world, double* args) {
	SimplePoint sp = world->pointFromXYD(x, y, args[0]);
	WorldItem tmp = world->get(sp.x, sp.y);
	if (tmp.type == 2) {
		bot->energy += (int) tmp.proxyPointer;
	}
}

void comTest_eatBot(int x, int y, Bot* bot, VM* vm, World* world, double* args) {
	cout << "T1 \n";
	SimplePoint sp = world->pointFromXYD(x, y, args[0]);
	cout << "T2 \n";
	WorldItem tmp = world->get(sp.x, sp.y);
	cout << "T3 \n";
	if (tmp.type == 1) {
		Bot* tb = (Bot*) tmp.proxyPointer;
		bot->energy += tb->energy / 6;
		world->clear(sp.x, sp.y);
		setProp(bot, 1, true);
	}
	cout << "T4 \n";
}

void comTest_reproduce(int x, int y, Bot* bot, VM* vm, World* world, double* args) {
	SimplePoint sp = world->pointFromXYD(x, y, args[0]);
	WorldItem tmp = world->get(sp.x, sp.y);
	if (tmp.type == 0) {
		Bot* tb = vm->createChildBot(bot);
		world->setToDir(sp.x, sp.y, args[0], 1, (long) tb);
		bot->energy -= bot->energy / 2;
	}
}

void comTest_goto(int x, int y, Bot* bot, VM* vm, World* world, double* args) {
	bot->pointer = args[0];
}

void comTest_gotoInc(int x, int y, Bot* bot, VM* vm, World* world, double* args) {
	bot->pointer += args[0];
}

void comTest_moreEnergy(int x, int y, Bot* bot, VM* vm, World* world, double* args) {
	if (bot->pointer > ((int) args[0]) % vm->getProgSize()) bot->pointer += args[1];
}

void comTest_lessEnergy(int x, int y, Bot* bot, VM* vm, World* world, double* args) {
	if (bot->pointer < ((int) args[0]) % vm->getProgSize()) bot->pointer += args[1];
}

void comTest_ifBotToDir(int x, int y, Bot* bot, VM* vm, World* world, double* args) {
	SimplePoint sp = world->pointFromXYD(x, y, args[0]);
	if (world->get(x, y).type == 1) bot->pointer += args[1];
}

VM* createTestVM() {
	VM* testVM = new VM(0, 10);
	testVM->setCommand(0, Command{comTest_sun       , 0, new int[1]});
	int at1[] = {4};
	testVM->setCommand(1, Command{comTest_move      , 1, initIntMass(1, at1) }); cout << " # С2\n";
	int at2[] = {4};
	testVM->setCommand(2, Command{comTest_eatCompl  , 1, initIntMass(1, at2) }); cout << " # С3\n";
	int at3[] = {4};
	testVM->setCommand(3, Command{comTest_eatBot    , 1, initIntMass(1, at3) });
	int at4[] = {4};
	testVM->setCommand(4, Command{comTest_reproduce , 1, initIntMass(1, at4) });
	int at5[] = {3};
	testVM->setCommand(5, Command{comTest_goto      , 1, initIntMass(1, at5) });
	int at6[] = {3};
	testVM->setCommand(6, Command{comTest_gotoInc   , 1, initIntMass(1, at6) });
	int at7[] = {1, 3};
	testVM->setCommand(7, Command{comTest_moreEnergy, 2, initIntMass(2, at7) });
	int at8[] = {1, 3};
	testVM->setCommand(8, Command{comTest_lessEnergy, 2, initIntMass(2, at8) });
	int at9[] = {4, 3};
	testVM->setCommand(9, Command{comTest_ifBotToDir, 2, initIntMass(2, at9) });

	testVM->setMaxEnergy(2000);
	testVM->setStartEnergy(300);
	cout << " # Register commands - OK\n";

	return testVM;
};

Bot* createFirsBot(VM* vm) {
	Bot* firstBot = vm->createNewBot();
	CommandItem c = CommandItem{0, new double[0]};
	firstBot->prog[0] = c;
	c = CommandItem{2, new double[1]};
	c.args[0] = 0;
	firstBot->prog[1] = c;
	c = CommandItem{2, new double[1]};
	c.args[0] = 1;
	firstBot->prog[2] = c;
	c = CommandItem{2, new double[1]};
	c.args[0] = 2;
	firstBot->prog[3] = c;
	c = CommandItem{2, new double[1]};
	c.args[0] = 3;
	firstBot->prog[4] = c;
	c = CommandItem{2, new double[1]};
	c.args[0] = 4;
	firstBot->prog[5] = c;
	c = CommandItem{2, new double[1]};
	c.args[0] = 5;
	firstBot->prog[6] = c;
	c = CommandItem{2, new double[1]};
	c.args[0] = 6;
	firstBot->prog[7] = c;
	c = CommandItem{2, new double[1]};
	c.args[0] = 7;
	firstBot->prog[8] = c;
	c = CommandItem{0, new double[0]};
	firstBot->prog[9] = c;
	c = CommandItem{0, new double[0]};
	firstBot->prog[10] = c;
	c = CommandItem{0, new double[0]};
	firstBot->prog[11] = c;
	c = CommandItem{0, new double[0]};
	firstBot->prog[12] = c;
	c = CommandItem{5, new double[1]};
	c.args[0] = 64;
	firstBot->prog[13] = c;
	c = CommandItem{5, new double[1]};
	c.args[0] = 0;
	firstBot->prog[14] = c;
	c = CommandItem{5, new double[1]};
	c.args[0] = 2;
	firstBot->prog[15] = c;
	return firstBot;
}