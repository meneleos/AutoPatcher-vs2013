#pragma once

class MA_CCommandLine
{
public:
	MA_CCommandLine(void);
	MA_CCommandLine(MA_PCWSTR szCommandLine, MA_BOOL bHasProgramName = MA_TRUE);
	MA_CCommandLine(MA_INT IN nArgumentCount, MA_PWSTR IN aszArguments[], MA_BOOL bHasProgramName = MA_TRUE);
	~MA_CCommandLine(void);

	MA_BOOL			Set(MA_PCWSTR IN szCommandLine, MA_BOOL bHasProgramName = MA_FALSE);
	MA_BOOL			Set(MA_INT IN nArgumentCount, MA_PWSTR IN aszArguments[], MA_BOOL bHasProgramName = MA_TRUE);

	MA_SIZE			FindArgument(MA_PCWSTR tszParameter, MA_SIZE sizeParameter = (MA_SIZE)-1) const;
	//MA_BOOL			DeleteArgument( MA_INT iIndex );
	MA_PCWSTR		GetProgramName(void) const { return (m_nArgumentCount > 0) ? m_aszArguments[0] : MA_NULL; }
	//MA_VOID			SetProgramName( MA_PCWSTR szProgramName );
	MA_PCWSTR		GetCommandLine(MA_BOOL bExcludeProgramName = MA_TRUE) const { return bExcludeProgramName ? (m_szCommandLine + m_sizeProgramName) : m_szCommandLine; }
	MA_INT	 		GetArgumentCount(void) const { return m_nArgumentCount; }
	MA_PWSTR*		GetArgumentVector(MA_BOOL bExcludeProgramName = MA_TRUE) const { return bExcludeProgramName ? (m_aszArguments + 1) : m_aszArguments; }
	MA_PCWSTR		GetArgument(MA_INT iIndex) const { return (iIndex >= m_nArgumentCount) ? MA_NULL : m_aszArguments[iIndex]; }
	MA_PCWSTR		operator[](MA_INT IN iIndex) const { return GetArgument(iIndex); }
	MA_PWSTR		operator[](MA_INT IN iIndex) { return (iIndex >= m_nArgumentCount) ? MA_NULL : m_aszArguments[iIndex]; }

protected:
	void			Reset(void);
	void			Free(void);
	MA_BOOL			FillCommandLine(MA_INT IN nArgumentCount, MA_PWSTR IN aszArguments[], MA_BOOL bHasProgramName);
	MA_BOOL			FillArguments(MA_PCWSTR IN szCommandLine, MA_BOOL bHasProgramName);

protected:
	MA_PWSTR		m_szCommandLine;
	MA_SIZE			m_sizeProgramName;

	MA_INT			m_nArgumentCount;
	MA_PWSTR*		m_aszArguments;
	MA_PWSTR		m_szCommandBuffer;
};
