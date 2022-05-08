#ifndef _MA_CHARACTER_H_
#define _MA_CHARACTER_H_

_NTR_EXTERN_C_BEGIN

#if defined( _NTR_UNICODE )
	#define MA_CharIsSpace						MA_CharIsSpaceW
	#define MA_CharIsTab						MA_CharIsTabW
	#define MA_CharIsTabs						MA_CharIsTabsW
	#define MA_CharIsBlank						MA_CharIsBlankW
	#define MA_CharIsDot						MA_CharIsDotW
	#define MA_CharIsAsterisk					MA_CharIsAsteriskW
	#define MA_CharIsLineFeed					MA_CharIsLineFeedW		// Line Feed
	#define MA_CharIsFormFeed					MA_CharIsFormFeedW		// Form Feed
	#define MA_CharIsCarrageReturn				MA_CharIsCarrageReturnW	// Carriage Return
	#define MA_CharIsNewLine					MA_CharIsNewLineW				// New Line
	#define MA_CharIsWhiteSpace					MA_CharIsWhiteSpaceW			// White Space
	#define MA_CharIsLower						MA_CharIsLowerW
	#define MA_CharIsUpper						MA_CharIsUpperW
	#define MA_CharLIsLower						MA_CharLIsLowerW
	#define MA_CharLIsUpper						MA_CharLIsUpperW
	#define MA_CharToLower						MA_CharToLowerW
	#define MA_CharToUpper						MA_CharToUpperW
	#define MA_CharLToLower						MA_CharLToLowerW
	#define MA_CharLToUpper						MA_CharLToUpperW
	#define MA_CharIsSymbolable					MA_CharIsSymbolableW
	#define MA_CharIsBin						MA_CharIsBinW
	#define MA_CharIsOct						MA_CharIsOctW
	#define MA_CharIsDec						MA_CharIsDecW
	#define MA_CharIsDigit						MA_CharIsDecW
	#define MA_CharIsHexAlphabet				MA_CharIsHexAlphabetW
	#define MA_CharIsHex						MA_CharIsHexW
	#define MA_CharIsPathDelimiter				MA_CharIsPathDelimiterW
	#define MA_CharIsEOS						MA_CharIsEOSW
	#define MA_CharIsQuote						MA_CharIsQuoteW
	#define MA_CharIsDoubleQuote				MA_CharIsDoubleQuoteW
	#define MA_CharIsPrint						MA_CharIsPrintW
	#define MA_HexToInt							MA_HexToIntW
#elif defined( _NTR_ASCII )
	#define MA_CharIsSpace						MA_CharIsSpaceA
	#define MA_CharIsTab						MA_CharIsTabA
	#define MA_CharIsTabs						MA_CharIsTabsA
	#define MA_CharIsBlank						MA_CharIsBlankA
	#define MA_CharIsDot						MA_CharIsDotA
	#define MA_CharIsAsterisk					MA_CharIsAsteriskA
	#define MA_CharIsLineFeed					MA_CharIsLineFeedA
	#define MA_CharIsFormFeed					MA_CharIsFormFeedA
	#define MA_CharIsCarrageReturn				MA_CharIsCarrageReturnA
	#define MA_CharIsNewLine					MA_CharIsNewLineA
	#define MA_CharIsWhiteSpace					MA_CharIsWhiteSpaceA
	#define MA_CharIsLower						MA_CharIsLowerA
	#define MA_CharIsUpper						MA_CharIsUpperA
	#define MA_CharLIsLLower					MA_CharLIsLowerA
	#define MA_CharLIsLUpper					MA_CharLIsUpperA
	#define MA_CharToLower						MA_CharToLowerA
	#define MA_CharToUpper						MA_CharToUpperA
	#define MA_CharLToLower						MA_CharLToLowerA
	#define MA_CharLToUpper						MA_CharLToUpperA
	#define MA_CharIsSymbolable					MA_CharIsSymbolableA
	#define MA_CharIsBin						MA_CharIsBinA
	#define MA_CharIsOct						MA_CharIsOctA
	#define MA_CharIsDec						MA_CharIsDecA
	#define MA_CharIsDigit						MA_CharIsDecA
	#define MA_CharIsHexAlphabet				MA_CharIsHexAlphabetA
	#define MA_CharIsHex						MA_CharIsHexA
	#define MA_CharIsPathDelimiter				MA_CharIsPathDelimiterA
	#define MA_CharIsEOS						MA_CharIsEOSA
	#define MA_CharIsQuote						MA_CharIsQuoteA
	#define MA_CharIsDoubleQuote				MA_CharIsDoubleQuoteA
	#define MA_CharIsPrint						MA_CharIsPrintA
	#define MA_HexToInt							MA_HexToIntA
