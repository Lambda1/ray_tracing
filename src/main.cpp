#include "./Image.h"
#include "../glm/glm/vec3.hpp"
#include "./Ball.h"

void HiddenSurfaceErasure()
{
	my::Image img{};
	const size_t width = 512;
	const size_t height = 512;
	img.Init(width, height, 3);

	glm::vec3 eye{ 0.0f, 0.0f, 1.0f }; // 視線ベクトル
	my::Ball ball{ 0.0f, 0.0f, 1.0f, 0.5f }; // 球

	// スクリーンサイズ
	const int s_h = height / 2; // [-1.0, 1.0]
	const int s_w = width / 2;  // [-1.0, 1.0]
	for (int i = -s_h; i < s_h; ++i)
	{
		for (int j = -s_w; j < s_w; ++j)
		{
			const float x = j / static_cast<float>(s_w);
			const float y = i / static_cast<float>(s_h);
			if (ball.RayCast(glm::vec3{x, y, 0.0f}, eye) != 0.0f)
			{
				img.WritePixel(j + s_w, i + s_h, 1.0f, 0.0f, 0.0f);
			}
		}
	}

	img.Output("./output/001_HiddenSurfaceErasure.png");
}

int main(int argc, char* argv[])
{
	HiddenSurfaceErasure();

	return 0;
}