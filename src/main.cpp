#include "./Image.h"
#include "./Ball.h"

#include "../glm/glm/glm.hpp"
#include "../glm/glm/vec3.hpp"

void HiddenSurfaceErasure(my::Image& img)
{
	glm::vec3 eye{ 0.0f, 0.0f, 1.0f }; // 視線ベクトル
	my::Ball ball{ 0.0f, 0.0f, 100.0f, 100.0f }; // 球

	// スクリーンサイズ
	const int s_h_div2 = img.GetHeight() / 2;
	const int s_w_div2 = img.GetWidth() / 2;
	for (int i = -s_h_div2; i < s_h_div2; ++i)
	{
		for (int j = -s_w_div2; j < s_w_div2; ++j)
		{
			const float x = j;
			const float y = -i;

			const float t = ball.RayCast(glm::vec3{ x, y, 0.0f }, eye);
			if (t == 1e5f) { continue; } // 解なし

			img.WritePixel(j + s_w_div2, -i + s_h_div2, 1.0f, 0.0f, 0.0f);
		}
	}

	img.Output("./output/001_HiddenSurfaceErasure.png");
}

void Shading(my::Image& img, const bool& ambient_flag)
{
	const glm::vec3 eye{ 0.0f, 0.0f, 1.0f }; // 視線ベクトル

	my::Ball ball{ 0.0f, 0.0f, 100.0f, 100.0f }; // 球
	ball.SetLuminance(glm::vec3{ 1.0f, 0.f, 0.f });

	const glm::vec3 light{ -1.0f, 1.0f, -1.0f }; // 光源ベクトル
	const glm::vec3 i_p{ 1.0f, 1.0f, 1.0f }; // 光源強度(白色)

	const glm::vec3 light_n = glm::normalize(light);

	glm::vec3 i_a = !ambient_flag ? glm::vec3{ 0.0f, 0.0f, 0.0f } : glm::vec3{ 0.2f, 0.2f, 0.2f };

	// スクリーンサイズ
	const int s_h_div2 = img.GetHeight() / 2;
	const int s_w_div2 = img.GetWidth() / 2;
	for (int i = -s_h_div2; i < s_h_div2; ++i)
	{
		for (int j = -s_w_div2; j < s_w_div2; ++j)
		{
			const float x = j;
			const float y = -i;

			const float t = ball.RayCast(glm::vec3{ x, y, 0.0f }, eye);
			if (t == 1e5f) { continue; } // 解なし

			const glm::vec3 normal = glm::normalize(glm::vec3{ j, i, t - ball.GetCenter().z });
			float ln = glm::dot(light_n, normal);
			float ln2 = glm::dot(-light_n, normal);
			ln2 = 0.0f; // (2個目の光源を消しておく: メモとして残してるだけ)
			glm::vec3 i_d = { 0.0f, 0.0f, 0.0f };
			
			// ln <  0.0f: 面の裏から光線 (影)
			// ln >= 0.0f: 面の表から光線 (反射)
			if (ln < 0.0f)
			{
				ln = 0.0f;
			}
			i_d = ball.GetLuminance() * ((i_p * ln + glm::vec3{1.0f, 0.0f, 1.0f} * ln2) + i_a);
			
			img.WritePixel(j + s_w_div2, -i + s_h_div2, i_d.r, i_d.g, i_d.b);
		}
	}

	if (!ambient_flag)
		img.Output("./output/002_Shading.png");
	else
		img.Output("./output/003_Shading_ambient.png");
}

int main(int argc, char* argv[])
{
	my::Image img{};
	const size_t width = 512;
	const size_t height = 512;
	img.Init(width, height, 3);

	//HiddenSurfaceErasure(img);
	Shading(img, false);

	return 0;
}