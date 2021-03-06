#include "config.h"
#include "WebView.h"

#include "ChromeClientSpd.h"
#include "ContextMenuClientSpd.h"
#include "DragClientSpd.h"
#include "EditorClientSpd.h"
#include "HTMLElement.h"
#include "FocusController.h"
#include "Frame.h"
#include "FrameLoader.h"
#include "FrameLoaderClientSpd.h"
#include "FrameView.h"
#include "GraphicsContext.h"
#include "InitializeThreading.h"
#include "InspectorClientSpd.h"
#include "IntSize.h"
#include "MainThread.h"
#include "Threading.h"
#include "NotImplemented.h"
#include "Page.h"
#include "markup.h"
#include "PlatformKeyboardEvent.h"
#include "PlatformMouseEvent.h"
//#include "PlatformStrategiesSpd.h"
//#include "PlatformWheelEvent.h"
#include "ResourceRequest.h"
#include "Settings.h"
#include "SharedBuffer.h"
//#include "WebCoreInstanceHandle.h"
#include "BeforeTextInsertedEvent.h"
#include "ResourceHandleManager.h"

using namespace WebCore;

//const LPCWSTR kWebViewWindowClassName = L"WebViewWindowClass";

/*
LRESULT CALLBACK WebView::webViewWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (WebView* webView = reinterpret_cast<WebView*>(GetWindowLong(hWnd, 0)))
        return webView->wndProc(hWnd, message, wParam, lParam);

    return DefWindowProc(hWnd, message, wParam, lParam);
}
*/

PassRefPtr<SharedBuffer> loadResourceIntoBuffer(const char* name)
{
    notImplemented();
    return 0;
}


WebView::WebView()
    : m_frame(0)
    , m_page(0)
{
    Page::PageClients pageClients;
    pageClients.chromeClient = new WebKit::ChromeClientSpd(this);
    //pageClients.contextMenuClient = new WebKit::ContextMenuClientSpd(this);
    pageClients.editorClient = new WebKit::EditorClientSpd(this);
    //pageClients.dragClient = new WebKit::DragClientSpd();
    pageClients.inspectorClient = new WebKit::InspectorClientSpd(this);
    m_page = new Page(pageClients);

    Settings* settings = m_page->settings();
    settings->setDefaultFixedFontSize(14);
    settings->setDefaultFontSize(14);
    settings->setMinimumFontSize(8);
    settings->setMinimumLogicalFontSize(8);
    settings->setScriptEnabled(true);
    settings->setLoadsImagesAutomatically(true);

    WebKit::FrameLoaderClientSpd* loaderClient = new WebKit::FrameLoaderClientSpd(this);
    RefPtr<Frame> frame = Frame::create(m_page, 0, loaderClient);
    m_frame = frame.get();
    loaderClient->setFrame(m_frame);

    m_page->mainFrame()->init();

	//ResourceHandleManager* resHdlMgr = ResourceHandleManager::sharedInstance();
    //resHdlMgr->setCookieJarFileName("/ape/cookie/spdWebKit.cookies");
}

