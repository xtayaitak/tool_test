#include "stdafx.h"

#include "StringTool.h"

#include <windows.h>
#include <locale>
#include <codecvt>
#include <wincrypt.h>
namespace string_tool
{


	template<>
	int lexical_cast<int,std::wstring>(const std::wstring & s)
	{
		return std::stoi(s);
	}

	template<>
	unsigned long lexical_cast<unsigned long,std::wstring>(const std::wstring &  s)
	{
		return std::stoul(s);
	}

	template<>
	std::wstring lexical_cast<std::wstring , DWORD>(const DWORD  & value)
	{
		return std::to_wstring(value);
	}




	wstring CharToWide(const char * szBuf)
	{
		int nLenBytesRequire = ::MultiByteToWideChar(CP_ACP,
			0,
			szBuf,
			-1,
			NULL,
			0);
		wchar_t * szWbuf = new wchar_t[nLenBytesRequire];
		::MultiByteToWideChar(CP_ACP,
			0,
			szBuf,
			-1,
			szWbuf,
			nLenBytesRequire * (sizeof(wchar_t)));

		wstring ret_str = szWbuf;
		delete[] szWbuf;
		return ret_str;
	}

	string WideToChar(const wchar_t * szWBuf)
	{
		BOOL bOk = FALSE;
		int nLen = ::WideCharToMultiByte(CP_ACP,
			0,
			szWBuf,
			-1,
			NULL,
			0,
			NULL,
			&bOk
			);
		char * szBuf = new char[nLen];
		::WideCharToMultiByte(CP_ACP,
			0,
			szWBuf,
			-1,
			szBuf,
			nLen,
			NULL,
			&bOk);
		string str = szBuf;
		delete[] szBuf;
		return str;
	}




	std::wstring utf8_to_wstring(const std::string& str)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
		return myconv.from_bytes(str);
	}
	std::string wstring_to_utf8(const std::wstring& str)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
		return myconv.to_bytes(str);
	}

	std::string gpk_to_utf8(const std::string & str)
	{
		return wstring_to_utf8(CharToWide(str.c_str()));
	}

	size_t GetHash(_In_ CONST std::string& str)
	{
		size_t result = 0;
		for (auto it = str.cbegin(); it != str.cend(); ++it) {
			result = (result * 131) + *it;
		}
		return result;
	}

	size_t GetHash(_In_ CONST std::wstring& wstr)
	{
		size_t result = 0;
		for (auto it = wstr.cbegin(); it != wstr.cend(); ++it) {
			result = (result * 131) + *it;
		}
		return result;
	}

	bool IsUTF8String(const char* str, int length)
	{
		int i = 0;
		int nBytes = 0;//UTF8����1-6���ֽڱ���,ASCII��һ���ֽ�
		unsigned char chr = 0;
		bool bAllAscii = true;//���ȫ������ASCII,˵������UTF-8

		while (i < length)
		{
			chr = *(str + i);
			if ((chr & 0x80) != 0)//��һλ����0˵������һ��ascii
				bAllAscii = false;
			if (nBytes == 0)//�����ֽ���
			{
				if ((chr & 0x80) != 0)
				{
					while ((chr & 0x80) != 0)
					{
						chr <<= 1;
						nBytes++;
					}
					if (nBytes < 2 || nBytes > 6)
						return false;//��һ���ֽ�����Ϊ110x xxxx
					nBytes--;//��ȥ����ռ��һ���ֽ�
				}
			}
			else//���ֽڳ��˵�һ���ֽ���ʣ�µ��ֽ�
			{
				if ((chr & 0xc0) != 0x80)
					return false;//ʣ�µ��ֽڶ���10xx xxxx����ʽ
				nBytes--;
			}
			++i;
		}
		if (bAllAscii)
			return false;
		return nBytes == 0;
	}

#define BUFMD5SIZE 1024
#define MD5LEN  16
	std::wstring GetBufferMd5(const char * buffer, size_t len)
	{
		std::wstring ret = L"";
		if (len <= 0)
			throw std::length_error("buffer size is error!");
		
		// Get handle to the crypto provider
		HCRYPTPROV hProv = 0;
		if (!CryptAcquireContext(&hProv,
			NULL,
			NULL,
			PROV_RSA_FULL,
			CRYPT_VERIFYCONTEXT))
		{
			DWORD dwStatus = GetLastError();
			throw std::exception("CryptAcquireContext failed");
		}


		HCRYPTHASH hHash = 0;
		if (!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash))
		{
			DWORD dwStatus = GetLastError();
			CryptReleaseContext(hProv, 0);
			throw std::exception("CryptAcquireContext failed");
			return FALSE;
		}


		int nCurPos = 0;
		int nRemain = len;
		DWORD cbRead = 0;
		BYTE rgbFile[BUFMD5SIZE];
		while (nRemain > 0)
		{
			//bResult = ReadFile(hFile, rgbFile, BUFMD5SIZE, &cbRead, NULL)
			if (nRemain > BUFMD5SIZE)
			{
				memcpy(rgbFile, buffer, BUFMD5SIZE);
				nRemain = nRemain - BUFMD5SIZE;
				cbRead = BUFMD5SIZE;
			}
			else
			{
				memcpy(rgbFile, buffer, nRemain);
				cbRead = nRemain;
				nRemain = 0;
			}

			if (!CryptHashData(hHash, rgbFile, cbRead, 0))
			{
				DWORD dwStatus = GetLastError();
				CryptDestroyHash(hHash);
				CryptReleaseContext(hProv, 0);
				throw std::exception("CryptHashData failed!");
			}
		}

		DWORD cbHash = MD5LEN;
		BYTE rgbHash[MD5LEN];
		if (CryptGetHashParam(hHash, HP_HASHVAL, rgbHash, &cbHash, 0))
		{
			//printf("MD5 hash of file %s is: ", filename);
			CHAR rgbDigits[] = "0123456789abcdef";
			for (DWORD i = 0; i < cbHash; i++)
			{
				//printf("%c%c", rgbDigits[rgbHash[i] >> 4],rgbDigits[rgbHash[i] & 0xf]);
				wchar_t szBuf[10] = { 0 };
				swprintf_s(szBuf, 10, L"%c%c", rgbDigits[rgbHash[i] >> 4], rgbDigits[rgbHash[i] & 0xf]);
				ret += szBuf;
			}
		}
		else
		{
			DWORD dwStatus = GetLastError();
			CryptDestroyHash(hHash);
			CryptReleaseContext(hProv, 0);
			throw std::exception("CryptGetHashParam failed!");
		}

		CryptDestroyHash(hHash);
		CryptReleaseContext(hProv, 0);

		return ret;
	}
	
}