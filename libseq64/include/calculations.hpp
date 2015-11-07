#ifndef SEQ64_CALCULATIONS_H
#define SEQ64_CALCULATIONS_H

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
 * \file          calculations.h
 *
 *  This module declares/defines some common calculations needed by the
 *  application.
 *
 * \library       sequencer64 application
 * \author        Seq24 team; modifications by Chris Ahlstrom
 * \date          2015-11-07
 * \updates       2015-11-07
 * \license       GNU GPLv2 or above
 *
 *  These items were moved from the globals.h module so that only the modules
 *  that need them need to include them.  Also included are some minor
 *  "utility" functions.
 *
 *  Many of the functions are defined in this module, as inline code.
 */

#include <string>

#include "easy_macros.h"                /* with platform_macros.h, too  */

/**
 *  The MIDI beat clock (also known as "MIDI timing clock" or "MIDI clock") is
 *  a clock signal that is broadcast via MIDI to ensure that several
 *  MIDI-enabled devices or sequencers stay in synchronization.  Do not
 *  confuse it with "MIDI timecode".
 *
 *  The standard MIDI beat clock ticks every 24 times every quarter note
 *  (crotchet).
 *
 *  Unlike MIDI timecode, the MIDI beat clock is tempo-dependent. Clock events
 *  are sent at a rate of 24 ppqn (pulses per quarter note). Those pulses are
 *  used to maintain a synchronized tempo for synthesizers that have
 *  BPM-dependent voices and also for arpeggiator synchronization.
 *
 *  The following macro represents the MIDI clock rate in
 *  pulses-per-quarter-note.
 */

#define MIDI_CLOCK_IN_PPQN               24

/*
 * Global functions in the seq64 namespace for MIDI timing calculations.
 */

