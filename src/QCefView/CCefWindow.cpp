#include "stdafx.h"
#pragma region qt_headers
#include <QCoreApplication>
#include <QResizeEvent>
#include <QPaintDevice>
#include <QPainter>
#pragma endregion qt_headers

#include "CCefWindow.h"
#include "CCefManager.h"

#define CEF_BROWSER_WINDOW_CLASS_NAME_A "CefBrowserWindow"

bool CCefWindow::enable_high_dpi;

bool CCefWindow::enable_local_storage;

QString CCefWindow::cache_filename;

CCefWindow::CCefWindow(bool dpi, bool cache, const QString& filename, QWindow* parent)
	: QWindow(parent)
	, hwndCefBrowser_(nullptr)
{
	setFlags(Qt::FramelessWindowHint);
	enable_high_dpi = dpi;
	enable_local_storage = cache;
	cache_filename = filename;

	CCefManager::getInstance().initializeCef();
}

CCefWindow::~CCefWindow()
{
	destroy();
	
	if (hwndCefBrowser_)
		hwndCefBrowser_ = nullptr;

	CCefManager::getInstance().uninitializeCef();
}

void CCefWindow::updateCefBrowserWindow()
{
	if (!hwndCefBrowser_)
		hwndCefBrowser_ = ::FindWindowExA((HWND)winId(), nullptr, CEF_BROWSER_WINDOW_CLASS_NAME_A, nullptr);

	if (hwndCefBrowser_)
		::MoveWindow(hwndCefBrowser_, 0, 0, width(), height(), TRUE);
}

void CCefWindow::exposeEvent(QExposeEvent *e)
{
	updateCefBrowserWindow();
	return __super::exposeEvent(e);
}

void CCefWindow::resizeEvent(QResizeEvent *e)
{
	updateCefBrowserWindow();
	return __super::resizeEvent(e);
}