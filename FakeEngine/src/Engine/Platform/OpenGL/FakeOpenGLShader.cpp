#include "FakePch.h"
#include "FakeOpenGLShader.h"

#include "Engine/Core/FakeVirtualFileSystem.h"
#include "Engine/Renderer/FakeRenderer.h"

namespace Utils
	{
	static bool fake_is_type_string_resource(const FakeString &type)
		{
		if (type == "sampler1D")		return true;
		if (type == "sampler2D")		return true;
		if (type == "sampler2DMS")		return true;
		if (type == "samplerCube")		return true;
		if (type == "sampler2DShadow")	return true;

		return false;
		}

	static FakeString fake_extract_name(const FakeString &path)
		{
		FakeString result = path.Substr(path.LastIndexOf('/') + 1);
		if (result.Contains("."))
			result = result.Substr(0, result.Find("."));

		return result;
		}

	static const char *fake_find_token(const char *str, const FakeString &token)
		{
		const char *t = str;
		while (t = strstr(t, *token))
			{
			bool left = str == t || isspace(t[-1]);
			bool right = !t[token.Length()] || isspace(t[token.Length()]);
			if (left && right)
				return t;

			t += token.Length();
			}
		return nullptr;
		}

	static const char *fake_find_token(const FakeString &string, const FakeString &token)
		{
		return fake_find_token(*string, token);
		}

	static std::vector<FakeString> fake_split_string(const FakeString &string, const FakeString &delimiters)
		{
		uint32 start = 0;
		uint32 end = string.Find(delimiters);

		std::vector<FakeString> result;

		while (end <= FakeString::NPOS)
			{
			FakeString token = string.Substr(start, end - start);

			if (end == FakeString::NPOS)
				break;

			if (!token.IsEmpty())
				result.push_back(token);

			start = end + 1;
			end = string.Find(delimiters, start);
			}

		return result;
		}

	static std::vector<FakeString> fake_split_string(const FakeString &string, const char delimiter)
		{
		return fake_split_string(string, std::string(1, delimiter));
		}

	static std::vector<FakeString> fake_tokenize(const FakeString &string)
		{
		return fake_split_string(string, " \t\n\r");
		}

	static std::vector<FakeString> fake_get_lines(const FakeString &string)
		{
		return fake_split_string(string, "\n");
		}

	static FakeString fake_get_block(const char *str, const char **outPosition)
		{
		const char *end = strstr(str, "}");
		if (!end)
			return str;

		if (outPosition)
			*outPosition = end;

		uint32 length = (uint32)(end - str + 1);
		return std::string(str, length);
		}

	static FakeString fake_get_statement(const char *str, const char **outPosition)
		{
		const char *end = strstr(str, ";");
		if (!end)
			return str;

		if (outPosition)
			*outPosition = end;
			
		uint32 length = (uint32)(end - str + 1);
		return std::string(str, length);
		}

	static bool fake_starts_with(const FakeString &string, const FakeString &start)
		{
		return string.Find(start) == 0;
		}

	static GLenum fake_shader_type_from_string(const FakeString &type)
		{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;
		if (type == "compute")
			return GL_COMPUTE_SHADER;

		return GL_NONE;
		}
	}

FakeOpenGLShader::FakeOpenGLShader(const FakeString &filePath)
	{
	AssetPath = FakeVirtualFileSystem::Get()->GetAbsoluteFilePath(filePath);
	Name = Utils::fake_extract_name(AssetPath);
	FAKE_LOG_TRACE("Loading Shader %s", *Name);
	Reload();
	}

FakeOpenGLShader::FakeOpenGLShader(const FakeString &vertexSrc, const FakeString &fragmentSrc)
	{
	ShaderSources.insert({ GL_VERTEX_SHADER, *vertexSrc});
	ShaderSources.insert({ GL_FRAGMENT_SHADER, *fragmentSrc});
	Load("", false);
	}

FakeOpenGLShader::FakeOpenGLShader(const FakeString &name, const FakeString &vertexSrc, const FakeString &fragmentSrc)
	: Name(name)
	{
	ShaderSources.insert({ GL_VERTEX_SHADER, *vertexSrc});
	ShaderSources.insert({ GL_FRAGMENT_SHADER, *fragmentSrc});
	Load("", false);
	}

void FakeOpenGLShader::Bind() const
	{
	FakeRenderer::Submit([=]() { glUseProgram(RendererID); });
	}

void FakeOpenGLShader::Unbind() const
	{
	FakeRenderer::Submit([]() { glUseProgram(0); });
	}

void FakeOpenGLShader::Reload()
	{
	if (AssetPath.IsEmpty()) return;

	if (FakeVirtualFileSystem::Get()->FileExists(AssetPath))
		{
		FakeString source = FakeVirtualFileSystem::Get()->ReadTextFile(AssetPath);
		Load(source);
		}
	else
		{
		FAKE_LOG_ERROR("Shader %s not found!", *AssetPath);
		}
	}

