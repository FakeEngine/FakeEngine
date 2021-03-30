#include "FakePch.h"
#include "FakeOpenGLTexture2D.h"

#include <stb_image.h>

#include "Engine/Renderer/FakeRenderer.h"
#include "Engine/Core/FakeVirtualFileSystem.h"

namespace Utils
	{
	static GLenum fake_to_open_gl_texture_format(FakeTextureFormat format)
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

FakeOpenGLTexture2D::FakeOpenGLTexture2D(const FakeString &path, bool srgb, FakeTextureWrap wrap)
	: FilePath(path)
	{
	Name = FakeVirtualFileSystem::Get()->GetFileNameFromPath(path);
	stbi_set_flip_vertically_on_load(1);

	int32 width, height, channels;
	if (stbi_is_hdr(*path))
		{
		FAKE_LOG_INFO("Loading HDR texture %s, srgb=%d", *path, srgb);
		ImageData.Data = (Byte*)stbi_loadf(*path, &width, &height, &channels, 0);
		IsHDR = true;
		Format = FakeTextureFormat::Float16;
		}
	else
		{
		FAKE_LOG_INFO("Loading texture %s, srgb=%d", *path, srgb);
		ImageData.Data = stbi_load(*path, &width, &height, &channels, srgb ? STBI_rgb : STBI_rgb_alpha);
		FAKE_ASSERT(ImageData.Data, "Could not read image!");
		Format = FakeTextureFormat::RGBA;
		}

	if (!ImageData.Data)
		return;

	IsLoaded = true;
	Width = width;
	Height = height;

	FakeRef<FakeOpenGLTexture2D> instance = this;
	FakeRenderer::Submit([instance, srgb]() mutable
		{
		if (srgb)
			{
			glCreateTextures(GL_TEXTURE_2D, 1, &instance->RendererID);
			int32 levels = FakeTexture::CalculateMipLevelCount(instance->Width, instance->Height);
			glTextureStorage2D(instance->RendererID, levels, GL_SRGB8, instance->Width, instance->Height);
			glTextureParameteri(instance->RendererID, GL_TEXTURE_MIN_FILTER, levels > 1 ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR);
			glTextureParameteri(instance->RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTextureSubImage2D(instance->RendererID, 0, 0, 0, instance->Width, instance->Height, GL_RGB, GL_UNSIGNED_BYTE, instance->ImageData.Data);
			glGenerateTextureMipmap(instance->RendererID);
			}
		else
			{
			glGenTextures(1, &instance->RendererID);
			glBindTexture(GL_TEXTURE_2D, instance->RendererID);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

			GLenum internalFormat = Utils::fake_to_open_gl_texture_format(instance->Format);
			GLenum format = srgb ? GL_SRGB8 : (instance->IsHDR ? GL_RGB : Utils::fake_to_open_gl_texture_format(instance->Format)); // HDR = GL_RGB for now
			GLenum type = internalFormat == GL_RGBA16F ? GL_FLOAT : GL_UNSIGNED_BYTE;
			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, instance->Width, instance->Height, 0, format, type, instance->ImageData.Data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glBindTexture(GL_TEXTURE_2D, 0);
			}
		stbi_image_free(instance->ImageData.Data);
		});
	}

FakeOpenGLTexture2D::FakeOpenGLTexture2D(FakeTextureFormat format, uint32 width, uint32 height, FakeTextureWrap wrap)
	: Format(format), Width(width), Height(height), Wrap(wrap), FilePath(""), Name("Undefined")
	{
	FakeRef<FakeOpenGLTexture2D> instance = this;
	FakeRenderer::Submit([instance]() mutable
		{
		glGenTextures(1, &instance->RendererID);
		glBindTexture(GL_TEXTURE_2D, instance->RendererID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		GLenum wrap = instance->Wrap == FakeTextureWrap::Clamp ? GL_CLAMP_TO_EDGE : GL_REPEAT;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
		glTextureParameterf(instance->RendererID, GL_TEXTURE_MAX_ANISOTROPY, FakeRendererAPI::GetCapabilities().MaxAnisotropy);

		glTexImage2D(GL_TEXTURE_2D, 0, Utils::fake_to_open_gl_texture_format(instance->Format), instance->Width, instance->Height, 0, Utils::fake_to_open_gl_texture_format(instance->Format), GL_UNSIGNED_BYTE, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
		});
	
	ImageData.Allocate(width * height * FakeTexture::GetBPP(Format));
	}

FakeOpenGLTexture2D::~FakeOpenGLTexture2D()
	{
	GLuint rendererID = RendererID;
	FakeRenderer::Submit([rendererID]()
		{
		glDeleteTextures(1, &rendererID);
		});
	}

void FakeOpenGLTexture2D::Bind(uint32 slot) const
	{
	FakeRef<const FakeOpenGLTexture2D> instance = this;
	FakeRenderer::Submit([instance, slot]()
		{
		glBindTextureUnit(slot, instance->RendererID);
		});
	}

void FakeOpenGLTexture2D::Unbind() const
	{
	}

bool FakeOpenGLTexture2D::Loaded() const
	{
	return IsLoaded;
	}

const FakeString &FakeOpenGLTexture2D::GetName() const
	{
	return Name;
	}

const FakeString &FakeOpenGLTexture2D::GetPath() const
	{
	return FilePath;
	}

FakeTextureFormat FakeOpenGLTexture2D::GetFormat() const
	{
	return Format;
	}

uint32 FakeOpenGLTexture2D::GetWidth() const
	{
	return Width;
	}

uint32 FakeOpenGLTexture2D::GetHeight() const
	{
	return Height;
	}

uint32 FakeOpenGLTexture2D::GetMipLevelCount() const
	{
	return FakeTexture::CalculateMipLevelCount(Width, Height);
	}

FakeRendererID FakeOpenGLTexture2D::GetRendererID() const
	{
	return RendererID;
	}

bool FakeOpenGLTexture2D::operator==(const FakeTexture &other) const
	{
	return RendererID == ((FakeOpenGLTexture2D&)other).RendererID;
	}

bool FakeOpenGLTexture2D::operator!=(const FakeTexture &other) const
	{
	return RendererID != ((FakeOpenGLTexture2D&)other).RendererID;
	}

void FakeOpenGLTexture2D::Lock()
	{
	IsLocked = true;
	}

void FakeOpenGLTexture2D::Unlock()
	{
	IsLocked = false;
	FakeRef<FakeOpenGLTexture2D> instance = this;
	FakeRenderer::Submit([instance]()
		{
		glTextureSubImage2D(instance->RendererID, 0, 0, 0, instance->Width, instance->Height, Utils::fake_to_open_gl_texture_format(instance->Format), GL_UNSIGNED_BYTE, instance->ImageData.Data);
		});
	}

void FakeOpenGLTexture2D::Resize(uint32 width, uint32 height)
	{
	FAKE_ASSERT(IsLocked);
	ImageData.Allocate(width * height * FakeTexture::GetBPP(Format));
	
#ifdef FAKE_DEBUG
	ImageData.ZeroInitialize();
#endif
	}

FakeAllocator FakeOpenGLTexture2D::GetWriteableBuffer()
	{
	FAKE_ASSERT(IsLocked, "Texture must be locked!");
	return ImageData;
	}

void FakeOpenGLTexture2D::SetData(void *data, uint32 size)
	{
	FAKE_ASSERT(IsLocked, "Texture must be locked!");
	ImageData = FakeAllocator::Copy(data, size);
	}

