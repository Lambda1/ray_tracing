#include "./Image.h"
#include "../glm/glm/vec3.hpp"
#include "./Ball.h"

void HiddenSurfaceErasure()
{
	my::Image img{};
	const size_t width = 512;
	const size_t height = 512;
	img.Init(width, height, 3);

	glm::vec3 eye{ 0.0f, 0.0f, 1.0f };

	my::Ball ball{ 0.0f, 0.0f, 100.0f, 100.0f };

	const int S = 199;
	for (int i = S; i > -S; --i)
	{
		for (int j = -S; j < S; ++j)
		{
			const float val = ball.RayCast(glm::vec3{ j, i, 0 }, eye);
			if (val >= 0)
			{
				img.WritePixel(j + S, i + S, 1.0f, 0.0f, 0.0f);
			}
		}
	}

	img.Output("./output/program01.png");
}

int main(int argc, char* argv[])
{
	HiddenSurfaceErasure();

	return 0;
}