#else
	#define MA_CharIsSpace						MA_CharIsSpaceE
	#define MA_CharIsTab						MA_CharIsTabE
	#define MA_CharIsTabs						MA_CharIsTabsE
	#define MA_CharIsBlank						MA_CharIsBlankE
	#define MA_CharIsDot						MA_CharIsDotE
	#define MA_CharIsAsterisk					MA_CharIsAsteriskE
	#define MA_CharIsLineFeed					MA_CharIsLineFeedE
	#define MA_CharIsFormFeed					MA_CharIsFormFeedE
	#define MA_CharIsCarrageReturn				MA_CharIsCarrageReturnE
	#define MA_CharIsNewLine					MA_CharIsNewLineE
	#define MA_CharIsWhiteSpace					MA_CharIsWhiteSpaceE
	#define MA_CharIsLower						MA_CharIsLowerE
	#define MA_CharIsUpper						MA_CharIsUpperE
	#define MA_CharLIsLower						MA_CharLIsLowerE
	#define MA_CharLIsUpper						MA_CharLIsUpperE
	#define MA_CharToLower						MA_CharToLowerE
	#define MA_CharToUpper						MA_CharToUpperE
	#define MA_CharLToLower						MA_CharLToLowerE
	#define MA_CharLToUpper						MA_CharLToUpperE
	#define MA_CharIsSymbolable					MA_CharIsSymbolableE
	#define MA_CharIsBin						MA_CharIsBinE
	#define MA_CharIsOct						MA_CharIsOctE
	#define MA_CharIsDec						MA_CharIsDecE
	#define MA_CharIsDigit						MA_CharIsDecE
	#define MA_CharIsHexAlphabet				MA_CharIsHexAlphabetE
	#define MA_CharIsHex						MA_CharIsHexE
	#define MA_CharIsPathDelimiter				MA_CharIsPathDelimiterE
	#define MA_CharIsEOS						MA_CharIsEOSE
	#define MA_CharIsQuote						MA_CharIsQuoteE
	#define MA_CharIsDoubleQuote				MA_CharIsDoubleQuoteE
	#define MA_CharIsPrint						MA_CharIsPrintE
	#define MA_HexToInt							MA_HexToIntE
#endif

#define MA_CharIsSpaceE							MA_CharIsSpaceA
#define MA_CharIsTabE							MA_CharIsTabA
#define MA_CharIsTabE							MA_CharIsTabA
#define MA_CharIsBlankE							MA_CharIsBlankA
#define MA_CharIsDotE							MA_CharIsDotA
#define MA_CharIsAsteriskE						MA_CharIsAsteriskA
#define MA_CharIsLineFeedE						MA_CharIsLineFeedA
#define MA_CharIsFormFeedE						MA_CharIsFormFeedA
#define MA_CharIsCarrageReturnE					MA_CharIsCarrageReturnA
#define MA_CharIsNewLineE						MA_CharIsNewLineA
#define MA_CharIsWhiteSpaceE					MA_CharIsWhiteSpaceA
#define MA_CharIsLowerE							MA_CharIsLowerA
#define MA_CharIsUpperE							MA_CharIsUpperA
#define MA_CharLIsLowerE						MA_CharLIsLowerA
#define MA_CharLIsUpperE						MA_CharLIsUpperA
#define MA_CharToLowerE							MA_CharToLowerA
#define MA_CharToUpperE							MA_CharToUpperA
#define MA_CharLToLowerE						MA_CharLToLowerA
#define MA_CharLToUpperE						MA_CharLToUpperA
#define MA_CharIsSymbolableE					MA_CharIsSymbolableA
#define MA_CharIsBinE							MA_CharIsBinA
#define MA_CharIsOctE							MA_CharIsOctA
#define MA_CharIsDecE							MA_CharIsDecA
#define MA_CharIsDecE							MA_CharIsDecA
#define MA_CharIsHexAlphabetE					MA_CharIsHexAlphabetA
#define MA_CharIsHexE							MA_CharIsHexA
#define MA_CharIsPathDelimiterE					MA_CharIsPathDelimiterA
#define MA_CharIsEOSE							MA_CharIsEOSA
#define MA_CharIsQuoteE							MA_CharIsQuoteA
#define MA_CharIsDoubleQuoteE					MA_CharIsDoubleQuoteA
#define MA_CharIsPrintE							MA_CharIsPrintA
#define MA_HexToIntE							MA_HexToIntA

