#include "FakePch.h"
#include "FakeOpenGLFramebuffer.h"

static const uint32 MaxFramebufferSize = 8192;

namespace Utils
	{
	static GLenum fake_texture_target(bool multisampled)
		{
		return multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
		}

	static void fake_create_texture(bool multisampled, uint32 *outID, uint32 count)
		{
		glCreateTextures(fake_texture_target(multisampled), count, outID);
		}

	static void fake_bind_texture(bool multisampled, uint32 id)
		{
		glBindTexture(fake_texture_target(multisampled), id);
		}

	static void fake_attach_color_texture(uint32 id, int32 samples, GLenum internalFormat, GLenum format, uint32 width, uint32 height, int32 index)
		{
		bool multisampled = samples > 1;
		if (multisampled)
			{
			glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, internalFormat, width, height, GL_FALSE);
			}
		else
			{
			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);

			// TODO: 
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, fake_texture_target(multisampled), id, 0);
		}

	static void fake_attach_depth_texture(uint32 id, int32 samples, GLenum format, GLenum attachmentType, uint32 width, uint32 height)
		{
		bool multisampled = samples > 1;
		if (multisampled)
			{
			glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
			}
		else
			{
			glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}

		glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, fake_texture_target(multisampled), id, 0);
		}

	static bool fake_is_depth_format(FakeFramebufferTextureFormat format)
		{
		switch (format)
			{
			case FakeFramebufferTextureFormat::DEPTH24STENCIL8:  return true;
			}

		return false;
		}

	static GLenum fake_texture_format_to_opengl(FakeFramebufferTextureFormat format)
		{
		switch (format)
			{
			case FakeFramebufferTextureFormat::RGBA8:       return GL_RGBA8;
			case FakeFramebufferTextureFormat::RED_INTEGER: return GL_RED_INTEGER;
			}

		FAKE_ASSERT(false);
		return 0;
		}
	}

