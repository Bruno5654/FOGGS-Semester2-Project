#include "HelloGL.h"
#include<ctime>

int main(int argc, char* argv[])
{
	srand(unsigned(time(NULL)));
	HelloGL* game = new HelloGL(argc,argv); //Create an instance of the game.
	
	return 0; //Assume a successful exit if the game exists.
}