void FakeOpenGLShader::UploadUniformBuffer(const FakeUniformBufferBase &uniformBuffer)
	{
	for (uint32 i = 0; i < uniformBuffer.GetUniformCount(); i++)
		{
		const FakeUniformDecl &decl = uniformBuffer.GetUniforms()[i];
		switch (decl.Type)
			{
			case FakeUniformType::Float:
				{
				const FakeString &name = decl.Name;
				float value = *(float*)(uniformBuffer.GetBuffer() + decl.Offset);
				FakeRenderer::Submit([=]()
					{
					UploadUniformFloat(name, value);
					});
				break;
				}

			case FakeUniformType::Int32:
				{
				const FakeString &name = decl.Name;
				int32 value = *(int32*)(uniformBuffer.GetBuffer() + decl.Offset);
				FakeRenderer::Submit([=]()
					{
					UploadUniformInt(name, value);
					});
				break;
				}

			case FakeUniformType::Float2:
				{
				const FakeString &name = decl.Name;
				FakeVec2f &values = *(FakeVec2f*)(uniformBuffer.GetBuffer() + decl.Offset);
				FakeRenderer::Submit([=]()
					{
					UploadUniformFloat2(name, values);
					});
				break;
				}

			case FakeUniformType::Float3:
				{
				const FakeString &name = decl.Name;
				FakeVec3f &values = *(FakeVec3f*)(uniformBuffer.GetBuffer() + decl.Offset);
				FakeRenderer::Submit([=]()
					{
					UploadUniformFloat3(name, values);
					});
				break;
				}

			case FakeUniformType::Float4:
				{
				const FakeString &name = decl.Name;
				FakeVec4f &values = *(FakeVec4f*)(uniformBuffer.GetBuffer() + decl.Offset);
				FakeRenderer::Submit([=]()
					{
					UploadUniformFloat4(name, values);
					});
				break;
				}

			case FakeUniformType::Matrix2x2:
				{
				const FakeString &name = decl.Name;
				FakeMat2f &values = *(FakeMat2f*)(uniformBuffer.GetBuffer() + decl.Offset);
				FakeRenderer::Submit([=]()
					{
					UploadUniformMat2(name, values);
					});
				break;
				}

			case FakeUniformType::Matrix3x3:
				{
				const FakeString &name = decl.Name;
				FakeMat3f &values = *(FakeMat3f*)(uniformBuffer.GetBuffer() + decl.Offset);
				FakeRenderer::Submit([=]()
					{
					UploadUniformMat3(name, values);
					});
				break;
				}

			case FakeUniformType::Matrix4x4:
				{
				const FakeString &name = decl.Name;
				FakeMat4f &values = *(FakeMat4f*)(uniformBuffer.GetBuffer() + decl.Offset);
				FakeRenderer::Submit([=]()
					{
					UploadUniformMat4(name, values);
					});
				break;
				}
			}
		}
	}

void FakeOpenGLShader::SetVSMaterialUniformBuffer(FakeAllocator buffer)
	{
	FakeRenderer::Submit([this, buffer]()
		{
		glUseProgram(RendererID);
		ResolveAndSetUniforms(VSMaterialUniformBuffer, buffer);
		});
	}

void FakeOpenGLShader::SetFSMaterialUniformBuffer(FakeAllocator buffer)
	{
	FakeRenderer::Submit([this, buffer]()
		{
		glUseProgram(RendererID);
		ResolveAndSetUniforms(FSMaterialUniformBuffer, buffer);
		});
	}

void FakeOpenGLShader::SetUniform(const FakeString &name, const void *data, uint32 size)
	{
	FakeRenderer::Submit([=]()
		{
		UploadUniformStruct(name, data, size);
		});
	}

void FakeOpenGLShader::SetUniform(const FakeString &name, float value)
	{
	FakeRenderer::Submit([=]()
		{
		UploadUniformFloat(name, value);
		});
	}

void FakeOpenGLShader::SetUniform(const FakeString &name, int32 value)
	{
	FakeRenderer::Submit([=]()
		{
		UploadUniformInt(name, value);
		});
	}

void FakeOpenGLShader::SetUniform(const FakeString &name, const FakeMat2f &value)
	{
	FakeRenderer::Submit([=]()
		{
		UploadUniformMat2(name, value);
		});
	}

void FakeOpenGLShader::SetUniform(const FakeString &name, const FakeMat3f &value)
	{
	FakeRenderer::Submit([=]()
		{
		UploadUniformMat3(name, value);
		});
	}

void FakeOpenGLShader::SetUniform(const FakeString &name, const FakeMat4f &value)
	{
	FakeRenderer::Submit([=]()
		{
		UploadUniformMat4(name, value);
		});
	}

void FakeOpenGLShader::SetUniform(const FakeString &name, const FakeVec2f &value)
	{
	FakeRenderer::Submit([=]()
		{
		UploadUniformFloat2(name, value);
		});
	}

void FakeOpenGLShader::SetUniform(const FakeString &name, const FakeVec3f &value)
	{
	FakeRenderer::Submit([=]()
		{
		UploadUniformFloat3(name, value);
		});
	}

void FakeOpenGLShader::SetUniform(const FakeString &name, const FakeVec4f &value)
	{
	FakeRenderer::Submit([=]()
		{
		UploadUniformFloat4(name, value);
		});
	}

void FakeOpenGLShader::SetUniform(const FakeString &name, const FakeVec2i &value)
	{
	FakeRenderer::Submit([=]()
		{
		UploadUniformInt2(name, value);
		});
	}

