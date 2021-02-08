#include "FakePch.h"
#include "FakeVertexBufferLayout.h"

namespace Utils
	{
	static uint32 fake_render_helper_sizeof_shader_data_type(FakeShaderDataType type)
		{
		switch (type)
			{
			case FakeShaderDataType::Bool:
				return 1;

			case FakeShaderDataType::Int:
			case FakeShaderDataType::Float:
				return 4;

			case FakeShaderDataType::Int2:
			case FakeShaderDataType::Float2:
				return 4 * 2;

			case FakeShaderDataType::Int3:
			case FakeShaderDataType::Float3:
				return 4 * 3;

			case FakeShaderDataType::Int4:
			case FakeShaderDataType::Float4:
				return 4 * 4;

			case FakeShaderDataType::Mat2:
				return 4 * 2 * 2;

			case FakeShaderDataType::Mat3:
				return 4 * 3 * 3;

			case FakeShaderDataType::Mat4:
				return 4 * 4 * 4;
			}

		FAKE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
		}
	}

FakeVertexBufferElement::FakeVertexBufferElement(FakeShaderDataType type, const FakeString &name, bool normalized)
	: Name(name), Type(type), Size(Utils::fake_render_helper_sizeof_shader_data_type(type)), Offset(0), Normalized(normalized)
	{
	}

uint32 FakeVertexBufferElement::GetComponentCount() const
	{
	switch (Type)
		{
		case FakeShaderDataType::Bool:
		case FakeShaderDataType::Float:
		case FakeShaderDataType::Int:
			return 1;

		case FakeShaderDataType::Float2:
		case FakeShaderDataType::Int2:
			return 2;

		case FakeShaderDataType::Float3:
		case FakeShaderDataType::Int3:
			return 3;

		case FakeShaderDataType::Float4:
		case FakeShaderDataType::Int4:
			return 4;

		case FakeShaderDataType::Mat2:
			return 2 * 2;

		case FakeShaderDataType::Mat3:
			return 3 * 3;

		case FakeShaderDataType::Mat4:
			return 4 * 4;
		}

	FAKE_ASSERT(false, "Unknown ShaderDataType!");
	return 0;
	}

FakeVertexBufferLayout::FakeVertexBufferLayout(const std::initializer_list<FakeVertexBufferElement> &elements)
	: Elements(elements), Stride(0)
	{
	uint32 offset = 0;
	for (auto &element : Elements)
		{
		element.Offset = offset;
		offset += element.Size;
		Stride += element.Size;
		}
	}

uint32 FakeVertexBufferLayout::GetStride() const
	{
	return Stride;
	}

const std::vector<FakeVertexBufferElement> &FakeVertexBufferLayout::GetElements() const
	{
	return Elements;
	}

std::vector<FakeVertexBufferElement>::iterator FakeVertexBufferLayout::begin()
	{
	return Elements.begin();
	}

std::vector<FakeVertexBufferElement>::iterator FakeVertexBufferLayout::end()
	{
	return Elements.end();
	}

std::vector<FakeVertexBufferElement>::const_iterator FakeVertexBufferLayout::begin() const
	{
	return Elements.begin();
	}

std::vector<FakeVertexBufferElement>::const_iterator FakeVertexBufferLayout::end() const
	{
	return Elements.end();
	}

