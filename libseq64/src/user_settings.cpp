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

#include "globals.h"                    /* to support legacy variables */

/**
 * \file          user_settings.cpp
 *
 *  This module declares/defines just some of the global (gasp!) variables
 *  in this application.
 *
 * \library       sequencer64 application
 * \author        Seq24 team; modifications by Chris Ahlstrom
 * \date          2015-09-23
 * \updates       2015-09-23
 * \license       GNU GPLv2 or above
 *
 *  Note that this module also sets the legacy global variables, so that
 *  they can be used by modules that have not yet been cleaned up.
 */

#include "user_settings.hpp"

/**
 *  Default constructor.
 */

user_settings::user_settings ()
 :
    m_mainwnd_rows      (0),
    m_mainwnd_cols      (0),
    m_seqs_in_set       (0),
    m_gmute_tracks      (0),
    m_max_sets          (0),
    m_total_seqs        (0),
    m_max_sequence      (0),
    m_text_x            (0),
    m_text_y            (0),
    m_seqchars_x        (0),
    m_seqchars_y        (0),
    m_seqarea_x         (0),
    m_seqarea_y         (0),
    m_seqarea_seq_x     (0),
    m_seqarea_seq_y     (0),
    m_mainwid_border    (0),
    m_mainwid_spacing   (0),
    m_control_height    (0),
    m_mainwid_x         (0),
    m_mainwid_y         (0)
{
    // Empty body
}

/**
 *  Copy constructor.
 */

user_settings::user_settings (const user_settings & rhs)
 :
    m_mainwnd_rows      (rhs.m_mainwnd_rows),
    m_mainwnd_cols      (rhs.m_mainwnd_cols),
    m_seqs_in_set       (rhs.m_seqs_in_set),
    m_gmute_tracks      (rhs.m_gmute_tracks),
    m_max_sets          (rhs.m_max_sets),
    m_total_seqs        (rhs.m_total_seqs),
    m_max_sequence      (rhs.m_max_sequence),
    m_text_x            (rhs.m_text_x),
    m_text_y            (rhs.m_text_y),
    m_seqchars_x        (rhs.m_seqchars_x),
    m_seqchars_y        (rhs.m_seqchars_y),
    m_seqarea_x         (rhs.m_seqarea_x),
    m_seqarea_y         (rhs.m_seqarea_y),
    m_seqarea_seq_x     (rhs.m_seqarea_seq_x),
    m_seqarea_seq_y     (rhs.m_seqarea_seq_y),
    m_mainwid_border    (rhs.m_mainwid_border),
    m_mainwid_spacing   (rhs.m_mainwid_spacing),
    m_control_height    (rhs.m_control_height),
    m_mainwid_x         (rhs.m_mainwid_x),
    m_mainwid_y         (rhs.m_mainwid_y)
{
    // Empty body
}

/**
 *  Principal assignment operator.
 */

user_settings &
user_settings::operator = (const user_settings & rhs)
{
    if (this != &rhs)
    {
        m_mainwnd_rows      = m_mainwnd_rows;
        m_mainwnd_cols      = m_mainwnd_cols;
        m_seqs_in_set       = m_seqs_in_set;
        m_gmute_tracks      = m_gmute_tracks;
        m_max_sets          = m_max_sets;
        m_total_seqs        = m_total_seqs;
        m_max_sequence      = m_max_sequence;
        m_text_x            = m_text_x;
        m_text_y            = m_text_y;
        m_seqchars_x        = m_seqchars_x;
        m_seqchars_y        = m_seqchars_y;
        m_seqarea_x         = m_seqarea_x;
        m_seqarea_y         = m_seqarea_y;
        m_seqarea_seq_x     = m_seqarea_seq_x;
        m_seqarea_seq_y     = m_seqarea_seq_y;
        m_mainwid_border    = m_mainwid_border;
        m_mainwid_spacing   = m_mainwid_spacing;
        m_control_height    = m_control_height;
        m_mainwid_x         = m_mainwid_x;
        m_mainwid_y         = m_mainwid_y;
    }
    return *this;
}

/**
 *  Sets the default values.
 */

