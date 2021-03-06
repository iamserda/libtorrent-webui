/*

Copyright (c) 2013, Arvid Norberg
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

#ifndef TORRENT_PAM_AUTH_HPP
#define TORRENT_PAM_AUTH_HPP

#include "auth_interface.hpp"
#include <string>
#include <map>

namespace libtorrent
{
	struct pam_auth : auth_interface
	{
		pam_auth(std::string service_name);
		~pam_auth();

		// these are the permissions the user receives
		// if successfully authenticated
		void set_permissions(permissions_interface* perms) { m_perms = perms; }

		void set_user_permissions(std::string username, permissions_interface* p)
		{ m_users[username] = p; }

		permissions_interface const* find_user(std::string username, std::string password) const;

	private:

		permissions_interface* m_perms;
		std::string m_service_name;
		// if some users have different permissions than the default
		// users, they have an entry in this map. Users not in this
		// map that successfully authenticate will still get the
		// default permissions in m_perms (which defaults to full permissions)
		std::map<std::string, permissions_interface*> m_users;
	};
}

#endif

