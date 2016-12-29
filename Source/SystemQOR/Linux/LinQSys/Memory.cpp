//FloatScan.cpp

// Copyright Querysoft Limited 2013
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

//Float Scanner

#include "SystemQOR.h"
#include <errno.h>
#include <stddef.h>
#include "LinQSys/Memory.h"
#include "SystemQOR/Linux/internal/libc.h"

//------------------------------------------------------------------------------
namespace nsLinQSys
{
    //------------------------------------------------------------------------------
    CMemory::CMemory()
    {
        cur = 0;
        brk = 0;
    }

    //------------------------------------------------------------------------------
    CMemory::~CMemory()
    {

    }

    //------------------------------------------------------------------------------
    CMemory& CMemory::Instance( void )
    {
        static CMemory _Memory;
        return _Memory;
    }

    //------------------------------------------------------------------------------
    void* CMemory::__simple_malloc( size_t n )
    {
    /*
        uintptr_t base;
        uintptr_t _new;
        static int lock[ 2 ];
        size_t align = 1;

        if( !n )
        {
            n++;
        }

        if( n > SIZE_MAX / 2 )
        {
            goto toobig;
        }

        while( align < n && align < ALIGN )
        {
            align += align;
        }

        n = n + align - 1 & -align;

        //TODO:LOCK( lock );

        if( !cur )
        {
            cur = brk = m_Kernel.__brk( 0 ) + 16;
        }

        base = cur + align-1 & -align;

        if( n > SIZE_MAX - PAGE_SIZE - base )
        {
            goto fail;
        }

        if( base + n > brk )
        {
            _new = base + n + PAGE_SIZE - 1 & -PAGE_SIZE;
            if( m_Kernel.__brk( _new ) != _new )
            {
                goto fail;
            }
            brk = _new;
        }
        cur = base + n;
        //TODO:UNLOCK( lock );

        return (void*)base;

    fail:

        //TODO:UNLOCK( lock );

    toobig:
*/
        errno = ENOMEM;
        return 0;
    }

#if defined(__GNUC__) && defined(__PIC__)
#   define inline inline __attribute__((always_inline))
#endif

#define CHUNK_SIZE(c) ((c)->csize & -2)
#define CHUNK_PSIZE(c) ((c)->psize & -2)
#define PREV_CHUNK(c) ((struct chunk *)((char *)(c) - CHUNK_PSIZE(c)))
#define NEXT_CHUNK(c) ((struct chunk *)((char *)(c) + CHUNK_SIZE(c)))
#define MEM_TO_CHUNK(p) (struct chunk *)((char *)(p) - OVERHEAD)
#define CHUNK_TO_MEM(c) (void *)((char *)(c) + OVERHEAD)
#define BIN_TO_CHUNK(i) (MEM_TO_CHUNK(&mal.bins[i].head))
#define IS_MMAPPED(c) !((c)->csize & (C_INUSE))


    // Synchronization tools

    //------------------------------------------------------------------------------
    inline void CMemory::lock( volatile int* lk )
    {
        /*TODO:
        if( !libc.threads_minus_1 )
        {
            return;
        }
        while( a_swap( lk, 1 ) )
        {
            m_Kernel.__wait( lk, lk + 1, 1, 1 );
        }
        */
    }

    //------------------------------------------------------------------------------
    inline void CMemory::unlock( volatile int* lk )
    {
        /*TODO:
        if( !libc.threads_minus_1 )
        {
            return;
        }

        a_store( lk, 0 );

        if( lk[ 1 ] )
        {
            m_Kernel.__wake( lk, 1, 1 );
        }
        */
    }

    //------------------------------------------------------------------------------
    inline void CMemory::lock_bin( int i )
    {
        /*TODO:
        if( libc.threads_minus_1 )
        {
            lock( mal.bins[ i ].lock );
        }
        */
        if( !mal.bins[ i ].head )
        {
            mal.bins[ i ].head = mal.bins[ i ].tail = BIN_TO_CHUNK( i );
        }
    }

    //------------------------------------------------------------------------------
    inline void CMemory::unlock_bin( int i )
    {
        /*TODO:
        if( !libc.threads_minus_1 )
        {
            return;
        }
        unlock( mal.bins[ i ].lock );
        */
    }

