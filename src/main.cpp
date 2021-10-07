#include <vector>

#include "./Image.h"
#include "./Ball.h"
#include "./Plane.h"

int main(int argc, char* argv[])
{
	// �X�N���[���T�C�Y
	constexpr int screen_width = 512;
	constexpr int screen_height = 512;
	
	// �}�`��`
	std::vector<my::Shape*> shapes;
	shapes.emplace_back(new my::Ball{0.0f, 0.0f, 100.0f, 100.0f});

	my::Image img{screen_width, screen_height, 3};
	
	// �����_�����O
	constexpr float sh_half = screen_height / 2.0f;
	constexpr float sw_half = screen_width / 2.0f;
	for (int i = 0; i < screen_height; ++i)
	{
		for (int j = 0; j < screen_width; ++j)
		{
			// ������W�n�ɕϊ�
			const float y = i - (sh_half - 1);
			const float x = j - (sw_half - 1);

			img.WritePixel(j, i, 0.0f, 0.0f, 0.0f);
		}
	}
	img.Output("./output/test.png");
	
	// ���
	for (auto shape : shapes)
	{
		delete shape;
		shape = nullptr;
	}

	return 0;
}