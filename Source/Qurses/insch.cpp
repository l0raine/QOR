/* Public Domain Curses */

#include "Qurses/curspriv.h"

RCSID("$Id: insch.c,v 1.44 2008/07/13 16:08:18 wmcbrine Exp $")

/*man-start**************************************************************

  Name:                                                         insch

  Synopsis:
        int insch(chtype ch);
        int winsch(WINDOW *win, chtype ch);
        int mvinsch(int y, int x, chtype ch);
        int mvwinsch(WINDOW *win, int y, int x, chtype ch);

        int insrawch(chtype ch);
        int winsrawch(WINDOW *win, chtype ch);
        int mvinsrawch(int y, int x, chtype ch);
        int mvwinsrawch(WINDOW *win, int y, int x, chtype ch);

        int ins_wch(const cchar_t *wch);
        int wins_wch(WINDOW *win, const cchar_t *wch);
        int mvins_wch(int y, int x, const cchar_t *wch);
        int mvwins_wch(WINDOW *win, int y, int x, const cchar_t *wch);

  Description:
        The insch() functions insert a chtype into the window at the 
        current or specified cursor position. The cursor is NOT 
        advanced. A newline is equivalent to clrtoeol(); tabs are 
        expanded; other control characters are converted as with 
        unctrl().

        The ins_wch() functions are the wide-character
        equivalents, taking cchar_t pointers rather than chtypes.

        Video attributes can be combined with a character by ORing
        them into the parameter. Text, including attributes, can be 
        copied from one place to another using inch() and insch().

        insrawch() etc. are PDCurses-specific wrappers for insch() etc. 
        that disable the translation of control characters.

  Return Value:
        All functions return OK on success and ERR on error.

  Portability                                X/Open    BSD    SYS V
        insch                                   Y       Y       Y
        winsch                                  Y       Y       Y
        mvinsch                                 Y       Y       Y
        mvwinsch                                Y       Y       Y
        insrawch                                -       -       -
        winsrawch                               -       -       -
        ins_wch                                 Y
        wins_wch                                Y
        mvins_wch                               Y
        mvwins_wch                              Y

**man-end****************************************************************/

#include <string.h>

//------------------------------------------------------------------------------
int winsch( WINDOW* win, chtype ch )
{
	__QCS_FCONTEXT( "winsch" );

    int x, y;
    chtype attr;
    bool xlat;

    if( !win )
	{
        return ERR;
	}

    x = win->_curx;
    y = win->_cury;

    if( y > win->_maxy || x > win->_maxx || y < 0 || x < 0 )
	{
        return ERR;
	}

    xlat = !SP->raw_out && !( ch & A_ALTCHARSET );
    attr = ch & A_ATTRIBUTES;
    ch &= A_CHARTEXT;

    if( xlat && ( ch < ' ' || ch == 0x7f ) )
    {
        int x2;

        switch( ch )
        {
        case '\t':
            for( x2 = ( ( x / TABSIZE ) + 1 ) * TABSIZE; x < x2; x++ )
            {
                if( winsch( win, attr | ' ' ) == ERR )
				{
                    return ERR;
				}
            }
            return 0;

        case '\n':
            wclrtoeol( win );
            break;

        case 0x7f:
            if( winsch( win, attr | '?' ) == ERR )
			{
                return ERR;
			}

            return winsch( win, attr | '^' );

        default:
            // handle control chars

            if( winsch( win, attr | ( ch + '@' ) ) == ERR )
			{
                return ERR;
			}

            return winsch( win, attr | '^' );
        }
    }
    else
    {
        int maxx;
        chtype *temp;

        /* If the incoming character doesn't have its own attribute,
           then use the current attributes for the window. If it has
           attributes but not a color component, OR the attributes to
           the current attributes for the window. If it has a color
           component, use the attributes solely from the incoming
           character. */

        if( !( attr & A_COLOR ) )
		{
            attr |= win->_attrs;
		}

        /* wrs (4/10/93): Apply the same sort of logic for the window
           background, in that it only takes precedence if other color
           attributes are not there and that the background character
           will only print if the printing character is blank. */

        if( !( attr & A_COLOR ) )
		{
            attr |= win->_bkgd & A_ATTRIBUTES;
		}
        else
		{
            attr |= win->_bkgd & ( A_ATTRIBUTES ^ A_COLOR );
		}

        if( ch == ' ' )
		{
            ch = win->_bkgd & A_CHARTEXT;
		}

        // Add the attribute back into the character.

        ch |= attr;

        maxx = win->_maxx;
        temp = &win->_y[y][x];

        memmove( temp + 1, temp, ( maxx - x - 1 ) * sizeof( chtype ) );

        win->_lastch[ y ] = maxx - 1;

        if( ( win->_firstch[ y ] == _NO_CHANGE ) || ( win->_firstch[ y ] > x ) )
		{
            win->_firstch[ y ] = x;
		}

        *temp = ch;
    }

    PDC_sync( win );

    return 0;
}