    //------------------------------------------------------------------------------
    int CMemory::first_set( uint64_t x )
    {
    /*
#if 1
        return a_ctz_64( x );
#else
        static const char debruijn64[ 64 ] =
        {
            0, 1, 2, 53, 3, 7, 54, 27, 4, 38, 41, 8, 34, 55, 48, 28,
            62, 5, 39, 46, 44, 42, 22, 9, 24, 35, 59, 56, 49, 18, 29, 11,
            63, 52, 6, 26, 37, 40, 33, 47, 61, 45, 43, 21, 23, 58, 17, 10,
            51, 25, 36, 32, 60, 20, 57, 16, 50, 31, 19, 15, 30, 14, 13, 12
        };

        static const char debruijn32[ 32 ] =
        {
            0, 1, 23, 2, 29, 24, 19, 3, 30, 27, 25, 11, 20, 8, 4, 13,
            31, 22, 28, 18, 26, 10, 7, 12, 21, 17, 9, 6, 16, 5, 15, 14
        };

        if( sizeof( long ) < 8 )
        {
            uint32_t y = x;
            if( !y )
            {
                y = x >> 32;
                return 32 + debruijn32[ ( y & -y ) * 0x076be629 >> 27 ];
            }
            return debruijn32[ ( y & -y ) * 0x076be629 >> 27 ];
        }
        return debruijn64[ ( x & -x ) * 0x022fdd63cc95386dull >> 58 ];
#endif
*/
        return 0;
    }

    //------------------------------------------------------------------------------
    int CMemory::bin_index( size_t x )
    {
    /*
        x = x / SIZE_ALIGN - 1;
        if( x <= 32 )
        {
            return x;
        }

        if( x > 0x1c00 )
        {
            return 63;
        }
        return ( ( union { float v; uint32_t r; } ){(int)x}.r >> 21 ) - 496;
        */
        return 0;
    }

    //------------------------------------------------------------------------------
    int CMemory::bin_index_up( size_t x )
    {
    /*
        x = x / SIZE_ALIGN - 1;
        if( x <= 32 )
        {
            return x;
        }
        return ( ( union { float v; uint32_t r; } ){ (int)x }.r + 0x1fffff >> 21 ) - 496;
        */
        return 0;
    }

#if 0
    //------------------------------------------------------------------------------
    void __dump_heap(int x)
    {
        struct chunk *c;
        int i;
        for (c = (void *)mal.heap; CHUNK_SIZE(c); c = NEXT_CHUNK(c))
            fprintf(stderr, "base %p size %zu (%d) flags %d/%d\n",
                c, CHUNK_SIZE(c), bin_index(CHUNK_SIZE(c)),
                c->csize & 15,
                NEXT_CHUNK(c)->psize & 15);
        for (i=0; i<64; i++) {
            if (mal.bins[i].head != BIN_TO_CHUNK(i) && mal.bins[i].head) {
                fprintf(stderr, "bin %d: %p\n", i, mal.bins[i].head);
                if (!(mal.binmap & 1ULL<<i))
                    fprintf(stderr, "missing from binmap!\n");
            } else if (mal.binmap & 1ULL<<i)
                fprintf(stderr, "binmap wrongly contains %d!\n", i);
        }
    }
#endif

    //------------------------------------------------------------------------------
    CMemory::chunk* CMemory::expand_heap( size_t n )
    {
        struct chunk* w;
        /*
        uintptr_t _new;

        lock( mal.brk_lock );

        if( n > SIZE_MAX - mal.brk - 2 * PAGE_SIZE )
        {
            goto fail;
        }
        _new = mal.brk + n + SIZE_ALIGN + PAGE_SIZE - 1 & -PAGE_SIZE;
        n = _new - mal.brk;

        if( m_Kernel.__brk( _new ) != _new )
        {
            goto fail;
        }

        w = MEM_TO_CHUNK( _new );
        w->psize = n | C_INUSE;
        w->csize = 0 | C_INUSE;

        w = MEM_TO_CHUNK( mal.brk );
        w->csize = n | C_INUSE;
        mal.brk = _new;

        unlock( mal.brk_lock );

        return w;

    fail:

        unlock( mal.brk_lock );
        */
        return 0;
    }

