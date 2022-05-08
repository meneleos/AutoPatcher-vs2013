#pragma once

#include "../eterLib/NetStream.h"

#ifdef ENABLE_GUARD_CHECKER
	class CServerGuardChecker
	{
		public:
			CServerGuardChecker();
			virtual ~CServerGuardChecker();

			void Create();
			void AddChannel(UINT uServerIndex, const char* c_szAddr, UINT uPort);
			bool Request();
			bool Update();

			void Initialize();

		private:
			typedef struct SChannel
			{
				UINT uServerIndex;
				const char* c_szAddr;
				UINT uPort;
			} TGuardChannel;

			std::list<TGuardChannel> m_lstChannel;

			CNetworkStream m_kStream;
	};
#endif
