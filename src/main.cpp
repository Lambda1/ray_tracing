#include <vector>

#include "./Image.h"
#include "./Ball.h"
#include "./Plane.h"

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
			i_d = ball.GetLuminance() * ((i_p * ln + glm::vec3{ 1.0f, 0.0f, 1.0f } *ln2) + i_a);

			img.WritePixel(j + s_w_div2, -i + s_h_div2, i_d.r, i_d.g, i_d.b);
		}
	}

	if (!ambient_flag)
		img.Output("./output/002_Shading.png");
	else
		img.Output("./output/003_Shading_ambient.png");
}

void Perspective(my::Image& img)
{
	// 球定義
	std::vector<my::Shape*> balls;
	// 球1
	balls.emplace_back(new my::Ball{ 0.0f, 0.0f, 100.0f, 100.0f });
	balls[0]->SetLuminance(glm::vec3{ 1.0f, 0.0f, 0.0f });
	// 球2
	balls.emplace_back(new my::Ball{ 200.0f, 0.0f, 200.0f, 100.0f });
	balls[1]->SetLuminance(glm::vec3{ 0.0f, 1.0f, 0.0f });
	// 球3
	balls.emplace_back(new my::Ball{ -200.0f, 0.0f, 300.0f, 100.0f });
	balls[2]->SetLuminance(glm::vec3{ 0.0f, 0.0f, 1.0f });

	// 光源定義
	const glm::vec3 light{ -1.0f, 1.0f, -1.0f }; // 光源ベクトル
	const glm::vec3 i_p{ 1.0f, 1.0f, 1.0f }; // 光源強度(白色)
	glm::vec3 i_a = glm::vec3{ 0.2f, 0.2f, 0.2f }; // 環境光

	const glm::vec3 light_n = glm::normalize(light);

	// 視点位置
	const glm::vec3 eye_v = glm::vec3{0.0f, 0.0f, -300.0f};

	// スクリーンサイズ
	const int s_h_div2 = img.GetHeight() / 2;
	const int s_w_div2 = img.GetWidth() / 2;
	for (int i = -s_h_div2; i < s_h_div2; ++i)
	{
		for (int j = -s_w_div2; j < s_w_div2; ++j)
		{
			const glm::vec3 eye = glm::normalize(glm::vec3{ (j - eye_v.x), (i - eye_v.y), -eye_v.z }); // 視線ベクトル

			// レイトレ
			glm::vec3 i_d = { 0.0f, 0.0f, 0.0f };
			float t = 1e5f;
			for (const auto& ball : balls)
			{
				// 当たり判定
				const float tmp_t = ball->RayCast(eye_v, eye);
				if (tmp_t == 1e5f) { continue; } // 解なし

				// 現在の物体より手前に別の物体がある
				if (!(tmp_t < t)) { continue; }
				t = tmp_t;

				// 法線ベクトル
				const glm::vec3 xyz = {eye * t + eye_v};
				const glm::vec3 normal = glm::normalize(xyz - ball->GetCenter());

				// シェーディング
				float ln = glm::dot(light_n, normal);
				if (ln < 0.0f)
				{
					ln = 0.0f;
				}
				i_d = ball->GetLuminance() * ((i_p * ln) + i_a);
			}

			if (t < 1e5f)
				img.WritePixel(j + s_w_div2, -i + s_h_div2, i_d.r, i_d.g, i_d.b);
		}
	}

	for (auto ptr : balls)
	{
		delete ptr;
	}

	img.Output("./output/005_Perspective.png");
}