    //------------------------------------------------------------------------------
    int CMemory::init_malloc( size_t n )
    {
    /*
        static int init, waiters;
        int state;
        struct chunk *c;

        if( init == 2 )
        {
            return 0;
        }

        while( ( state = a_swap( &init, 1 ) ) == 1 )
        {
            m_Kernel.__wait( &init, &waiters, 1, 1 );
        }

        if( state )
        {
            a_store( &init, 2 );
            return 0;
        }

        mal.brk = m_Kernel.__brk( 0 );
#ifdef SHARED
        mal.brk = mal.brk + PAGE_SIZE - 1 & -PAGE_SIZE;
#endif
        mal.brk = mal.brk + 2 * SIZE_ALIGN - 1 & -SIZE_ALIGN;

        c = expand_heap( n );

        if( !c )
        {
            a_store( &init, 0 );
            if( waiters )
            {
                m_Kernel.__wake( &init, 1, 1 );
            }
            return -1;
        }

        mal.heap = (size_t*)c;

        c->psize = 0 | C_INUSE;

        free( CHUNK_TO_MEM( c ) );

        a_store( &init, 2 );
        if( waiters )
        {
            m_Kernel.__wake( &init, -1, 1 );
        }
        */
        return 1;
    }

    //------------------------------------------------------------------------------
    int CMemory::adjust_size( size_t* n )
    {
    /*
        // Result of pointer difference must fit in ptrdiff_t
        if( *n - 1 > PTRDIFF_MAX - SIZE_ALIGN - PAGE_SIZE )
        {
            if( *n )
            {
                errno = ENOMEM;
                return -1;
            }
            else
            {
                *n = SIZE_ALIGN;
                return 0;
            }
        }
        *n = (*n + OVERHEAD + SIZE_ALIGN - 1) & SIZE_MASK;
        */
        return 0;
    }

    //------------------------------------------------------------------------------
    void CMemory::unbin( struct chunk *c, int i )
    {
    /*
        if( c->prev == c->next )
        {
            a_and_64( &mal.binmap, ~( 1ULL << i ) );
        }
        c->prev->next = c->next;
        c->next->prev = c->prev;
        c->csize |= C_INUSE;
        NEXT_CHUNK( c )->psize |= C_INUSE;
        */
    }

    //------------------------------------------------------------------------------
    int CMemory::alloc_fwd( struct chunk*c )
    {
    /*
        int i;
        size_t k;
        while( ! (( k = c->csize ) & C_INUSE ) )
        {
            i = bin_index( k );
            lock_bin( i );
            if( c->csize == k )
            {
                unbin( c, i );
                unlock_bin( i );
                return 1;
            }
            unlock_bin( i );
        }
        */
        return 0;
    }

    //------------------------------------------------------------------------------
    int CMemory::alloc_rev( struct chunk* c )
    {
    /*
        int i;
        size_t k;
        while( ! (( k = c->psize ) & C_INUSE ) )
        {
            i = bin_index( k );
            lock_bin( i );
            if( c->psize == k )
            {
                unbin( PREV_CHUNK( c ), i );
                unlock_bin( i );
                return 1;
            }
            unlock_bin( i );
        }
        */
        return 0;
    }


    //------------------------------------------------------------------------------
    /* pretrim - trims a chunk _prior_ to removing it from its bin.
     * Must be called with i as the ideal bin for size n, j the bin
     * for the _free_ chunk self, and bin j locked. */
    int CMemory::pretrim( struct chunk* self, size_t n, int i, int j )
    {
    /*
        size_t n1;
        struct chunk *next, *split;

        // We cannot pretrim if it would require re-binning.
        if( j < 40 )
        {
            return 0;
        }

        if( j < i + 3 )
        {
            if( j != 63 )
            {
                return 0;
            }
            n1 = CHUNK_SIZE( self );
            if( n1 - n <= MMAP_THRESHOLD )
            {
                return 0;
            }
        }
        else
        {
            n1 = CHUNK_SIZE( self );
        }

        if( bin_index( n1 - n ) != j )
        {
            return 0;
        }

        next = NEXT_CHUNK( self );
        split = (chunk*)( (char*)self + n );

        split->prev = self->prev;
        split->next = self->next;
        split->prev->next = split;
        split->next->prev = split;
        split->psize = n | C_INUSE;
        split->csize = n1-n;
        next->psize = n1-n;
        self->csize = n | C_INUSE;
        */
        return 1;
    }

