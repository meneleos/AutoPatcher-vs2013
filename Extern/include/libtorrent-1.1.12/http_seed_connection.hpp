/*

Copyright (c) 2008-2018, Arvid Norberg
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

#ifndef TORRENT_HTTP_SEED_CONNECTION_HPP_INCLUDED
#define TORRENT_HTTP_SEED_CONNECTION_HPP_INCLUDED

#include <ctime>
#include <algorithm>
#include <deque>
#include <string>

#include "libtorrent-1.1.12/debug.hpp"

#include "libtorrent-1.1.12/aux_/disable_warnings_push.hpp"

#include <boost/smart_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <boost/array.hpp>
#include <boost/optional.hpp>
#include <boost/cstdint.hpp>

#include "libtorrent-1.1.12/aux_/disable_warnings_pop.hpp"

#include "libtorrent-1.1.12/config.hpp"
#include "libtorrent-1.1.12/web_connection_base.hpp"
#include "libtorrent-1.1.12/disk_buffer_holder.hpp"
#include "libtorrent-1.1.12/torrent.hpp"
#include "libtorrent-1.1.12/piece_block_progress.hpp"
#include "libtorrent-1.1.12/http_parser.hpp"

namespace libtorrent
{
	class torrent;
	struct peer_request;

	namespace detail
	{
		struct session_impl;
	}

	class TORRENT_EXTRA_EXPORT http_seed_connection
		: public web_connection_base
	{
	friend class invariant_access;
	public:

		// this is the constructor where the we are the active part.
		// The peer_conenction should handshake and verify that the
		// other end has the correct id
		http_seed_connection(peer_connection_args const& pack
			, web_seed_t& web);

		virtual int type() const TORRENT_OVERRIDE
		{ return peer_connection::http_seed_connection; }

		// called from the main loop when this connection has any
		// work to do.
		virtual void on_receive(error_code const& error
			, std::size_t bytes_transferred) TORRENT_OVERRIDE;

		std::string const& url() const TORRENT_OVERRIDE { return m_url; }

		virtual void get_specific_peer_info(peer_info& p) const TORRENT_OVERRIDE;
		virtual void disconnect(error_code const& ec, operation_t op, int error = 0) TORRENT_OVERRIDE;

		virtual void write_request(peer_request const& r) TORRENT_OVERRIDE;

	private:

		// returns the block currently being
		// downloaded. And the progress of that
		// block. If the peer isn't downloading
		// a piece for the moment, the boost::optional
		// will be invalid.
		boost::optional<piece_block_progress> downloading_piece_progress() const TORRENT_OVERRIDE;

		// this is const since it's used as a key in the web seed list in the torrent
		// if it's changed referencing back into that list will fail
		const std::string m_url;

		web_seed_t* m_web;

		// the number of bytes left to receive of the response we're
		// currently parsing
		boost::int64_t m_response_left;

		// this is the offset inside the current receive
		// buffer where the next chunk header will be.
		// this is updated for each chunk header that's
		// parsed. It does not necessarily point to a valid
		// offset in the receive buffer, if we haven't received
		// it yet. This offset never includes the HTTP header
		boost::int64_t m_chunk_pos;

		// this is the number of bytes we've already received
		// from the next chunk header we're waiting for
		int m_partial_chunk_header;
	};
}

#endif // TORRENT_WEB_PEER_CONNECTION_HPP_INCLUDED

