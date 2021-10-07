#ifndef MY_IMAGE_H
#define MY_IMAGE_H

#include <algorithm>
#include <string>
#include <cassert>

namespace my
{
	class Image final
	{
	public:
		explicit Image(const int& width, const int& height, const int& channel);
		~Image();

		void Output(const std::string &file_path);

		// rgb = [0.0f, 1.0f]
		inline void WritePixel(const int& x, const int& y, const float& r, const float& g, const float& b)
		{
			unsigned char rr = static_cast<unsigned char>(std::clamp(r * 255.0f, 0.0f, 255.0f));
			unsigned char gg = static_cast<unsigned char>(std::clamp(g * 255.0f, 0.0f, 255.0f));
			unsigned char bb = static_cast<unsigned char>(std::clamp(b * 255.0f, 0.0f, 255.0f));

			WritePixelValue(x, y, rr, gg, bb);
		}
		// rgb = [0, 255]
		inline void WritePixelValue(const int& x, const int& y, const unsigned char& r, const unsigned char& g, const unsigned char& b)
		{
			const int idx = (y * m_width + x) * m_channel;
			assert((idx >= 0) || (idx + 2 < max_size));

			m_pixels[idx + 0] = r;
			m_pixels[idx + 1] = g;
			m_pixels[idx + 2] = b;
		}

		inline int GetWidth() const { return m_width; }
		inline int GetHeight() const { return m_height; }
		
	private:
		void Init_();

	private:
		unsigned char* m_pixels;
		const int m_width, m_height;
		const int m_channel;
		int max_size;
	};
}

#endif // MY_IMAGE_H
