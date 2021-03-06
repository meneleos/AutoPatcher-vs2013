/*

Copyright (c) 2009-2018, Arvid Norberg
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in
      the documentation and/or other materials provided with the distribution.
    * Neither the name of the author nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

*/

#ifndef TORRENT_THREAD_HPP_INCLUDED
#define TORRENT_THREAD_HPP_INCLUDED

#include "libtorrent-1.1.12/config.hpp"
#include "libtorrent-1.1.12/assert.hpp"
#include "libtorrent-1.1.12/time.hpp"

#include "libtorrent-1.1.12/aux_/disable_warnings_push.hpp"

#if defined TORRENT_WINDOWS || defined TORRENT_CYGWIN
// asio assumes that the windows error codes are defined already
#include <winsock2.h>
#endif

#if defined TORRENT_BEOS
#include <kernel/OS.h>
#endif

#include <memory> // for auto_ptr required by asio

#include <boost/asio/detail/thread.hpp>
#include <boost/asio/detail/mutex.hpp>
#include <boost/asio/detail/event.hpp>
#include <boost/asio/detail/scoped_lock.hpp>
#include <boost/cstdint.hpp>

#include "libtorrent-1.1.12/aux_/disable_warnings_pop.hpp"

namespace libtorrent
{
	typedef boost::asio::detail::thread thread;
	typedef boost::asio::detail::mutex mutex;
	typedef boost::asio::detail::event event;

	// internal
	void sleep(int milliseconds);

	struct TORRENT_EXTRA_EXPORT recursive_mutex;

	struct TORRENT_EXTRA_EXPORT condition_variable
	{
		condition_variable();
		~condition_variable();
		void wait(mutex::scoped_lock& l);
		void wait_for(mutex::scoped_lock& l, time_duration);
		void wait(boost::asio::detail::scoped_lock<recursive_mutex>& l);
		void wait_for(boost::asio::detail::scoped_lock<recursive_mutex>&, time_duration);
		void notify_all();
		void notify();
	private:

		template <typename LockGuard>
		void wait_impl(LockGuard& l);
		template <typename LockGuard>
		void wait_for_impl(LockGuard& l, time_duration rel_time);

#ifdef BOOST_HAS_PTHREADS
		pthread_cond_t m_cond;
#elif defined TORRENT_WINDOWS || defined TORRENT_CYGWIN
		HANDLE m_sem;
		mutex m_mutex;
		int m_num_waiters;
#elif defined TORRENT_BEOS
		sem_id m_sem;
		mutex m_mutex;
		int m_num_waiters;
#else
#error not implemented
#endif
	};

#if defined TORRENT_WINDOWS || defined TORRENT_CYGWIN
	typedef DWORD thread_id_t;
#elif defined TORRENT_BEOS
	typedef thread_id thread_id_t;
#endif

	// internal
	struct TORRENT_EXTRA_EXPORT recursive_mutex
	{
		typedef boost::asio::detail::scoped_lock<recursive_mutex> scoped_lock;

		recursive_mutex();
		~recursive_mutex();

		void lock();
		void unlock();

	private:
		recursive_mutex(recursive_mutex const&);
		recursive_mutex& operator=(recursive_mutex const&);

#ifdef BOOST_HAS_PTHREADS
		::pthread_mutex_t m_mutex;
#else
		mutex m_mutex;
		condition_variable m_cond;
		thread_id_t m_owner;
		int m_count;
#endif
	};
}

#endif

