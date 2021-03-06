#include "Image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../stb/stb_image_write.h"

namespace my
{
	Image::Image() :
		m_pixels{ nullptr },
		m_width{ 0 }, m_height{ 0 }, m_channel{ 0 }
	{
	}
	Image::~Image()
	{
		delete[] m_pixels;
		m_pixels = nullptr;
	}
	void Image::Init(const size_t& width, const size_t& height, const size_t& channel)
	{
		m_width = width;
		m_height = height;
		m_channel = channel;

		const size_t img_size = m_width * m_height * m_channel;
		m_pixels = new unsigned char[img_size];

		const size_t real_img_size = m_width * m_height;
		for (size_t i = 0; i < img_size; i += m_channel)
		{
			m_pixels[i + 0] = 255;
			m_pixels[i + 1] = 255;
			m_pixels[i + 2] = 255;

		}
	}

	void Image::Output(const std::string& file_path)
	{
		stbi_write_png(file_path.c_str(), m_width, m_height, m_channel, m_pixels, 0);
	}
}
