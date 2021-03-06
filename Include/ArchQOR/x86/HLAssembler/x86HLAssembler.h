//Cx86HLAssembler.h

// Copyright Querysoft Limited 2015
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

//x86 specific High Level Assembler

#ifndef ARCHQOR_X86PC_HLASSEMBLER_H_2
#define ARCHQOR_X86PC_HLASSEMBLER_H_2

#include "CompilerQOR.h"
#include "ArchQOR/Common/HLAssembler/HighLevelAssemblerBase.h"
#include "ArchQOR/x86/HLAssembler/Emittables/ETarget.h"
#include "ArchQOR/x86/HLAssembler/Emittables/EJmp.h"
#include "ArchQOR/x86/HLAssembler/Emittables/EFunction.h"
#include "ArchQOR/x86/HLAssembler/Emittables/ECall.h"
#include "CodeQOR/DataStructures/PODVector.h"

//------------------------------------------------------------------------------
namespace nsArch
{
//------------------------------------------------------------------------------
namespace nsx86
{		
	class __QOR_INTERFACE( __ARCHQOR ) StateData;

	//------------------------------------------------------------------------------
	class __QOR_INTERFACE( __ARCHQOR ) Cx86HLAssembler : public nsArch::CHighLevelAssemblerBase
	{

	public:

		__QOR_DECLARE_OCLASS_ID(Cx86HLAssembler);
		
		Cx86HLAssembler( nsArch::CCodeGeneratorBase* codeGenerator ) __QCMP_THROW;		// Create new (empty) instance of HLA
		virtual ~Cx86HLAssembler() __QCMP_THROW;										// Destroy HLA instance.		
		virtual void setLogger( CLogger* logger ) __QCMP_THROW;							// Set logger to logger.

		//------------------------------------------------------------------------------
		inline Cmp_unsigned__int32 getError() const __QCMP_THROW 
		{ 
			return m_uiError; 
		}

		
		virtual void setError( Cmp_unsigned__int32 error ) __QCMP_THROW;				// Set error code. This method is virtual, because higher classes can use it to catch all errors.
		Cmp_unsigned__int32 getProperty( Cmp_unsigned__int32 propertyId );				// Get HLA property.
		void setProperty( Cmp_unsigned__int32 propertyId, Cmp_unsigned__int32 value );	// Set HLA property.	
		void clear() __QCMP_THROW;														// Clear everything, but not deallocate buffers. Note This method will destroy your code.
		void free() __QCMP_THROW;														// Free internal buffer, all emitters and 0 all pointers. Note This method will destroy your code.

		// Emit a single comment line that will be logged.
		// Emitting comments are useful to log something. Because assembler can be
		// generated from AST or other data structures, you may sometimes need to
		// log data characteristics or statistics.
		// Note Emitting comment is not directly sent to logger, but instead it's
		// stored in HLA and emitted when serialize() method is
		// called. Each comment keeps correct order.
		void comment( const char* fmt, ... ) __QCMP_THROW;

		// --------------------------------------------------------------------------
		// Create a new function.
		//
		// cconv Calling convention to use (see CALL_CONV enum)
		// params Function arguments prototype.
		//
		// This method is usually used as a first step when generating functions
		// by HLA. First parameter cconv specifies function calling
		// convention to use. Second parameter params specifies function
		// arguments. To create function arguments are used templates
		// BuildFunction0<>, BuildFunction1<...>, BuildFunction2<...>,
		// etc...
		//
		// Templates with BuildFunction prefix are used to generate argument IDs
		// based on real C++ types. See next example how to generate function with
		// two 32-bit integer arguments.
		//
		// // Building function using AsmJit::Compiler example.
		//
		// // Compiler instance
		// Compiler c;
		//
		// // Begin of function (also emits function Prolog)
		// c.newFunction(
		//   // Default calling convention (32-bit cdecl or 64-bit for host OS)
		//   CALL_CONV_DEFAULT,
		//   // Using function builder to generate arguments list
		//   BuildFunction2<int, int>());
		//
		// // End of function (also emits function Epilog)
		// c.endFunction();
		//
		// You can see that building functions is really easy. Previous code snipped
		// will generate code for function with two 32-bit integer arguments. You
		// can access arguments by @c AsmJit::Function::argument() method. Arguments
		// are indexed from 0 (like everything in C).
		//
		// // Accessing function arguments through AsmJit::Function example.
		//
		// // Compiler instance
		// Compiler c;
		//
		// // Begin of function (also emits function Prolog)
		// c.newFunction(
		//   // Default calling convention (32-bit cdecl or 64-bit for host OS)
		//   CALL_CONV_DEFAULT,
		//   // Using function builder to generate arguments list
		//   BuildFunction2<int, int>());
		//
		// // Arguments are like other variables, you need to reference them by
		// // variable operands:
		// GPVar a0 = c.argGP(0);
		// GPVar a1 = c.argGP(1);
		//
		// // Use them.
		// c.add(a0, a1);
		//
		// // End of function (emits function epilog and return)
		// c.endFunction();
		//
		// Arguments are like variables. How to manipulate with variables is
		// documented in AsmJit::Compiler, variables section.
		//
		// To get current function use currentFunction() method or save
		// pointer to CEFunction returned by newFunction<>
		// method. Recommended is to save the pointer.
		//
		inline CEFunction* newFunction( Cmp_unsigned__int32 cconv, const CFunctionDefinition& def ) __QCMP_THROW
		{
			return newFunction_( cconv, def.getArguments(), def.getArgumentsCount(), def.getReturnValue() );
		}

