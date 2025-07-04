#include "../deb/WinMsgText.h"

namespace deb
{

	std::string getWinMsgText(const UINT msg)
	{
		auto res = getOptionalWinMsgText(msg);
		if (!res)
		{
			return "(" + std::to_string(msg) + ")";
		}
		return *res;
	}

	std::optional<std::string> getOptionalWinMsgText(const UINT msg)
	{
#define ENTRY(MSG) case WM_##MSG: return { #MSG } ;
		switch (msg)
		{
			ENTRY(NULL)
				ENTRY(CREATE)
				ENTRY(DESTROY)
				ENTRY(MOVE)
				ENTRY(SIZE)
				ENTRY(ACTIVATE)
				ENTRY(SETFOCUS)
				ENTRY(KILLFOCUS)
				ENTRY(ENABLE)
				ENTRY(SETREDRAW)
				ENTRY(SETTEXT)
				ENTRY(GETTEXT)
				ENTRY(GETTEXTLENGTH)
				ENTRY(PAINT)
#ifndef _WIN32_WCE
				ENTRY(QUERYENDSESSION)
				ENTRY(QUERYOPEN)
				ENTRY(ENDSESSION)
#endif
				ENTRY(CLOSE)
				ENTRY(QUIT)
				ENTRY(ERASEBKGND)
				ENTRY(SYSCOLORCHANGE)
				ENTRY(SHOWWINDOW)
				ENTRY(WININICHANGE)
				ENTRY(DEVMODECHANGE)
				ENTRY(ACTIVATEAPP)
				ENTRY(FONTCHANGE)
				ENTRY(TIMECHANGE)
				ENTRY(CANCELMODE)
				ENTRY(SETCURSOR)
				ENTRY(MOUSEACTIVATE)
				ENTRY(CHILDACTIVATE)
				ENTRY(QUEUESYNC)
				ENTRY(GETMINMAXINFO)
				ENTRY(PAINTICON)
				ENTRY(ICONERASEBKGND)
				ENTRY(NEXTDLGCTL)
				ENTRY(SPOOLERSTATUS)
				ENTRY(DRAWITEM)
				ENTRY(MEASUREITEM)
				ENTRY(DELETEITEM)
				ENTRY(VKEYTOITEM)
				ENTRY(CHARTOITEM)
				ENTRY(SETFONT)
				ENTRY(GETFONT)
				ENTRY(SETHOTKEY)
				ENTRY(GETHOTKEY)
				ENTRY(QUERYDRAGICON)
				ENTRY(COMPAREITEM)
				ENTRY(GETOBJECT)
				ENTRY(COMPACTING)
				ENTRY(COMMNOTIFY)
				ENTRY(WINDOWPOSCHANGING)
				ENTRY(WINDOWPOSCHANGED)
				ENTRY(POWER)
				ENTRY(COPYDATA)
				ENTRY(CANCELJOURNAL)
				ENTRY(NOTIFY)
				ENTRY(INPUTLANGCHANGEREQUEST)
				ENTRY(INPUTLANGCHANGE)
				ENTRY(TCARD)
				ENTRY(HELP)
				ENTRY(USERCHANGED)
				ENTRY(NOTIFYFORMAT)
				ENTRY(CONTEXTMENU)
				ENTRY(STYLECHANGING)
				ENTRY(STYLECHANGED)
				ENTRY(DISPLAYCHANGE)
				ENTRY(GETICON)
				ENTRY(SETICON)
				ENTRY(NCCREATE)
				ENTRY(NCDESTROY)
				ENTRY(NCCALCSIZE)
				ENTRY(NCHITTEST)
				ENTRY(NCPAINT)
				ENTRY(NCACTIVATE)
				ENTRY(GETDLGCODE)
				ENTRY(SYNCPAINT)
				ENTRY(NCMOUSEMOVE)
				ENTRY(NCLBUTTONDOWN)
				ENTRY(NCLBUTTONUP)
				ENTRY(NCLBUTTONDBLCLK)
				ENTRY(NCRBUTTONDOWN)
				ENTRY(NCRBUTTONUP)
				ENTRY(NCRBUTTONDBLCLK)
				ENTRY(NCMBUTTONDOWN)
				ENTRY(NCMBUTTONUP)
				ENTRY(NCMBUTTONDBLCLK)
				ENTRY(NCXBUTTONDOWN)
				ENTRY(NCXBUTTONUP)
				ENTRY(NCXBUTTONDBLCLK)
				ENTRY(INPUT_DEVICE_CHANGE)
				ENTRY(INPUT)
				ENTRY(KEYDOWN)
				ENTRY(KEYUP)
				ENTRY(CHAR)
				ENTRY(DEADCHAR)
				ENTRY(SYSKEYDOWN)
				ENTRY(SYSKEYUP)
				ENTRY(SYSCHAR)
				ENTRY(SYSDEADCHAR)
				ENTRY(KEYLAST)
				ENTRY(IME_STARTCOMPOSITION)
				ENTRY(IME_ENDCOMPOSITION)
				ENTRY(IME_KEYLAST)
				ENTRY(INITDIALOG)
				ENTRY(COMMAND)
				ENTRY(SYSCOMMAND)
				ENTRY(TIMER)
				ENTRY(HSCROLL)
				ENTRY(VSCROLL)
				ENTRY(INITMENU)
				ENTRY(INITMENUPOPUP)
				ENTRY(GESTURE)
				ENTRY(GESTURENOTIFY)
				ENTRY(MENUSELECT)
				ENTRY(MENUCHAR)
				ENTRY(ENTERIDLE)
				ENTRY(MENURBUTTONUP)
				ENTRY(MENUDRAG)
				ENTRY(MENUGETOBJECT)
				ENTRY(UNINITMENUPOPUP)
				ENTRY(MENUCOMMAND)
				ENTRY(CHANGEUISTATE)
				ENTRY(UPDATEUISTATE)
				ENTRY(QUERYUISTATE)
				ENTRY(CTLCOLORMSGBOX)
				ENTRY(CTLCOLOREDIT)
				ENTRY(CTLCOLORLISTBOX)
				ENTRY(CTLCOLORBTN)
				ENTRY(CTLCOLORDLG)
				ENTRY(CTLCOLORSCROLLBAR)
				ENTRY(CTLCOLORSTATIC)
				ENTRY(MOUSEMOVE)
				ENTRY(LBUTTONDOWN)
				ENTRY(LBUTTONUP)
				ENTRY(LBUTTONDBLCLK)
				ENTRY(RBUTTONDOWN)
				ENTRY(RBUTTONUP)
				ENTRY(RBUTTONDBLCLK)
				ENTRY(MBUTTONDOWN)
				ENTRY(MBUTTONUP)
				ENTRY(MBUTTONDBLCLK)
				ENTRY(MOUSEWHEEL)
				ENTRY(XBUTTONDOWN)
				ENTRY(XBUTTONUP)
				ENTRY(XBUTTONDBLCLK)
				ENTRY(MOUSEHWHEEL)
				ENTRY(PARENTNOTIFY)
				ENTRY(ENTERMENULOOP)
				ENTRY(EXITMENULOOP)
				ENTRY(NEXTMENU)
				ENTRY(SIZING)
				ENTRY(CAPTURECHANGED)
				ENTRY(MOVING)
				ENTRY(POWERBROADCAST)
				ENTRY(DEVICECHANGE)
				ENTRY(MDICREATE)
				ENTRY(MDIDESTROY)
				ENTRY(MDIACTIVATE)
				ENTRY(MDIRESTORE)
				ENTRY(MDINEXT)
				ENTRY(MDIMAXIMIZE)
				ENTRY(MDITILE)
				ENTRY(MDICASCADE)
				ENTRY(MDIICONARRANGE)
				ENTRY(MDIGETACTIVE)
				ENTRY(MDISETMENU)
				ENTRY(ENTERSIZEMOVE)
				ENTRY(EXITSIZEMOVE)
				ENTRY(DROPFILES)
				ENTRY(MDIREFRESHMENU)
				ENTRY(POINTERDEVICECHANGE)
				ENTRY(POINTERDEVICEINRANGE)
				ENTRY(POINTERDEVICEOUTOFRANGE)
				ENTRY(TOUCH)
				ENTRY(NCPOINTERUPDATE)
				ENTRY(NCPOINTERDOWN)
				ENTRY(NCPOINTERUP)
				ENTRY(POINTERUPDATE)
				ENTRY(POINTERDOWN)
				ENTRY(POINTERUP)
				ENTRY(POINTERENTER)
				ENTRY(POINTERLEAVE)
				ENTRY(POINTERACTIVATE)
				ENTRY(POINTERCAPTURECHANGED)
				ENTRY(TOUCHHITTESTING)
				ENTRY(POINTERWHEEL)
				ENTRY(POINTERHWHEEL)
				ENTRY(POINTERROUTEDTO)
				ENTRY(POINTERROUTEDAWAY)
				ENTRY(POINTERROUTEDRELEASED)
				ENTRY(IME_SETCONTEXT)
				ENTRY(IME_NOTIFY)
				ENTRY(IME_CONTROL)
				ENTRY(IME_COMPOSITIONFULL)
				ENTRY(IME_SELECT)
				ENTRY(IME_CHAR)
				ENTRY(IME_REQUEST)
				ENTRY(IME_KEYDOWN)
				ENTRY(IME_KEYUP)
				ENTRY(MOUSEHOVER)
				ENTRY(MOUSELEAVE)
				ENTRY(NCMOUSEHOVER)
				ENTRY(NCMOUSELEAVE)
				ENTRY(WTSSESSION_CHANGE)
				ENTRY(TABLET_FIRST)
				ENTRY(TABLET_LAST)
				ENTRY(DPICHANGED)
				ENTRY(DPICHANGED_BEFOREPARENT)
				ENTRY(DPICHANGED_AFTERPARENT)
				ENTRY(GETDPISCALEDSIZE)
				ENTRY(CUT)
				ENTRY(COPY)
				ENTRY(PASTE)
				ENTRY(CLEAR)
				ENTRY(UNDO)
				ENTRY(RENDERFORMAT)
				ENTRY(RENDERALLFORMATS)
				ENTRY(DESTROYCLIPBOARD)
				ENTRY(DRAWCLIPBOARD)
				ENTRY(PAINTCLIPBOARD)
				ENTRY(VSCROLLCLIPBOARD)
				ENTRY(SIZECLIPBOARD)
				ENTRY(ASKCBFORMATNAME)
				ENTRY(CHANGECBCHAIN)
				ENTRY(HSCROLLCLIPBOARD)
				ENTRY(QUERYNEWPALETTE)
				ENTRY(PALETTEISCHANGING)
				ENTRY(PALETTECHANGED)
				ENTRY(HOTKEY)
				ENTRY(PRINT)
				ENTRY(PRINTCLIENT)
				ENTRY(APPCOMMAND)
				ENTRY(THEMECHANGED)
				ENTRY(CLIPBOARDUPDATE)
				ENTRY(DWMCOMPOSITIONCHANGED)
				ENTRY(DWMNCRENDERINGCHANGED)
				ENTRY(DWMCOLORIZATIONCOLORCHANGED)
				ENTRY(DWMWINDOWMAXIMIZEDCHANGE)
				ENTRY(DWMSENDICONICTHUMBNAIL)

		default:
			break;
		}
		return {};
	}

}
