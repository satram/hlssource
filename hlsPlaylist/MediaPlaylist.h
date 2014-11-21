/*
 * MediaPlaylist.h
 *
 *  Created on: Aug 6, 2014
 *      Author: satram
 */

#ifndef MEDIAPLAYLIST_H_
#define MEDIAPLAYLIST_H_

#include "playlist_common.h"
#include "PlaylistInterface.h"


class MediaPlaylist : public PlaylistInterface
{
	unsigned int sequence_number;
	unsigned int node_count;
public:
	MediaPlaylist();
	virtual ~MediaPlaylist();
};

#endif /* MEDIAPLAYLIST_H_ */