		//--------------------------------------------------------------------------
		// Create a new function (low level version).
		//
		// cconv Function calling convention (see CALL_CONV).
		// args Function arguments (see VARIABLE_TYPE).
		// count Arguments count.
		//
		// This method is internally called from newFunction() method and
		// contains arguments thats used internally by HLA
		//
		// Note To get current function use currentFunction() method.
		CEFunction* newFunction_( Cmp_unsigned__int32 cconv, const Cmp_unsigned__int32* arguments, Cmp_unsigned__int32 argumentsCount, Cmp_unsigned__int32 returnValue ) __QCMP_THROW;

		//--------------------------------------------------------------------------
		// Get current function.
		// This method can be called within newFunction() and endFunction()
		// block to get current function you are working with. It's recommended
		// to store Function pointer returned by newFunction<> method,
		// because this allows you in future implement function sections outside of
		// function itself (yeah, this is possible!).
		inline CEFunction* getFunction() const __QCMP_THROW 
		{ 
			return m_pFunction; 
		}

		// End of current function scope and all variables.
		CEFunction* endFunction() __QCMP_THROW;

		inline CEInstruction* newInstruction( Cmp_unsigned__int32 code, COperand** operandsData, Cmp_unsigned__int32 operandsCount ) __QCMP_THROW;

		
		void _emitInstruction( Cmp_unsigned__int32 code ) __QCMP_THROW;																// Emit instruction with no operand.
		void _emitInstruction( Cmp_unsigned__int32 code, const COperand* o0 ) __QCMP_THROW;											// Emit instruction with one operand.
		void _emitInstruction( Cmp_unsigned__int32 code, const COperand* o0, const COperand* o1 ) __QCMP_THROW;						// Emit instruction with two operands.
		void _emitInstruction( Cmp_unsigned__int32 code, const COperand* o0, const COperand* o1, const COperand* o2 ) __QCMP_THROW;	// Emit instruction with three operands.
		void _emitInstruction( Cmp_unsigned__int32 code, const COperand* o0, const COperand* o1, const COperand* o2, const COperand* o3 ) __QCMP_THROW;	// Emit instruction with four operands (Special instructions).
		void _emitInstruction( Cmp_unsigned__int32 code, const COperand* o0, const COperand* o1, const COperand* o2, const COperand* o3, const COperand* o4 ) __QCMP_THROW;	// Emit instruction with five operands (Special instructions).
		void _emitJcc( Cmp_unsigned__int32 code, const CLabel* label, Cmp_unsigned__int32 hint ) __QCMP_THROW;						// method for emitting jcc.
		CECall* _emitCall( const COperand* o0 ) __QCMP_THROW;																		// method for emitting function call.
		void _emitReturn( const COperand* first, const COperand* second ) __QCMP_THROW;												// method for returning a value from the function.

		void embed( const void* data, Cmp_uint_ptr len ) __QCMP_THROW;																// Embed data into instruction stream.

