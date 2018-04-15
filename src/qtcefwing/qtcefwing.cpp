#include "stdafx.h"

#pragma region cef_headers
#include <include/cef_app.h>
#pragma endregion cef_headers

#pragma region project_heasers
#include "CefViewRenderApp/QCefViewRenderApp.h"
#include "qtcefwing.h"
#pragma endregion project_heasers

#include <windows.h>


static std::string WStringToString(std::wstring wstr)
{
	std::string result;
	int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);
	if (len <= 0) {
		return result;
	}

	char* buffer = new char[len + 1];
	if (buffer == NULL) {
		return result;
	}

	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len, NULL, NULL);
	buffer[len] = '\0';               
	result.append(buffer);            
	delete[] buffer;                  

	return result;
}

int APIENTRY _tWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR lpCmdLine,
	_In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);

	FILE* file = fopen("render.log", "w");
	std::wstring wstring = lpCmdLine;
	std::string string = WStringToString(wstring);
	if (string.find("HighDPI") != std::string::npos) {
		if (file) {
			fputs(string.c_str(), file);
			fputs("HighDPI", file);
			fclose(file);
		}
		CefEnableHighDPISupport();
	} else {
		if (file) {
			fputs(string.c_str(), file);
			fputs("NO-HighDPI", file);
			fclose(file);
		}
	}

	CefRefPtr<QCefViewRenderApp> app(new QCefViewRenderApp);
	CefMainArgs main_args(hInstance);
	void* sandboxInfo = nullptr;
	int exit_code = CefExecuteProcess(main_args, app.get(), sandboxInfo);
	
	if (exit_code >= 0) {
		return exit_code;
	}
	
	return 0;
}