#include "FakePch.h"
#include "FakeTexture.h"

uint32 FakeTexture::GetBPP(FakeTextureFormat format)
	{
	switch (format)
		{
		case FakeTextureFormat::RGB:
			return 3;

		case FakeTextureFormat::RGBA:
			return 4;
		}

	return 0;
	}

uint32 FakeTexture::CalculateMipLevelCount(uint32 width, uint32 height)
	{
	uint32 levels = 1;

	while ((width | height) >> levels)
		levels++;

	return levels;
	}
