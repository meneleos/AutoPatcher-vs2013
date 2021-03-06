/*

Copyright (c) 2006, MassaRoddel
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

#ifndef TORRENT_UT_PEX_EXTENSION_HPP_INCLUDED
#define TORRENT_UT_PEX_EXTENSION_HPP_INCLUDED

#include "libtorrent-1.1.12/config.hpp"

#ifndef TORRENT_DISABLE_EXTENSIONS

#include "libtorrent-1.1.12/socket.hpp" // for endpoint

#include "libtorrent-1.1.12/aux_/disable_warnings_push.hpp"

#include <boost/shared_ptr.hpp>

#include "libtorrent-1.1.12/aux_/disable_warnings_pop.hpp"

namespace libtorrent
{
	struct torrent_plugin;
	struct peer_plugin;
	struct torrent_handle;

	// constructor function for the ut_pex extension. The ut_pex
	// extension allows peers to gossip about their connections, allowing
	// the swarm stay well connected and peers aware of more peers in the
	// swarm. This extension is enabled by default unless explicitly disabled in
	// the session constructor.
	// 
	// This can either be passed in the add_torrent_params::extensions field, or
	// via torrent_handle::add_extension().
	TORRENT_EXPORT boost::shared_ptr<torrent_plugin> create_ut_pex_plugin(torrent_handle const&, void*);

	bool was_introduced_by(peer_plugin const* pp, tcp::endpoint const& ep);
}

#endif // TORRENT_DISABLE_EXTENSIONS

#endif // TORRENT_UT_PEX_EXTENSION_HPP_INCLUDED
