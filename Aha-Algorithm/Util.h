#pragma once
#include "stdafx.h"


namespace Global_Function {


	std::tuple<byte*, size_t> GetFileWithBinary(const std::string & path)
	{
		FILE* file = fopen("D:/g.bmp", "rb");

		fseek(file, 0, 2);

		size_t len = ftell(file);

		byte* m_byte = new byte[len];


		fseek(file, 0, 0);

		for (size_t i = 0; i < len; i++)
		{
			m_byte[i] = fgetc(file);
		}

		fclose(file);

		return std::make_tuple(m_byte, len);

	}


}
