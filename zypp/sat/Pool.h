/*---------------------------------------------------------------------\
|                          ____ _   __ __ ___                          |
|                         |__  / \ / / . \ . \                         |
|                           / / \ V /|  _/  _/                         |
|                          / /__ | | | | | |                           |
|                         /_____||_| |_| |_|                           |
|                                                                      |
\---------------------------------------------------------------------*/
/** \file	zypp/sat/Pool.h
 *
*/
#ifndef ZYPP_SAT_POOL_H
#define ZYPP_SAT_POOL_H

#include <iosfwd>

#include "zypp/Pathname.h"

#include "zypp/sat/detail/PoolMember.h"
#include "zypp/sat/Repo.h"
#include "zypp/sat/WhatProvides.h"

///////////////////////////////////////////////////////////////////
namespace zypp
{ /////////////////////////////////////////////////////////////////

  class SerialNumber;
  class RepoInfo;

  ///////////////////////////////////////////////////////////////////
  namespace sat
  { /////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    //
    //	CLASS NAME : Pool
    //
    /** Global sat-pool.
     *
     * Explicitly shared singleton \ref Pool::instance.
     */
    class Pool : protected detail::PoolMember
    {
      public:
        typedef detail::SolvableIterator SolvableIterator;
        typedef detail::RepoIterator     RepoIterator;
        typedef detail::size_type        size_type;

      public:
        /** Singleton ctor. */
        static Pool instance()
        { return Pool(); }

        /** Ctor from \ref PoolMember. */
        Pool( const detail::PoolMember & )
        {}

      public:
        /** Internal array size for stats only. */
        size_type capacity() const;

        /** Housekeeping data serial number. */
        const SerialNumber & serial() const;

        /** Update housekeeping data if necessary (e.g. whatprovides). */
        void prepare() const;

      public:
        /** Whether \ref Pool contains repos. */
        bool reposEmpty() const;

        /** Number of repos in \ref Pool. */
        size_type reposSize() const;

        /** Iterator to the first \ref Repo. */
        RepoIterator reposBegin() const;

        /** Iterator behind the last \ref Repo. */
        RepoIterator reposEnd() const;

        /** Return a \ref Repo named \c name_r.
         * It a such a \ref Repo does not already exist
         * a new empty \ref Repo is created.
         */
        Repo reposInsert( const std::string & name_r );

        /** Find a \ref Repo named \c name_r.
         * Returns \ref norepo if there is no such \ref Repo.
         */
        Repo reposFind( const std::string & name_r ) const;

        /** Remove a \ref Repo named \c name_r.
         * \see \ref Repo::eraseFromPool
         */
        void reposErase( const std::string & name_r )
        { reposFind( name_r ).eraseFromPool(); }

      public:
        /** Reserved system repo name \c @System. */
        static const std::string & systemRepoName();

        /** Return the system repo. */
        Repo systemRepo()
        { return reposInsert( systemRepoName() ); }

      public:
        /** Load \ref Solvables from a solv-file into a \ref Repo named \c name_r.
         * In case of an exception the \ref Repo is removed from the \ref Pool.
         * \throws Exception if loading the solv-file fails.
         * \see \ref Repo::EraseFromPool
        */
        Repo addRepoSolv( const Pathname & file_r, const std::string & name_r );
        /** \overload Using the files basename as \ref Repo name. */
        Repo addRepoSolv( const Pathname & file_r );
        /** \overload Using the \ref RepoInfo::alias \ref Repo name.
         * Additionally stores the \ref RepoInfo. \See \ref Prool::setInfo.
        */
        Repo addRepoSolv( const Pathname & file_r, const RepoInfo & info_r );

      public:
        /** Whether \ref Pool contains solvables. */
        bool solvablesEmpty() const;

        /** Number of solvables in \ref Pool. */
        size_type solvablesSize() const;

        /** Iterator to the first \ref Solvable. */
        SolvableIterator solvablesBegin() const;

        /** Iterator behind the last \ref Solvable. */
        SolvableIterator solvablesEnd() const;

      public:
        /** Conainer of all \ref Solvable providing \c cap_r.  */
        WhatProvides whatProvides( Capability cap_r ) const
        { return WhatProvides( cap_r ); }

      public:
        /** \name Requested locales. */
        //@{
        /** Set the requested locales.
         * Languages to be supported by the system, e.g. language specific
         * packages to be installed.
         */
        void setRequestedLocales( const LocaleSet & locales_r );

        /** Add one \ref Locale to the set of requested locales.
         * Return \c true if \c locale_r was newly added to the set.
        */
        bool addRequestedLocale( const Locale & locale_r );

        /** Erase one \ref Locale from the set of requested locales.
        * Return \c false if \c locale_r was not found in the set.
         */
        bool eraseRequestedLocale( const Locale & locale_r );

        /** Return the requested locales.
         * \see \ref setRequestedLocales
        */
        const LocaleSet & getRequestedLocales() const;

        /** Wheter this \ref Locale is in the set of requested locales. */
        bool isRequestedLocale( const Locale & locale_r ) const;

        /** Get the set of available locales.
         * This is computed from the package data so it actually
         * represents all locales packages claim to support.
         */
        const LocaleSet & getAvailableLocales() const;

        /** Wheter this \ref Locale is in the set of available locales. */
        bool isAvailableLocale( const Locale & locale_r ) const;
        //@}

      public:
        /** Expert backdoor. */
        ::_Pool * get() const;
      private:
        /** Default ctor */
        Pool() {}
    };
    ///////////////////////////////////////////////////////////////////

    /** \relates Pool Stream output */
    std::ostream & operator<<( std::ostream & str, const Pool & obj );

    /** \relates Pool */
    inline bool operator==( const Pool & lhs, const Pool & rhs )
    { return lhs.get() == rhs.get(); }

    /** \relates Pool */
    inline bool operator!=( const Pool & lhs, const Pool & rhs )
    { return lhs.get() != rhs.get(); }

    /////////////////////////////////////////////////////////////////
  } // namespace sat
  ///////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////
} // namespace zypp
///////////////////////////////////////////////////////////////////
#endif // ZYPP_SAT_POOL_H
