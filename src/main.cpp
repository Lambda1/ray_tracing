#include "./Image.h"

void Program01()
{
	my::Image img{};
	const size_t width = 512;
	const size_t height = 512;
	img.Init(width, height, 3);

	img.Output("./output/program01.png");
}

int main(int argc, char* argv[])
{
	Program01();

	return 0;
}