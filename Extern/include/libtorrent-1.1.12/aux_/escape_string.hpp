/*

Copyright (c) 2003-2014, Arvid Norberg
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

#ifndef TORRENT_ESCAPE_STRING_HPP_INCLUDED
#define TORRENT_ESCAPE_STRING_HPP_INCLUDED

#include <string>
#include "libtorrent-1.1.12/config.hpp"
#include "libtorrent-1.1.12/error_code.hpp"

namespace libtorrent
{
	namespace string
	{
		enum flags_t
		{
			// use lower case alphabet used with i2p
			lowercase = 0x1,
			// don't insert padding
			no_padding = 0x2,
			// shortcut used for addresses as sha256 hashes
			i2p = lowercase | no_padding
		};

	}
	TORRENT_EXTRA_EXPORT std::string unescape_string(std::string const& s, error_code& ec);
	// replaces all disallowed URL characters by their %-encoding
	TORRENT_EXTRA_EXPORT std::string escape_string(const char* str, int len);
	// same as escape_string but does not encode '/'
	TORRENT_EXTRA_EXPORT std::string escape_path(const char* str, int len);
	// if the url does not appear to be encoded, and it contains illegal url characters
	// it will be encoded
	TORRENT_EXTRA_EXPORT std::string maybe_url_encode(std::string const& url);

	// convert a file://-URL to a proper path
	TORRENT_EXTRA_EXPORT std::string resolve_file_url(std::string const& url);

	// returns true if the given string (not null terminated) contains
	// characters that would need to be escaped if used in a URL
	TORRENT_EXTRA_EXPORT bool need_encoding(char const* str, int len);

	// encodes a string using the base64 scheme
	TORRENT_EXTRA_EXPORT std::string base64encode(std::string const& s);
	// encodes a string using the base32 scheme
	TORRENT_EXTRA_EXPORT std::string base32encode(std::string const& s, int flags=0);
	TORRENT_EXTRA_EXPORT std::string base32decode(std::string const& s);

	TORRENT_EXTRA_EXPORT std::string url_has_argument(
		std::string const& url, std::string argument, std::string::size_type* out_pos = 0);

	// replaces \ with /
	TORRENT_EXTRA_EXPORT void convert_path_to_posix(std::string& path);
#ifdef TORRENT_WINDOWS
	TORRENT_EXTRA_EXPORT void convert_path_to_windows(std::string& path);
#endif

	TORRENT_EXTRA_EXPORT std::string read_until(char const*& str, char delim
		, char const* end);

#if defined TORRENT_WINDOWS && TORRENT_USE_WSTRING
	TORRENT_EXTRA_EXPORT std::wstring convert_to_wstring(std::string const& s);
	TORRENT_EXTRA_EXPORT std::string convert_from_wstring(std::wstring const& s);
#endif
	
#if TORRENT_USE_ICONV || TORRENT_USE_LOCALE || defined TORRENT_WINDOWS
	TORRENT_EXTRA_EXPORT std::string convert_to_native(std::string const& s);
	TORRENT_EXTRA_EXPORT std::string convert_from_native(std::string const& s);
#else
	// internal
	inline std::string const& convert_to_native(std::string const& s) { return s; }
	// internal
	inline std::string const& convert_from_native(std::string const& s) { return s; }
#endif		
}

#endif // TORRENT_ESCAPE_STRING_HPP_INCLUDED

