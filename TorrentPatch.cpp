#include "Metin2TorrentConsole.h"

#ifndef NO_LIBTORRENT
#include "TorrentPatch.h"

#include <libtorrent-1.1.12/bencode.hpp>
#include <libtorrent-1.1.12/session.hpp>
#include <libtorrent-1.1.12/torrent_info.hpp>
#include <libtorrent-1.1.12/alert_types.hpp>
#include <libtorrent-1.1.12/extensions/smart_ban.hpp>

#include "TorrentPatchApp.h"
#include "TorrentPatchFrame.h"
#include "PatchThread.h"

//#include "StringFromFile.h"
#include "StringFromHttp.h"
#include "PatchStatus.h"
//#include "CrcPatcher.h"
#include "CVersionFile.h"

//#include <YmirBase/DiskUtils.h>
//#include <strsafe.h>
#include <boost/random.hpp>
#include "Helper.h"

#include "torrentSkin.h"
#include "StringMa.h"
#include <boost/filesystem/fstream.hpp>
#include <iostream>
//
//#define stdin  (__acrt_iob_func(0))
//#define stdout (__acrt_iob_func(1))
//#define stderr (__acrt_iob_func(2))

using namespace libtorrent;	

/////////////////////////////////////////////////////////////////////////////////////////////////////////

EL_TorrentPatcher::EL_TorrentPatcher(EL_PatchThread* pcPatchThread)
: m_pcPatchThread(pcPatchThread)
, m_pcSession(NULL)
{
}

EL_TorrentPatcher::EL_TorrentPatcher()
: m_pcSession(NULL)
{
}

EL_TorrentPatcher::~EL_TorrentPatcher()
{
	MA_SAFE_DELETE(m_pcSession);
}

void EL_TorrentPatcher::__SetBandwidth(MA_UINT uiBandwidth)
{
	if( uiBandwidth == 0 ) {
		m_pcSession->set_download_rate_limit(-1);
		m_pcSession->set_upload_rate_limit(-1);
	} else {
		m_pcSession->set_download_rate_limit(uiBandwidth);
		m_pcSession->set_upload_rate_limit(uiBandwidth);
	}
}

bool EL_TorrentPatcher::__DownloadPatches(const PatchInfos& patchInfos, EL_PatchConfig& config, CStatus *pcStatus)
{	
	typedef boost::uniform_int<unsigned int> uint_dist;

	BOOST_FOREACH(const PatchInfo& patchInfo, patchInfos)
	{
		if( m_pcPatchThread->_IsAlive() == false )
			break;

		if( patchInfo.torrentUrl.empty() )
			continue;

		bool start = false;

		if (0 == patchInfo.randomStart)
			start = true;
		else
		{
			boost::minstd_rand randGen;
			randGen.seed(time(0));

			boost::variate_generator<boost::minstd_rand, uint_dist> deg(randGen, uint_dist(1, patchInfo.randomStart));

			if (1 == deg())
				start = true;
		}

		if (true == start)
		{
			std::string torrentHead;
			std::wstring wstrTorrentState;

			if (EL_StringFromHttpW(torrentHead, patchInfo.torrentUrl, pcStatus)) {
				int urlSepPos = patchInfo.torrentUrl.rfind(L'/');
				if (urlSepPos >= 0) {
					urlSepPos += 1;
					int urlDotPos = patchInfo.torrentUrl.rfind(L'.');

					wstrTorrentState = patchInfo.torrentUrl.substr(urlSepPos, urlDotPos-urlSepPos);
					m_pcPatchThread->SetUINameState( wstrTorrentState.c_str() );
				}

				const std::string fastResumeName = EL_ToString(wstrTorrentState);
				if( !__DownloadTorrentBody(torrentHead, patchInfo, config, fastResumeName, pcStatus) ) {
					//m_pcPatchThread->SetUINameState( L"" );

					if( pcStatus )
						pcStatus->AddNR( CStatus::EA_STATUS_ERROR, EL_LTEXT("TORRENT_DOWNLOAD_ERROR") );
					return false;
				}

				//m_pcPatchThread->SetUINameState(L"");
				m_pcPatchThread->UpdateUI();
			} else {
				EL_WCHAR wszError[1024];
				StringFormat( wszError, MA_ARRAYCOUNT(wszError), _T("%s: %s"), EL_LTEXT("TORRENT_FILE_NOT_FOUND"), patchInfo.torrentUrl.c_str() );
				m_pcPatchThread->SetUISubState(wszError);
				m_pcPatchThread->UpdateUI();

				if( pcStatus )
					pcStatus->AddNRf( CStatus::EA_STATUS_ERROR, EL_LTEXT("TORRENT_NOT_FOUND"), patchInfo.torrentUrl.c_str() );
				return false;
			}
		}
		m_pcPatchThread->SetUINextSubState();
		m_pcPatchThread->UpdateUI();
	}
	return true;
}