    //------------------------------------------------------------------------------
    void CMemory::trim( struct chunk* self, size_t n )
    {
    /*
        size_t n1 = CHUNK_SIZE( self );
        struct chunk *next, *split;

        if( n >= n1 - DONTCARE )
        {
            return;
        }

        next = NEXT_CHUNK( self );
        split = (chunk*)((char *)self + n);

        split->psize = n | C_INUSE;
        split->csize = n1-n | C_INUSE;
        next->psize = n1-n | C_INUSE;
        self->csize = n | C_INUSE;

        free( CHUNK_TO_MEM( split ) );
        */
    }

    //------------------------------------------------------------------------------
    void* CMemory::malloc( size_t n )
    {
    /*
        struct chunk *c;
        int i, j;

        if( adjust_size( &n ) < 0 )
        {
            return 0;
        }

        if( n > MMAP_THRESHOLD )
        {
            size_t len = n + OVERHEAD + PAGE_SIZE - 1 & -PAGE_SIZE;
            char *base = (char*)( m_Kernel.__mmap(0, len, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) );
            if( base == (char*) - 1 )
            {
                return 0;
            }
            c = (chunk*)(base + SIZE_ALIGN - OVERHEAD);
            c->csize = len - (SIZE_ALIGN - OVERHEAD);
            c->psize = SIZE_ALIGN - OVERHEAD;
            return CHUNK_TO_MEM( c );
        }

        i = bin_index_up( n );
        for (;;)
        {
            uint64_t mask = mal.binmap & -(1ULL<<i);
            if (!mask)
            {
                if( init_malloc( n ) > 0 )
                {
                    continue;
                }
                c = expand_heap( n );
                if( !c )
                {
                    return 0;
                }
                if( alloc_rev( c ) )
                {
                    struct chunk *x = c;
                    c = PREV_CHUNK( c );
                    NEXT_CHUNK( x )->psize = c->csize = x->csize + CHUNK_SIZE( c );
                }
                break;
            }
            j = first_set( mask );
            lock_bin( j );
            c = mal.bins[ j ].head;

            if( c != BIN_TO_CHUNK( j ) && j == bin_index( c->csize ) )
            {
                if( !pretrim( c, n, i, j ) )
                {
                    unbin( c, j );
                }
                unlock_bin( j );
                break;
            }
            unlock_bin( j );
        }

        // Now patch up in case we over-allocated
        trim( c, n );

        return CHUNK_TO_MEM( c );
        */
        return 0;
    }

    //------------------------------------------------------------------------------
    void* CMemory::realloc( void* p, size_t n )
    {
    /*
        struct chunk *self, *next;
        size_t n0, n1;
        void* _new;

        if( !p )
        {
            return malloc( n );
        }

        if( adjust_size( &n ) < 0 )
        {
            return 0;
        }

        self = MEM_TO_CHUNK( p );
        n1 = n0 = CHUNK_SIZE( self );

        if( IS_MMAPPED( self ) )
        {
            size_t extra = self->psize;
            char* base = (char*)self - extra;
            size_t oldlen = n0 + extra;
            size_t newlen = n + extra;
            // Crash on realloc of freed chunk
            if( extra & 1 )
            {
                a_crash();
            }
            if( newlen < PAGE_SIZE && ( _new = malloc( n ) ) )
            {
                memcpy( _new, p, n - OVERHEAD );
                free( p );
                return _new;
            }

            newlen = ( newlen + PAGE_SIZE - 1 ) & -PAGE_SIZE;

            if( oldlen == newlen )
            {
                return p;
            }
            base = (char*)( m_Kernel.__mremap( base, oldlen, newlen, MREMAP_MAYMOVE ) );
            if( base == (char*)-1 )
            {
                return newlen < oldlen ? p : 0;
            }
            self = (chunk*)( base + extra );
            self->csize = newlen - extra;
            return CHUNK_TO_MEM( self );
        }

        next = NEXT_CHUNK( self );

        // Crash on corrupted footer (likely from buffer overflow)
        if( next->psize != self->csize )
        {
            a_crash();
        }

        // Merge adjacent chunks if we need more space. This is not
        // a waste of time even if we fail to get enough space, because our
        // subsequent call to free would otherwise have to do the merge.
        if( n > n1 && alloc_fwd( next ) )
        {
            n1 += CHUNK_SIZE( next );
            next = NEXT_CHUNK( next );
        }

        // FIXME: find what's wrong here and reenable it..?
        if( 0 && n > n1 && alloc_rev( self ) )
        {
            self = PREV_CHUNK( self );
            n1 += CHUNK_SIZE( self );
        }

        self->csize = n1 | C_INUSE;
        next->psize = n1 | C_INUSE;

        // If we got enough space, split off the excess and return
        if( n <= n1 )
        {
            //memmove(CHUNK_TO_MEM(self), p, n0-OVERHEAD);
            trim( self, n );
            return CHUNK_TO_MEM( self );
        }

        // As a last resort, allocate a new chunk and copy to it.
        _new = malloc( n - OVERHEAD );
        if( !_new )
        {
            return 0;
        }

        memcpy( _new, p, n0-OVERHEAD );
        free( CHUNK_TO_MEM( self ) );
        return _new;
        */
        return 0;
    }