namespace seq64
{

extern std::string shorten_file_spec (const std::string & fpath, int leng);

/**
 *  This function calculates the effective beats-per-minute based on the value
 *  of a Tempo meta-event.  The tempo event's numeric value is given in 3
 *  bytes, and is in units of microseconds-per-quarter-note (us/qn).
 *
 * \param tempo
 *      The value of the Tempo meta-event, in units of us/qn.
 *
 * \return
 *      Returns the beats per minute.  If the tempo value is too small,
 *      then this function will crash.  :-D
 */

inline double beats_per_minute_from_tempo (double tempo)
{
    return 60000000.0 / tempo;
}

/**
 *  This function is the inverse of beats_per_minute_from_tempo().
 *
 * \param bpm
 *      The value of beats-per-minute.
 *
 * \return
 *      Returns the tempo in qn/us.  If the bpm value is too small,
 *      then this function will crash.  :-D
 */

inline double tempo_from_beats_per_minute (double bpm)
{
    return 60000000.0 / bpm;
}

/**
 *  Calculates pulse-length from the BPM (beats-per-minute) and PPQN
 *  (pulses-per-quarter-note) values.  The formula for the pulse-length in
 *  seconds is:
 *
\verbatim
                 60
        P = ------------
             BPM * PPQN
\endverbatim
 *
 * \param bpm
 *      Provides the beats-per-minute value.  No sanity check is made.
 *
 * \param ppqn
 *      Provides the pulses-per-quarter-note value.  No sanity check is
 *      made.
 *
 * \return
 *      Returns the pulse length in microseconds.  If either parameter is
 *      invalid, then this function will crash. :-D
 */

inline double pulse_length_us (int bpm, int ppqn)
{
    return 60000000.0 / double(bpm * ppqn);
}

/**
 *  Converts delta time in microseconds to ticks.  This function is the
 *  inverse of ticks_to_delta_time_us().
 *
 *  Please note that terms "ticks" and "pulses" are equivalent, and refer to
 *  the "pulses" in "pulses per quarter note".
 *
 * \param delta_us
 *      The number of microseconds in the delta time.
 *
 * \param bpm
 *      Provides the beats-per-minute value, otherwise known as the "tempo".
 *
 * \param ppqn
 *      Provides the pulses-per-quarter-note value, otherwise known as the
 *      "division".
 *
 * \return
 *      Returns the tick value.
 */

inline double delta_time_us_to_ticks (long delta_us, int bpm, int ppqn)
{
    return double(bpm) * double(ppqn) * (double(delta_us) / 60000000.0);
}

/**
 *  Converts the time in ticks ("clocks") to delta time in microseconds.
 *  The inverse of delta_time_us_to_ticks().
 *
 *  Please note that terms "ticks" and "pulses" are equivalent, and refer to
 *  the "pulses" in "pulses per quarter note".
 *
 * \param delta_ticks
 *      The number of ticks or "clocks".
 *
 * \param bpm
 *      Provides the beats-per-minute value, otherwise known as the "tempo".
 *
 * \param ppqn
 *      Provides the pulses-per-quarter-note value, otherwise known as the
 *      "division".
 *
 * \return
 *      Returns the time value in microseconds.
 */

inline double ticks_to_delta_time_us (long delta_ticks, int bpm, int ppqn)
{
    return 60000000.0 * double(delta_ticks) / (double(bpm) * double(ppqn));
}

/**
 *  Calculates the duration of a clock tick based on PPQN and BPM settings.
 *
 * \deprecated
 *      This is a somewhat bogus calculation used only for "statistical"
 *      output in the old perform module.  Name changed to reflect this
 *      unfortunate fact.  Use pulse_length_us() instead.
 *
\verbatim
        us =           60000000 ppqn
             ---------------------------------
              MIDI_CLOCK_IN_PPQN * bpm * ppqn
\endverbatim
 *
 *  MIDI_CLOCK_IN_PPQN is 24.
 *
 * \param bpm
 *      Provides the beats-per-minute value.  No sanity check is made.
 *
 * \param ppqn
 *      Provides the pulses-per-quarter-note value.  No sanity check is
 *      made.
 *
 * \return
 *      Returns the clock tick duration in microseconds.  If either parameter
 *      is invalid, this will crash.  Who wants to waste time on value checks
 *      here? :-D
 */

inline double clock_tick_duration_bogus (int bpm, int ppqn)
{
    return (ppqn / MIDI_CLOCK_IN_PPQN) * 60000000.0 / (bpm * ppqn);
}

/**
 *  A simple calculation to convert PPQN to MIDI clock ticks.
 *
 * \param ppqn
 *      The number of pulses per quarter note.  For example, the default value
 *      for Seq24 is 192.
 *
 * \return
 *      The integer value of ppqn / 24 [MIDI_CLOCK_IN_PPQN] is returned.
 */

inline int clock_ticks_from_ppqn (int ppqn)
{
    return ppqn / MIDI_CLOCK_IN_PPQN;
}

/**
 *  A simple calculation to convert PPQN to MIDI clock ticks.  The same as
 *  clock_ticks_from_ppqn(), but returned as a double float.
 *
 * \param ppqn
 *      The number of pulses per quarter note.
 *
 * \return
 *      The double value of ppqn / 24 [MIDI_CLOCK_IN_PPQN]_is returned.
 */

inline double double_ticks_from_ppqn (int ppqn)
{
    return double(ppqn) / double(MIDI_CLOCK_IN_PPQN);
}

/**
 *  Calculates the length of a number of measures, in ticks.
 *  This function is called in seqedit::apply_length(), when the user
 *  selects a sequence length in measures.  That function calculates the
 *  length in ticks:
 *
\verbatim
    L = M x B x 4 x P / W
        L == length (ticks or pulses)
        M == number of measures
        B == beats per measure
        P == pulses per quarter-note
        W == beat width in beats per measure
\endverbatim
 *
 *  For our "b4uacuse" MIDI file, M can be about 100 measures, B is 4,
 *  P can be 192 (but we want to support higher values), and W is 4.
 *  So L = 100 * 4 * 4 * 192 / 4 = 76800 ticks.  Seems small.
 *
 * \param bpm
 *      The B value in the equation.
 *
 * \param ppqn
 *      The P value in the equation.
 *
 * \param bw
 *      The W value in the equation.
 *
 * \param measures
 *      The M value in the equation.  It defaults to 1, in case one desires a
 *      simple "ticks per measure" number.
 *
 * \return
 *      Returns the L value (ticks of pulses) as calculated via the given
 *      equation.  If bw is 0, then 0 is returned.
 */

inline long measures_to_ticks
(
    int bpm,
    int ppqn,
    int bw,
    int measures = 1
)
{
    return (bw > 0) ? (4 * measures * bpm * ppqn / bw) : 0 ;
}

}           // namespace seq64

#endif      // SEQ64_CALCULATIONS_H

/*
 * calculations.h
 *
 * vim: sw=4 ts=4 wm=4 et ft=cpp
 */