void FakeOpenGLShader::SetUniform(const FakeString &name, const FakeVec3i &value)
	{
	FakeRenderer::Submit([=]()
		{
		UploadUniformInt3(name, value);
		});
	}

void FakeOpenGLShader::SetUniform(const FakeString &name, const FakeVec4i &value)
	{
	FakeRenderer::Submit([=]()
		{
		UploadUniformInt4(name, value);
		});
	}

void FakeOpenGLShader::SetUniform(const FakeString &name, int32 *value, uint32 size)
	{
	FakeRenderer::Submit([=]()
		{
		UploadUniformIntArray(name, value, size);
		});
	}

void FakeOpenGLShader::SetUniform(const FakeString &name, float *value, uint32 size)
	{
	FakeRenderer::Submit([=]()
		{
		UploadUniformFloatArray(name, value, size);
		});
	}

void FakeOpenGLShader::SetUniform(const FakeString &name, const FakeMat4f &values, uint32 count)
	{
	FakeRenderer::Submit([=]()
		{
		UploadUniformMat4Array(name, values, count);
		});
	}

void FakeOpenGLShader::SetUniform(const FakeString &name, int32 v0, int32 v1)
	{
	FakeRenderer::Submit([=]()
		{
		UploadUniformInt2(name, { v0, v1 });
		});
	}

void FakeOpenGLShader::SetUniform(const FakeString &name, int32 v0, int32 v1, int32 v2)
	{
	FakeRenderer::Submit([=]()
		{
		UploadUniformInt3(name, { v0, v1, v2 });
		});
	}

void FakeOpenGLShader::SetUniform(const FakeString &name, int32 v0, int32 v1, int32 v2, int32 v3)
	{
	FakeRenderer::Submit([=]()
		{
		UploadUniformInt4(name, { v0, v1, v2, v3 });
		});
	}

void FakeOpenGLShader::SetUniform(const FakeString &name, float v0, float v1)
	{
	FakeRenderer::Submit([=]()
		{
		UploadUniformFloat2(name, { v0, v1 });
		});
	}

void FakeOpenGLShader::SetUniform(const FakeString &name, float v0, float v1, float v2)
	{
	FakeRenderer::Submit([=]()
		{
		UploadUniformFloat3(name, { v0, v1, v2 });
		});
	}

void FakeOpenGLShader::SetUniform(const FakeString &name, float v0, float v1, float v2, float v3)
	{
	FakeRenderer::Submit([=]()
		{
		UploadUniformFloat4(name, { v0, v1, v2, v3 });
		});
	}

void FakeOpenGLShader::Load(const FakeString &source, bool shouldPreProcess)
	{
	if (shouldPreProcess)
		ShaderSources = PreProcess(source);

	if (!IsCompute)
		Parse();

	FakeRenderer::Submit([=]()
		{
		if (RendererID)
			glDeleteProgram(RendererID);
		
		CompileAndUploadShader();
		if (!IsCompute)
			ResolveUniforms();

		if (Loaded)
			{
			for (auto &callback : ShaderReloadedCallbacks)
				callback();
			}

		Loaded = true;
		});
	}

std::unordered_map<GLenum, std::string> FakeOpenGLShader::PreProcess(const FakeString &source)
	{
	std::unordered_map<uint32, std::string> shaderSources;

	FakeString typeToken = "#type";
	uint32 pos = source.Find(typeToken); // Start of shader type declaration line
	while (pos != FakeString::NPOS)
		{
		uint32 eol = source.Find("\n", pos); // End of shader type declaration line
		FAKE_ASSERT(eol != FakeString::NPOS, "Syntax Error!");

		uint32 begin = pos + typeToken.Length() + 1; // Start of shader type name (after "#type " keyword)
		FakeString type = source.Substr(begin, eol);
		GLenum glType = Utils::fake_shader_type_from_string(type);
		FAKE_ASSERT(glType, "Invalid Shader type specified!");

		uint32 nextLinePos = source.FirstIndexNotOf("\n", eol); // Start of shader code after shader type declaration line
		FAKE_ASSERT(nextLinePos != FakeString::NPOS, "Syntax Error!");
		pos = source.Find(typeToken, nextLinePos); // Start of next shader type declaration line

		FakeString newSrc = (pos == FakeString::NPOS) ? source.Substr(nextLinePos) : source.Substr(nextLinePos, pos - nextLinePos + typeToken.Length() + type.Length());
		newSrc = newSrc.Replace("\r", "");
		newSrc = newSrc.Replace("\n\n", "\n");
		shaderSources[glType] = *newSrc;

		if (glType == GL_COMPUTE_SHADER)
			{
			IsCompute = true;
			break;
			}
		}

	return shaderSources;
	}