/*
 * Function: MA_CharIsSpace
 * ���ڰ� Space���� �˻��Ѵ�.
 * �� �Լ��� Ȯ���ϴ� ���� ���ڴ� 0x09 ~ 0x0D, 0x20 �̴�.
 *
 * Parameters:
 *	ch [in]		- Space���� �˻��� ����
 *
 * Returns:
 *	ch�� Space�̸� MA_TRUE, �׷��� ������ MA_FALSE�� return �Ѵ�.
 */
NTR_INLINE MA_BOOL 	MA_CharIsSpaceA( MA_CHAR IN ch )	{ return (ch  == ' ')?  MA_TRUE: MA_FALSE; }
NTR_INLINE MA_BOOL 	MA_CharIsSpaceW( MA_WCHAR IN wch )	{ return (wch == L' ')? MA_TRUE: MA_FALSE; }

/*
 * Function: MA_CharIsTab
 * ���ڰ� Tab(Horizontal Tab)���� �˻��Ѵ�.
 *
 * Parameters:
 *	ch [in]		- Tab���� �˻��� ����
 *
 * Returns:
 *	ch�� Tab�̸� MA_TRUE, �׷��� ������ MA_FALSE�� return �Ѵ�.
 */
NTR_INLINE MA_BOOL 	MA_CharIsTabA( MA_CHAR IN ch )			{ return (ch  == '\t')?  MA_TRUE: MA_FALSE; }
NTR_INLINE MA_BOOL 	MA_CharIsTabW( MA_WCHAR IN wch )		{ return (wch == L'\t')? MA_TRUE: MA_FALSE; }

/*
 * Function: MA_CharIsTab
 * ���ڰ� Tab���� �˻��Ѵ�.
 *
 * Parameters:
 *	ch [in]		- Tab���� �˻��� ����
 *
 * Returns:
 *	ch�� Tab�̸� MA_TRUE, �׷��� ������ MA_FALSE�� return �Ѵ�.
 */
NTR_INLINE MA_BOOL 	MA_CharIsTabsA( MA_CHAR IN ch )			{ return ((ch  == '\t')  || (ch  == L'v'))?  MA_TRUE: MA_FALSE; }
NTR_INLINE MA_BOOL 	MA_CharIsTabsW( MA_WCHAR IN wch )		{ return ((wch == L'\t') || (wch == L'\v'))? MA_TRUE: MA_FALSE; }

/*
 * Function: MA_CharIsBlank
 * ���ڰ� Blank���� �˻��Ѵ�.
 *
 * Parameters:
 *	ch [in]		- Blank���� �˻��� ����
 *
 * Returns:
 *	ch�� Blank�̸� MA_TRUE, �׷��� ������ MA_FALSE�� return �Ѵ�.
 */
NTR_INLINE MA_BOOL 	MA_CharIsBlankA( MA_CHAR IN ch )		{ return (MA_CharIsSpaceA( ch )  || MA_CharIsTabA( ch ))?  MA_TRUE: MA_FALSE; }
NTR_INLINE MA_BOOL 	MA_CharIsBlankW( MA_WCHAR IN wch )		{ return (MA_CharIsSpaceW( wch ) || MA_CharIsTabW( wch ))? MA_TRUE: MA_FALSE; }