void
user_settings::set_defaults ()
{
    m_mainwnd_rows = 4;                 // range: 4 to 8
    m_mainwnd_cols = 8;                 // range: 8 to 10
    m_max_sets = 32;                    // range: 32 to 64
    m_text_x =  6;                      // range: 6 to 6
    m_text_y = 12;                      // range: 12 to 12
    m_seqchars_x = 15;                  // range: 15 to 15
    m_seqchars_y =  5;                  // range: 5 to 5
    m_mainwid_border = 0;               // range: 0 to 3, try 2 or 3
    m_mainwid_spacing = 2;              // range: 2 to 6, try 4 or 6
    m_control_height = 0;               // range: 0 to 4
    normalize();
}

/**
 *  Calculate the derived values from the already-set values.
 */

void
user_settings::normalize ()
{
    m_seqs_in_set = m_mainwnd_rows * m_mainwnd_cols;
    m_gmute_tracks = m_seqs_in_set * m_seqs_in_set;
    m_total_seqs = m_seqs_in_set * m_max_sets;
    m_max_sequence = m_seqs_in_set * m_max_sets;
    m_seqarea_x = m_text_x * m_seqchars_x;
    m_seqarea_y = m_text_y * m_seqchars_y;
    m_seqarea_seq_x = m_text_x * 13;
    m_seqarea_seq_y = m_text_y * 2;
    m_mainwid_x =
    (
        (m_seqarea_x + m_mainwid_spacing) * m_mainwnd_cols -
            m_mainwid_spacing + m_mainwid_border * 2
    );
    m_mainwid_y =
    (
        (m_seqarea_y + m_mainwid_spacing) * m_mainwnd_rows +
             m_control_height + m_mainwid_border * 2
    );
}

/**
 *  Copies the current values of the member variables into their
 *  corresponding global variables.
 */

void
user_settings::globalize_settings ()
{
    // TO DO?
}

/**
 * \setter m_mainwnd_rows
 *      This value is not modified unless the value parameter is
 *      between 4 and 8, inclusive.  The default value is 4.
 *      Dependent values are recalculated after the assignment.
 */

void
user_settings::mainwnd_rows (int value)
{
    if (value >= 4 && value <= 8)
    {
        m_mainwnd_rows = value;
        normalize();
    }
}

/**
 * \setter m_mainwnd_cols
 *      This value is not modified unless the value parameter is
 *      between 8 and 10, inclusive.  The default value is 8.
 *      Dependent values are recalculated after the assignment.
 */

void
user_settings::mainwnd_cols (int value)
{
    if (value >= 8 && value <= 10)
    {
        m_mainwnd_cols = value;
        normalize();
    }
}

/**
 * \setter m_seqs_in_set
 *
 * \warning
 *      This is a dependent value at present, and changing it is
 *      experimental.
 *
void
user_settings::seqs_in_set (int value)
{
    m_seqs_in_set = value;
}
 *
 */

/**
 * \setter m_gmute_tracks
 *
 * \warning
 *      This is a dependent value at present, and changing it is
 *      experimental.
 *
void
user_settings::gmute_tracks (int value)
{
    m_gmute_tracks = value;
}
 *
 */

/**
 * \setter m_max_sets
 *      This value is not modified unless the value parameter is
 *      between 32 and 64, inclusive.  The default value is 32.
 *      Dependent values are recalculated after the assignment.
 */

void
user_settings::max_sets (int value)
{
    if (value >= 32 && value <= 64)
    {
        m_max_sets = value;
        normalize();
    }
}

/**
 * \setter m_max_sequence
 *
 * \warning
 *      This is a dependent value at present, and changing it is
 *      experimental.
 *
void
user_settings::max_sequence (int value)
{
    m_max_sequence = value;
}
 *
 */

/**
 * \setter m_text_x
 *      This value is not modified unless the value parameter is
 *      between 6 and 6, inclusive.  The default value is 6.
 *      Dependent values are recalculated after the assignment.
 *      This value is currently restricted, until we can code up a bigger
 *      font.
 */

void
user_settings::text_x (int value)
{
    if (value == 6)
    {
        m_text_x = value;
        normalize();
    }
}

