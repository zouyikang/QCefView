#ifndef QCEFCOMMON_H
#define QCEFCOMMON_H
#if defined(_MSVC_) && _MSC_VER > 1000
#pragma once 
#endif // _MSC_VER > 1000 

#define QCEF_SCHEMA						"qcef"
#define QCEF_QUERY_NAME					"QCefQuery"
#define QCEF_QUERY_CANCEL_NAME			"QCefQueryCancel"


#define QCEF_OBJECT_NAME				"QCefClient"

/*
 * QCefClient.invokeMethod("method_name", ...)
 */
#define QCEF_INVOKEMETHOD				"invokeMethod"

/*
 * QCefClient.addEventListener(type, listener)
 */
#define QCEF_ADDEVENTLISTENER			"addEventListener"
/*
 * QCefClient.removeEventListener(type, listener)
 */
#define QCEF_REMOVEEVENTLISTENER		"removeEventListener"

/*
 * this message is send from render process to browser process
 * and is processed in the Qt UI thread
 * 
 * format:
 *		msg.name: 
 *		msg.arg[0]: frame id
 *		msg.arg[1]: function name
 *		msg.arg[2~...]: function parameters
 *
 */
#define INVOKEMETHOD_NOTIFY_MESSAGE		"QCefClient#InvokeMethodNotify"


/*
 * this message is send from browser process to render process
 * and is processed in the CefRenderer_Main thread
 * 
 * format:
 *		msg.name: 
 *		msg.arg[0]: frame id
 *		msg.arg[1]: function name
 *		msg.arg[2~...]: function parameters
 *
 */
#define TRIGGEREVENT_NOTIFY_MESSAGE		"QCefClient#TriggerEventNotify"

#define RENDER_PROCESS_NAME				"qtcefwing.exe"
#define RESOURCE_DIRECTORY_NAME			"resources"
#define LOCALES_DIRECTORY_NAME			"locales"
#define QCEF_USER_AGENT					"Mozilla/5.0 (Windows NT 6.2;WOW64) AppleWebKit/537.36 (KHTML, like Gecko) XesCef/2623 Chrome/49.0.2623.87 Safari/537.36"

#endif
