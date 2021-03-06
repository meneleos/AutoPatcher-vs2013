/*

Copyright (c) 2013-2018, Arvid Norberg
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

#ifndef TORRENT_RESOLVER_HPP_INCLUDE
#define TORRENT_RESOLVER_HPP_INCLUDE

#include "libtorrent-1.1.12/aux_/disable_warnings_push.hpp"

#include <boost/asio/ip/tcp.hpp>
#include <boost/function.hpp>
#include <boost/unordered_map.hpp>
#include <vector>

#include "libtorrent-1.1.12/aux_/disable_warnings_pop.hpp"

#include "libtorrent-1.1.12/error_code.hpp"
#include "libtorrent-1.1.12/io_service.hpp"
#include "libtorrent-1.1.12/socket.hpp"
#include "libtorrent-1.1.12/resolver_interface.hpp"
#include "libtorrent-1.1.12/address.hpp"
#include "libtorrent-1.1.12/time.hpp"

namespace libtorrent
{

struct TORRENT_EXTRA_EXPORT resolver TORRENT_FINAL : resolver_interface
{
	resolver(io_service& ios);

	virtual void async_resolve(std::string const& host, int flags
		, callback_t const& h) TORRENT_OVERRIDE;

	virtual void abort() TORRENT_OVERRIDE;

private:

	void on_lookup(error_code const& ec, tcp::resolver::iterator i
		, resolver_interface::callback_t h, std::string hostname);

	struct dns_cache_entry
	{
		time_point last_seen;
		std::vector<address> addresses;
	};

	typedef boost::unordered_map<std::string, dns_cache_entry> cache_t;
	cache_t m_cache;
	io_service& m_ios;

	// all lookups in this resolver are aborted on shutdown.
	tcp::resolver m_resolver;

	// lookups in this resolver are not aborted on shutdown
	tcp::resolver m_critical_resolver;

	// max number of cached entries
	int m_max_size;

	// timeout of cache entries
	time_duration m_timeout;
};

}

#endif