/*
WebView::WebView(HWND hwnd, unsigned features)
    : m_frame(0)
    , m_page(0)
    , m_parentWindowHandle(hwnd)
    , m_enableDoubleBuffer(features & EnableDoubleBuffering)
{
    RECT rcClient;
    GetClientRect(hwnd, &rcClient);

    m_windowHandle = CreateWindow(kWebViewWindowClassName, 0, WS_CHILD,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, hwnd, 0, WebCore::instanceHandle(), 0);

    SetWindowLong(m_windowHandle, 0, reinterpret_cast<LONG>(this));

    MoveWindow(m_windowHandle, 0, 0, rcClient.right, rcClient.bottom, TRUE);
    ShowWindow(m_windowHandle, SW_SHOW);

    Page::PageClients pageClients;
    pageClients.chromeClient = new WebKit::ChromeClientSpd(this);
    pageClients.contextMenuClient = new WebKit::ContextMenuClientSpd(this);
    pageClients.editorClient = new WebKit::EditorClientSpd(this);
    pageClients.dragClient = new WebKit::DragClientSpd();
    pageClients.inspectorClient = new WebKit::InspectorClientSpd(this);
    m_page = new Page(pageClients);

    Settings* settings = m_page->settings();
    settings->setDefaultFixedFontSize(14);
    settings->setDefaultFontSize(14);
    settings->setMinimumFontSize(8);
    settings->setMinimumLogicalFontSize(8);
    settings->setScriptEnabled(true);
    settings->setLoadsImagesAutomatically(true);

    WebKit::FrameLoaderClientSpd* loaderClient = new WebKit::FrameLoaderClientSpd(this);
    RefPtr<Frame> frame = Frame::create(m_page, 0, loaderClient);
    m_frame = frame.get();
    loaderClient->setFrame(m_frame);

    m_page->mainFrame()->init();

    if (view()) {
        RECT windowRect;
        frameRect(&windowRect);
        view()->resize(IntRect(windowRect).size());
    }
}
*/

WebView::~WebView()
{
    delete m_page;
    //DestroyWindow(m_windowHandle);
}
/*
void event_loop(void* data)
{
    WebView* pView = (WebView*)data;
    while(1)
    {
          sleep(10);
          printf("\n\n\n\n\n\n\n\nevent_loop()\n");
          String text = pView->innerText();
          text.show();
    }
}
*/
//void WebView::initialize(HINSTANCE instanceHandle)
void WebView::initialize(WebView** view)
{
    JSC::initializeThreading();
    WTF::initializeMainThread();
    //createThread(event_loop,view,"loader");
/*
    PlatformStrategiesSpd::initialize();

    WebCore::setInstanceHandle(instanceHandle);
    WNDCLASS wc;
    wc.style          = CS_DBLCLKS;
    wc.lpfnWndProc    = WebView::webViewWndProc;
    wc.cbClsExtra     = 0;
    wc.cbWndExtra     = sizeof(void *);
    wc.hInstance      = instanceHandle;
    wc.hIcon          = 0;
    wc.hCursor        = LoadCursor(0, IDC_ARROW);
    wc.hbrBackground  = 0;
    wc.lpszMenuName   = 0;
    wc.lpszClassName  = kWebViewWindowClassName;

    RegisterClass(&wc);
*/
}

void WebView::cleanup()
{
    //UnregisterClass(kWebViewWindowClassName, WebCore::instanceHandle());
}

PassRefPtr<Frame> WebView::createFrame(const KURL& url, const String& name, HTMLFrameOwnerElement* ownerElement, const String& referrer,
                                       bool /*allowsScrolling*/, int /*marginWidth*/, int /*marginHeight*/)
{
    Frame* coreFrame = m_frame;

    WebKit::FrameLoaderClientSpd *loaderClient = new WebKit::FrameLoaderClientSpd(this);
    RefPtr<Frame> childFrame = Frame::create(m_page, ownerElement, loaderClient);
    loaderClient->setFrame(childFrame.get());

    coreFrame->tree()->appendChild(childFrame);
    childFrame->tree()->setName(name);
    childFrame->init();

    // The creation of the frame may have run arbitrary JavaScript that removed it from the page already.
    if (!childFrame->page())
        return 0;

    coreFrame->loader()->loadURLIntoChildFrame(url, referrer, childFrame.get());

    // The frame's onload handler may have removed it from the document.
    if (!childFrame->tree()->parent())
        return 0;

    return childFrame.release();
}

void WebView::runJavaScriptAlert(const String& message)
{
    notImplemented();
}

bool WebView::runJavaScriptConfirm(const String& message)
{
    notImplemented();
    return false;
}

bool WebView::runJavaScriptPrompt(const String& message, const String& defaultValue, String& result)
{
    notImplemented();
    return false;
}
/*
void WebView::frameRect(RECT* rect) const
{
    GetWindowRect(m_windowHandle, rect);
}
*/
FrameView* WebView::view() const
{
    return m_frame ? m_frame->view() : 0;
}

