#include "FakePch.h"
#include "FakeOpenGLTextureCube.h"

#include <stb_image.h>
#include "Engine/Renderer/FakeRenderer.h"

namespace Utils
	{
	static FakeString fake_texture_extract_name(const FakeString &path)
		{
		FakeString result = path.Substr(path.LastIndexOf('/') + 1);
		if (result.Contains("."))
			result = result.Substr(0, result.IndexOf("."));

		return result;
		}

	static GLenum fake_to_open_gl_cube_texture_format(FakeTextureFormat format)
		{
		switch (format)
			{
			case FakeTextureFormat::RGB:     return GL_RGB;
			case FakeTextureFormat::RGBA:    return GL_RGBA;
			case FakeTextureFormat::Float16: return GL_RGBA16F;
			}

		FAKE_ASSERT(false);
		return 0;
		}
	}

FakeOpenGLTextureCube::FakeOpenGLTextureCube(const FakeString &path)
	: FilePath(path)
	{
	Name = Utils::fake_texture_extract_name(path);

	int32 width, height, channels;
	stbi_set_flip_vertically_on_load(false);
	ImageData.Data = stbi_load(*path, &width, &height, &channels, STBI_rgb);
	FAKE_ASSERT(ImageData.Data, "Failed to load texture");

	if (!ImageData.Data)
		return;

	IsLoaded = true;

	Width = width;
	Height = height;
	Format = FakeTextureFormat::RGB;

	uint32 faceWidth = Width / 4;
	uint32 faceHeight = Height / 3;
	FAKE_ASSERT(faceWidth == faceHeight, "Non-Square faces!");

	std::array<uint8*, 6> faces;
	for (size_t i = 0; i < faces.size(); ++i)
		faces[i] = new uint8[faceWidth * faceHeight * 3]; // 3 bytes per pixel

	int32 faceIndex = 0;
	for (size_t i = 0; i < 4; ++i)
		{
		for (size_t y = 0; y < faceHeight; ++y)
			{
			size_t yOffset = y + i * faceHeight;
			for (size_t x = 0; x < faceWidth; ++x)
				{
				size_t xOffset = x + faceWidth;
				faces[faceIndex][(x + y * faceWidth) * 3 + 0] = ImageData.Data[(xOffset + yOffset * Width) * 3 + 0];
				faces[faceIndex][(x + y * faceWidth) * 3 + 1] = ImageData.Data[(xOffset + yOffset * Width) * 3 + 1];
				faces[faceIndex][(x + y * faceWidth) * 3 + 2] = ImageData.Data[(xOffset + yOffset * Width) * 3 + 2];
				}
			}
		++faceIndex;
		}

	FakeRef<FakeOpenGLTextureCube> instance = this;
	FakeRenderer::Submit([instance, faceWidth, faceHeight, faces]() mutable
		{
		glGenTextures(1, &instance->RendererID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, instance->RendererID);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTextureParameterf(instance->RendererID, GL_TEXTURE_MAX_ANISOTROPY, FakeRendererAPI::GetCapabilities().MaxAnisotropy);

		auto format = Utils::fake_to_open_gl_cube_texture_format(instance->Format);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, format, faceWidth, faceHeight, 0, format, GL_UNSIGNED_BYTE, faces[2]);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, format, faceWidth, faceHeight, 0, format, GL_UNSIGNED_BYTE, faces[0]);

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, format, faceWidth, faceHeight, 0, format, GL_UNSIGNED_BYTE, faces[4]);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, format, faceWidth, faceHeight, 0, format, GL_UNSIGNED_BYTE, faces[5]);

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, format, faceWidth, faceHeight, 0, format, GL_UNSIGNED_BYTE, faces[1]);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, format, faceWidth, faceHeight, 0, format, GL_UNSIGNED_BYTE, faces[3]);

		glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

		glBindTexture(GL_TEXTURE_2D, 0);

		for (size_t i = 0; i < faces.size(); i++)
			delete[] faces[i];

		stbi_image_free(instance->ImageData.Data);
		});
	}

FakeOpenGLTextureCube::FakeOpenGLTextureCube(FakeTextureFormat format, uint32 width, uint32 height)
	: Format(format), Width(width), Height(height), Name("Undefined"), IsLoaded(true)
	{
	uint32 levels = FakeTexture::CalculateMipLevelCount(width, height);
	FakeRef<FakeOpenGLTextureCube> instance = this;
	FakeRenderer::Submit([instance, levels]() mutable
		{
		glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &instance->RendererID);
		glTextureStorage2D(instance->RendererID, levels, Utils::fake_to_open_gl_cube_texture_format(instance->Format), instance->Width, instance->Height);

		glTextureParameteri(instance->RendererID, GL_TEXTURE_MIN_FILTER, levels > 1 ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR);
		glTextureParameteri(instance->RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		});

	ImageData.Allocate(width * height * FakeTexture::GetBPP(Format));
	}

FakeOpenGLTextureCube::~FakeOpenGLTextureCube()
	{
	GLuint rendererID = RendererID;
	FakeRenderer::Submit([rendererID]() { glDeleteTextures(1, &rendererID); });
	}

void FakeOpenGLTextureCube::Bind(uint32 slot) const
	{
	FakeRef<const FakeOpenGLTextureCube> instance = this;
	FakeRenderer::Submit([instance, slot]()
		{
		glBindTextureUnit(slot, instance->RendererID);
		});
	}

void FakeOpenGLTextureCube::Unbind() const
	{
	}

bool FakeOpenGLTextureCube::Loaded() const
	{
	return IsLoaded;
	}

const FakeString &FakeOpenGLTextureCube::GetName() const
	{
	return Name;
	}

const FakeString &FakeOpenGLTextureCube::GetPath() const
	{
	return FilePath;
	}

FakeTextureFormat FakeOpenGLTextureCube::GetFormat() const
	{
	return Format;
	}

uint32 FakeOpenGLTextureCube::GetWidth() const
	{
	return Width;
	}

uint32 FakeOpenGLTextureCube::GetHeight() const
	{
	return Height;
	}

uint32 FakeOpenGLTextureCube::GetMipLevelCount() const
	{
	return FakeTexture::CalculateMipLevelCount(Width, Height);
	}

FakeRendererID FakeOpenGLTextureCube::GetRendererID() const
	{
	return RendererID;
	}

bool FakeOpenGLTextureCube::operator==(const FakeTexture &other) const
	{
	return RendererID == ((FakeOpenGLTextureCube&)other).RendererID;
	}

bool FakeOpenGLTextureCube::operator!=(const FakeTexture &other) const
	{
	return RendererID != ((FakeOpenGLTextureCube&)other).RendererID;
	}
