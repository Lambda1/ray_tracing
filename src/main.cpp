#include "./Image.h"

int main(int argc, char* argv[])
{
	my::Image img{512, 512, 3};
	
	img.Output("./output/test.png");

	return 0;
}