		// Align target buffer to m bytes.
		// Typical usage of this is to align labels at start of the inner loops.
		// Inserts nop() instructions or CPU optimized NOPs.
		//void align( Cmp_unsigned__int32 m ) __QCMP_THROW;
		CLabel newLabel() __QCMP_THROW;																								// Create and return new label.
		void bind( const CLabel& label ) __QCMP_THROW;																				// Bind label to the current offset. Note Label can be bound only once!
		VarData* _newVarData( const char* name, Cmp_unsigned__int32 type, Cmp_unsigned__int32 size ) __QCMP_THROW;					// Create a new variable data.

		//--------------------------------------------------------------------------
		// Get variable data.
		inline VarData* _getVarData( Cmp_unsigned__int32 id ) const __QCMP_THROW
		{
			//assert(id != INVALID_VALUE);
			return m_VarData[ id & OPERAND_ID_VALUE_MASK ];
		}

		CGPVar newGP( Cmp_unsigned__int32 variableType = VARIABLE_TYPE_GPN, const char* name = 0 ) __QCMP_THROW;					// Create a new general-purpose variable.
		CGPVar argGP( Cmp_unsigned__int32 index ) __QCMP_THROW;																		// Get argument as general-purpose variable.
		CMMVar newMM( Cmp_unsigned__int32 variableType = VARIABLE_TYPE_MM, const char* name = 0 ) __QCMP_THROW;						// Create a new MM variable.
		CMMVar argMM( Cmp_unsigned__int32 index ) __QCMP_THROW;																		// Get argument as MM variable.
		CXMMVar newXMM( Cmp_unsigned__int32 variableType = VARIABLE_TYPE_XMM, const char* name = 0 ) __QCMP_THROW;					// Create a new XMM variable.
		CXMMVar argXMM( Cmp_unsigned__int32 index ) __QCMP_THROW;																	// Get argument as XMM variable.
		void _vhint( CBaseVar& var, Cmp_unsigned__int32 hintId, Cmp_unsigned__int32 hintValue) __QCMP_THROW;						// Serialize variable hint.

		void alloc( CBaseVar& var ) __QCMP_THROW;																					// Alloc variable var.
		void alloc( CBaseVar& var, Cmp_unsigned__int32 regIndex ) __QCMP_THROW;														// Alloc variable var using regIndex as a register index.
		void alloc( CBaseVar& var, const CBaseReg& reg ) __QCMP_THROW;																// Alloc variable var using reg as a demanded register.
		void spill( CBaseVar& var ) __QCMP_THROW;																					// Spill variable var.
		void save( CBaseVar& var ) __QCMP_THROW;																					// Save variable var if modified.
		void unuse( CBaseVar& var ) __QCMP_THROW;																					// Unuse variable var.
		void getMemoryHome( CBaseVar& var, CGPVar* home, int* displacement = 0 );													// Get memory home of variable var.

		// Set memory home of variable var.
		// Default memory home location is on stack (ESP/RSP), but when needed the
		// bebahior can be changed by this method.
		// It is an error to chaining memory home locations. For example the given 
		// code is invalid:
		//
		// Compiler c;
		//
		// ...
		// GPVar v0 = c.newGP();
		// GPVar v1 = c.newGP();
		// GPVar v2 = c.newGP();
		// GPVar v3 = c.newGP();
		//
		// c.setMemoryHome(v1, v0, 0); // Allowed, [v0] is memory home for v1.
		// c.setMemoryHome(v2, v0, 4); // Allowed, [v0+4] is memory home for v2.
		// c.setMemoryHome(v3, v2);    // CHAINING, NOT ALLOWED!
		
		void setMemoryHome( CBaseVar& var, const CGPVar& home, int displacement = 0 );

		Cmp_unsigned__int32 getPriority( CBaseVar& var ) const __QCMP_THROW;											// Get priority of variable var.
		void setPriority( CBaseVar& var, Cmp_unsigned__int32 priority ) __QCMP_THROW;									// Set priority of variable var to priority.
		bool getSaveOnUnuse( CBaseVar& var ) const __QCMP_THROW;														// Get save-on-unuse var property.
		void setSaveOnUnuse( CBaseVar& var, bool value ) __QCMP_THROW;													// Set save-on-unuse var property to value.
		void rename( CBaseVar& var, const char* name ) __QCMP_THROW;													// Rename variable var to name. Note Only new name will appear in the logger.

		StateData* _newStateData( Cmp_unsigned__int32 memVarsCount ) __QCMP_THROW;										// Create a new StateData instance.