void EL_TorrentPatcher::UpdateProgressPeerAndSpeed()
{
	std::vector<torrent_handle> torrents = m_pcSession->get_torrents();

	MA_INT		nActivePeers	= 0;
	MA_INT		nPeers			= 0;
	MA_INT		nActiveSeeds	= 0;
	MA_INT		nSeeds			= 0;
	MA_FLOAT	fDownloadBPS	= 0.0f;
	MA_FLOAT	fUploadBPS		= 0.0f;

	for( std::vector<torrent_handle>::iterator it = torrents.begin(); it != torrents.end(); it++ ) {
		torrent_handle&					hTorrentHandle = *it;
		torrent_status					stTorrentStatus = hTorrentHandle.status();

		fDownloadBPS					+= MA_FLOAT(stTorrentStatus.download_rate);
		fUploadBPS						+= MA_FLOAT(stTorrentStatus.upload_rate);

		nActivePeers					+= stTorrentStatus.num_peers;
		nPeers							+= stTorrentStatus.list_peers;

		nActiveSeeds					+= stTorrentStatus.num_seeds;
		nSeeds							+= stTorrentStatus.list_seeds;
	}

	m_pcPatchThread->SetUICurrentPeers( nActiveSeeds, nSeeds, nActivePeers, nPeers );
	m_pcPatchThread->SetUICurrentSpeed( fDownloadBPS, fUploadBPS );
	m_pcPatchThread->UpdateUI();
}

