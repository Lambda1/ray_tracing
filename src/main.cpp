#include "./Image.h"

int main(int argc, char* argv[])
{
	my::Image img{};

	img.Init(32, 32, 3);
	img.Write("./test.png");

	return 0;
}