/**
 * \setter m_text_y
 *      This value is not modified unless the value parameter is
 *      between 12 and 12, inclusive.  The default value is 12.
 *      Dependent values are recalculated after the assignment.
 *      This value is currently restricted, until we can code up a bigger
 *      font.
 */

void
user_settings::text_y (int value)
{
    if (value == 12)
    {
        m_text_y = value;
        normalize();
    }
}

/**
 * \setter m_seqchars_x
 *      This affects the size or crampiness of a pattern slot, and for now
 *      we will hardwire it to 15.
 */

void
user_settings::seqchars_x (int value)
{
    if (value == 15)
    {
        m_seqchars_x = value;
        normalize();
    }
}

/**
 * \setter m_seqchars_y
 *      This affects the size or crampiness of a pattern slot, and for now
 *      we will hardwire it to 5.
 */

void
user_settings::seqchars_y (int value)
{
    if (value == 5)
    {
        m_seqchars_y = value;
        normalize();
    }
}

/**
 * \setter m_seqarea_x
 */

void
user_settings::seqarea_x (int value)
{
    m_seqarea_x = value;
}

/**
 * \setter m_seqarea_y
 */

void
user_settings::seqarea_y (int value)
{
    m_seqarea_y = value;
}

/**
 * \setter m_seqarea_seq_x
 */

void
user_settings::seqarea_seq_x (int value)
{
    m_seqarea_seq_x = value;
}

/**
 * \setter m_seqarea_seq_y
 */

void
user_settings::seqarea_seq_y (int value)
{
    m_seqarea_seq_y = value;
}

/**
 * \setter m_mainwid_border
 *      This value is not modified unless the value parameter is
 *      between 0 and 3, inclusive.  The default value is 0.
 *      Dependent values are recalculated after the assignment.
 */

void
user_settings::mainwid_border (int value)
{
    if (value >= 0 && value <= 3)
    {
        m_mainwid_border = value;
        normalize();
    }
}

/**
 * \setter m_mainwid_spacing
 *      This value is not modified unless the value parameter is
 *      between 2 and 6, inclusive.  The default value is 2.
 *      Dependent values are recalculated after the assignment.
 */

void
user_settings::mainwid_spacing (int value)
{
    if (value >= 2 && value <= 6)
    {
        m_mainwid_spacing = value;
        normalize();
    }
}

/**
 * \setter m_control_height
 *      This value is not modified unless the value parameter is
 *      between 0 and 4, inclusive.  The default value is 0.
 *      Dependent values are recalculated after the assignment.
 */

void
user_settings::control_height (int value)
{
    if (value >= 0 && value <= 4)
    {
        m_control_height = value;
        normalize();
    }
}

/*
 * \setter m_mainwid_x
 *
 * \warning
 *      This is a dependent value at present, and changing it is
 *      experimental.
 *
void
user_settings::mainwid_x (int value)
{
    m_mainwid_x = value;
}
 *
 */

/**
 * \setter m_mainwid_y
 *
 * \warning
 *      This is a dependent value at present, and changing it is
 *      experimental.
 *
void
user_settings::mainwid_y (int value)
{
    m_mainwid_y = value;
}
 *
 */

#if EXPOSE_THESE

user_midi_bus_t   global_user_midi_bus_definitions[c_max_busses];
user_instrument_t global_user_instrument_definitions[c_max_instruments];

/**
 *  Prepare global MIDI definitions.  Why are only 16 instruments
 *  supported in the first for-loop, but 64 (see globals.h) in the
 *  second for-loop?  Well, actually the 16 applies to the number of MIDI
 *  busses, not instruments.
 */

void
user_settings::prepare_midi_defs ()
{
    for (int i = 0; i < c_max_busses; i++)
    {
        for (int j = 0; j < 16; j++)
            global_user_midi_bus_definitions[i].instrument[j] = -1;
    }
    for (int i = 0; i < c_max_instruments; i++)
    {
        for (int j = 0; j < MIDI_COUNT_MAX; j++)
            global_user_instrument_definitions[i].controllers_active[j] = false;
    }
}

#endif

/*
* user_settings.cpp
*
* vim: sw=4 ts=4 wm=8 et ft=cpp
*/