bool EL_TorrentPatcher::__DownloadTorrentBody(const std::string& torrentHead, const PatchInfo& patchInfo, EL_PatchConfig& config, const std::string& fastResumeName, CStatus *pcStatus)
{
	if (torrentHead.empty())
	{
		if( pcStatus )
			pcStatus->AddNR( CStatus::EA_STATUS_ERROR, EL_LTEXT("TORRENT_DATA_EMPTY") );
		return false;
	}

	entry e = bdecode(torrentHead.begin(), torrentHead.end());
	torrent_info ti(e);

	// ��Ƽ �䷻Ʈ�� ��� ��� ���� ���� ��θ� ���� ���� �������� ������ش�.
	{
		const std::string& tname = ti.name();

		int numFiles = ti.num_files();
		for (int i = 0; i != numFiles; ++i)
		{
			const file_entry& fe = ti.file_at(i);
			const std::string& filePath = fe.path.c_str();
			if (filePath.compare(0, tname.length(), tname) == 0)
			{
				std::string newPath = filePath.substr(tname.length()+1);
				ti.rename_file(i, newPath);
			}
		}
	}

	const int W_OK = 2;
	if (access("temp", W_OK) != 0)
		_mkdir("temp");

	std::string fastResumePath = "temp";
	fastResumePath = fastResumePath + "/" + fastResumeName + ".fastresume";

	std::vector<EL_ACHAR> fastResumeData;	
	{
		FILE* fp;
		if (fopen_s(&fp, fastResumePath.c_str(), "rb") == 0)
		{
			fseek(fp, 0, SEEK_END);
			long fastResumeDataSize = ftell(fp);
			fseek(fp, 0, SEEK_SET);

			fastResumeData.resize(fastResumeDataSize);
			fread(&fastResumeData[0], fastResumeDataSize, 1, fp);
			fclose(fp);
		}
	}

	CW2E convSaveDir(config.saveDir.c_str());

	add_torrent_params params;
	params.ti = boost::make_shared<torrent_info>(ti);
	params.save_path = (const char*) MA_LPESTR(convSaveDir);
	//params.storage_mode = storage_mode_sparse;

	if (!fastResumeData.empty())
	{
		params.resume_data = fastResumeData; // delete &
	}
	
	error_code ec;

	torrent_handle th = m_pcSession->add_torrent(params, ec);	

	th.pause(); // �䷻Ʈ ������ �����Ϸ��� �������Ѿ� �Ѵ�

	th.set_max_uploads(config.maxUploadsPerTorrent);
	th.set_max_connections(config.maxConnectionsPerTorrent);

	// ���� ���Ĵ� web seed ������� ����
	std::set<std::string> urlSeeds(th.url_seeds());
	//std::string urlSeed;
	//BOOST_FOREACH(&urlSeed, urlSeeds)

	for (auto& urlSeed : urlSeeds)
	{
		th.remove_url_seed(urlSeed);
	}		

	th.resume();

	bool isSeed = false;
	bool isWebSeedStarted = false;
	EL_UINT nIdleTicks = 0;
	float fBaseProgress = 0.0f;
	bool isDownloadStarted = false;

	while (m_pcPatchThread->_IsAlive() && !isSeed)
	{
		if( m_pcPatchThread->TestDestroy() )
			break;
		if( MA_FALSE == m_pcPatchThread->UpdateSpawning() )
			break;

		// ALERT üũ
		std::vector<alert*> autoAlertPtr;
		//std::auto_ptr<alert*> autoAlertPtr;
		//autoAlertPtr = m_pcSession->pop_alert();
		m_pcSession->pop_alerts(&autoAlertPtr);
		//alert* alertPtr;

		//while (NULL != (alertPtr = autoAlertPtr.get()))
		for (alert* alertPtr : autoAlertPtr)
		{
			bool error = false;
			bool ignore = false;

			// list of ignoreed alert:
			//   tracker_warning_alert
			//   fastresume_rejected_alert
			//   udp_error_alert
			//   save_resume_data_failed_alert
			if (file_error_alert* p = dynamic_cast<file_error_alert*>(alertPtr))
				error = true;
			else if (metadata_failed_alert* p = dynamic_cast<metadata_failed_alert*>(alertPtr))
				error = true;
			else if (listen_failed_alert* p = dynamic_cast<listen_failed_alert*>(alertPtr))
				error = true;
			else if (url_seed_alert* p = dynamic_cast<url_seed_alert*>(alertPtr))
				error = true;
			else if (torrent_delete_failed_alert* p = dynamic_cast<torrent_delete_failed_alert*>(alertPtr))
				error = true;
			else if (scrape_failed_alert* p = dynamic_cast<scrape_failed_alert*>(alertPtr))
				error = true;
			else if (file_rename_failed_alert* p = dynamic_cast<file_rename_failed_alert*>(alertPtr))
				error = true;
			else if (storage_moved_failed_alert* p = dynamic_cast<storage_moved_failed_alert*>(alertPtr))
				error = true;
			else if (torrent_delete_failed_alert* p = dynamic_cast<torrent_delete_failed_alert*>(alertPtr))
				error = true;
			else if (portmap_error_alert* p = dynamic_cast<portmap_error_alert*>(alertPtr))
				ignore = true;
			else if (tracker_error_alert* p = dynamic_cast<tracker_error_alert*>(alertPtr))
				error = false;

			if (error)
			{
				Mantle::MA_CA2T walertPtr(alertPtr->message().c_str());
				pcStatus->AddNRf( CStatus::EA_STATUS_ERROR, (MA_LPCWSTR) walertPtr );
				return false;
			}
			else if (!ignore)
			{
				FILE * fp;
				
				if (0 == fopen_s(&fp, "temp\\patch.log", "a+"))
				{
					fprintf_s(fp, "%s\n", alertPtr->message().c_str());
					fclose(fp);
				}
			}

			m_pcSession->pop_alerts(&autoAlertPtr);
			//autoAlertPtr = m_pcSession->pop_alert();
		}
		
		if (th.is_seed())
			isSeed = true; // ��� ������ �гο� ��ü �������� �Ϸ�� ǥ�õ��� �����Ƿ� ������ �� ���� ������

		EL_TorrentPatchApp & app = wxGetApp();

		EL_UINT bandwidth;
		if (app.m_changeBandwidthQueue.Dequeue(bandwidth))
		{
			if (bandwidth != config.currentBandwidth)
			{
				config.currentBandwidth = bandwidth;
				//EL_LOGA_ERROR("bandwidth changed to %u", config.currentBandwidth);
				__SetBandwidth(config.currentBandwidth);
			}
		}

		m_pcPatchThread->_PollRunEvent();

		torrent_status ts = th.status();

		// WEB_SEED ����
		if (config.isWebSeedEnable && !isWebSeedStarted)
		{
			if (ts.state == TORRENT_STATE_DOWNLOADING)
				nIdleTicks++;

			//if (progressStatus.dnBytesPerSec >= (patchInfo.triggerBandwidth))
			//	nIdleTicks=0;
			if (nIdleTicks >= (patchInfo.triggerTime * 10)) 
			{
				th.pause(); // �䷻Ʈ ������ �����Ϸ��� �������Ѿ� �Ѵ�
				BOOST_FOREACH(const std::string& urlSeed, patchInfo.webseedUrls)
				{
					th.add_url_seed(urlSeed);
					//progressStatus.webSeedsCount++;
				}
				th.resume();
				isWebSeedStarted = true;
			}
		}

		MA_LPCWSTR wszState = EL_LTEXT("TORRENT_STATE_UNKNOWN");
		if (ts.state < TORRENT_STATE_MAX)
				wszState = CLocaleManager::sGetActive()->Get(TORRENT_STATE_NAMES[ts.state]);

		if (!isDownloadStarted && (ts.state == TORRENT_STATE_DOWNLOADING)) {
			fBaseProgress = ts.progress;
			isDownloadStarted = true;
		}

		// sub ratio
		if( isDownloadStarted ) {
			m_pcPatchThread->SetUICurrentProgress( (ts.progress - fBaseProgress) / (1.0f - fBaseProgress) );
		} else {
			m_pcPatchThread->SetUICurrentProgress( ts.progress, MA_FALSE );
		}
		m_pcPatchThread->SetUISubState( wszState, (ts.state == TORRENT_STATE_DOWNLOADING) ? MA_TRUE : MA_FALSE  );
		m_pcPatchThread->SetUIMainState( EL_LTEXT("TORRENT_TOTAL_PROGRESS") );
		UpdateProgressPeerAndSpeed();
		Sleep( 150 ); // old 100
	}	
	
	// �õ尡 �Ǿ������� fast resume �����͸� �����
	if (th.is_seed())
	{
		m_pcPatchThread->SetUISubState( EL_LTEXT("TORRENT_SAVING_RESUME_DATA") );
		m_pcPatchThread->UpdateUI();

		th.pause();
		th.save_resume_data();
		
		bool isAlertChecking = EL_TRUE;
		for (EL_UINT i = 0; i != 100 && isAlertChecking; ++i)
		{
			//std::auto_ptr<alert> autoAlertPtr = m_pcSession->pop_alert();
			//alert* alertPtr;

			//while (NULL != (alertPtr = autoAlertPtr.get()))

			std::vector<alert*> autoAlertPtr;
			m_pcSession->pop_alerts(&autoAlertPtr);
			for (alert* alertPtr : autoAlertPtr)
			{
				if (save_resume_data_failed_alert* p = dynamic_cast<save_resume_data_failed_alert*>(alertPtr))
				{
					FILE * fp;					
					if (0 == fopen_s(&fp, "temp\\patch.log", "a+"))
					{
						fprintf_s(fp, "%s\n", p->message().c_str());
						fclose(fp);
					}

					isAlertChecking = EL_FALSE;
					break;
				}

				if (save_resume_data_alert const* p = dynamic_cast<save_resume_data_alert const*>(alertPtr))
				{
					torrent_handle h = p->handle;
					boost::filesystem::ofstream out(fastResumePath, std::ios_base::binary);
					out.unsetf(std::ios_base::skipws);
					bencode(std::ostream_iterator<char>(out), *p->resume_data);

					isAlertChecking = EL_FALSE;
					break;
				}

				//autoAlertPtr = m_pcSession->pop_alert();
				m_pcSession->pop_alerts(&autoAlertPtr);
			}

			if (EL_TRUE == isAlertChecking)
				Sleep(100);
		}

		th.resume();
	}

	return true;
}

