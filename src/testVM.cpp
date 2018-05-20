#include "./includes/testVM.h"

#include "./includes/vm.h"
#include "./includes/world.h"
#include "./includes/utils.h"

void comTest_sun(int x, int y, Bot* bot, VM* vm, World* world, double* args) {
	bot->energy += 10;
	setProp(bot, 1, true);
}

void comTest_move(int x, int y, Bot* bot, VM* vm, World* world, double* args) {
	world->moveToDir(x, y, args[0]);
}

void comTest_eatCompl(int x, int y, Bot* bot, VM* vm, World* world, double* args) {
	SimplePoint sp = world->pointFromXYD(x, y, args[0]);
	WorldItem tmp = world->get(sp.x, sp.y);
	if (tmp.type == 2) {
		bot->energy += tmp.proxyPointer;
	}
}

void comTest_eatBot(int x, int y, Bot* bot, VM* vm, World* world, double* args) {
	SimplePoint sp = world->pointFromXYD(x, y, args[0]);
	WorldItem tmp = world->get(sp.x, sp.y);
	if (tmp.type == 1) {
		Bot* tb = (Bot*) tmp.proxyPointer;
		bot->energy += tb->energy / 2;
		world->clear(sp.x, sp.y);
	}
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
	testVM->setCommand(0, Command{comTest_sun       , 0, 0});
	int at1[] = {4};
	testVM->setCommand(1, Command{comTest_move      , 1, initIntMass(1, at1) });
	int at2[] = {4};
	testVM->setCommand(2, Command{comTest_eatCompl  , 1, initIntMass(1, at2) });
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
	return testVM;
};