/*
 * Function: MA_CharIsDot
 * ���ڰ� Dot���� �˻��Ѵ�.
 *
 * Parameters:
 *	ch [in]		- Dot���� �˻��� ����
 *
 * Returns:
 *	ch�� Dot�̸� MA_TRUE, �׷��� ������ MA_FALSE�� return �Ѵ�.
 */
NTR_INLINE MA_BOOL 	MA_CharIsDotA( MA_CHAR IN ch )	{ return (ch  == '.')?  MA_TRUE: MA_FALSE; }
NTR_INLINE MA_BOOL 	MA_CharIsDotW( MA_WCHAR IN wch )	{ return (wch == L'.')? MA_TRUE: MA_FALSE; }

/*
 * Function: MA_CharIsAsterisk
 * ���ڰ� Asterisk���� �˻��Ѵ�.
 *
 * Parameters:
 *	ch [in]		- Asterisk���� �˻��� ����
 *
 * Returns:
 *	ch�� Asterisk�̸� MA_TRUE, �׷��� ������ MA_FALSE�� return �Ѵ�.
 */
NTR_INLINE MA_BOOL 	MA_CharIsAsteriskA( MA_CHAR IN ch )	{ return (ch  == MA_ASTERISK_A)? MA_TRUE: MA_FALSE; }
NTR_INLINE MA_BOOL 	MA_CharIsAsteriskW( MA_WCHAR IN wch )	{ return (wch == MA_ASTERISK_W)? MA_TRUE: MA_FALSE; }

/*
 * Function: MA_CharIsLineFeed
 * ���ڰ� Line Feed���� �˻��Ѵ�.
 *
 * Parameters:
 *	ch [in]		- Line Feed���� �˻��� ����
 *
 * Returns:
 *	ch�� Line Feed�̸� MA_TRUE, �׷��� ������ MA_FALSE�� return �Ѵ�.
 */
NTR_INLINE MA_BOOL 	MA_CharIsLineFeedA( MA_CHAR IN ch )	{ return (ch  == MA_LF_A)?  MA_TRUE: MA_FALSE; }
NTR_INLINE MA_BOOL 	MA_CharIsLineFeedW( MA_WCHAR IN wch )	{ return (wch == MA_LF_W)? MA_TRUE: MA_FALSE; }

/*
 * Function: MA_CharIsFormFeed
 * ���ڰ� Form Feed���� �˻��Ѵ�.
 *
 * Parameters:
 *	ch [in]		- Form Feed���� �˻��� ����
 *
 * Returns:
 *	ch�� Form Feed�̸� MA_TRUE, �׷��� ������ MA_FALSE�� return �Ѵ�.
 */
NTR_INLINE MA_BOOL 	MA_CharIsFormFeedA( MA_CHAR IN ch )	{ return (ch  == '\f')?  MA_TRUE: MA_FALSE; }
NTR_INLINE MA_BOOL 	MA_CharIsFormFeedW( MA_WCHAR IN wch )	{ return (wch == L'\f')? MA_TRUE: MA_FALSE; }

/*
 * Function: MA_CharIsCarrageReturn
 * ���ڰ� Carriage Return���� �˻��Ѵ�.
 *
 * Parameters:
 *	ch [in]		- Carriage Return���� �˻��� ����
 *
 * Returns:
 *	ch�� Carriage Return�̸� MA_TRUE, �׷��� ������ MA_FALSE�� return �Ѵ�.
 */
NTR_INLINE MA_BOOL 	MA_CharIsCarrageReturnA( MA_CHAR IN ch )	{ return (ch  == MA_CR_A)?  MA_TRUE: MA_FALSE; }
NTR_INLINE MA_BOOL 	MA_CharIsCarrageReturnW( MA_WCHAR IN wch )	{ return (wch == MA_CR_W)? MA_TRUE: MA_FALSE; }

/*
 * Function: MA_CharIsNewLine
 * ���ڰ� NewLine���� �˻��Ѵ�.
 *
 * Parameters:
 *	ch [in]		- NewLine���� �˻��� ����
 *
 * Returns:
 *	ch�� NewLine�̸� MA_TRUE, �׷��� ������ MA_FALSE�� return �Ѵ�.
 */