bool EL_TorrentPatcher::Seeding(EL_PatchConfig& config)
{
	if (config.seedingDuration > 0) {
		m_pcPatchThread->SetUISubState( EL_LTEXT("TORRENT_PATCH_SEEDING") );
		m_pcPatchThread->UpdateUI();

		EL_UINT minDuration = 10; // 10 ��
		EL_UINT maxDuration = 60 * 60 * 24 * 7; // 7��
		EL_UINT baseTime = time(NULL);
		EL_UINT seedingEndTime = baseTime + EL_MIN(EL_MAX(config.seedingDuration, minDuration), maxDuration);

		while (m_pcPatchThread->_IsAlive()) {
			EL_UINT curTime = time(NULL);

			if( m_pcPatchThread->_PollRunEvent() )
				return false;
			if (curTime >= seedingEndTime)
				break;
			UpdateProgressPeerAndSpeed(); 
			Sleep(50);
		}
	}

	m_pcPatchThread->SetUISubState( EL_LTEXT("TORRENT_SESSION_PAUSING") );
	m_pcPatchThread->UpdateUI();

	m_pcSession->pause();
	return true;
}

bool EL_TorrentPatcher::Begin(EL_PatchConfig& stConfig, CStatus *pcStatus)
{
	MA_SAFE_DELETE(m_pcSession);
	m_pcSession = new session(fingerprint("LT",LIBTORRENT_VERSION_MAJOR,LIBTORRENT_VERSION_MINOR,0,0),session::add_default_plugins);

	m_pcSession->set_alert_mask(alert::error_notification | alert::storage_notification);

	libtorrent::settings_pack settings;
	settings.set_str(settings_pack::user_agent, APP_NAME);
	settings.set_bool(settings_pack::prioritize_partial_pieces, true);
	settings.set_int(settings_pack::min_announce_interval, 30);
	//m_pcSession->set_settings(settings);

	m_pcSession->add_extension(&libtorrent::create_smart_ban_plugin);

	m_pcSession->set_max_half_open_connections(stConfig.maxHalfOpenConnections);
	m_pcSession->set_max_uploads(stConfig.maxUploadsPerSession);
	m_pcSession->set_max_connections(stConfig.maxConnectionsPerSession);

	std::pair<int, int> portRange(stConfig.minPort, stConfig.maxPort);
	error_code ec;
	m_pcSession->listen_on(portRange, ec, nullptr, 0);
	if (ec.value() != 0)
	{
		if( pcStatus )
			pcStatus->AddNRf( CStatus::EA_STATUS_ERROR, EL_LTEXT("TORRENT_SESSION_LISTEN_ERROR"), portRange.first, portRange.second );

		return false;
	}

	// �Ʒ� ��ɵ��� listen_on ���Ŀ� �ϵ��� �����ϰ� ����
	m_pcSession->start_upnp();
	m_pcSession->start_natpmp();
	m_pcSession->start_dht();
	m_pcSession->start_lsd();

	return true;
}

