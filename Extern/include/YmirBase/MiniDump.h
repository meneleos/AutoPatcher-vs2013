////////////////////////////////////////////////////////////////////////////////
/// \file MiniDump.h
/// \author excel96
/// \date 2003.11.18
////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef _WINDOWS_
    #include <windows.h>
#endif

////////////////////////////////////////////////////////////////////////////////
/// \class cMiniDump
/// \brief �̴� ������ �����ϱ� ���� Ŭ����. Ư���� � �������� �־ ���� 
/// Ŭ������ �ƴϰ�, ���� ������ �Լ��� ������ �ֱ� ���� ���� ���� �����̽� 
/// ���� Ŭ�����̴�. 
///
/// ������ �ʱ�ȭ�� Install �Լ��� ���� �̷������. ���α׷� ���� �κ� �ƹ� 
/// �������� cMiniDump::Install(...) �Լ��� ȣ�����ָ� �ȴ�. 
///
/// <pre>
/// int main()
/// {
///     ...
///     cMiniDump::Install(cMiniDump::DUMP_LEVEL_LIGHT);
///     ...
/// }
/// </pre>
///
/// GUI�� ����� �� �ִ� ���α׷��� ���, ����ڿ��� ���� ���� ���� ���θ� ����
/// �͵� �����ٰ� �����ؼ�, ��ȭâ �ݹ� �Լ��� �ϳ� ���� �־���. Install �Լ��� 
/// ���� ��ȭâ �ݹ� �Լ��� �����ϸ�, ���� ������ �̸� Ȯ���� ���� ��ȭâ�� 
/// ����. ��ȭâ�� IDOK�� ������, ���� ������ �����ϰ�, �׿��� ������ ������ 
/// ���� ������ �������� �ʴ´�. �⺻���� ��ȭâ �Լ��� �������ڸ� ���� �Ʒ��� 
/// ���� ���̴�.
///
/// <pre>
/// BOOL CALLBACK CrashDialogProc(
///     HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM /*lParam*/)
/// {
///     RECT parent, dlg;
///     int x, y;
/// 
///     switch (iMessage)
///     {
///     case WM_INITDIALOG:
///         ::GetWindowRect(::GetForegroundWindow(), &parent);
///         ::GetWindowRect(hDlg, &dlg);
///         x = (parent.left + parent.right - dlg.right) / 2;
///         y = (parent.top + parent.bottom - dlg.bottom) / 2;
///         ::MoveWindow(hDlg, x, y, dlg.right, dlg.bottom, FALSE);
//          ...
///         return TRUE;
///     case WM_COMMAND:
///         switch (LOWORD(wParam))
///         {
///         case IDOK: EndDialog(hDlg, IDOK); break;
///         case IDCANCEL: EndDialog(hDlg, IDCANCEL); break;
///         default: break;
///         }
///         return FALSE;
///     default:
///         break;
///     }
/// 
///     return FALSE;
/// }
/// </pre>
////////////////////////////////////////////////////////////////////////////////

class MiniDump
{
public:
    /// ������ �������� ����
    enum DumpLevel
    {
        DUMP_LEVEL_LIGHT = 1,  ///< MiniDumpNormal�� ���
        DUMP_LEVEL_MEDIUM, ///< MiniDumpWithDataSegs�� ���
        DUMP_LEVEL_HEAVY   ///< MiniDumpWithFullMemory�� ���
    };

private:
	enum
	{
		BUFFER_MAX = 32 * 1024,
	};

	typedef EL_VOID (*SEND_REPORT_PROC)();

    static DumpLevel s_DumpLevel;          ///< ���� ����.
    static bool      s_AddTimeStamp;       ///< ��¥ ��� ���� ���� �̸� ���
    static TCHAR     s_AppName[_MAX_PATH]; ///< ���� ���� �̸�
    static TCHAR     s_CallStack[BUFFER_MAX];    ///< �ݽ��� ���ڿ�
    static TCHAR     s_Modules[BUFFER_MAX];      ///< ��� ���ڿ�
    static LPCTSTR   s_DialogTemplate;     ///< ��ȭâ ���ø�
    static DLGPROC   s_DialogProc;         ///< ��ȭâ ���ν���
	static SEND_REPORT_PROC s_SendReportProc;

public:
    /// \brief �̴� ���� ����� �ʱ�ȭ�Ѵ�.
    static void Install(DumpLevel dumpLevel, bool addTimestamp=true, LPCTSTR dialogTemplate=NULL, DLGPROC dialogProc=NULL, SEND_REPORT_PROC SendReportProc=NULL);

    /// \brief �ݽ��� ���ڿ��� ��ȯ�Ѵ�.
    static LPCTSTR GetCallStack() { return s_CallStack; }

    /// \brief ��� ���ڿ��� ��ȯ�Ѵ�.
    static LPCTSTR GetModules() { return s_Modules; }

	/// \brief ���ܿ� ���� ������ �޾Ƽ�, �̴� ���� ������ �����Ѵ�. 
    static LONG WINAPI WriteDump(PEXCEPTION_POINTERS exPtrs);

	static bool IsDataSectionNeeded(PWCHAR pModuleName);

private:
    /// \brief ���� ����
    MiniDump() {}

    /// \brief ���� ���� ����
    MiniDump(const MiniDump&);

    /// \brief ���� ���� ����
	MiniDump& operator = (const MiniDump&);

	static void GetCallStackOfAllThread(PEXCEPTION_POINTERS exPtrs);
};