void FakeOpenGLShader::Parse()
	{
	const char *token;
	const char *vstr;
	const char *fstr;

	Resources.clear();
	Structs.clear();
	VSMaterialUniformBuffer.Reset();
	FSMaterialUniformBuffer.Reset();

	auto &vertexSource = ShaderSources[GL_VERTEX_SHADER];
	auto &fragmentSource = ShaderSources[GL_FRAGMENT_SHADER];

	// Vertex Shader
	vstr = vertexSource.c_str();
	while (token = Utils::fake_find_token(vstr, "struct"))
		ParseUniformStruct(Utils::fake_get_block(token, &vstr), FakeShaderDomain::Vertex);

	vstr = vertexSource.c_str();
	while (token = Utils::fake_find_token(vstr, "uniform"))
		ParseUniform(Utils::fake_get_statement(token, &vstr), FakeShaderDomain::Vertex);

	// Fragment Shader
	fstr = fragmentSource.c_str();
	while (token = Utils::fake_find_token(fstr, "struct"))
		ParseUniformStruct(Utils::fake_get_block(token, &fstr), FakeShaderDomain::Fragment);

	fstr = fragmentSource.c_str();
	while (token = Utils::fake_find_token(fstr, "uniform"))
		ParseUniform(Utils::fake_get_statement(token, &fstr), FakeShaderDomain::Fragment);

	}

void FakeOpenGLShader::ParseUniform(const FakeString &statement, FakeShaderDomain domain)
	{
	std::vector<FakeString> tokens = Utils::fake_tokenize(statement);
	uint32 index = 0;

	if (tokens.size() == 0)
		return;

	index++; // "uniform"
	FakeString typeString = tokens[index++];
	FakeString name = tokens[index++];

	// Strip ; from name if present
	if (const char *s = strstr(*name, ";"))
		name = std::string(*name, s - *name);

	FakeString n(name);
	int32 count = 1;
	const char *namestr = *n;
	if (const char *s = strstr(namestr, "["))
		{
		name = std::string(namestr, s - namestr);

		const char *end = strstr(namestr, "]");
		std::string c(s + 1, end - s);
		count = atoi(c.c_str());
		}

	if (Utils::fake_is_type_string_resource(typeString))
		{
		FakeShaderResourceDeclaration *declaration = new FakeOpenGLResourceDeclaration(FakeOpenGLResourceDeclaration::StringToType(typeString), name, count);
		Resources.push_back(declaration);
		}
	else
		{
		FakeOpenGLShaderUniformDeclaration::Type t = FakeOpenGLShaderUniformDeclaration::StringToType(typeString);
		FakeOpenGLShaderUniformDeclaration *declaration = nullptr;

		if (t == FakeOpenGLShaderUniformDeclaration::Type::NONE)
			{
			// Find struct
			FakeShaderStruct *s = FindStruct(typeString);
			FAKE_ASSERT(s, "");
			declaration = new FakeOpenGLShaderUniformDeclaration(domain, s, name, count);
			}
		else
			{
			declaration = new FakeOpenGLShaderUniformDeclaration(domain, t, name, count);
			}

		if (Utils::fake_starts_with(name, "r_"))
			{
			if (domain == FakeShaderDomain::Vertex)
				((FakeOpenGLShaderUniformBufferDeclaration*)VSRendererUniformBuffers.front())->PushUniform(declaration);
			else if (domain == FakeShaderDomain::Fragment)
				((FakeOpenGLShaderUniformBufferDeclaration*)FSRendererUniformBuffers.front())->PushUniform(declaration);
			}
		else
			{
			if (domain == FakeShaderDomain::Vertex)
				{
				if (!VSMaterialUniformBuffer)
					VSMaterialUniformBuffer.Reset(new FakeOpenGLShaderUniformBufferDeclaration("", domain));

				VSMaterialUniformBuffer->PushUniform(declaration);
				}
			else if (domain == FakeShaderDomain::Fragment)
				{
				if (!FSMaterialUniformBuffer)
					FSMaterialUniformBuffer.Reset(new FakeOpenGLShaderUniformBufferDeclaration("", domain));

				FSMaterialUniformBuffer->PushUniform(declaration);
				}
			}
		}
	}

void FakeOpenGLShader::ParseUniformStruct(const FakeString &block, FakeShaderDomain domain)
	{
	std::vector<FakeString> tokens = Utils::fake_tokenize(block);

	uint32 index = 0;
	index++; // struct
	FakeString name = tokens[index++];
	FakeShaderStruct *uniformStruct = new FakeShaderStruct(name);
	index++; // {
	while (index < tokens.size())
		{
		if (tokens[index] == "}")
			break;

		FakeString type = tokens[index++];
		FakeString name = tokens[index++];

		// Strip ; from name if present
		if (const char *s = strstr(*name, ";"))
			name = std::string(*name, s - *name);

		uint32 count = 1;
		const char *namestr = *name;
		if (const char *s = strstr(namestr, "["))
			{
			name = std::string(namestr, s - namestr);

			const char *end = strstr(namestr, "]");
			std::string c(s + 1, end - s);
			count = atoi(c.c_str());
			}
		FakeShaderUniformDeclaration *field = new FakeOpenGLShaderUniformDeclaration(domain, FakeOpenGLShaderUniformDeclaration::StringToType(type), name, count);
		uniformStruct->AddField(field);
		}

	Structs.push_back(uniformStruct);
	}

FakeShaderStruct *FakeOpenGLShader::FindStruct(const FakeString &name)
	{
	for (FakeShaderStruct *s : Structs)
		{
		if (s->GetName() == name)
			return s;
		}

	return nullptr;
	}

