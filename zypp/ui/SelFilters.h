/*---------------------------------------------------------------------\
|                          ____ _   __ __ ___                          |
|                         |__  / \ / / . \ . \                         |
|                           / / \ V /|  _/  _/                         |
|                          / /__ | | | | | |                           |
|                         /_____||_| |_| |_|                           |
|                                                                      |
\---------------------------------------------------------------------*/
/** \file	zypp/ui/SelFilters.h
 *
*/
#ifndef ZYPP_UI_SELFILTERS_H
#define ZYPP_UI_SELFILTERS_H

#include "zypp/base/Functional.h"
#include "zypp/ui/Selectable.h"

///////////////////////////////////////////////////////////////////
namespace zypp
{ /////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////
  namespace ui
  { /////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////
    namespace selfilter
    { /////////////////////////////////////////////////////////////////

      typedef std::unary_function<ui::Selectable::constPtr,bool> SelectableFilterFunctor;

      /** */
      struct ByKind : public SelectableFilterFunctor
      {
        ByKind( const ResObject::Kind & kind_r )
        : _kind( kind_r )
        {}

        bool operator()( const ui::Selectable::constPtr & obj ) const
        {
          return obj && obj->kind() == _kind;
        }

        ResObject::Kind _kind;
      };

      /** */
      struct ByName : public SelectableFilterFunctor
      {
        ByName( const std::string & name_r )
        : _name( name_r )
        {}

        bool operator()( const ui::Selectable::constPtr & obj ) const
        { return obj && obj->name() == _name; }

        std::string _name:
      };

      /** */
      struct ByHasInstalledObj : public SelectableFilterFunctor
      {
        bool operator()( const ui::Selectable::constPtr & obj ) const
        { return obj && obj->hasInstalledObj(); }
      };

      /** */
      struct ByHasCandidateObj : public SelectableFilterFunctor
      {
        bool operator()( const ui::Selectable::constPtr & obj ) const
        { return obj && obj->hasCandidateObj(); }
      };

      struct ByStatus : public SelectableFilterFunctor
      /** */
      {
        ByStatus( Status status_r )
        : _status( status_r )
        {}

        bool operator()( const ui::Selectable::constPtr & obj ) const
        { return obj && obj->status() == _status; }

        Status _status:
      };

      /////////////////////////////////////////////////////////////////
    } // namespace selfilter
    ///////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////
  } // namespace ui
  ///////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////
} // namespace zypp
///////////////////////////////////////////////////////////////////
#endif // ZYPP_UI_SELFILTERS_H