//------------------------------------------------------------------------------
int insch( chtype ch )
{
    __QCS_FCONTEXT( "insch" );

    return winsch( stdscr, ch );
}

//------------------------------------------------------------------------------
int mvinsch( int y, int x, chtype ch )
{
    __QCS_FCONTEXT( "mvinsch" );

    if( move( y, x ) == ERR )
	{
        return ERR;
	}

    return winsch( stdscr, ch );
}

//------------------------------------------------------------------------------
int mvwinsch( WINDOW* win, int y, int x, chtype ch )
{
    __QCS_FCONTEXT( "mvwinsch" );

    if( wmove( win, y, x ) == ERR )
	{
        return ERR;
	}

    return winsch( win, ch );
}

//------------------------------------------------------------------------------
int winsrawch( WINDOW* win, chtype ch )
{
    __QCS_FCONTEXT( "winsrawch" );

    if( ( ch & A_CHARTEXT) < ' ' || ( ch & A_CHARTEXT ) == 0x7f )
	{
        ch |= A_ALTCHARSET;
	}

    return winsch( win, ch );
}

//------------------------------------------------------------------------------
int insrawch( chtype ch )
{
    __QCS_FCONTEXT( "insrawch" );

    return winsrawch( stdscr, ch );
}

//------------------------------------------------------------------------------
int mvinsrawch( int y, int x, chtype ch )
{
    __QCS_FCONTEXT( "mvinsrawch" );

    if( move( y, x ) == ERR )
	{
        return ERR;
	}

    return winsrawch( stdscr, ch );
}

//------------------------------------------------------------------------------
int mvwinsrawch( WINDOW* win, int y, int x, chtype ch )
{
    __QCS_FCONTEXT( "mvwinsrawch" );

    if( wmove( win, y, x ) == ERR )
	{
        return ERR;
	}

    return winsrawch( win, ch );
}

#if __QOR_UNICODE
//------------------------------------------------------------------------------
int wins_wch( WINDOW* win, const cchar_t* wch )
{
    __QCS_FCONTEXT( "wins_wch" );

    return wch ? winsch( win, *wch ) : ERR;
}

//------------------------------------------------------------------------------
int ins_wch( const cchar_t* wch )
{
    __QCS_FCONTEXT( "ins_wch" );

    return wins_wch( stdscr, wch );
}

//------------------------------------------------------------------------------
int mvins_wch( int y, int x, const cchar_t* wch )
{
    __QCS_FCONTEXT( "mvins_wch" );

    if( move( y, x ) == ERR )
	{
        return ERR;
	}

    return wins_wch( stdscr, wch );
}

//------------------------------------------------------------------------------
int mvwins_wch( WINDOW* win, int y, int x, const cchar_t* wch )
{
    __QCS_FCONTEXT( "mvwins_wch" );

    if( wmove( win, y, x ) == ERR )
	{
        return ERR;
	}

    return wins_wch( win, wch );
}

#endif
