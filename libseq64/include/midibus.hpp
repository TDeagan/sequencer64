#ifndef SEQ64_MIDIBUS_HPP
#define SEQ64_MIDIBUS_HPP

/*
 *  This file is part of seq24/sequencer64.
 *
 *  seq24 is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  seq24 is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with seq24; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/**
 * \file          midibus.hpp
 *
 *  This module declares the right version of the midibus header for the
 *  current API.
 *
 * \library       sequencer64 application
 * \author        Seq24 team; modifications by Chris Ahlstrom
 * \date          2016-11-28
 * \updates       2016-11-28
 * \license       GNU GPLv2 or above
 *
 */

#include "seq64-config.h"

#if defined SEQ64_ALSAMIDI_SUPPORT
#include "midibus_am.hpp"               /* seq64::midibus for ALSA    */
#elif defined SEQ64_RTMIDI_SUPPORT
#include "midibus_rm.hpp"               /* seq64::midibus for RtMidi  */
#elif defined SEQ64_PORTMIDI_SUPPORT
#include "midibus_pm.hpp"               /* seq64::midibus, PortMidi   */
#endif

#endif      // SEQ64_MIDIBUS_HPP

/*
 * midibus.hpp
 *
 * vim: sw=4 ts=4 wm=4 et ft=cpp
 */

