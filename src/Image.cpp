#include "Image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../stb/stb_image_write.h"

namespace my
{
	Image::Image(const int& width, const int& height, const int& channel) :
		m_pixels{ nullptr },
		m_width{ width }, m_height{ height }, m_channel{ channel },
		max_size{ 0 }
	{
		Init_();
	}
	Image::~Image()
	{
		delete[] m_pixels;
		m_pixels = nullptr;
	}
	void Image::Init_()
	{
		const int img_size = m_width * m_height * m_channel;
		max_size = img_size;

		m_pixels = new unsigned char[img_size];

		// îíÇ≈èâä˙âª
		const int real_img_size = m_width * m_height * m_channel;
		for (int i = 0; i < img_size; ++i) { m_pixels[i] = 255; }
	}

	void Image::Output(const std::string& file_path)
	{
		stbi_write_png(file_path.c_str(), m_width, m_height, m_channel, m_pixels, 0);
	}
}
