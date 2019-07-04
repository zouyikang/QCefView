#include "stdafx.h"

#include <QCoreApplication>
#include <QDir>

#include "CCefSetting.h"
#include "CCefWindow.h"

CefString CCefSetting::browser_sub_process_path;

CefString CCefSetting::resource_directory_path;

CefString CCefSetting::locales_directory_path;

CefString CCefSetting::user_agent;

CefString CCefSetting::cache_path;

CefString CCefSetting::user_data_path;

int CCefSetting::persist_session_cookies;

int CCefSetting::persist_user_preferences;

CefString CCefSetting::locale;

int CCefSetting::remote_debugging_port;

cef_color_t CCefSetting::background_color;

CefString CCefSetting::accept_language_list;

void CCefSetting::initializeInstance()
{
	static CCefSetting s_instance;
}

CCefSetting::CCefSetting()
{
	QDir ExeDir = QDir::current();

	QString strExePath = ExeDir.filePath(RENDER_PROCESS_NAME);
	browser_sub_process_path.FromString(
		QDir::toNativeSeparators(strExePath).toStdString());

	QString strResPath = ExeDir.filePath(RESOURCE_DIRECTORY_NAME);
	resource_directory_path.FromString(
		QDir::toNativeSeparators(strResPath).toStdString());

	QDir ResPath(strResPath);
	locales_directory_path.FromString(
		QDir::toNativeSeparators(ResPath.filePath(LOCALES_DIRECTORY_NAME)).toStdString());

	QString userAgent(QCEF_USER_AGENT);
	if (CCefWindow::enable_high_dpi) {
		userAgent += " HighDPI";
	}
	user_agent.FromString(userAgent.toStdString());

	if (CCefWindow::enable_local_storage) {
		QString cachePath = CCefWindow::cache_filename;
		QDir d;
		if (d.mkpath(cachePath)) {
			cache_path.FromString(QDir::toNativeSeparators(cachePath).toStdString());
		} else {
			cache_path.FromString("");
		}
	}
}