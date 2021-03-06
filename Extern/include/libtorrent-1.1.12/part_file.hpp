/*

Copyright (c) 2012-2018, Arvid Norberg
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

#include "libtorrent-1.1.12/aux_/disable_warnings_push.hpp"

#include <string>
#include <vector>
#include <boost/unordered_map.hpp>
#include <boost/cstdint.hpp>

#include "libtorrent-1.1.12/aux_/disable_warnings_pop.hpp"

#include "libtorrent-1.1.12/config.hpp"
#include "libtorrent-1.1.12/file.hpp"
#include "libtorrent-1.1.12/error_code.hpp"
#include "libtorrent-1.1.12/thread.hpp" // for mutex

namespace libtorrent
{
	struct TORRENT_EXTRA_EXPORT part_file
	{
		// create a part file at 'path', that can hold 'num_pieces' pieces.
		// each piece being 'piece_size' number of bytes
		part_file(std::string const& path, std::string const& name, int num_pieces, int piece_size);
		~part_file();

		int writev(file::iovec_t const* bufs, int num_bufs, int piece, int offset, error_code& ec);
		int readv(file::iovec_t const* bufs, int num_bufs, int piece, int offset, error_code& ec);

		// free the slot the given piece is stored in. We no longer need to store this
		// piece in the part file
		void free_piece(int piece);

		void move_partfile(std::string const& path, error_code& ec);

		void import_file(file& f, boost::int64_t offset, boost::int64_t size, error_code& ec);
		void export_file(file& f, boost::int64_t offset, boost::int64_t size, error_code& ec);

		// flush the metadata
		void flush_metadata(error_code& ec);

	private:

		void open_file(int mode, error_code& ec);
		void flush_metadata_impl(error_code& ec);

		boost::int64_t slot_offset(boost::int64_t const slot) const
		{ return m_header_size + slot * m_piece_size; }

		std::string m_path;
		std::string const m_name;

		// allocate a slot and return the slot index
		int allocate_slot(int piece);

		// this mutex must be held while accessing the data
		// structure. Not while reading or writing from the file though!
		// it's important to support multithreading
		mutex m_mutex;

		// this is a list of unallocated slots in the part file
		// within the m_num_allocated range
		std::vector<int> m_free_slots;

		// this is the number of slots allocated
		int m_num_allocated;

		// the max number of pieces in the torrent this part file is
		// backing
		int const m_max_pieces;

		// number of bytes each piece contains
		int const m_piece_size;

		// this is the size of the part_file header, it is added
		// to offsets when calculating the offset to read and write
		// payload data from
		int const m_header_size;

		// if this is true, the metadata in memory has changed since
		// we last saved or read it from disk. It means that we
		// need to flush the metadata before closing the file
		bool m_dirty_metadata;

		// maps a piece index to the part-file slot it is stored in
		boost::unordered_map<int, int> m_piece_map;

		// this is the file handle to the part file
		// it's allocated on the heap and reference counted, to allow it to be
		// closed and re-opened while other threads are still using it
		boost::shared_ptr<file> m_file;
	};
}