/*
void WebView::load(LPCWSTR url)
{
    load(String(url));
}
*/


void WebView::load(const String &url)
{
    //createThread(event_loop,this,"loader");  
    load(WebCore::ResourceRequest(url));
}

void WebView::load(const WebCore::ResourceRequest &request)
{
    frame()->loader()->load(request, false);
}

void WebView::reload()
{
    frame()->loader()->reload();
}

WTF::String WebView::innerText()
{
    return createMarkup(m_frame->document());
    //return m_frame->document()->body()->innerText();
}

void WebView::stop()
{
    frame()->loader()->stopAllLoaders();
}

int WebView::setCurrentElementById(char* id)
{
    String selector(id);
    ExceptionCode e;
    m_curElement = frame()->document()->querySelector(selector,e).get();
    //printf("querySelector(%s) return %d\n",id,(int)m_curElement);
    return 0;

    AtomicString strID(id);
    m_curElement = frame()->document()->getElementById(strID);
    return 0;
}

int WebView::setCurrentElementValue(char* value)
{
    ExceptionCode e;
    AtomicString AttrName("value");
    AtomicString AtrrValue(value);
    m_curElement->setAttribute(AttrName,AtrrValue,e);

    return 0;
}

int WebView::click()
{
    //m_curElement->onclick();
    PlatformMouseEvent event;
    AtomicString type("click");
    //m_curElement->dispatchMouseEvent(event,type,1,NULL);
    frame()->eventHandler()->dispatchMouseEvent(type,m_curElement,1);
    return 0;
}

int WebView::type(char* text)
{
    ExceptionCode e;
    AtomicString name("value");
    AtomicString value(text);
    m_curElement->setAttribute(name,value,e);
    return 0;
/*
    m_curElement->setFocus(true);
    String tx(text);
    AtomicString type("keypress");
    PassRefPtr<Event> event = Event::create(type,true,true);
    frame()->eventHandler()->handleTextInputEvent(tx,event.get());
*/
/*
    //m_curElement->setFocus(true);
    //Frame* frame = m_page->focusController()->focusedOrMainFrame();
    
    PassRefPtr<Node> node(m_curElement);
    m_curElement->document()->setFocusedNode(node);
    Frame* frame = m_curElement->document()->frame();
    //m_curElement->setFocus(true);
    //    m_curElement->document()->frame();
    //        Frame* frame = m_page->focusController()->focusedOrMainFrame();
    //
    PlatformKeyboardEvent keyEvent(text[0]);
    //// IE does not dispatch keypress event for WM_SYSCHAR.
    //if (systemKeyDown)
    //    return frame->eventHandler()->handleAccessKey(keyEvent);
    frame->eventHandler()->keyEvent(keyEvent);
    String eText = text;
    String newText = eText;
    ExceptionCode ec = 0;
    RefPtr<BeforeTextInsertedEvent> evt = BeforeTextInsertedEvent::create(eText);
    m_curElement->dispatchEvent(evt, ec);
    newText = evt->text();
*/
    return 0;
}

