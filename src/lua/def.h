/* libquvi
 * Copyright (C) 2012  Toni Gundogdu <legatvs@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#ifndef l_def_h
#define l_def_h

#define USERDATA_QUVI_T   "_quvi_t"

/* Common to all scripts */

#define GS_VERBOSE  "verbose"   /* Verbose flag */

/* Media script */

#define MS_DOMAIN_PATTERN   "domain"        /* Domain (lua) pattern */
#define MS_AVAIL_FORMATS    "avail_formats" /* Available formats to URL */
#define MS_START_TIME_MS    "start_time_ms" /* Start streaming at */
#define MS_DURATION_MS      "duration_ms"   /* Media duration in ms */
#define MS_CATEGORIES       "categories"    /* Protocol categories */
#define MS_STREAM_URL       "stream_url"    /* Media stream URL */
#define MS_REQ_FORMAT       "req_format"    /* User requested format */
#define MS_INPUT_URL        "input_url"     /* App req. URL */
#define MS_THUMB_URL        "thumb_url"     /* Image thumbnail URL */
#define MS_GOTO_URL         "goto_url"      /* Redirect to URL */
#define MS_ACCEPTS          "accepts"       /* Script accepts URL */
#define MS_TITLE            "title"         /* Media title */
#define MS_SITE             "site"          /* Site (domain) string */
#define MS_ID               "id"            /* Media ID */

#define MS_EMPTY         ""

/* Playlist script */

#define PS_DOMAIN_PATTERN "domain"    /* Domain (lua) pattern */
#define PS_INPUT_URL      "input_url" /* App req. URL */
#define PS_MEDIA_URL      "media_url" /* Array of found media URLs */
#define PS_ACCEPTS        "accepts"   /* Script accepts URL */
#define PS_ID             "id"        /* Playlist ID */

/* Scan script */

#define SS_INPUT_URL  "input_url" /* App req. URL */
#define SS_MEDIA_URL  "media_url" /* Array of found media URLs */
#define SS_CONTENT    "content"   /* Content to scan */

#endif /* l_def_h */

/* vim: set ts=2 sw=2 tw=72 expandtab: */
