#ifndef QCEFVIEWHANDLER_H_
#define QCEFVIEWHANDLER_H_
#pragma once

#pragma region std_headers
#include <list>
#include <map>
#include <set>
#include <string>
#include <mutex>
#include <QPointer>
#pragma endregion std_headers

#pragma region cef_headers
#include <include/cef_client.h>
#include <include/wrapper/cef_message_router.h>
#pragma endregion cef_headers

#include "../CCefWindow.h"
#include "QCefQueryHandler.h"

#include <QObject>

class QCefViewBrowserHandler
	: public QObject
	, public CefClient
	, public CefContextMenuHandler
	, public CefDisplayHandler
	, public CefDragHandler
	, public CefJSDialogHandler
	, public CefKeyboardHandler
	, public CefLifeSpanHandler
	, public CefLoadHandler
	, public CefRequestHandler
{
	Q_OBJECT

public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="host"></param>
	QCefViewBrowserHandler(CCefWindow* pQCefWin);

	/// <summary>
	/// 
	/// </summary>
	~QCefViewBrowserHandler();

	//////////////////////////////////////////////////////////////////////////
	// CefClient methods:
	virtual CefRefPtr<CefContextMenuHandler> GetContextMenuHandler()
	{
		return pContextMenuHandler_ ? pContextMenuHandler_ : this;
	}
	virtual CefRefPtr<CefDialogHandler> GetDialogHandler()
	{
		return pDialogHandler_;
	}
	virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler()
	{
		return pDisplayHandler_ ? pDisplayHandler_ : this;
	}
	virtual CefRefPtr<CefDownloadHandler> GetDownloadHandler()
	{
		return pDownloadHandler_;
	}
	virtual CefRefPtr<CefDragHandler> GetDragHandler()
	{
		return this;
	}
	virtual CefRefPtr<CefJSDialogHandler> GetJSDialogHandler()
	{
		return pJSDialogHandler_ ? pJSDialogHandler_ : this;
	}
	virtual CefRefPtr<CefKeyboardHandler> GetKeyboardHandler()
	{
		return pKeyboardHandler_ ? pKeyboardHandler_ : this;
	}
	virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler()
	{
		return this;
	}
	virtual CefRefPtr<CefLoadHandler> GetLoadHandler()
	{
		return this;
	}
	virtual CefRefPtr<CefRequestHandler> GetRequestHandler()
	{
		return this;
	}

	virtual bool OnProcessMessageReceived(
		CefRefPtr<CefBrowser> browser,
		CefProcessId source_process,
		CefRefPtr<CefProcessMessage> message);

	// CefContextMenuHandler methods
	virtual void OnBeforeContextMenu(
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefContextMenuParams> params,
		CefRefPtr<CefMenuModel> model);
	virtual bool OnContextMenuCommand(
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefContextMenuParams> params,
		int command_id,
		EventFlags event_flags);

	// CefDisplayHandler methods
	virtual void OnAddressChange(
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		const CefString& url);
	virtual void OnTitleChange(
		CefRefPtr<CefBrowser> browser,
		const CefString& title);
	virtual bool OnConsoleMessage(
		CefRefPtr<CefBrowser> browser,
		const CefString& message,
		const CefString& source,
		int line);

	//CefDragHandler methods
	virtual bool OnDragEnter(
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefDragData> dragData,
		CefDragHandler::DragOperationsMask mask);

	// CefJSDialogHandler methods
	virtual bool OnJSDialog(
		CefRefPtr<CefBrowser> browser,
		const CefString& origin_url,
		const CefString& accept_lang,
		JSDialogType dialog_type,
		const CefString& message_text,
		const CefString& default_prompt_text,
		CefRefPtr<CefJSDialogCallback> callback,
		bool& suppress_message);
	virtual bool OnBeforeUnloadDialog(
		CefRefPtr<CefBrowser> browser,
		const CefString& message_text,
		bool is_reload,
		CefRefPtr<CefJSDialogCallback> callback);
	virtual void OnResetDialogState(
		CefRefPtr<CefBrowser> browser);

	// CefKeyboardHandler methods
	virtual bool OnPreKeyEvent(
		CefRefPtr<CefBrowser> browser,
		const CefKeyEvent& event,
		CefEventHandle os_event,
		bool* is_keyboard_shortcut);

	// CefLifeSpanHandler methods:
	virtual bool OnBeforePopup(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		const CefString& target_url,
		const CefString& target_frame_name,
		CefLifeSpanHandler::WindowOpenDisposition target_disposition,
		bool user_gesture,
		const CefPopupFeatures& popupFeatures,
		CefWindowInfo& windowInfo,
		CefRefPtr<CefClient>& client,
		CefBrowserSettings& settings,
		bool* no_javascript_access);
	virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser);
	virtual bool DoClose(CefRefPtr<CefBrowser> browser);
	virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser);

	// CefLoadHandler methods
	virtual void OnLoadingStateChange(
		CefRefPtr<CefBrowser> browser,
		bool isLoading,
		bool canGoBack,
		bool canGoForward);
	virtual void OnLoadStart(
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame);
	virtual void OnLoadEnd(
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		int httpStatusCode);
	virtual void OnLoadError(
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		ErrorCode errorCode,
		const CefString& errorText,
		const CefString& failedUrl);

	// CefRequestHandler methods
	virtual bool OnBeforeBrowse(
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefRequest> request,
		bool is_redirect);
	virtual bool OnOpenURLFromTab(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		const CefString& target_url,
		CefRequestHandler::WindowOpenDisposition target_disposition,
		bool user_gesture);
	virtual CefRefPtr<CefResourceHandler> GetResourceHandler(
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefRequest> request);
	virtual bool OnQuotaRequest(
		CefRefPtr<CefBrowser> browser,
		const CefString& origin_url,
		int64 new_size,
		CefRefPtr<CefRequestCallback> callback);
	virtual void OnProtocolExecution(
		CefRefPtr<CefBrowser> browser,
		const CefString& url,
		bool& allow_os_execution);
	virtual void OnRenderProcessTerminated(
		CefRefPtr<CefBrowser> browser,
		TerminationStatus status);

	//////////////////////////////////////////////////////////////////////////

	CefRefPtr<CefBrowser> GetBrowser() const;

	int GetBrowserId() const;

	// Request that all existing browser windows close.
	void CloseAllBrowsers(bool force_close);

	void CloseAllPopupBrowsers(bool force_close);

	bool IsClosing() const;

	bool TriggerEvent(const CefRefPtr<CefProcessMessage> msg);

	bool ResponseQuery(int64_t query,
		bool success, const CefString& response, int error);

	bool DispatchNotifyRequest(CefRefPtr<CefBrowser> browser,
		CefProcessId source_process,
		CefRefPtr<CefProcessMessage> message);

	void SetContextMenuHandler(CefRefPtr<CefContextMenuHandler> handler)
	{
		pContextMenuHandler_ = handler;
	}

	void SetDialogHandler(CefRefPtr<CefDialogHandler> handler)
	{
		pDialogHandler_ = handler;
	}

	void SetDisplayHandler(CefRefPtr<CefDisplayHandler> handler)
	{
		pDisplayHandler_ = handler;
	}

	void SetDownloadHandler(CefRefPtr<CefDownloadHandler> handler)
	{
		pDownloadHandler_ = handler;
	}

	void SetJSDialogHandler(CefRefPtr<CefJSDialogHandler> handler)
	{
		pJSDialogHandler_ = handler;
	}

	void SetKeyboardHandler(CefRefPtr<CefKeyboardHandler> handler)
	{
		pKeyboardHandler_ = handler;
	}

