/**************************************************************************/
/* FILE   **************      AssignNewLpor.c      ************************/
/**************************************************************************/
/* Author: Dave Cann                                                      */
/* Update: Patrick Miller -- Ansi support (Dec 2000)                      */
/* Copyright (C) University of California Regents                         */
/**************************************************************************/
/**************************************************************************/

#include "world.h"


/**************************************************************************/
/* GLOBAL **************      AssignNewLports      ************************/
/**************************************************************************/
/* PURPOSE: ASSIGN NEW L PORT NUMBERS, STARTING WITH p, TO THE IMPORTS    */
/*          OF LOOP l'S INITIAL SUBGRAPH AND ADJUST ALL REFERENCES. THE   */
/*          NEXT LEGAL PORT NUMBER IS RETURNED. BECAUSE IT CANNOT BE      */
/*          ASSUMED THAT ANY OF THE NODES EXIST, THEY ARE TESTED FOR      */
/*          EXISTENCE BEFORE ANY OPERATIONS ON THEM ARE DONE              */
/**************************************************************************/

int AssignNewLports( p, l )
int   p;
PNODE l;
{
  register PEDGE i;
  register PNODE n;

  if (l->L_INIT)
    {
      for ( i = l->L_INIT->imp; i != NULL; i = i->isucc, p++ )
        if ( i->iport != p ) {
          for (n = l->L_TEST; n != NULL; n = n->gsucc)
            ChangeExportPorts( n, i->iport, -p );
          if ((l->L_TEST) && (l->L_BODY))
            ChangeImportPorts( l->L_BODY, i->iport, -p );

/*        ChangeExportPorts( l->L_TEST, i->iport, -p );
          ChangeExportPorts( l->L_BODY, i->iport, -p );
          ChangeExportPorts( l->L_RET,  i->iport, -p );
          ChangeImportPorts( l->L_BODY, i->iport, -p );
*/        
          i->iport = -p;
        }
    }
  return( p );
}

/*
 * $Log$
 * Revision 1.1.1.1  2000/12/31 17:58:11  patmiller
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
 * Revision 1.2  1994/03/03  17:13:59  solomon
 * Added some tests to help prevent failing when dealing with invalid
 * if1 code.
 *
 * Revision 1.1  1993/04/16  18:59:48  miller
 * Name shortening to keep the archiver from truncating names in Backend/Library
 * Since some names were changed, other files were affected.  All names in the
 * library now start with no more than 13 (unique) characters.
 *
 * Revision 1.1  1993/01/21  23:27:52  miller
 * Initial version of the IFX library.  It replaces the if[12]build.c
 * read.c timer.c util.c and write.c and if[12].h files from the
 * backend phases.
 *
 */
