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

#ifndef qmediaprop_h
#define qmediaprop_h

/** @file qmediaprop.h */

/** @cond NODOC */
#define QUVI_MEDIA_PROPERTY_TYPE_STRING 0x100000
#define QUVI_MEDIA_PROPERTY_TYPE_LONG   0x200000
#define QUVI_MEDIA_PROPERTY_TYPE_DOUBLE 0x300000
#define QUVI_MEDIA_PROPERTY_TYPE_VOID   0x400000
#define QUVI_MEDIA_PROPERTY_TYPE_MASK   0xf00000
/** @endcond */

/** @enum QuviMediaProperty */
typedef enum
{
  /* string */
  QUVI_MEDIA_PROPERTY_THUMBNAIL_URL = QUVI_MEDIA_PROPERTY_TYPE_STRING+1,
  QUVI_MEDIA_PROPERTY_TITLE,
  QUVI_MEDIA_PROPERTY_ID,
  QUVI_MEDIA_STREAM_PROPERTY_VIDEO_ENCODING,
  QUVI_MEDIA_STREAM_PROPERTY_AUDIO_ENCODING,
  QUVI_MEDIA_STREAM_PROPERTY_CONTAINER,
  QUVI_MEDIA_STREAM_PROPERTY_URL,
  QUVI_MEDIA_STREAM_PROPERTY_ID,
  /* double */
  QUVI_MEDIA_PROPERTY_START_TIME_MS =
  ((QUVI_MEDIA_STREAM_PROPERTY_URL - QUVI_MEDIA_PROPERTY_TYPE_STRING)
  + QUVI_MEDIA_PROPERTY_TYPE_DOUBLE + 0x20),
  QUVI_MEDIA_PROPERTY_DURATION_MS,
  QUVI_MEDIA_STREAM_PROPERTY_VIDEO_BITRATE_KBIT_S,
  QUVI_MEDIA_STREAM_PROPERTY_AUDIO_BITRATE_KBIT_S,
  QUVI_MEDIA_STREAM_PROPERTY_VIDEO_HEIGHT,
  QUVI_MEDIA_STREAM_PROPERTY_VIDEO_WIDTH
} QuviMediaProperty;

#endif /* qmediaprop_h */

/* vim: set ts=2 sw=2 tw=72 expandtab: */