NTR_INLINE MA_BOOL 	MA_CharIsNewLineA( MA_CHAR IN ch )		{ return (MA_CharIsCarrageReturnA( ch )  || MA_CharIsLineFeedA( ch ))?  MA_TRUE: MA_FALSE; }
NTR_INLINE MA_BOOL 	MA_CharIsNewLineW( MA_WCHAR IN wch )	{ return (MA_CharIsCarrageReturnW( wch ) || MA_CharIsLineFeedW( wch ))? MA_TRUE: MA_FALSE; }

/*
 * Function: MA_CharIsWhiteSpace
 * ���ڰ� Whiespace���� �˻��Ѵ�.
 * white space ���ڴ� ������ ����.
 * HT(0x09, Horizontal Tab), LF(0x0A, Line Feed), VT(0x0B, Vertical Tab), FF(0x0C, FormFeed), CR(0x0D, Carrage Return), Space(0x20)
 *
 * Parameters:
 *	ch [in]		- Whitespace���� �˻��� ����
 *
 * Returns:
 *	ch�� Whitespace�̸� MA_TRUE, �׷��� ������ MA_FALSE�� return �Ѵ�.
 */
NTR_INLINE MA_BOOL 	MA_CharIsWhiteSpaceA( MA_CHAR IN ch )	{ return (MA_CharIsBlankA( ch )  || MA_CharIsNewLineA( ch )  || MA_CharIsLineFeedA( ch ))?  MA_TRUE: MA_FALSE; }
NTR_INLINE MA_BOOL 	MA_CharIsWhiteSpaceW( MA_WCHAR IN wch )	{ return (MA_CharIsBlankW( wch ) || MA_CharIsNewLineW( wch ) || MA_CharIsLineFeedW( wch ))? MA_TRUE: MA_FALSE; }

/*
 * Function: MA_CharIsLower
 * ���ڰ� �ҹ������� �˻��Ѵ�.
 *
 * Parameters:
 *	ch [in]		- �ҹ������� �˻��� ����
 *
 * Returns:
 *	ch�� �ҹ����̸� MA_TRUE, �׷��� ������ MA_FALSE�� return �Ѵ�.
 */
NTR_INLINE MA_BOOL 	MA_CharIsLowerA( MA_CHAR IN ch )		{ return (('a'  <= ch)  && (ch  <= 'z'))?  MA_TRUE: MA_FALSE; }
NTR_INLINE MA_BOOL 	MA_CharIsLowerW( MA_WCHAR IN wch )		{ return ((L'a' <= wch) && (wch <= L'z'))? MA_TRUE: MA_FALSE; }

#if defined(_NTR_WINDOWS)
NTR_INLINE MA_BOOL 	MA_CharLIsLowerA( MA_CHAR IN ch )		{ return IsCharLowerA( ch ); }
NTR_INLINE MA_BOOL 	MA_CharLIsLowerW( MA_WCHAR IN wch )		{ return IsCharLowerW( wch ); }
#endif

/*
 * Function: MA_CharIsUpper
 * ���ڰ� �빮������ �˻��Ѵ�.
 *
 * Parameters:
 *	ch [in]		- �빮������ �˻��� ����
 *
 * Returns:
 *	ch�� �빮���̸� MA_TRUE, �׷��� ������ MA_FALSE�� return �Ѵ�.
 */
NTR_INLINE MA_BOOL 	MA_CharIsUpperA( MA_CHAR IN ch )		{ return (('A'  <= ch)  && (ch  <= 'Z')) ?  MA_TRUE: MA_FALSE; }
NTR_INLINE MA_BOOL 	MA_CharIsUpperW( MA_WCHAR IN wch )		{ return ((L'A' <= wch) && (wch <= L'Z')) ? MA_TRUE: MA_FALSE; }

#if defined(_NTR_WINDOWS)
NTR_INLINE MA_BOOL 	MA_CharLIsUpperA( MA_CHAR IN ch )		{ return IsCharUpperA( ch ); }
NTR_INLINE MA_BOOL 	MA_CharLIsUpperW( MA_WCHAR IN wch )		{ return IsCharUpperW( wch ); }
#endif

