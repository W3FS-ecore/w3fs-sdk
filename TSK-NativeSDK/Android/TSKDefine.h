//////////////////////////////////////////////////////////////////////////////
//Filename: TSKDefine.h
//Description: Basic Definition Support
//Author: ecore
/////////////////////////////////////////////////////////////////////////////
#ifndef _TSK_DEFINE_H
#define _TSK_DEFINE_H

/////////////////////////////////////////////
//The following macros need to be defined in the project using TSK according to the needs of your project
/////////////////////////////////////////////
//--------------------------------------
//Define the environment: Use one of the following as needed.
//--------------------------------------
//Kernel layer environment, use TSK in the kernel layer should enable the macro, otherwise disable the macro
//#define __KERNEL  1
//Application layer environment, use TSK in the application layer should enable the macro, otherwise disable the macro
#define __APPLICATION  1 
//Macro defining whether a kernel connection is required
#define TSK_WITH_NOKERNEL  1


/////////////////////////////////////////////
//Define memory management support macros: use different support for different environments
/////////////////////////////////////////////
#ifdef _WIN32
//Define the tag for memory allocation: only one copy of memory for the whole project, usually a single instance of the object
#define POOLTAG_SINGLE 'TSK1'
//Define tag:generic tag for memory allocation
#define POOLTAG_TSK 'TSKn'
#ifdef __APPLICATION
//Memory allocation: MemType is the specified memory type, MemLen is the specified number of allocated bytes, and MemTag is the specified memory block label.
#define __mem_malloc(MemType,MemLen,MemTag)  (malloc(MemLen))
//Memory release:MemPointer is a pointer to the memory block to be released
#define __mem_free(MemPointer) (free(MemPointer))

//Memory management functions needed for the algorithm part
#define KAlgo_malloc(nLen)  (malloc(nLen))
#define KAlgo_free(p) (free(p))
#define KAlgo_calloc(nLen)  (calloc(nLen))
#define KAlgo_realloc(p,nOldLen,nNewLen) (realloc(p,nNewLen))
#endif
#ifdef __KERNEL
//Aligned memory allocation: Inst is the aligned instance, MemType is the specified memory type, MemLen is the specified number of bytes allocated, and MemTag is the specified memory block label
#define __mem_align_malloc(Inst,MemType,MemLen,MemTag)  (FltAllocatePoolAlignedWithTag((Inst),(MemType),(MemLen),(MemTag)))
//Aligned memory release: Inst is the aligned instance, p is the pointer to the memory block to be released, and MemTag is the specified memory block tag
#define __mem_align_free(Inst,p,MemTag) FltFreePoolAlignedWithTag((Inst),(p),(MemTag))
//Reallocate the aligned memory after it is freed (the old memory will not be copied): p is the memory pointer to be reallocated, Inst is the aligned instance, Type is the specified memory type, Len is the specified number of bytes to be allocated, Tag is the specified memory block label
#define __mem_align_realloc(p,Inst,MemType,MemLen,MemTag) ((p)?__mem_align_free((Inst),(p),(MemTag)):0,__mem_align_malloc((Inst),(MemType),(MemLen),(MemTag)))
//Memory allocation: MemType is the specified memory type, MemLen is the specified number of allocated bytes, and MemTag is the specified memory block label.
#define __mem_malloc(MemType,MemLen,MemTag)  (ExAllocatePoolWithTag((MemType),(MemLen),(MemTag)))
//Memory release:p is a pointer to the memory block to be released
#define __mem_free(p) ExFreePool((p))

//Memory management functions needed for the algorithm part
#ifdef __cplusplus
extern "C"
#endif
void* __stdcall KAlgo_malloc(int nLen);
#ifdef __cplusplus
extern "C"
#endif
void __stdcall KAlgo_free(void* p);
#ifdef __cplusplus
extern "C"
#endif
void* __stdcall KAlgo_calloc(int nLen);
#ifdef __cplusplus
extern "C"
#endif
void* __stdcall KAlgo_realloc(void* p, int nOldLen, int nNewLen);
#endif
#else
//Memory allocation: MemType is the specified memory type, MemLen is the specified number of allocated bytes, and MemTag is the specified memory block label.
#define __mem_malloc(MemType,MemLen,MemTag)  (malloc(MemLen))
//Memory release:MemPointer is a pointer to the memory block to be released
#define __mem_free(MemPointer) (free(MemPointer))

//Memory management functions needed for the algorithm part
#define KAlgo_malloc(nLen)  (malloc(nLen))
#define KAlgo_free(p) (free(p))
#define KAlgo_calloc(nLen)  (calloc(nLen))
#define KAlgo_realloc(p,nOldLen,nNewLen) (realloc(p,nNewLen))
#endif

#endif