		// Make is convenience method to make currently serialized code and
		// return pointer to generated function.
		//
		// What you need is only to cast this pointer to your function type and call
		// it. Note that if there was an error and calling getError() method doesn't
		// return ERROR_NONE (zero) then this function always return 0 and
		// error value remains the same.
		virtual void* make() __QCMP_THROW;

		// Method that will emit everything to Assembler instance a.
		virtual void serialize() __QCMP_THROW;

		//--------------------------------------------------------------------------
		// Get target (emittable) from operand id (label id).
		inline CETarget* _getTarget( Cmp_unsigned__int32 id )
		{
			//assert((id & OPERAND_ID_TYPE_MASK) == OPERAND_ID_TYPE_LABEL);
			return m_TargetData[ id & OPERAND_ID_VALUE_MASK ];
		}

		//--------------------------------------------------------------------------
		inline nsCodeQOR::PodVector< VarData* >& getVarData( void )
		{
			return m_VarData;
		}

		//--------------------------------------------------------------------------
		inline Cmp_unsigned__int32 getEmitOptions( void )
		{
			return m_uiEmitOptions;
		}

		//--------------------------------------------------------------------------
		inline void setEmitOptions( Cmp_unsigned__int32 uiOptions )
		{
			m_uiEmitOptions = uiOptions;
		}

		//--------------------------------------------------------------------------
		inline Cx86HLAContext* getContext( void ) const __QCMP_THROW
		{
			return m_pContext;
		}

		//--------------------------------------------------------------------------
		virtual nsArch::CCPUBase* getAssembler( void ) __QCMP_THROW
		{
			return &m_CPU;
		}

		//--------------------------------------------------------------------------
		void WriteLaunchPad( byte* pFunc, byte* pLaunchPad )
		{
#if	( QOR_ARCH_WORDSIZE == 32 )
			pLaunchPad[ 0 ] = 0xE9;												//jmp
			( (Cmp_unsigned__int32*)( pLaunchPad + 1 ) )[ 0 ] = (Cmp_uint_ptr)( pFunc - ( pLaunchPad + 5 ) );	//relative address of target
			pLaunchPad[ 5 ] = 0xC3;												//ret					|
			/*
			pLaunchPad[ 0 ] = 0xFF;												//call	
			pLaunchPad[ 1 ] = 0x15;
			( (Cmp_unsigned__int32*)( pLaunchPad + 2 ) )[ 0 ] = (Cmp_uint_ptr)( pLaunchPad + 8 );	//address of target
			pLaunchPad[ 6 ] = 0xC3;												//ret					|
			( (Cmp_uint_ptr*)( pLaunchPad + 8 ) )[ 0 ] = (Cmp_uint_ptr)pFunc;	// Absolute address.   <'
			*/
#elif ( QOR_ARCH_WORDSIZE == 64 )
			pLaunchPad[ 0 ] = 0xFF;												// Jmp.			
			pLaunchPad[ 1 ] = 0x25;												// ModM (RIP addressing).			
			( (Cmp_unsigned__int32*)( pLaunchPad + 2 ) )[ 0 ] = 0;				// Offset (zero).			
			( (Cmp_uint_ptr*)( pLaunchPad + 6 ) )[ 0 ] = (Cmp_uint_ptr)pFunc;	// Absolute address.
#endif
		}

	protected:

		Cmp_unsigned__int32 m_uiError;										// Last error code.
		Cmp_unsigned__int32 m_uiProperties;									// Properties.
		Cmp_unsigned__int32 m_uiEmitOptions;								// Contains options for next emitted instruction, clear after each emit.
		Cmp_unsigned__int32 m_uiFinished;									// Whether compiler was finished the job (register allocator, etc...).
		CEFunction* m_pFunction;											// Current function.
		nsCodeQOR::PodVector< CETarget* > m_TargetData;						// Label data.
		nsCodeQOR::PodVector< VarData* > m_VarData;							// Variable data.
		int m_iVarNameId;													// Variable name id (used to generate unique names per function).
		Cx86HLAContext* m_pContext;											// Compiler context instance, only available after prepare().
		CCPU m_CPU;															// Assembler instance.

		__QCS_DECLARE_NONCOPYABLE( Cx86HLAssembler );
	};

}//nsx86
}//nsArch

#endif//ARCHQOR_X86PC_HLASSEMBLER_H_2
