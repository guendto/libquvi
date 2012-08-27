/* libquvi
 * Copyright (C) 2012  Toni Gundogdu <legatvs@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301  USA
 */

#ifndef l_def_h
#define l_def_h

#define USERDATA_QUVI_T   "_quvi_t"

/* Common to all scripts */

#define GS_VERBOSE  "verbose"   /* Verbose flag */

/* Media script: Media properties */

#define MS_START_TIME_MS    "start_time_ms" /* Start streaming at */
#define MS_DURATION_MS      "duration_ms"   /* Media duration in ms */
#define MS_CATEGORIES       "categories"    /* Protocol categories */
#define MS_INPUT_URL        "input_url"     /* App req. URL */
#define MS_THUMB_URL        "thumb_url"     /* Image thumbnail URL */
#define MS_GOTO_URL         "goto_url"      /* Redirect to URL */
#define MS_ACCEPTS          "accepts"       /* Script accepts URL */
#define MS_DOMAINS          "domains"       /* Accepted domains */
#define MS_TITLE            "title"         /* Media title */
#define MS_ID               "id"            /* Media ID */
#define MS_STREAMS          "streams"       /* Media streams */

/* Media script: stream properties */

#define MSS_VIDEO                 "video"
#define MSS_VIDEO_BITRATE_KBIT_S  "bitrate_kbit_s"
#define MSS_VIDEO_ENCODING        "encoding"
#define MSS_VIDEO_HEIGHT          "height"
#define MSS_VIDEO_WIDTH           "width"

#define MSS_AUDIO                 "audio"
#define MSS_AUDIO_BITRATE_KBIT_S  MSS_VIDEO_BITRATE_KBIT_S
#define MSS_AUDIO_ENCODING        MSS_VIDEO_ENCODING

#define MSS_FLAGS                 "flags"
#define MSS_FLAGS_BEST            "best"

#define MSS_CONTAINER             "container"
#define MSS_URL                   "url"
#define MSS_ID                    "id"

#define MS_EMPTY         ""

/* Playlist script */

#define PS_INPUT_URL  "input_url" /* App req. URL */
#define PS_THUMB_URL  "thumb_url" /* Playlist thumbnail URL */
#define PS_ACCEPTS    "accepts"   /* Script accepts URL */
#define PS_DOMAINS    "domains"   /* Accepted domains */
#define PS_TITLE      "title"     /* Title */
#define PS_MEDIA      "media"     /* Found media */
#define PS_ID         "id"        /* Playlist ID */

/* Playlist script: Media properties */

#define PSM_DURATION_MS "duration_ms" /* Duration in ms */
#define PSM_TITLE       "title"       /* Title */
#define PSM_URL         "url"         /* URL */

/* Scan script */

#define SS_INPUT_URL  "input_url" /* App req. URL */
#define SS_MEDIA_URL  "media_url" /* Array of found media URLs */
#define SS_CONTENT    "content"   /* Content to scan */

/* Utility script */

#define US_INPUT_URL "input_url" /* App req. URL */

/* Lua indexes.
 *
 * Used as 'key' (at index -2) and 'value' (at index -1). Many of
 * the libquvi functions that call lua_next use these indexes. This is
 * similar to (in Lua):
 *   for k,v in pairs(t) do ... end
 */

enum {LI_VALUE = -1, LI_KEY = -2};

#endif /* l_def_h */

/* vim: set ts=2 sw=2 tw=72 expandtab: */
