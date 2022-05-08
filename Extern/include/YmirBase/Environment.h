#pragma once

#include "TStringBuffer.h"
#include "TStringTable.h"
#include "TPointerSingleton.h"

class EL_Environment
: public EL_TPointerSingleton<EL_Environment>
, public EL_TStringTable<EL_TCHAR>
{
public:
	EL_DECLARE_POINTER_SINGLETON(Environment)

public:
	EL_Environment();

	EL_UINT32 GetAllocationGranularity();

public:
	const IN_BasicString& GetValue(const IN_SimpleString& key) const
	{
		return EL_TStringTable::GetValue(key, m_defaultValue);
	}

	EL_FLOAT GetValuef(const IN_SimpleString& key) const
	{
		return EL_TStringTable::GetValue<EL_FLOAT>(key, 0.0f);
	}

	int GetValuei(const IN_SimpleString& key) const
	{
		return EL_TStringTable::GetValue<EL_INT>(key, 0);
	}

	bool GetValueb(const IN_SimpleString& key) const
	{
		return EL_TStringTable::GetValue<EL_BOOL>(key, EL_FALSE);
	}

private:
	// �⺻���� SetValue�� �̸� ���ؾ� ����� �� �ֵ��� �⺻���� ���ڷ� ���� �Լ���
	// private���� �Űܼ� �ǵ������� ������ ������ �Ѵ�.
	virtual const IN_BasicString& GetValue(const IN_SimpleString&, const IN_BasicString& defValue) const
	{
		return defValue;
	}

	virtual EL_FLOAT GetValuef(const IN_SimpleString&, EL_FLOAT) const
	{
		return 0.0f;
	}

	virtual int GetValuei(const IN_SimpleString&, int) const
	{
		return 0;
	}

	virtual bool GetValueb(const IN_SimpleString&, bool) const
	{
		return EL_FALSE;
	}

private:
	SYSTEM_INFO m_sysInfo;
	IN_BasicString m_defaultValue;
};
