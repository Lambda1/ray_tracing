#ifndef MY_IMAGE_H
#define MY_IMAGE_H

#include <string>

namespace my
{
	class Image final
	{
	public:
		Image();
		~Image();

		void Init(const size_t& width, const size_t& height, const size_t& channel);
		void Write(const std::string &file_path);

	private:
		unsigned char* m_pixels;
		size_t m_width, m_height;
		size_t m_channel;
	};
}

#endif // MY_IMAGE_H