    //------------------------------------------------------------------------------
    void CMemory::free( void* p )
    {
    /*
        struct chunk* self = MEM_TO_CHUNK( p );
        struct chunk* next;
        size_t final_size, new_size, size;
        int reclaim=0;
        int i;

        if( !p )
        {
            return;
        }

        if( IS_MMAPPED( self ) )
        {
            size_t extra = self->psize;
            char *base = (char*)self - extra;
            size_t len = CHUNK_SIZE( self ) + extra;
            // Crash on double free
            if( extra & 1 )
            {
                a_crash();
            }
            m_Kernel.__munmap( base, len );
            return;
        }

        final_size = new_size = CHUNK_SIZE( self );
        next = NEXT_CHUNK( self );

        // Crash on corrupted footer (likely from buffer overflow)
        if( next->psize != self->csize )
        {
            a_crash();
        }

        for( ; ; )
        {
            // Replace middle of large chunks with fresh zero pages
            if( reclaim && ( self->psize & next->csize & C_INUSE ) )
            {
                uintptr_t a = (uintptr_t)self + SIZE_ALIGN+PAGE_SIZE-1 & -PAGE_SIZE;
                uintptr_t b = (uintptr_t)next - SIZE_ALIGN & -PAGE_SIZE;
#if 1
                m_Kernel.__madvise((void *)a, b-a, MADV_DONTNEED);
#else
                m_Kernel.__mmap((void *)a, b-a, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS|MAP_FIXED, -1, 0);
#endif
            }

            if( self->psize & next->csize & C_INUSE )
            {
                self->csize = final_size | C_INUSE;
                next->psize = final_size | C_INUSE;
                i = bin_index( final_size );
                lock_bin(i);
                lock( mal.free_lock );
                if( self->psize & next->csize & C_INUSE )
                {
                    break;
                }
                unlock( mal.free_lock );
                unlock_bin( i );
            }

            if( alloc_rev( self ) )
            {
                self = PREV_CHUNK( self );
                size = CHUNK_SIZE( self );
                final_size += size;
                if( new_size + size > RECLAIM && ( new_size + size ^ size ) > size )
                {
                    reclaim = 1;
                }
            }

            if( alloc_fwd( next ) )
            {
                size = CHUNK_SIZE( next );
                final_size += size;
                if( new_size + size > RECLAIM && ( new_size + size ^ size ) > size )
                {
                    reclaim = 1;
                }
                next = NEXT_CHUNK( next );
            }
        }

        self->csize = final_size;
        next->psize = final_size;
        unlock( mal.free_lock );

        self->next = BIN_TO_CHUNK( i );
        self->prev = mal.bins[ i ].tail;
        self->next->prev = self;
        self->prev->next = self;

        if( ! ( mal.binmap & 1ULL << i ) )
        {
            a_or_64( &mal.binmap, 1ULL << i );
        }

        unlock_bin( i );
        */
    }

}//nsLinQSys
