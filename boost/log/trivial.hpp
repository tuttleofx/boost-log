/*
 *          Copyright Andrey Semashev 2007 - 2013.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   log/trivial.hpp
 * \author Andrey Semashev
 * \date   07.11.2009
 *
 * This header defines tools for trivial logging support
 */

#ifndef BOOST_LOG_TRIVIAL_HPP_INCLUDED_
#define BOOST_LOG_TRIVIAL_HPP_INCLUDED_

#include <iosfwd>
#include <ostream>
#include <boost/log/detail/config.hpp>
#include <boost/log/keywords/severity.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_LOG_HAS_PRAGMA_ONCE
#pragma once
#endif

#if !defined(BOOST_LOG_USE_CHAR)
#error Boost.Log: Trivial logging is available for narrow-character builds only. Use advanced initialization routines to setup wide-character logging.
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace trivial {

//! Trivial severity levels
enum severity_level
{
    trace,
    debug,
    info,
    warning,
    error,
    fatal
};

//! Returns stringified enumeration value or \c NULL, if the value is not valid
BOOST_LOG_API const char* to_string(severity_level lvl);

template< typename CharT, typename TraitsT >
inline std::basic_ostream< CharT, TraitsT >& operator<< (
    std::basic_ostream< CharT, TraitsT >& strm, severity_level lvl)
{
    const char* str = boost::log::trivial::to_string(lvl);
    if (str)
        strm << str;
    else
        strm << static_cast< int >(lvl);
    return strm;
}

template< typename CharT, typename TraitsT >
BOOST_LOG_API std::basic_istream< CharT, TraitsT >& operator>> (
    std::basic_istream< CharT, TraitsT >& strm, severity_level& lvl);

//! Trivial logger type
#if !defined(BOOST_LOG_NO_THREADS)
typedef sources::severity_logger_mt< severity_level > logger_type;
#else
typedef sources::severity_logger< severity_level > logger_type;
#endif

//! Trivial logger tag
struct logger
{
    //! Logger type
    typedef trivial::logger_type logger_type;

    /*!
     * Returns a reference to the trivial logger instance
     */
    static BOOST_LOG_API logger_type& get();

    // Implementation details - never use these
#if !defined(BOOST_LOG_DOXYGEN_PASS)
    enum registration_line_t { registration_line = __LINE__ };
    static const char* registration_file() { return __FILE__; }
    static BOOST_LOG_API logger_type construct_logger();
#endif
};

//! The macro is used to initiate logging
#define BOOST_LOG_TRIVIAL(lvl)\
    BOOST_LOG_STREAM_WITH_PARAMS(::boost::log::trivial::logger::get(),\
        (::boost::log::keywords::severity = ::boost::log::trivial::lvl))

} // namespace trivial

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>
#if defined(BOOST_LOG_EXPRESSIONS_KEYWORD_HPP_INCLUDED_)
#include <boost/log/detail/trivial_keyword.hpp>
#endif

#endif // BOOST_LOG_TRIVIAL_HPP_INCLUDED_