void FakeOpenGLFramebuffer::Invalidate()
	{
	if (RendererID)
		{
		glDeleteFramebuffers(1, &RendererID);
		glDeleteTextures((int32)ColorAttachmentRendererIDs.size(), ColorAttachmentRendererIDs.data());
		glDeleteTextures(1, &DepthAttachmentRendererID);

		ColorAttachmentRendererIDs.clear();
		DepthAttachmentRendererID = 0;
		}

	glCreateFramebuffers(1, &RendererID);
	glBindFramebuffer(GL_FRAMEBUFFER, RendererID);

	bool multisample = Specification.Samples > 1;
	if (ColorAttachmentSpecification.size())
		{
		ColorAttachmentRendererIDs.resize(ColorAttachmentSpecification.size());
		Utils::fake_create_texture(multisample, ColorAttachmentRendererIDs.data(), (int32)ColorAttachmentRendererIDs.size());

		for (int32 i = 0; i < ColorAttachmentRendererIDs.size(); ++i)
			{
			Utils::fake_bind_texture(multisample, ColorAttachmentRendererIDs[i]);
			switch (ColorAttachmentSpecification[i].Format)
				{
				case FakeFramebufferTextureFormat::RGBA8:
					Utils::fake_attach_color_texture(ColorAttachmentRendererIDs[i], Specification.Samples, GL_RGBA8, GL_RGBA, Specification.Width, Specification.Height, i);
					break;

				case FakeFramebufferTextureFormat::RED_INTEGER:
					Utils::fake_attach_color_texture(ColorAttachmentRendererIDs[i], Specification.Samples, GL_R32I, GL_RED_INTEGER, Specification.Width, Specification.Height, i);
					break;
				}
			}
		}

	if (DepthAttachmentSpecification.Format != FakeFramebufferTextureFormat::None)
		{
		Utils::fake_create_texture(multisample, &DepthAttachmentRendererID, 1);
		Utils::fake_bind_texture(multisample, DepthAttachmentRendererID);

		switch (DepthAttachmentSpecification.Format)
			{
			case FakeFramebufferTextureFormat::DEPTH24STENCIL8:
				Utils::fake_attach_depth_texture(DepthAttachmentRendererID, Specification.Samples, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, Specification.Width, Specification.Height);
				break;
			}
		}

	if (ColorAttachmentRendererIDs.size() > 1)
		{
		FAKE_ASSERT(ColorAttachmentRendererIDs.size() <= 4);
		GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
		glDrawBuffers((int32)ColorAttachmentRendererIDs.size(), buffers);
		}
	else if (ColorAttachmentRendererIDs.empty())
		{
		// Draw only depth pass
		glDrawBuffer(GL_NONE);
		}

	FAKE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

FakeOpenGLFramebuffer::FakeOpenGLFramebuffer(const FakeFramebufferSpecification &spec)
	: Specification(spec)
	{
	for (auto spec : Specification.Attachments.Attachments)
		{
		if (!Utils::fake_is_depth_format(spec.Format))
			ColorAttachmentSpecification.emplace_back(spec);
		else
			DepthAttachmentSpecification = spec;
		}

	Invalidate();
	}

FakeOpenGLFramebuffer::~FakeOpenGLFramebuffer()
	{
	glDeleteFramebuffers(1, &RendererID);
	glDeleteTextures((int32)ColorAttachmentRendererIDs.size(), ColorAttachmentRendererIDs.data());
	glDeleteTextures(1, &DepthAttachmentRendererID);
	}

void FakeOpenGLFramebuffer::Bind() const
	{
	glBindFramebuffer(GL_FRAMEBUFFER, RendererID);
	glViewport(0, 0, Specification.Width, Specification.Height);
	}

void FakeOpenGLFramebuffer::Unbind() const
	{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

void FakeOpenGLFramebuffer::Resize(uint32 width, uint32 height)
	{
	if (width == 0 || height == 0 || width > MaxFramebufferSize || height > MaxFramebufferSize)
		{
		FAKE_LOG_WARN("Attempted to rezize framebuffer to %d, %d", width, height);
		return;
		}
	
	Specification.Width = width;
	Specification.Height = height;

	Invalidate();
	}

uint32 FakeOpenGLFramebuffer::GetWidth() const
	{
	return Specification.Width;
	}

uint32 FakeOpenGLFramebuffer::GetHeight() const
	{
	return Specification.Height;
	}

int32 FakeOpenGLFramebuffer::ReadPixel(uint32 attachmentIndex, int32 x, int32 y)
	{
	FAKE_ASSERT(attachmentIndex < ColorAttachmentRendererIDs.size());

	glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex);
	int32 pixelData;
	glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData);
	return pixelData;
	}

void FakeOpenGLFramebuffer::ClearAttachment(uint32 attachmentIndex, int32 value)
	{
	FAKE_ASSERT(attachmentIndex < ColorAttachmentRendererIDs.size());
	auto &spec = ColorAttachmentSpecification[attachmentIndex];
	glClearTexImage(ColorAttachmentRendererIDs[attachmentIndex], 0, Utils::fake_texture_format_to_opengl(spec.Format), GL_INT, &value);
	}

void FakeOpenGLFramebuffer::ClearAttachment(uint32 attachmentIndex, float value)
	{
	FAKE_ASSERT(attachmentIndex < ColorAttachmentRendererIDs.size());
	auto &spec = ColorAttachmentSpecification[attachmentIndex];
	glClearTexImage(ColorAttachmentRendererIDs[attachmentIndex], 0, Utils::fake_texture_format_to_opengl(spec.Format), GL_FLOAT, &value);
	}

FakeRendererID FakeOpenGLFramebuffer::GetRendererID() const
	{
	return RendererID;
	}

FakeRendererID FakeOpenGLFramebuffer::GetColorAttachmentRendererID(int32 index) const
	{
	FAKE_ASSERT(index < ColorAttachmentRendererIDs.size());
	return ColorAttachmentRendererIDs[index];
	}

FakeRendererID FakeOpenGLFramebuffer::GetDepthAttachmentRendererID() const
	{
	return DepthAttachmentRendererID;
	}

const FakeFramebufferSpecification &FakeOpenGLFramebuffer::GetSpecification() const
	{
	return Specification;
	}
