#ifndef MY_IMAGE_H
#define MY_IMAGE_H

#include <algorithm>
#include <string>

namespace my
{
	class Image final
	{
	public:
		Image();
		~Image();

		void Init(const size_t& width, const size_t& height, const size_t& channel);
		void Output(const std::string &file_path);

		// rgb = [0.0f, 1.0f]
		inline void WritePixel(const int& x, const int& y, const float& r, const float& g, const float& b)
		{
			unsigned char rr = static_cast<unsigned char>(std::clamp(r * 255.0f, 0.0f, 255.0f));
			unsigned char gg = static_cast<unsigned char>(std::clamp(g * 255.0f, 0.0f, 255.0f));
			unsigned char bb = static_cast<unsigned char>(std::clamp(b * 255.0f, 0.0f, 255.0f));

			m_pixels[(y * m_width + x) * m_channel + 0] = rr;
			m_pixels[(y * m_width + x) * m_channel + 1] = gg;
			m_pixels[(y * m_width + x) * m_channel + 2] = bb;
		}
		// rgb = [0, 255]
		inline void WritePixelValue(const int& x, const int& y, const unsigned char& r, const unsigned char& g, const unsigned char& b)
		{
			m_pixels[(y * m_width + x) * m_channel + 0] = r;
			m_pixels[(y * m_width + x) * m_channel + 1] = g;
			m_pixels[(y * m_width + x) * m_channel + 2] = b;
		}

	private:
		unsigned char* m_pixels;
		size_t m_width, m_height;
		size_t m_channel;
	};
}

#endif // MY_IMAGE_H
