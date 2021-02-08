#include "FakePch.h"
#include "FakeWindowsFileDialogue.h"

FakeString FakeWindowsFileDialogue::OpenFileDialogueInternal(FILEOPENDIALOGOPTIONS options, bool open)
	{
	FakeString result = "";
	HRESULT hr = E_FAIL;

	if (open)
		hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void **>(&FileDialogue));
	else
		hr = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_ALL, IID_IFileSaveDialog, reinterpret_cast<void **>(&FileDialogue));

	if (!SUCCEEDED(hr))
		return result;

	if (Filter.HasFilters())
		{
		std::vector<COMDLG_FILTERSPEC> filters;
		for (auto &pair : Filter.GetFilters())
			{
			filters.push_back({ pair.first.W_Str(), pair.second.W_Str() });
			}

		FileDialogue->SetFileTypes((UINT) filters.size(), &filters[0]);
		}

	FileDialogue->SetOptions(options);
	hr = FileDialogue->Show(NULL);

	if (!SUCCEEDED(hr))
		{
		FileDialogue->Release();
		return result;
		}

	IShellItem *item;
	hr = FileDialogue->GetResult(&item);

	if (!SUCCEEDED(hr))
		{
		FileDialogue->Release();
		return result;
		}

	PWSTR filePath;
	hr = item->GetDisplayName(SIGDN_FILESYSPATH, &filePath);

	if (SUCCEEDED(hr))
		{
		size_t chars_converted = 0;
		char path[MAX_PATH];
		wcstombs_s(&chars_converted, path, filePath, MAX_PATH);

		result = path;
		CoTaskMemFree(filePath);
		}

	item->Release();
	FileDialogue->Release();
	return result;
	}

FakeString FakeWindowsFileDialogue::SelectDirectory()
	{
	return OpenFileDialogueInternal(FOS_PICKFOLDERS | FOS_PATHMUSTEXIST, true);
	}

FakeString FakeWindowsFileDialogue::SelectFile()
	{
	return OpenFileDialogueInternal(FOS_FILEMUSTEXIST | FOS_PATHMUSTEXIST, true);
	}

FakeString FakeWindowsFileDialogue::SaveFile()
	{
	return OpenFileDialogueInternal(FOS_PATHMUSTEXIST, false);
	}

