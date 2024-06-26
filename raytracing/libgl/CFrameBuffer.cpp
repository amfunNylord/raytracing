﻿#include "../stdafx.h"
#include "CFrameBuffer.h"

CFrameBuffer::CFrameBuffer(unsigned width, unsigned height)
	: m_pixels(width * height)
	, m_width(width)
	, m_height(height)
{
}

void CFrameBuffer::Clear(std::uint32_t color)
{
	std::fill(m_pixels.begin(), m_pixels.end(), color);
}