/*
 * Function: MA_CharToLower
 * ���ڸ� �ҹ��ڷ� �ٲ۴�.
 *
 * Parameters:
 *	ch [in]		- �ҹ��ڷ� �ٲ� ����
 *
 * Returns:
 *	�ҹ��ڷ� �ٲ� ����
 */
// return IS_UPPER( tch ) ? tch + _T_CV('a') - _T_CV('A') : tch;
NTR_INLINE MA_CHAR	MA_CharToLowerA( MA_CHAR IN ch )		{ return MA_CharIsUpperA( ch ) ? (ch  | 0x20): ch;  }
NTR_INLINE MA_WCHAR	MA_CharToLowerW( MA_WCHAR IN wch )		{ return MA_CharIsUpperW( wch )? (wch | 0x20): wch; }

#if defined(_NTR_WINDOWS)
//NTR_INLINE MA_CHAR	MA_CharLToLowerA( MA_CHAR IN ch )		{ return CharLowerA( (LPSTR) (ch) );  }
//NTR_INLINE MA_WCHAR	MA_CharLToLowerW( MA_WCHAR IN wch )		{ return CharLowerW( (LPWSTR) wch ); }
#endif

/*
 * Function: MA_CharToUpper
 * ���ڸ� �빮�ڷ� �ٲ۴�.
 *
 * Parameters:
 *	ch [in]		- �빮�ڷ� �ٲ� ����
 *
 * Returns:
 *	�빮�ڷ� �ٲ� ����
 */
// return IS_LOWER( tch ) ? tch - _T_CV('a') + _T_CV('A') : tch;
NTR_INLINE MA_CHAR	MA_CharToUpperA( MA_CHAR IN ch )		{ return MA_CharIsLowerA( ch )  ? (ch  & 0xDF): ch;  }
NTR_INLINE MA_WCHAR	MA_CharToUpperW( MA_WCHAR IN wch )		{ return MA_CharIsLowerW( wch ) ? (wch & 0xDF): wch; }

#if defined(_NTR_WINDOWS)
//NTR_INLINE MA_CHAR	MA_CharLToUpperA( MA_CHAR IN ch )		{ return (MA_CHAR) CharUpperA( (LPSTR) (ch) );  }
//NTR_INLINE MA_WCHAR	MA_CharLToUpperW( MA_WCHAR IN wch )		{ return (MA_WCHAR) CharUpperW( (LPWSTR) wch ); }
#endif

/*
 * Function: MA_CharIsBin
 * ���ڰ� 2���� ����(0 ~ 1)���� �˻��Ѵ�.
 *
 * Parameters:
 *	ch [in]		- 2���� �������� �˻��� ����
 *
 * Returns:
 *	2���� �����̸� MA_TRUE, �׷��� ������ MA_FALSE�� return �Ѵ�.
 */
NTR_INLINE MA_BOOL 	MA_CharIsBinA( MA_CHAR IN ch )		{ return ((ch  == '0')  || (ch  == '1'))?  MA_TRUE: MA_FALSE; }
NTR_INLINE MA_BOOL 	MA_CharIsBinW( MA_WCHAR IN wch )		{ return ((wch == L'0') || (wch == L'1'))? MA_TRUE: MA_FALSE; }

/*
 * Function: MA_CharIsOct
 * ���ڰ� 8���� ����(0 ~ 7)���� �˻��Ѵ�.
 *
 * Parameters:
 *	ch [in]		- 8���� �������� �˻��� ����
 *
 * Returns:
 *	8���� �����̸� MA_TRUE, �׷��� ������ MA_FALSE�� return �Ѵ�.
 */
NTR_INLINE MA_BOOL 	MA_CharIsOctA( MA_CHAR IN ch )		{ return (('0'  <= ch)  && (ch  <= '7'))?  MA_TRUE: MA_FALSE; }
NTR_INLINE MA_BOOL 	MA_CharIsOctW( MA_WCHAR IN wch )		{ return ((L'0' <= wch) && (wch <= L'7'))? MA_TRUE: MA_FALSE; }