int32 FakeOpenGLShader::GetUniformLocation(const FakeString &name) const
	{
	if (UniformLocations.find(*name) == UniformLocations.end())
		{
		int32 result = glGetUniformLocation(RendererID, *name);
		if (result == -1)
			FAKE_LOG_WARN("Could not find uniform '%s' in shader", *name);

		// TODO: insert into Uniform Locations
		return result;
		}

	return UniformLocations.at(*name);
	}

void FakeOpenGLShader::ResolveUniforms()
	{
	glUseProgram(RendererID);

	for (size_t i = 0; i < VSRendererUniformBuffers.size(); i++)
		{
		FakeOpenGLShaderUniformBufferDeclaration *decl = (FakeOpenGLShaderUniformBufferDeclaration*)VSRendererUniformBuffers[i];
		const FakeShaderUniformList &uniforms = decl->GetUniformDeclarations();
		for (size_t j = 0; j < uniforms.size(); j++)
			{
			FakeOpenGLShaderUniformDeclaration *uniform = (FakeOpenGLShaderUniformDeclaration*)uniforms[j];
			if (uniform->GetType() == FakeOpenGLShaderUniformDeclaration::Type::STRUCT)
				{
				const FakeShaderStruct &s = uniform->GetShaderUniformStruct();
				const auto &fields = s.GetFields();
				for (size_t k = 0; k < fields.size(); k++)
					{
					FakeOpenGLShaderUniformDeclaration *field = (FakeOpenGLShaderUniformDeclaration*)fields[k];
					field->Location = GetUniformLocation(uniform->Name + "." + field->Name);
					}
				}
			else
				{
				uniform->Location = GetUniformLocation(uniform->Name);
				}
			}
		}

	for (size_t i = 0; i < FSRendererUniformBuffers.size(); i++)
		{
		FakeOpenGLShaderUniformBufferDeclaration *decl = (FakeOpenGLShaderUniformBufferDeclaration*)FSRendererUniformBuffers[i];
		const FakeShaderUniformList &uniforms = decl->GetUniformDeclarations();
		for (size_t j = 0; j < uniforms.size(); j++)
			{
			FakeOpenGLShaderUniformDeclaration *uniform = (FakeOpenGLShaderUniformDeclaration*)uniforms[j];
			if (uniform->GetType() == FakeOpenGLShaderUniformDeclaration::Type::STRUCT)
				{
				const FakeShaderStruct &s = uniform->GetShaderUniformStruct();
				const auto &fields = s.GetFields();
				for (size_t k = 0; k < fields.size(); k++)
					{
					FakeOpenGLShaderUniformDeclaration *field = (FakeOpenGLShaderUniformDeclaration*)fields[k];
					field->Location = GetUniformLocation(uniform->Name + "." + field->Name);
					}
				}
			else
				{
				uniform->Location = GetUniformLocation(uniform->Name);
				}
			}
		}

	{
	const auto &decl = VSMaterialUniformBuffer;
	if (decl)
		{
		const FakeShaderUniformList &uniforms = decl->GetUniformDeclarations();
		for (size_t j = 0; j < uniforms.size(); j++)
			{
			FakeOpenGLShaderUniformDeclaration *uniform = (FakeOpenGLShaderUniformDeclaration*)uniforms[j];
			if (uniform->GetType() == FakeOpenGLShaderUniformDeclaration::Type::STRUCT)
				{
				const FakeShaderStruct &s = uniform->GetShaderUniformStruct();
				const auto &fields = s.GetFields();
				for (size_t k = 0; k < fields.size(); k++)
					{
					FakeOpenGLShaderUniformDeclaration *field = (FakeOpenGLShaderUniformDeclaration*)fields[k];
					field->Location = GetUniformLocation(uniform->Name + "." + field->Name);
					}
				}
			else
				{
				uniform->Location = GetUniformLocation(uniform->Name);
				}
			}
		}
	}

	{
	const auto &decl = FSMaterialUniformBuffer;
	if (decl)
		{
		const FakeShaderUniformList &uniforms = decl->GetUniformDeclarations();
		for (size_t j = 0; j < uniforms.size(); j++)
			{
			FakeOpenGLShaderUniformDeclaration *uniform = (FakeOpenGLShaderUniformDeclaration*)uniforms[j];
			if (uniform->GetType() == FakeOpenGLShaderUniformDeclaration::Type::STRUCT)
				{
				const FakeShaderStruct &s = uniform->GetShaderUniformStruct();
				const auto &fields = s.GetFields();
				for (size_t k = 0; k < fields.size(); k++)
					{
					FakeOpenGLShaderUniformDeclaration *field = (FakeOpenGLShaderUniformDeclaration*)fields[k];
					field->Location = GetUniformLocation(uniform->Name + "." + field->Name);
					}
				}
			else
				{
				uniform->Location = GetUniformLocation(uniform->Name);
				}
			}
		}
	}

	uint32 sampler = 0;
	for (size_t i = 0; i < Resources.size(); i++)
		{
		FakeOpenGLResourceDeclaration *resource = (FakeOpenGLResourceDeclaration*)Resources[i];
		int32 location = GetUniformLocation(resource->Name);

		if (resource->GetCount() == 1)
			{
			resource->Register = sampler;
			if (location != -1)
				UploadUniformInt(location, sampler);

			sampler++;
			}
		else if (resource->GetCount() > 1)
			{
			resource->Register = sampler;
			uint32 count = resource->GetCount();
			int *samplers = new int[count];
			for (uint32 s = 0; s < count; s++)
				samplers[s] = sampler++;
			UploadUniformIntArray(resource->GetName(), samplers, count);
			delete[] samplers;
			}
		}
	}

