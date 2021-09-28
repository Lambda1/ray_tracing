#include "./Image.h"

int main(int argc, char* argv[])
{
	my::Image img{};

	img.Init(512, 512, 3);

	img.WritePixel(256, 256, 1.0f, 1.0f, 1.0f);

	img.Output("./output/test.png");

	return 0;
}