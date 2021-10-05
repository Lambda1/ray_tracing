#include <vector>

#include "./Image.h"
#include "./Ball.h"
#include "./Plane.h"

#include "../glm/glm/glm.hpp"
#include "../glm/glm/vec3.hpp"

void HiddenSurfaceErasure(my::Image& img)
{
	glm::vec3 eye{ 0.0f, 0.0f, 1.0f }; // �����x�N�g��
	my::Ball ball{ 0.0f, 0.0f, 100.0f, 100.0f }; // ��

	// �X�N���[���T�C�Y
	const int s_h_div2 = img.GetHeight() / 2;
	const int s_w_div2 = img.GetWidth() / 2;
	for (int i = -s_h_div2; i < s_h_div2; ++i)
	{
		for (int j = -s_w_div2; j < s_w_div2; ++j)
		{
			const float x = j;
			const float y = -i;

			const float t = ball.RayCast(glm::vec3{ x, y, 0.0f }, eye);
			if (t == 1e5f) { continue; } // ���Ȃ�

			img.WritePixel(j + s_w_div2, -i + s_h_div2, 1.0f, 0.0f, 0.0f);
		}
	}

	img.Output("./output/001_HiddenSurfaceErasure.png");
}

void Shading(my::Image& img, const bool& ambient_flag)
{
	const glm::vec3 eye{ 0.0f, 0.0f, 1.0f }; // �����x�N�g��

	my::Ball ball{ 0.0f, 0.0f, 100.0f, 100.0f }; // ��
	ball.SetLuminance(glm::vec3{ 1.0f, 0.f, 0.f });

	const glm::vec3 light{ -1.0f, 1.0f, -1.0f }; // �����x�N�g��
	const glm::vec3 i_p{ 1.0f, 1.0f, 1.0f }; // �������x(���F)

	const glm::vec3 light_n = glm::normalize(light);

	glm::vec3 i_a = !ambient_flag ? glm::vec3{ 0.0f, 0.0f, 0.0f } : glm::vec3{ 0.2f, 0.2f, 0.2f };

	// �X�N���[���T�C�Y
	const int s_h_div2 = img.GetHeight() / 2;
	const int s_w_div2 = img.GetWidth() / 2;
	for (int i = -s_h_div2; i < s_h_div2; ++i)
	{
		for (int j = -s_w_div2; j < s_w_div2; ++j)
		{
			const float x = j;
			const float y = -i;

			const float t = ball.RayCast(glm::vec3{ x, y, 0.0f }, eye);
			if (t == 1e5f) { continue; } // ���Ȃ�

			const glm::vec3 normal = glm::normalize(glm::vec3{ j, i, t - ball.GetCenter().z });
			float ln = glm::dot(light_n, normal);
			float ln2 = glm::dot(-light_n, normal);
			ln2 = 0.0f; // (2�ڂ̌����������Ă���: �����Ƃ��Ďc���Ă邾��)
			glm::vec3 i_d = { 0.0f, 0.0f, 0.0f };

			// ln <  0.0f: �ʂ̗�������� (�e)
			// ln >= 0.0f: �ʂ̕\������� (����)
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
	// ����`
	std::vector<my::Shape*> balls;
	// ��1
	balls.emplace_back(new my::Ball{ 0.0f, 0.0f, 100.0f, 100.0f });
	balls[0]->SetLuminance(glm::vec3{ 1.0f, 0.0f, 0.0f });
	// ��2
	balls.emplace_back(new my::Ball{ 200.0f, 0.0f, 200.0f, 100.0f });
	balls[1]->SetLuminance(glm::vec3{ 0.0f, 1.0f, 0.0f });
	// ��3
	balls.emplace_back(new my::Ball{ -200.0f, 0.0f, 300.0f, 100.0f });
	balls[2]->SetLuminance(glm::vec3{ 0.0f, 0.0f, 1.0f });

	// ������`
	const glm::vec3 light{ -1.0f, 1.0f, -1.0f }; // �����x�N�g��
	const glm::vec3 i_p{ 1.0f, 1.0f, 1.0f }; // �������x(���F)
	glm::vec3 i_a = glm::vec3{ 0.2f, 0.2f, 0.2f }; // ����

	const glm::vec3 light_n = glm::normalize(light);

	// ���_�ʒu
	const glm::vec3 eye_v = glm::vec3{0.0f, 0.0f, -300.0f};

	// �X�N���[���T�C�Y
	const int s_h_div2 = img.GetHeight() / 2;
	const int s_w_div2 = img.GetWidth() / 2;
	for (int i = -s_h_div2; i < s_h_div2; ++i)
	{
		for (int j = -s_w_div2; j < s_w_div2; ++j)
		{
			const glm::vec3 eye = glm::normalize(glm::vec3{ (j - eye_v.x), (i - eye_v.y), -eye_v.z }); // �����x�N�g��

			// ���C�g��
			glm::vec3 i_d = { 0.0f, 0.0f, 0.0f };
			float t = 1e5f;
			for (const auto& ball : balls)
			{
				// �����蔻��
				const float tmp_t = ball->RayCast(eye_v, eye);
				if (tmp_t == 1e5f) { continue; } // ���Ȃ�

				// ���݂̕��̂���O�ɕʂ̕��̂�����
				if (!(tmp_t < t)) { continue; }
				t = tmp_t;

				// �@���x�N�g��
				const glm::vec3 xyz = {eye * t + eye_v};
				const glm::vec3 normal = glm::normalize(xyz - ball->GetCenter());

				// �V�F�[�f�B���O
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
	// �}�`��`
	std::vector<my::Shape*> shapes;
	// ��1
	shapes.emplace_back(new my::Ball{ 0.0f, 0.0f, 100.0f, 100.0f });
	shapes[0]->SetLuminance(glm::vec3{ 1.0f, 0.0f, 0.0f });
	// ��2
	shapes.emplace_back(new my::Ball{ 200.0f, 0.0f, 200.0f, 100.0f });
	shapes[1]->SetLuminance(glm::vec3{ 0.0f, 1.0f, 0.0f });
	// ��3
	shapes.emplace_back(new my::Ball{ -200.0f, 0.0f, 300.0f, 100.0f });
	shapes[2]->SetLuminance(glm::vec3{ 0.0f, 0.0f, 1.0f });
	// ��
	shapes.emplace_back(new my::Plane{ 0.0f, -100.0f, 0.0f });
	shapes[3]->SetLuminance(glm::vec3{ 0.5f, 0.5f, 0.5f });

	// ������`
	const glm::vec3 light{ -1.0f, 1.0f, -1.0f }; // �����x�N�g��
	const glm::vec3 i_p{ 1.0f, 1.0f, 1.0f }; // �������x(���F)
	glm::vec3 i_a = glm::vec3{ 0.2f, 0.2f, 0.2f }; // ����

	const glm::vec3 light_n = glm::normalize(light);

	// ���_�ʒu
	const glm::vec3 eye_v = glm::vec3{ 0.0f, 0.0f, -300.0f };

	// �X�N���[���T�C�Y
	const int s_h_div2 = img.GetHeight() / 2 - 1;
	const int s_w_div2 = img.GetWidth() / 2 - 1;
	for (int i = -s_h_div2; i < s_h_div2; ++i)
	{
		for (int j = -s_w_div2; j < s_w_div2; ++j)
		{
			const glm::vec3 eye = glm::normalize(glm::vec3{ (j - eye_v.x), (i - eye_v.y), -eye_v.z }); // �����x�N�g��

			// ���C�g��
			glm::vec3 i_d = { 0.0f, 0.0f, 0.0f };
			float t = 1e5f;
			for (const auto& shape : shapes)
			{
				// �����蔻��
				const float tmp_t = shape->RayCast(eye_v, eye);
				if (tmp_t == 1e5f) { continue; } // ���Ȃ�

				// ���݂̕��̂���O�ɕʂ̕��̂�����
				if (!(tmp_t < t)) { continue; }
				t = tmp_t;

				// �@���x�N�g��
				const glm::vec3 normal = shape->Normal(eye, eye_v, t);
				// (���ʂƕ��s)
				if (normal == glm::vec3{1e5f, 1e5f, 1e5f}) { continue; }

				// �V�F�[�f�B���O
				float ln = glm::dot(light_n, normal);
				if (ln < 0.0f)
				{
					ln = 0.0f;
				}
				i_d = shape->GetLuminance() * ((i_p * ln) + i_a);
			}

			if (t < 1e5f)
				img.WritePixel(j + s_w_div2, -i + s_h_div2, i_d.r, i_d.g, i_d.b);
		}
	}

	for (auto ptr : shapes)
	{
		delete ptr;
	}

	img.Output("./output/006_Plane.png");
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