void FakeOpenGLShader::CompileAndUploadShader()
	{
	std::vector<GLuint> shaderRendererIDs;

	GLuint program = glCreateProgram();
	for (auto &kv : ShaderSources)
		{
		GLenum type = kv.first;
		FakeString &source = FakeString(kv.second);

		GLuint shaderRendererID = glCreateShader(type);
		const GLchar *sourceCstr = (const GLchar*)*source;
		glShaderSource(shaderRendererID, 1, &sourceCstr, 0);

		glCompileShader(shaderRendererID);

		GLint isCompiled = 0;
		glGetShaderiv(shaderRendererID, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
			{
			GLint maxLength = 0;
			glGetShaderiv(shaderRendererID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(shaderRendererID, maxLength, &maxLength, &infoLog[0]);

			FAKE_LOG_ERROR("Shader compilation failed %s:\n%s", *AssetPath, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(shaderRendererID);

			FAKE_ASSERT(false, "Failed");
			}

		shaderRendererIDs.push_back(shaderRendererID);
		glAttachShader(program, shaderRendererID);
		}

	// Link our program
	glLinkProgram(program);

	// Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, (int*) &isLinked);
	if (isLinked == GL_FALSE)
		{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
		FAKE_LOG_ERROR("Shader linking failed %s:\n%s", *AssetPath, &infoLog[0]);

		// Don't leak shaders either.
		for (auto id : shaderRendererIDs)
			glDeleteShader(id);

		// We don't need the program anymore.
		glDeleteProgram(program);

		return;
		}

	// Always detach shaders after a successful link.
	for (auto id : shaderRendererIDs)
		glDetachShader(program, id);

	RendererID = program;
	}

void FakeOpenGLShader::ResolveAndSetUniforms(const FakeRef<FakeOpenGLShaderUniformBufferDeclaration> &decl, FakeAllocator buffer)
	{
	const FakeShaderUniformList &uniforms = decl->GetUniformDeclarations();
	for (size_t i = 0; i < uniforms.size(); i++)
		{
		FakeOpenGLShaderUniformDeclaration *uniform = (FakeOpenGLShaderUniformDeclaration*)uniforms[i];
		if (uniform->IsArray())
			ResolveAndSetUniformArray(uniform, buffer);
		else
			ResolveAndSetUniform(uniform, buffer);
		}
	}

void FakeOpenGLShader::ResolveAndSetUniform(FakeOpenGLShaderUniformDeclaration *uniform, FakeAllocator buffer)
	{
	if (uniform->GetLocation() == -1)
		return;

	FAKE_ASSERT(uniform->GetLocation() != -1, "Uniform has invalid location!");

	uint32 offset = uniform->GetOffset();
	switch (uniform->GetType())
		{
		case FakeOpenGLShaderUniformDeclaration::Type::BOOL:
			UploadUniformFloat(uniform->GetLocation(), *(bool*) &buffer.Data[offset]);
			break;

		case FakeOpenGLShaderUniformDeclaration::Type::FLOAT32:
			UploadUniformFloat(uniform->GetLocation(), *(float*) &buffer.Data[offset]);
			break;

		case FakeOpenGLShaderUniformDeclaration::Type::INT32:
			UploadUniformInt(uniform->GetLocation(), *(int32*) &buffer.Data[offset]);
			break;

		case FakeOpenGLShaderUniformDeclaration::Type::VEC2:
			UploadUniformFloat2(uniform->GetLocation(), *(FakeVec2f*) &buffer.Data[offset]);
			break;

		case FakeOpenGLShaderUniformDeclaration::Type::VEC3:
			UploadUniformFloat3(uniform->GetLocation(), *(FakeVec3f*) &buffer.Data[offset]);
			break;

		case FakeOpenGLShaderUniformDeclaration::Type::VEC4:
			UploadUniformFloat4(uniform->GetLocation(), *(FakeVec4f*) &buffer.Data[offset]);
			break;

		case FakeOpenGLShaderUniformDeclaration::Type::MAT2:
			UploadUniformMat2(uniform->GetLocation(), *(FakeMat2f*) &buffer.Data[offset]);
			break;

		case FakeOpenGLShaderUniformDeclaration::Type::MAT3:
			UploadUniformMat3(uniform->GetLocation(), *(FakeMat3f*) &buffer.Data[offset]);
			break;

		case FakeOpenGLShaderUniformDeclaration::Type::MAT4:
			UploadUniformMat4(uniform->GetLocation(), *(FakeMat4f*) &buffer.Data[offset]);
			break;

		case FakeOpenGLShaderUniformDeclaration::Type::STRUCT:
			UploadUniformStruct(uniform, buffer.Data, offset);
			break;

		default:
			FAKE_ASSERT(false, "Unknown uniform type!");
		}
	}

void FakeOpenGLShader::ResolveAndSetUniformArray(FakeOpenGLShaderUniformDeclaration *uniform, FakeAllocator buffer)
	{
	uint32 offset = uniform->GetOffset();
	switch (uniform->GetType())
		{
		case FakeOpenGLShaderUniformDeclaration::Type::BOOL:
			UploadUniformFloat(uniform->GetLocation(), *(bool*) &buffer.Data[offset]);
			break;

		case FakeOpenGLShaderUniformDeclaration::Type::FLOAT32:
			UploadUniformFloat(uniform->GetLocation(), *(float*) &buffer.Data[offset]);
			break;

		case FakeOpenGLShaderUniformDeclaration::Type::INT32:
			UploadUniformInt(uniform->GetLocation(), *(int32*) &buffer.Data[offset]);
			break;

		case FakeOpenGLShaderUniformDeclaration::Type::VEC2:
			UploadUniformFloat2(uniform->GetLocation(), *(FakeVec2f*) &buffer.Data[offset]);
			break;

		case FakeOpenGLShaderUniformDeclaration::Type::VEC3:
			UploadUniformFloat3(uniform->GetLocation(), *(FakeVec3f*) &buffer.Data[offset]);
			break;

		case FakeOpenGLShaderUniformDeclaration::Type::VEC4:
			UploadUniformFloat4(uniform->GetLocation(), *(FakeVec4f*) &buffer.Data[offset]);
			break;

		case FakeOpenGLShaderUniformDeclaration::Type::MAT2:
			UploadUniformMat2(uniform->GetLocation(), *(FakeMat2f*) &buffer.Data[offset]);
			break;

		case FakeOpenGLShaderUniformDeclaration::Type::MAT3:
			UploadUniformMat3(uniform->GetLocation(), *(FakeMat3f*) &buffer.Data[offset]);
			break;

		case FakeOpenGLShaderUniformDeclaration::Type::MAT4:
			UploadUniformMat4Array(uniform->GetLocation(), *(FakeMat4f*) &buffer.Data[offset], uniform->GetCount());
			break;

		case FakeOpenGLShaderUniformDeclaration::Type::STRUCT:
			UploadUniformStruct(uniform, buffer.Data, offset);
			break;

		default:
			FAKE_ASSERT(false, "Unknown uniform type!");
			break;
		}
	}

void FakeOpenGLShader::ResolveAndSetUniformField(const FakeOpenGLShaderUniformDeclaration &field, Byte *data, int32_t offset)
	{
	switch (field.GetType())
		{
		case FakeOpenGLShaderUniformDeclaration::Type::BOOL:
			UploadUniformFloat(field.GetLocation(), *(bool*) &data[offset]);
			break;

		case FakeOpenGLShaderUniformDeclaration::Type::FLOAT32:
			UploadUniformFloat(field.GetLocation(), *(float*) &data[offset]);
			break;

		case FakeOpenGLShaderUniformDeclaration::Type::INT32:
			UploadUniformInt(field.GetLocation(), *(int32*) &data[offset]);
			break;

		case FakeOpenGLShaderUniformDeclaration::Type::VEC2:
			UploadUniformFloat2(field.GetLocation(), *(FakeVec2f*) &data[offset]);
			break;

		case FakeOpenGLShaderUniformDeclaration::Type::VEC3:
			UploadUniformFloat3(field.GetLocation(), *(FakeVec3f*) &data[offset]);
			break;

		case FakeOpenGLShaderUniformDeclaration::Type::VEC4:
			UploadUniformFloat4(field.GetLocation(), *(FakeVec4f*) &data[offset]);
			break;

		case FakeOpenGLShaderUniformDeclaration::Type::MAT2:
			UploadUniformMat2(field.GetLocation(), *(FakeMat2f*) &data[offset]);
			break;

		case FakeOpenGLShaderUniformDeclaration::Type::MAT3:
			UploadUniformMat3(field.GetLocation(), *(FakeMat3f*) &data[offset]);
			break;

		case FakeOpenGLShaderUniformDeclaration::Type::MAT4:
			UploadUniformMat4(field.GetLocation(), *(FakeMat4f*) &data[offset]);
			break;

		default:
			FAKE_ASSERT(false, "Unknown uniform type!");
			break;
		}
	}

void FakeOpenGLShader::UploadUniformInt(uint32 location, int32 value)
	{
	glUniform1i(location, value);
	}

void FakeOpenGLShader::UploadUniformInt2(uint32 location, const FakeVec2i &value)
	{
	glUniform2i(location, value.X, value.Y);
	}

void FakeOpenGLShader::UploadUniformInt3(uint32 location, const FakeVec3i &value)
	{
	glUniform3i(location, value.X, value.Y, value.Z);
	}

void FakeOpenGLShader::UploadUniformInt4(uint32 location, const FakeVec4i &value)
	{
	glUniform4i(location, value.X, value.Y, value.Z, value.W);
	}

void FakeOpenGLShader::UploadUniformIntArray(uint32 location, int32 *values, int32 count)
	{
	glUniform1iv(location, count, values);
	}

void FakeOpenGLShader::UploadUniformFloat(uint32 location, float value)
	{
	glUniform1f(location, value);
	}

void FakeOpenGLShader::UploadUniformFloat2(uint32 location, const FakeVec2f &value)
	{
	glUniform2f(location, value.X, value.Y);
	}

void FakeOpenGLShader::UploadUniformFloat3(uint32 location, const FakeVec3f &value)
	{
	glUniform3f(location, value.X, value.Y, value.Z);
	}

void FakeOpenGLShader::UploadUniformFloat4(uint32 location, const FakeVec4f &value)
	{
	glUniform4f(location, value.X, value.Y, value.Z, value.W);
	}

void FakeOpenGLShader::UploadUniformFloatArray(uint32 location, float *values, int32 count)
	{
	glUniform1fv(location, count, values);
	}

void FakeOpenGLShader::UploadUniformMat2(uint32 location, const FakeMat2f &values)
	{
	glUniformMatrix2fv(location, 1, GL_FALSE, *values);
	}

void FakeOpenGLShader::UploadUniformMat3(uint32 location, const FakeMat3f &values)
	{
	glUniformMatrix3fv(location, 1, GL_FALSE, *values);
	}

void FakeOpenGLShader::UploadUniformMat4(uint32 location, const FakeMat4f &values)
	{
	glUniformMatrix4fv(location, 1, GL_FALSE, *values);
	}

void FakeOpenGLShader::UploadUniformMat4Array(uint32 location, const FakeMat4f &values, uint32 count)
	{
	glUniformMatrix4fv(location, count, GL_FALSE, *values);
	}

void FakeOpenGLShader::UploadUniformStruct(FakeOpenGLShaderUniformDeclaration *uniform, Byte *buffer, uint32 offset)
	{
	const FakeShaderStruct &s = uniform->GetShaderUniformStruct();
	const auto &fields = s.GetFields();
	for (size_t k = 0; k < fields.size(); k++)
		{
		FakeOpenGLShaderUniformDeclaration *field = (FakeOpenGLShaderUniformDeclaration*)fields[k];
		ResolveAndSetUniformField(*field, buffer, offset);
		offset += field->Size;
		}
	}

void FakeOpenGLShader::UploadUniformStruct(const FakeString &name, const void *data, uint32 size)
	{
	// TODO
	}

void FakeOpenGLShader::UploadUniformInt(const FakeString &name, int32 value)
	{
	glUseProgram(RendererID);
	int32 location = GetUniformLocation(name);
	UploadUniformInt(location, value);
	}

void FakeOpenGLShader::UploadUniformInt2(const FakeString &name, const FakeVec2i &values)
	{
	glUseProgram(RendererID);
	int32 location = GetUniformLocation(name);
	UploadUniformInt2(location, values);
	}

void FakeOpenGLShader::UploadUniformInt3(const FakeString &name, const FakeVec3i &values)
	{
	glUseProgram(RendererID);
	int32 location = GetUniformLocation(name);
	UploadUniformInt3(location, values);
	}

void FakeOpenGLShader::UploadUniformInt4(const FakeString &name, const FakeVec4i &values)
	{
	glUseProgram(RendererID);
	int32 location = GetUniformLocation(name);
	UploadUniformInt4(location, values);
	}

void FakeOpenGLShader::UploadUniformIntArray(const FakeString &name, int32 *values, uint32 count)
	{
	glUseProgram(RendererID);
	int32 location = GetUniformLocation(name);
	UploadUniformIntArray(location, values, count);
	}

void FakeOpenGLShader::UploadUniformFloat(const FakeString &name, float value)
	{
	glUseProgram(RendererID);
	int32 location = GetUniformLocation(name);
	UploadUniformFloat(location, value);
	}

void FakeOpenGLShader::UploadUniformFloat2(const FakeString &name, const FakeVec2f &values)
	{
	glUseProgram(RendererID);
	int32 location = GetUniformLocation(name);
	UploadUniformFloat2(location, values);
	}

void FakeOpenGLShader::UploadUniformFloat3(const FakeString &name, const FakeVec3f &values)
	{
	glUseProgram(RendererID);
	int32 location = GetUniformLocation(name);
	UploadUniformFloat3(location, values);
	}

void FakeOpenGLShader::UploadUniformFloat4(const FakeString &name, const FakeVec4f &values)
	{
	glUseProgram(RendererID);
	int32 location = GetUniformLocation(name);
	UploadUniformFloat4(location, values);
	}

void FakeOpenGLShader::UploadUniformFloatArray(const FakeString &name, float *values, uint32 count)
	{
	glUseProgram(RendererID);
	int32 location = GetUniformLocation(name);
	UploadUniformFloatArray(location, values, count);
	}

void FakeOpenGLShader::UploadUniformMat2(const FakeString &name, const FakeMat2f &value)
	{
	glUseProgram(RendererID);
	int32 location = GetUniformLocation(name);
	UploadUniformMat2(location, value);
	}

void FakeOpenGLShader::UploadUniformMat3(const FakeString &name, const FakeMat3f &value)
	{
	glUseProgram(RendererID);
	int32 location = GetUniformLocation(name);
	UploadUniformMat3(location, value);
	}

void FakeOpenGLShader::UploadUniformMat4(const FakeString &name, const FakeMat4f &value)
	{
	glUseProgram(RendererID);
	int32 location = GetUniformLocation(name);
	UploadUniformMat4(location, value);
	}

void FakeOpenGLShader::UploadUniformMat4Array(const FakeString &name, const FakeMat4f &values, uint32 count)
	{
	glUseProgram(RendererID);
	int32 location = GetUniformLocation(name);
	UploadUniformMat4Array(location, values, count);
	}

