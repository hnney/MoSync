/**
 * @file main.cpp
 *
 * Sample application that illustrates how to call into C++
 * from JavaScript.
 */

#include <Wormhole/WebAppMoblet.h>
#include <conprint.h>
#include "MessageProtocol.h"
#include "MessageStream.h"
#include "MessageStreamJSON.h"

// Namespaces we want to access.
using namespace MAUtil; // Class Moblet
using namespace NativeUI; // WebView widget.
using namespace Wormhole; // Class WebAppMoblet

/**
 * The application class.
 */
class MyMoblet : public WebAppMoblet
{
public:
	MyMoblet()
	{
		// Enable message sending from JavaScript to C++.
		enableWebViewMessages();

		// Remove this line to enable the user to
		// zoom the web page. To disable zoom is one
		// way of making web pages display in a
		// reasonable degault size on devices with
		// different screen sizes.
		getWebView()->enableZoom();

		// The page in the "LocalFiles" folder to
		// show when the application starts.
		showPage("index.html");
	}

	/**
	 * This method handles messages sent from the WebView.
	 * @param webView The WebView that sent the message.
	 * @param urlData Data object that holds message content.
	 * Note that the data object will be valid only during
	 * the life-time of the call of this method, then it
	 * will be deallocated.
	 */
	void handleWebViewMessage(WebView* webView, MAHandle data)
	{
		App::MessageProtocol protocol(data);

		if (protocol.isMessageStream())
		{
			 handleMessageStream(webView, data);
		}
		else if (protocol.isMessageArrayJSON())
		{
			 handleMessageStreamJSON(webView, data);
		}
		else
		{
			lprintfln("undefined message protocol");
		}
	}

	void handleMessageStream(WebView* webView, MAHandle data)
	{
		App::MessageStream stream(webView, data);

		const char* p;

		while (p = stream.getNext())
		{
			if (0 == strcmp(p, "StringMessage"))
			{
				// Get params.
				const char* p1 = stream.getNext();
				const char* p2 = stream.getNext();
//				lprintfln("@@@ p1: %s p2: %s", p1, p2);
			}
			else if (0 == strcmp(p, "StringMessageEnd"))
			{
				callJS("StringMessageEnd()");
			}
			else if (0 == strcmp(p, "StringRoundtripMessage"))
			{
				callJS("StringRoundtripCallback()");
			}
		}
	}

	void handleMessageStreamJSON(WebView* webView, MAHandle data)
	{
		App::MessageStreamJSON message(webView, data);

		while (message.next())
		{
			handleJSONMessage(message);
		}
	}

	void handleJSONMessage(App::MessageStreamJSON& message)
	{
		if (message.is("JSONMessage"))
		{
			// No action.
		}
		else if (message.is("JSONMessageEnd"))
		{
			callJS("JSONMessageEnd()");
		}
		else if (message.is("JSONRoundtripMessage"))
		{
			callJS("JSONRoundtripCallback()");
		}
		else
		{
			lprintfln("@@@ C++ Unknown message");
		}
	}
};

/**
 * Main function that is called when the program starts.
 * Here an instance of the MyMoblet class is created and
 * the program enters the main event loop.
 */
extern "C" int MAMain()
{
	Moblet::run(new MyMoblet());
	return 0;
}