/*
 * Function: MA_CharIsDec
 * ���ڰ� 10���� ����(0 ~ 9)���� �˻��Ѵ�.
 *
 * Parameters:
 *	ch [in]		- 10���� �������� �˻��� ����
 *
 * Returns:
 *	ch�� 10���� �����̸� MA_TRUE, �׷��� ������ MA_FALSE�� return �Ѵ�.
 */
NTR_INLINE MA_BOOL 	MA_CharIsDecA( MA_CHAR IN ch )			{ return (('0'  <= ch)  && (ch  <= '9'))?  MA_TRUE: MA_FALSE; }
NTR_INLINE MA_BOOL 	MA_CharIsDecW( MA_WCHAR IN wch )		{ return ((L'0' <= wch) && (wch <= L'9'))? MA_TRUE: MA_FALSE; }

/*
 * Function: MA_CharIsSymbolable
 * �ɺ��� �� �� �ִ� �������� �˻��Ѵ�. (���ĺ�, ����, _)
 *
 * Parameters:
 *	ch [in]		- �빮������ �˻��� ����
 *
 * Returns:
 *	ch�� �빮���̸� MA_TRUE, �׷��� ������ MA_FALSE�� return �Ѵ�.
 */
NTR_INLINE MA_BOOL 	MA_CharIsSymbolableA( MA_CHAR IN ch )		{ return MA_CharIsUpperA(ch) || MA_CharIsLowerA(ch) || MA_CharIsDecA(ch); }
NTR_INLINE MA_BOOL 	MA_CharIsSymbolableW( MA_WCHAR IN wch )		{ return MA_CharIsUpperW(wch) || MA_CharIsLowerW(wch) || MA_CharIsDecW(wch); }

/*
 * Function: MA_CharIsHexAlphabet
 * ���ڰ� 16���� Alphabet(A ~ F)���� �˻��Ѵ�.
 *
 * Parameters:
 *	ch [in]		- 16���� alphabet���� �˻��� ����
 *
 * Returns:
 *	ch�� 16���� alphabet�̸� MA_TRUE, �׷��� ������ MA_FALSE�� return �Ѵ�.
 */
NTR_INLINE MA_BOOL 	MA_CharIsHexAlphabetA( MA_CHAR IN ch )	{ MA_CHAR  chUpper  = MA_CharToUpperA( ch );  return (('A'  <= chUpper)  && (chUpper  <= 'F'))?  MA_TRUE: MA_FALSE; }
NTR_INLINE MA_BOOL 	MA_CharIsHexAlphabetW( MA_WCHAR IN wch )	{ MA_WCHAR wchUpper = MA_CharToUpperW( wch ); return ((L'A' <= wchUpper) && (wchUpper <= L'F'))? MA_TRUE: MA_FALSE; }

/*
 * Function: MA_CharIsHex
 * ���ڰ� 2���� ����(0 ~ 1)���� �˻��Ѵ�.
 *
 * Parameters:
 *	ch [in]		- 2���� �������� �˻��� ����
 *
 * Returns:
 *	ch�� 2���� �����̸� MA_TRUE, �׷��� ������ MA_FALSE�� return �Ѵ�.
 */
NTR_INLINE MA_BOOL 	MA_CharIsHexA( MA_CHAR IN ch )		{ return (MA_CharIsDecA( ch )  || MA_CharIsHexAlphabetA( ch ))?  MA_TRUE: MA_FALSE; }
NTR_INLINE MA_BOOL 	MA_CharIsHexW( MA_WCHAR IN wch )		{ return (MA_CharIsDecW( wch ) || MA_CharIsHexAlphabetW( wch ))? MA_TRUE: MA_FALSE; }

/*
 * Function: MA_CharIsPathDelimiter
 * ���ڰ� Path�� Delimiter���� �˻��Ѵ�.
 *
 * Parameters:
 *	ch [in]		- Path�� Delimiter���� �˻��� ����
 *
 * Returns:
 *	ch�� Path�� Delimiter�̸� MA_TRUE, �׷��� ������ MA_FALSE�� return �Ѵ�.
 */
