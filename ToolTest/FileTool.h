#pragma once




#include <vector>
#include <string>
#include <Windows.h>

namespace file_tools
{ 
	std::vector<std::string> ReadAsciiFileLines(const std::wstring & file_name);
	std::vector<std::wstring> ReadUnicodeFileLines(const std::wstring & file_name);
	const std::wstring GetCurrentAppPath();
	std::wstring GetCurrentPath();
	std::wstring GetPathByPathFile(const std::wstring & strPathFile);
	std::wstring GetFileByPathFile(const std::wstring & strPathFile);
	BOOL  CreateDirectoryNested(const std::wstring &  path);//Ƕ�״����ļ���
	BOOL IsValidFilePath(const std::wstring & file_path);
	BOOL ReadUnicodeFile(_In_ CONST std::wstring& wsPath, _Out_ std::wstring& wsContent);
	BOOL WriteUnicodeFile(const std::wstring & file_name, const std::wstring & wsContent);
	BOOL  AppendUnicodeFile(_In_ CONST std::wstring& cwsPath, _In_ CONST std::wstring& cwsContent);
	BOOL ReadFile(const std::wstring & file_name, std::vector<char>  &content);
	std::string ReadFileToString(const std::wstring & file_name);
	BOOL FileExist(const std::wstring & file_name);
	BOOL WriteFile(const std::wstring & file_namme, const char * buffer, size_t size,DWORD open_flag = CREATE_ALWAYS);
	BOOL CreateUnicodeTextFile(_In_ CONST std::wstring& cwsPath);
	BOOL ReadAsciiFileLen(_In_ CONST std::wstring& cwsPath, _Out_ ULONG& ulFileLen);
	std::wstring CalcFileMd5(LPCTSTR szFileName);
	BOOL GetFileNameList(std::vector<std::wstring> & retFileNameList, const std::wstring & strFolder, const std::wstring & suffix);
	std::wstring ReadUtf8FileStr(const std::wstring & file_name);
	void WriteUtf8FileStr(const std::wstring & file_name, const std::wstring & file_context,bool bom = true);
	std::wstring GetFileType(const std::wstring & file_path);
	BOOL GetFileNameListNoPath(std::vector<std::wstring> & retFileNameList, const std::wstring & strFolder, const std::wstring & suffix);
	std::wstring GetTempFolder();
	DWORD64 GetFolderSize(const std::wstring & path);
	BOOL CreateNormalFile(const std::wstring & file_name);
	std::wstring GetTmpFileName();
	void AppendLine(const std::wstring & file_path,const std::string& s);
}


