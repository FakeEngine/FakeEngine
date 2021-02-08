/*****************************************************************
 * \file   FakeVertexBufferLayout.h
 * \brief  
 * 
 * \author Can Karka
 * \date   January 2021
 * 
 * Copyright (C) 2021 Can Karka
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *********************************************************************/

#pragma once

enum class FakeShaderDataType
	{
	None = 0,
	Float, Float2, Float3, Float4,
	Int, Int2, Int3, Int4,
	Mat2, Mat3, Mat4,
	Bool
	};

/**
 *
 * This struct describes a VertexBufferLayout Element.
 *
 */
struct FAKE_API FakeVertexBufferElement
	{
	FakeString Name;
	FakeShaderDataType Type;
	uint32 Size;
	uint32 Offset;
	bool Normalized;

	/**
	 * 
	 * .
	 * 
	 */
	FakeVertexBufferElement() = default;

	/**
	 * 
	 * .
	 * 
	 * @param type
	 * @param name
	 * @param normalized
	 */
	FakeVertexBufferElement(FakeShaderDataType type, const FakeString &name, bool normalized = false);

	/**
	 * 
	 * .
	 * 
	 * @return 
	 */
	uint32 GetComponentCount() const;
	};

/**
 *
 * This class represents the VertexBuffer Layout. It is used to describe the vertices of a VertexBuffer.
 *
 */
class FAKE_API FakeVertexBufferLayout
	{
	private:
		std::vector<FakeVertexBufferElement> Elements;
		uint32 Stride = 0;

	public:

		/**
		 *
		 * default constructor.
		 *
		 */
		FakeVertexBufferLayout() = default;

		/**
		 *
		 * initializes the Elements with a initializer list.
		 *
		 * @param elements The Elements which should be initialized.
		 */
		FakeVertexBufferLayout(const std::initializer_list<FakeVertexBufferElement> &elements);

		/**
		 *
		 * The total size of the VertexBuffer Layout.
		 *
		 * @return Returns the total size of the VertexBuffer Layout.
		 */
		uint32 GetStride() const;

		/**
		 *
		 * Returns the complete VertexBuffer Layout.
		 *
		 * @return Returns the complete VertexBuffer Layout.
		 */
		const std::vector<FakeVertexBufferElement> &GetElements() const;

		/**
		 *
		 * Returns a iterator to the first element of the Layout Vector.
		 *
		 * @return Returns a iterator to the first element of the Layout Vector.
		 */
		std::vector<FakeVertexBufferElement>::iterator begin();

		/**
		 *
		 * Returns a iterator to the last element of the Layout Vector.
		 *
		 * @return Returns a iterator to the last element of the Layout Vector
		 */
		std::vector<FakeVertexBufferElement>::iterator end();

		/**
		 *
		 * Returns a iterator to the first element of the Layout Vector.
		 *
		 * @return Returns a iterator to the first element of the Layout Vector
		 */
		std::vector<FakeVertexBufferElement>::const_iterator begin() const;

		/**
		 *
		 * Returns a iterator to the last element of the Layout Vector.
		 *
		 * @return Returns a iterator to the last element of the Layout Vector
		 */
		std::vector<FakeVertexBufferElement>::const_iterator end() const;
	};