bool EL_TorrentPatcher::Patch(EL_PatchConfig& stConfig, PatchInfos& cPatchInfos, CStatus*pcStatus)
{
	libtorrent::session_proxy	cSessionProxy;

	if( m_pcSession == NULL )
		return MA_FALSE;

	m_pcPatchThread->SetUIMainState( EL_LTEXT("TORRENT_TOTAL_PROGRESS") );
	m_pcPatchThread->SetUISubState( EL_LTEXT("TORRENT_START") );
	m_pcPatchThread->UpdateUI();

	if (!__DownloadPatches(cPatchInfos, stConfig, pcStatus)) {
		cSessionProxy = m_pcSession->abort();
		return false;
	}

	if (m_pcPatchThread->_IsAlive() == EL_TRUE) {
		m_pcPatchThread->SetUISubState( EL_LTEXT("TORRENT_FOREGROUND_PATCH_RUN_GAME") );
		m_pcPatchThread->UpdateUI();
	}

	return true;
}

bool EL_TorrentPatcher::End( void )
{
	if( m_pcSession == NULL )
		return MA_FALSE;
	libtorrent::session_proxy	cSessionProxy;

	//m_pcPatchThread->SetUISubState( EL_LTEXT("TORRENT_SESSION_CLOSING") );
	//m_pcPatchThread->UpdateUI();

	cSessionProxy = m_pcSession->abort();

	m_pcPatchThread->SetUISubState( EL_LTEXT("TORRENT_SESSION_CLOSED") );
	m_pcPatchThread->UpdateUI();

	return true;
}

#endif