/*
void WebView::paint(HDC hDC, const IntRect& clipRect)
{
    FrameView* frameView = view();
    if (!frameView)
        return;

    OwnPtr<HRGN> clipRgn = adoptPtr(CreateRectRgn(clipRect.x(), clipRect.y(), clipRect.maxX(), clipRect.maxY()));
    SelectClipRgn(hDC, clipRgn.get());

    frameView->updateLayoutAndStyleIfNeededRecursive();

    GraphicsContext gc(hDC);
    frameView->paint(&gc, clipRect);
}

bool WebView::handlePaint(HWND hWnd)
{
    RECT updateRect;
    if (!GetUpdateRect(hWnd, &updateRect, false))
        return false;

    PAINTSTRUCT ps;
    HDC hDC = BeginPaint(m_windowHandle, &ps);

    IntRect clipRect(updateRect);

    if (m_enableDoubleBuffer) {
        if (!m_doubleBufferDC) {
            RECT rcClient;
            GetClientRect(m_windowHandle, &rcClient);

            m_doubleBufferDC = adoptPtr(CreateCompatibleDC(hDC));
            m_doubleBufferBitmap = adoptPtr(CreateCompatibleBitmap(hDC, rcClient.right, rcClient.bottom));
            SelectObject(m_doubleBufferDC.get(), m_doubleBufferBitmap.get());
        }

        paint(m_doubleBufferDC.get(), clipRect);

        BitBlt(hDC, clipRect.x(), clipRect.y(), clipRect.width(), clipRect.height(), m_doubleBufferDC.get(), clipRect.x(), clipRect.y(), SRCCOPY);
    } else
        paint(hDC, clipRect);

    EndPaint(m_windowHandle, &ps);
    return true;
}

bool WebView::handleMouseEvent(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static LONG globalClickCount;
    static IntPoint globalPrevPoint;
    static MouseButton globalPrevButton;
    static LONG globalPrevMouseDownTime;

    // Create our event.
    // On WM_MOUSELEAVE we need to create a mouseout event, so we force the position
    // of the event to be at (MINSHORT, MINSHORT).
    PlatformMouseEvent mouseEvent(hWnd, message, wParam, lParam);

    bool insideThreshold = abs(globalPrevPoint.x() - mouseEvent.position().x()) < ::GetSystemMetrics(SM_CXDOUBLECLK)
                           && abs(globalPrevPoint.y() - mouseEvent.position().y()) < ::GetSystemMetrics(SM_CYDOUBLECLK);
    LONG messageTime = 0;

    bool handled = false;
    if (message == WM_LBUTTONDOWN || message == WM_MBUTTONDOWN || message == WM_RBUTTONDOWN) {
        // FIXME: I'm not sure if this is the "right" way to do this
        // but without this call, we never become focused since we don't allow
        // the default handling of mouse events.
        SetFocus(m_windowHandle);

        PlatformMouseEvent moveEvent(hWnd, WM_MOUSEMOVE, 0, lParam, false);
        moveEvent.setClickCount(0);
        m_page->mainFrame()->eventHandler()->handleMouseMoveEvent(moveEvent);

        // Always start capturing events when the mouse goes down in our HWND.
        SetCapture(m_windowHandle);

        if (insideThreshold && mouseEvent.button() == globalPrevButton)
            globalClickCount++;
        else
            // Reset the click count.
            globalClickCount = 1;
        globalPrevMouseDownTime = messageTime;
        globalPrevButton = mouseEvent.button();
        globalPrevPoint = mouseEvent.position();

        mouseEvent.setClickCount(globalClickCount);
        handled = m_page->mainFrame()->eventHandler()->handleMousePressEvent(mouseEvent);
    } else if (message == WM_LBUTTONDBLCLK || message == WM_MBUTTONDBLCLK || message == WM_RBUTTONDBLCLK) {
        globalClickCount++;
        mouseEvent.setClickCount(globalClickCount);
        handled = m_page->mainFrame()->eventHandler()->handleMousePressEvent(mouseEvent);
    } else if (message == WM_LBUTTONUP || message == WM_MBUTTONUP || message == WM_RBUTTONUP) {
        // Record the global position and the button of the up.
        globalPrevButton = mouseEvent.button();
        globalPrevPoint = mouseEvent.position();
        mouseEvent.setClickCount(globalClickCount);
        m_page->mainFrame()->eventHandler()->handleMouseReleaseEvent(mouseEvent);
        ReleaseCapture();
    } else if (message == WM_MOUSEMOVE) {
        if (!insideThreshold)
            globalClickCount = 0;
        mouseEvent.setClickCount(globalClickCount);
        handled = m_page->mainFrame()->eventHandler()->mouseMoved(mouseEvent);
    }

    return handled;
}

bool WebView::handleMouseWheel(HWND hWnd, WPARAM wParam, LPARAM lParam, bool isHorizontal)
{
    PlatformWheelEvent wheelEvent(hWnd, wParam, lParam, isHorizontal);
    return frame()->eventHandler()->handleWheelEvent(wheelEvent);
}

bool WebView::handleKeyDown(WPARAM virtualKeyCode, LPARAM keyData, bool systemKeyDown)
{
    Frame* frame = m_page->focusController()->focusedOrMainFrame();

    PlatformKeyboardEvent keyEvent(m_windowHandle, virtualKeyCode, keyData, PlatformEvent::RawKeyDown, systemKeyDown);
    bool handled = frame->eventHandler()->keyEvent(keyEvent);

    // These events cannot be canceled, and we have no default handling for them.
    // FIXME: match IE list more closely, see <http://msdn2.microsoft.com/en-us/library/ms536938.aspx>.
    if (systemKeyDown && virtualKeyCode != VK_RETURN)
        return false;

    if (handled) {
        MSG msg;
        if (!systemKeyDown)
            ::PeekMessage(&msg, m_windowHandle, WM_CHAR, WM_CHAR, PM_REMOVE);
        return true;
    }

    return handled;
}

bool WebView::handleKeyPress(WPARAM charCode, LPARAM keyData, bool systemKeyDown)
{
    Frame* frame = m_page->focusController()->focusedOrMainFrame();

    PlatformKeyboardEvent keyEvent(m_windowHandle, charCode, keyData, PlatformEvent::Char, systemKeyDown);
    // IE does not dispatch keypress event for WM_SYSCHAR.
    if (systemKeyDown)
        return frame->eventHandler()->handleAccessKey(keyEvent);
    if (frame->eventHandler()->keyEvent(keyEvent))
        return true;

    return false;
}

bool WebView::handleKeyUp(WPARAM virtualKeyCode, LPARAM keyData, bool systemKeyDown)
{
    PlatformKeyboardEvent keyEvent(m_windowHandle, virtualKeyCode, keyData, PlatformEvent::KeyUp, systemKeyDown);

    Frame* frame = m_page->focusController()->focusedOrMainFrame();
    return frame->eventHandler()->keyEvent(keyEvent);
}

LRESULT WebView::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    bool handled = false;

    if (view()) {
        switch (message) {
        case WM_PAINT:
            handled = handlePaint(hWnd);
            break;

        case WM_MOUSEMOVE:
        case WM_LBUTTONDOWN:
        case WM_MBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_LBUTTONDBLCLK:
        case WM_MBUTTONDBLCLK:
        case WM_RBUTTONDBLCLK:
        case WM_LBUTTONUP:
        case WM_MBUTTONUP:
        case WM_RBUTTONUP:
            if (frame()->eventHandler() && view()->didFirstLayout())
                handled = handleMouseEvent(hWnd, message, wParam, lParam);
            break;

        case WM_MOUSEWHEEL:
            if (frame()->eventHandler() && view()->didFirstLayout())
                handled = handleMouseWheel(hWnd, wParam, lParam, wParam & MK_SHIFT);
            break;

        case WM_SYSKEYDOWN:
            handled = handleKeyDown(wParam, lParam, true);
            break;

        case WM_KEYDOWN:
            handled = handleKeyDown(wParam, lParam, false);
            break;

        case WM_SYSKEYUP:
            handled = handleKeyUp(wParam, lParam, true);
            break;

        case WM_KEYUP:
            handled = handleKeyUp(wParam, lParam, false);
            break;

        case WM_SYSCHAR:
            handled = handleKeyPress(wParam, lParam, true);
            break;

        case WM_CHAR:
            handled = handleKeyPress(wParam, lParam, false);
            break;

        case WM_CLOSE:
            PostMessage(m_parentWindowHandle, WM_CLOSE, wParam, lParam);
            handled = true;
            break;

        default:
            break;
        }
    }

    if (handled)
        return 0;

    return DefWindowProc(hWnd, message, wParam, lParam);
}
*/