void Shadow(my::Image& img)
{
	// 図形定義
	std::vector<my::Shape*> shapes;
	// 球1
	shapes.emplace_back(new my::Ball{ 0.0f, 0.0f, 0.0f, 100.0f });
	shapes[0]->SetLuminance(glm::vec3{ 1.0f, 0.0f, 0.0f });
	// 球2
	shapes.emplace_back(new my::Ball{ 200.0f, 0.0f, 100.0f, 100.0f });
	shapes[1]->SetLuminance(glm::vec3{ 0.0f, 1.0f, 0.0f });
	// 球3
	shapes.emplace_back(new my::Ball{ -200.0f, 0.0f, 200.0f, 100.0f });
	shapes[2]->SetLuminance(glm::vec3{ 0.0f, 0.0f, 1.0f });
	// 床
	shapes.emplace_back(new my::Plane{ 0.0f, -100.0f, 0.0f });
	shapes[3]->SetLuminance(glm::vec3{ 0.0f, 0.5f, 0.5f });

	// 光源定義
	const glm::vec3 light{ 0.0f, 200.0f, -200.0f }; // 光源ベクトル
	const glm::vec3 i_p{ 1.0f, 1.0f, 1.0f }; // 光源強度(白色)
	glm::vec3 i_a = glm::vec3{ 0.2f, 0.2f, 0.2f }; // 環境光

	// 視点位置
	const glm::vec3 eye_v = glm::vec3{ 0.0f, 0.0f, -300.0f };

	// スクリーンサイズ
	const int s_h_div2 = img.GetHeight() / 2 - 1;
	const int s_w_div2 = img.GetWidth() / 2 - 1;
	for (int i = -s_h_div2; i < s_h_div2; ++i)
	{
		for (int j = -s_w_div2; j < s_w_div2; ++j)
		{
			const glm::vec3 eye = glm::normalize(glm::vec3{ (j - eye_v.x), (i - eye_v.y), -eye_v.z }); // 視線ベクトル

			// レイトレ
			glm::vec3 i_d = { 0.0f, 0.0f, 0.0f };
			float t = 1e5f;
			my::Shape *shape_tmp;
			for (const auto& shape : shapes)
			{
				// 当たり判定
				const float tmp_t = shape->RayCast(eye_v, eye);
				if (tmp_t == 1e5f) { continue; } // 解なし

				// 現在の物体より手前に別の物体がある
				if (!(tmp_t < t || tmp_t < 0)) { continue; }
				t = tmp_t;

				shape_tmp = shape;
			}

			if (t < 1e5f)
			{
				// 法線ベクトル
				const glm::vec3 normal = shape_tmp->Normal(eye, eye_v, t);
				// (床面と平行)
				if (normal == glm::vec3{1e5f, 1e5f, 1e5f}) { continue; }

				// シェーディング
				const glm::vec3 xyz = {eye * t + eye_v};
				const glm::vec3 light_n = glm::normalize(light - xyz);
				float ln = glm::dot(light_n, normal);
				if (ln < 0.0f) { ln = 0.0f; }
				// 影の計算(球体のみ)
				float sc = 1;
				for (int i = 0; i < shapes.size() - 1; ++i)
				{
					const glm::vec3 w = (xyz - shapes[i]->GetCenter());
					// 判別式
					const float b = 2.0f * glm::dot(light_n, w);
					const float c = std::sqrtf(glm::dot(w, w)) - shapes[i]->GetR() * shapes[i]->GetR();
					const float d = b * b - 4.0f * c;
					if (d >= 0)
					{
						const float t = (-b - std::sqrtf(d)) / 2.0f;
						if (t > 0)
						{
							sc = 0;
							break;
						}
					}
				}
				
				i_d = shape_tmp->GetLuminance() * ((i_p * sc * ln) + i_a);
				
				img.WritePixel(j + s_w_div2, -i + s_h_div2, i_d.r, i_d.g, i_d.b);
			}
		}
	}

	for (auto ptr : shapes)
	{
		delete ptr;
	}

	img.Output("./output/007_Shadow.png");
}

int main(int argc, char* argv[])
{
	my::Image img{};
	const size_t width = 512;
	const size_t height = 512;
	img.Init(width, height, 3);

	//HiddenSurfaceErasure(img);
	//Shading(img, false);
	//Perspective(img);
	Shadow(img);

	return 0;
}