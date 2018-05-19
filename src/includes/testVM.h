struct Bot;
class World;
class VM;

void comTest_sun(int x, int y, Bot* bot, World world, double* args);
void comTest_move(int x, int y, Bot* bot, World world, double* args);

void comTest_eatCompl(int x, int y, Bot* bot, World world, double* args);
void comTest_eatBot(int x, int y, Bot* bot, World world, double* args);

void comTest_reproduce(int x, int y, Bot* bot, World world, double* args);

void comTest_goto(int x, int y, Bot* bot, World world, double* args);
void comTest_gotoInc(int x, int y, Bot* bot, World world, double* args);

void comTest_moreEnergy(int x, int y, Bot* bot, World world, double* args);
void comTest_lessEnergy(int x, int y, Bot* bot, World world, double* args);

void comTest_ifBotToDir(int x, int y, Bot* bot, World world, double* args);

VM* createTestVM();