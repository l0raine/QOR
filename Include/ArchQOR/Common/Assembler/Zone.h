//Zone.h

// Copyright (c) 2008-2010, Petr Kobalicek <kobalicek.petr@gmail.com>
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

//A specialist allocator for the JIT Assemblers
//Code is generic over standard C library interface

#ifndef ARCHQOR_ZONE_H_2
#define ARCHQOR_ZONE_H_2

#include "CompilerQOR.h"
#include "CodeQOR/Macros/codingmacros.h"
#include "CodeQOR/Macros/ClassIdentityMacros.h"
#include "CodeQOR/DataTypes/GUID.h"

//--------------------------------------------------------------------------------
namespace nsArch
{
	// Memory allocator designed to fast alloc memory that will be freed
	// in one step.
	//
	// Note This is hackery for performance. Concept is that objects created
	// by Zone are freed all at once. This means that lifetime of 
	// these objects are same as zone object itself.
	//
	// All emittables, variables, labels and states allocated by HLA are
	// allocated through Zone object.
	class __QOR_INTERFACE( __ARCHQOR ) CZone
	{
	public:

		__QOR_DECLARE_OCLASS_ID(CZone);

		CZone( Cmp_uint_ptr chunkSize ) __QCMP_THROW;
		~CZone() __QCMP_THROW;

		//--------------------------------------------------------------------------------
		// Allocate size bytes of memory and return pointer to it.
		//
		// Pointer allocated by this way will be valid until Zone object is
		// destroyed. To create class by this way use placement new and 
		// delete operators:
		//
		// // Example of allocating simple class
		//
		// // Your class
		// class Object
		// {
		//   // members...
		// };
		//
		// // Your function
		// void f()
		// {
		//   // We are using nsArch namespace
		//   using namespace nsArch
		//
		//   // Create zone object with chunk size of 65536 bytes.
		//   Zone zone(65536);
		//
		//   // Create your objects using zone object allocating, for example:
		//   Object* obj = new(zone.alloc(sizeof(YourClass))) Object();
		// 
		//   // ... lifetime of your objects ...
		// 
		//   // Destroy your objects:
		//   obj->~Object();
		//
		//   // Zone destructor will free all memory allocated through it, 
		//   // alternative is to call zone.freeAll().
		void* zalloc( Cmp_uint_ptr size ) __QCMP_THROW;

		
		char* zstrdup( const char* str ) __QCMP_THROW;		// Helper to duplicate string.

		// Free all allocated memory except first block that remains for reuse.
		//
		// Note that this method will invalidate all instances using this memory
		// allocated by this zone instance.
		void clear() __QCMP_THROW;

		// Free all allocated memory at once.
		//
		// Note that this method will invalidate all instances using this memory
		// allocated by this zone instance.
		void freeAll() __QCMP_THROW;

		//--------------------------------------------------------------------------------
		// Get total size of allocated objects - by alloc().
		inline Cmp_uint_ptr getTotal() const __QCMP_THROW 
		{ 
			return m_uiTotal; 
		}

		//--------------------------------------------------------------------------------
		// Get (default) chunk size.
		inline Cmp_uint_ptr getChunkSize() const __QCMP_THROW 
		{ 
			return m_uiChunkSize; 
		}

		//--------------------------------------------------------------------------------
		// One allocated chunk of memory.
		struct __QCMP_LOCAL Chunk
		{
			Chunk* prev;					// Link to previous chunk.
			Cmp_uint_ptr pos;				// Position in this chunk.
			Cmp_uint_ptr size;				// Size of this chunk (in bytes).
			Cmp_unsigned__int8 data[ sizeof(void*) ];		// Data.

			//--------------------------------------------------------------------------------
			// Get count of remaining (unused) bytes in chunk.
			inline Cmp_uint_ptr getRemainingBytes() const __QCMP_THROW 
			{ 
				return size - pos; 
			}
		};

	private:

		Chunk* m_pChunks;				// Last allocated chunk of memory.
		Cmp_uint_ptr m_uiTotal;			// Total size of allocated objects - by alloc() method.
		Cmp_uint_ptr m_uiChunkSize;		// One chunk size.

		__QCS_DECLARE_NONCOPYABLE( CZone );
	};

}//nsArch

#endif//ARCHQOR_ZONE_H_2