/**************************************************************************/
/* FILE   **************      GetAggregateT.c      ************************/
/**************************************************************************/
/* Author: Dave Cann                                                      */
/* Update: Patrick Miller -- Ansi support (Dec 2000)                      */
/* Copyright (C) University of California Regents                         */
/**************************************************************************/
/**************************************************************************/

#include "world.h"

/**************************************************************************/
/* GLOBAL **************     GetAggregateType      ************************/
/**************************************************************************/
/* PURPOSE:  Find the indicated Array[t], Stream[t], or Multiple[t]       */
/*           type.  If not found, make an anonymous new type              */
/**************************************************************************/
PINFO
GetAggregate(AggregateType,T,name)
     int        AggregateType;
     PINFO      T;
     char       *name;
{
  register PINFO i;

  /* ------------------------------------------------------------ */
  /* See if one already exists with the proper structure          */
  /* ------------------------------------------------------------ */
  for ( i = ihead; i != NULL; i = i->next ) {
    if ( i->type == AggregateType && i->info1 == T ) return i;
  }
  
  return NewType(AggregateType,T->label,0,name);
}

/*
 * $Log$
 * Revision 1.1.1.1  2000/12/31 17:58:18  patmiller
 * Well, here is the first set of big changes in the distribution
 * in 5 years!  Right now, I did a lot of work on configuration/
 * setup (now all autoconf), breaking out the machine dependent
 * #ifdef's (with a central acconfig.h driven config file), changed
 * the installation directories to be more gnu style /usr/local
 * (putting data in the /share/sisal14 dir for instance), and
 * reduced the footprint in the top level /usr/local/xxx hierarchy.
 *
 * I also wrote a new compiler tool (sisalc) to replace osc.  I
 * found that the old logic was too convoluted.  This does NOT
 * replace the full functionality, but then again, it doesn't have
 * 300 options on it either.
 *
 * Big change is making the code more portably correct.  It now
 * compiles under gcc -ansi -Wall mostly.  Some functions are
 * not prototyped yet.
 *
 * Next up: Full prototypes (little) checking out the old FLI (medium)
 * and a new Frontend for simpler extension and a new FLI (with clean
 * C, C++, F77, and Python! support).
 *
 * Pat
 *
 *
 * Revision 1.1  1994/05/25  19:44:32  denton
 * Added FindLargestLabel to return the value of LargestTypeLabelSoFar.
 * Shortened name of GetAggregateType.c to remove ar warnings.
 *
 *
 */