public:
	void ShowDevTools(CefRefPtr<CefBrowser> browser, const CefPoint& inspect_element_at);
	void DeleteCookies();
	void SetCookie(const CefString& name,
		const CefString& value,
		const CefString& domain,
		const CefString& path);

signals:
	void urlRequest(const QString& url);
	void urlChanged(const QString& url);

private:
	/// <summary>
	/// 
	/// </summary>
	QPointer<CCefWindow> pQCefWindow_;

	/// <summary>
	/// 
	/// </summary>
	int browser_count_;

	/// <summary>
	/// 
	/// </summary>
	int main_browser_id_;

	/// <summary>
	/// 
	/// </summary>
	bool is_closing_;

	/// <summary>
	/// 
	/// </summary>
	mutable std::mutex	mtx_;

	/// <summary>
	/// 
	/// </summary>
	CefRefPtr<CefBrowser> main_browser_;

	/// <summary>
	/// 
	/// </summary>
	CefRefPtr<CefMessageRouterBrowserSide> message_router_;

	/// <summary>
	/// 
	/// </summary>
	CefRefPtr<QCefQueryHandler> cefquery_handler_;
	
	/// <summary>
	/// List of existing browser windows. Only accessed on the CEF UI thread.
	/// </summary>
	std::list<CefRefPtr<CefBrowser>> popup_browser_list_;

	CefRefPtr<CefContextMenuHandler> pContextMenuHandler_;
	CefRefPtr<CefDialogHandler> pDialogHandler_;
	CefRefPtr<CefDisplayHandler> pDisplayHandler_;
	CefRefPtr<CefDownloadHandler> pDownloadHandler_;
	CefRefPtr<CefJSDialogHandler> pJSDialogHandler_;
	CefRefPtr<CefKeyboardHandler> pKeyboardHandler_;

	// Include the default reference counting implementation.
	IMPLEMENT_REFCOUNTING(QCefViewBrowserHandler);
};
#endif