NTR_INLINE MA_BOOL 	MA_CharIsPathDelimiterA( MA_CHAR IN ch )	{ return ((ch  == '\\')  || (ch  == '/'))?  MA_TRUE: MA_FALSE; }
NTR_INLINE MA_BOOL 	MA_CharIsPathDelimiterW( MA_WCHAR IN wch )	{ return ((wch == L'\\') || (wch == L'/'))? MA_TRUE: MA_FALSE; }

/*
 * Function: MA_CharIsEOS
 * ���ڰ� End-Of-String(\0)���� �˻��Ѵ�.
 *
 * Parameters:
 *	ch [in]		- Null���� �˻��� ����
 *
 * Returns:
 *	ch�� Null�̸� MA_TRUE, �׷��� ������ MA_FALSE�� return �Ѵ�.
 */
NTR_INLINE MA_BOOL 	MA_CharIsEOSA( MA_CHAR IN ch )		{ return (ch  == '\0')?  MA_TRUE: MA_FALSE; }
NTR_INLINE MA_BOOL 	MA_CharIsEOSW( MA_WCHAR IN wch )		{ return (wch == L'\0')? MA_TRUE: MA_FALSE; }

/*
 * Function: MA_CharIsQuote
 * ���ڰ� Single Quotation���� �˻��Ѵ�.
 *
 * Parameters:
 *	ch [in]		- Single Quotation���� �˻��� ����
 *
 * Returns:
 *	Single Quotation�̸� MA_TRUE, �׷��� ������ MA_FALSE�� return �Ѵ�.
 */
NTR_INLINE MA_BOOL 	MA_CharIsQuoteA( MA_CHAR IN ch )		{ return (ch  == '\'')?  MA_TRUE: MA_FALSE; }
NTR_INLINE MA_BOOL 	MA_CharIsQuoteW( MA_WCHAR IN wch )		{ return (wch == L'\'')? MA_TRUE: MA_FALSE; }

/*
 * Function: MA_CharIsDoubleQuote
 * ���ڰ� Double Quotation���� �˻��Ѵ�.
 *
 * Parameters:
 *	ch [in]		- Double Quotation���� �˻��� ����
 *
 * Returns:
 *	Double Quotation�̸� MA_TRUE, �׷��� ������ MA_FALSE�� return �Ѵ�.
 */
NTR_INLINE MA_BOOL 	MA_CharIsDoubleQuoteA( MA_CHAR IN ch )	{ return (ch  == '"') ?  MA_TRUE: MA_FALSE;	}
NTR_INLINE MA_BOOL 	MA_CharIsDoubleQuoteW( MA_WCHAR IN wch )	{ return (wch == L'"') ? MA_TRUE: MA_FALSE;	}

/*
 * Function: MA_CharIsPrint
 * Print ������ �������� �˻��Ѵ�.
 *
 * Parameters:
 *	ch [in]		- Print ������ �� �˻��� ����
 *
 * Returns:
 *	Print ������ ������ ��쿡�� 0�� �ƴ� ����, �׷��� ������ 0�� ����.
 */
NTR_INLINE MA_BOOL 	MA_CharIsPrintA( MA_CHAR IN ch )		{ return isprint( (unsigned char) ch );		}
NTR_INLINE MA_BOOL 	MA_CharIsPrintW( MA_WCHAR IN wch )		{ return iswprint( wch );			}


/*
 * Function: MA_HexToInt
 * Hex ���ڸ� ���ڷ� �ٲ۴�.
 *
 * Parameters:
 *	ch [in]		- Hex characterr
 *
 * Returns:
 *	ch�� ���ڷ� �ٲ� ��.
 */
NTR_INLINE MA_CHAR	MA_HexToIntA( MA_CHAR IN ch )		{ if( MA_CharIsDecA( ch ) )  return (MA_CHAR)(ch  - '0');  else return (MA_CHAR)(ch  - 'A' + 10);	}
NTR_INLINE MA_WCHAR	MA_HexToIntW( MA_WCHAR IN wch )		{ if( MA_CharIsDecW( wch ) ) return (MA_WCHAR)(wch - L'0'); else return (MA_WCHAR)(wch - L'A' + 10);	}

_NTR_EXTERN_C_END

#endif /* !_MA_CHARACTER_H_ */
