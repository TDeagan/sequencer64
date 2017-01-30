#ifndef SEQ64_MIDI_JACK_HPP
#define SEQ64_MIDI_JACK_HPP

/**
 * \file          midi_jack.hpp
 *
 *    A class for realtime MIDI input/output via JACK.
 *
 * \author        Gary P. Scavone; severe refactoring by Chris Ahlstrom
 * \date          2016-11-14
 * \updates       2017-01-29
 * \license       See the rtexmidi.lic file.  Too big for a header file.
 *
 *    In this refactoring, we've stripped out most of the original RtMidi
 *    functionality, leaving only the method for selecting the API to use for
 *    MIDI.  The method that Sequencer64's mastermidibus uses to initialize
 *    port has been transplanted to this rtmidi library.  The name "rtmidi" is
 *    now somewhat misleading.
 */

#include <string>

#include "midi_api.hpp"
#include "midi_jack_info.hpp"           /* seq64::midi_jack_info            */

/*
 * Do not document the namespace; it breaks Doxygen.
 */

namespace seq64
{
    class midibus;

/**
 *  This class implements with JACK version of the midi_alsa object.
 */

class midi_jack : public midi_api
{

private:

    /**
     *  Set to true if each JACK port should be its own client.  In this case,
     *  the functions api_init_in(), api_init_out(), api_init_in_sub(), and
     *  api_init_out_sub() need to open their own JACK client.  Otherwise,
     *  they will use the JACK client created in the midi_jack_info class.
     */

    bool m_multi_client;

    /**
     *  Preserves the original name of the remote port, so it can be used
     *  later for connection.
     */

    std::string m_remote_port_name;

protected:

    /**
     *  Holds the data needed for JACK processing.  Please do not confuse this
     *  item with the m_midi_handle of the midi_api base class.  This object
     *  holds a JACK-client pointer and a JACK-port pointer.
     */

    midi_jack_data m_jack_data;

public:

    midi_jack
    (
        midibus & parentbus,
        midi_info & masterinfo,
        int index = SEQ64_NO_INDEX
    );
    virtual ~midi_jack ();

    /**
     * \getter m_multi_client
     */

    bool multi_client () const
    {
        return m_multi_client;
    }

    /**
     * \getter m_jack_client
     *      This is the platform-specific version of midi_handle().
     */

    jack_client_t * client_handle ()
    {
        return m_jack_data.m_jack_client;
    }

    /**
     * \getter m_remote_port_name
     */

    const std::string & remote_port_name () const
    {
        return m_remote_port_name;
    }

    /**
     * \setter m_remote_port_name
     */

    void remote_port_name (const std::string & s)
    {
        m_remote_port_name = s;
    }

    /**
     * \getter m_jack_port
     *      This is the platform-specific version of midi_handle().
     */

    jack_port_t * port_handle ()
    {
        return m_jack_data.m_jack_port;
    }

protected:

    void client_handle (jack_client_t * handle)
    {
        m_jack_data.m_jack_client = handle;
    }

    void port_handle (jack_port_t * handle)
    {
        m_jack_data.m_jack_port = handle;
    }

    bool open_client_impl (bool input);     /* implements "connect()"   */
    void close_client ();
    void close_port ();
    bool connect_port
    (
        bool input,
        const std::string & sourceportname,
        const std::string & destportname
    );
    bool register_port (bool input, const std::string & portname);

protected:

    virtual bool open_client () = 0;    // replaces "connect()"
    virtual bool api_connect ();
    virtual bool api_init_out ();       // still in progress
    virtual bool api_init_in ();
    virtual bool api_init_out_sub ();
    virtual bool api_init_in_sub ();
    virtual bool api_deinit_in ();

    virtual int api_poll_for_midi ()
    {
        return 0;
    }

    virtual void api_play (event * e24, midibyte channel);
    virtual void api_sysex (event * e24);
    virtual void api_flush ();
    virtual void api_continue_from (midipulse tick, midipulse beats);
    virtual void api_start ();
    virtual void api_stop ();
    virtual void api_clock (midipulse tick);
    virtual void api_set_ppqn (int ppqn);
    virtual void api_set_beats_per_minute (int bpm);
    virtual std::string api_get_port_name ();

private:

    bool set_virtual_name (int portid, const std::string & portname);

};          // class midi_jack

/**
 *  The class for handling JACK MIDI input.
 */

class midi_in_jack: public midi_jack
{

protected:

    std::string m_clientname;

public:

    midi_in_jack
    (
        midibus & parentbus,
        midi_info & masterinfo,
        int index = SEQ64_NO_INDEX,
        unsigned queuesize = 0
    );
    virtual ~midi_in_jack ();

private:

    /**
     *  This function is virtual, so we don't call it in the constructor,
     *  using open_client_impl() directly instead.  This function replaces the
     *  RtMidi function "connect()".
     */

    virtual bool open_client ()
    {
        return open_client_impl(SEQ64_MIDI_INPUT);
    }

};          // midi_in_jack

/**
 *  The JACK MIDI output API class.
 */

class midi_out_jack: public midi_jack
{

public:

    midi_out_jack
    (
        midibus & parentbus,
        midi_info & masterinfo,
        int index = SEQ64_NO_INDEX
    );
    virtual ~midi_out_jack ();

    /*
     *  Note that midi_message::container is a vector<midibyte> object.
     */

    virtual bool send_message (const midi_message::container & message);

private:

    /**
     *  This function is virtual, so we don't call it in the constructor,
     *  using open_client_impl() directly instead.  This function replaces the
     *  RtMidi function "connect()".
     */

    virtual bool open_client ()
    {
        return open_client_impl(SEQ64_MIDI_OUTPUT);
    }

};          // midi_out_jack

}           // namespace seq64

#endif      // SEQ64_MIDI_JACK_HPP

/*
 * midi_jack.hpp
 *
 * vim: sw=4 ts=4 wm=4 et ft=cpp
 */

