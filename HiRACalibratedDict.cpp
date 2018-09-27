// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME HiRACalibratedDict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "HiRACalibratedRootEvent.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_HiRACalibratedData(void *p = 0);
   static void *newArray_HiRACalibratedData(Long_t size, void *p);
   static void delete_HiRACalibratedData(void *p);
   static void deleteArray_HiRACalibratedData(void *p);
   static void destruct_HiRACalibratedData(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::HiRACalibratedData*)
   {
      ::HiRACalibratedData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::HiRACalibratedData >(0);
      static ::ROOT::TGenericClassInfo 
         instance("HiRACalibratedData", ::HiRACalibratedData::Class_Version(), "HiRACalibratedRootEvent.h", 8,
                  typeid(::HiRACalibratedData), DefineBehavior(ptr, ptr),
                  &::HiRACalibratedData::Dictionary, isa_proxy, 4,
                  sizeof(::HiRACalibratedData) );
      instance.SetNew(&new_HiRACalibratedData);
      instance.SetNewArray(&newArray_HiRACalibratedData);
      instance.SetDelete(&delete_HiRACalibratedData);
      instance.SetDeleteArray(&deleteArray_HiRACalibratedData);
      instance.SetDestructor(&destruct_HiRACalibratedData);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::HiRACalibratedData*)
   {
      return GenerateInitInstanceLocal((::HiRACalibratedData*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::HiRACalibratedData*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_HiRACalibratedBuffer(void *p = 0);
   static void *newArray_HiRACalibratedBuffer(Long_t size, void *p);
   static void delete_HiRACalibratedBuffer(void *p);
   static void deleteArray_HiRACalibratedBuffer(void *p);
   static void destruct_HiRACalibratedBuffer(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::HiRACalibratedBuffer*)
   {
      ::HiRACalibratedBuffer *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::HiRACalibratedBuffer >(0);
      static ::ROOT::TGenericClassInfo 
         instance("HiRACalibratedBuffer", ::HiRACalibratedBuffer::Class_Version(), "HiRACalibratedRootEvent.h", 48,
                  typeid(::HiRACalibratedBuffer), DefineBehavior(ptr, ptr),
                  &::HiRACalibratedBuffer::Dictionary, isa_proxy, 4,
                  sizeof(::HiRACalibratedBuffer) );
      instance.SetNew(&new_HiRACalibratedBuffer);
      instance.SetNewArray(&newArray_HiRACalibratedBuffer);
      instance.SetDelete(&delete_HiRACalibratedBuffer);
      instance.SetDeleteArray(&deleteArray_HiRACalibratedBuffer);
      instance.SetDestructor(&destruct_HiRACalibratedBuffer);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::HiRACalibratedBuffer*)
   {
      return GenerateInitInstanceLocal((::HiRACalibratedBuffer*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::HiRACalibratedBuffer*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr HiRACalibratedData::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *HiRACalibratedData::Class_Name()
{
   return "HiRACalibratedData";
}

//______________________________________________________________________________
const char *HiRACalibratedData::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HiRACalibratedData*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int HiRACalibratedData::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HiRACalibratedData*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *HiRACalibratedData::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HiRACalibratedData*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *HiRACalibratedData::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HiRACalibratedData*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr HiRACalibratedBuffer::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *HiRACalibratedBuffer::Class_Name()
{
   return "HiRACalibratedBuffer";
}

//______________________________________________________________________________
const char *HiRACalibratedBuffer::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HiRACalibratedBuffer*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int HiRACalibratedBuffer::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HiRACalibratedBuffer*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *HiRACalibratedBuffer::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HiRACalibratedBuffer*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *HiRACalibratedBuffer::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HiRACalibratedBuffer*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void HiRACalibratedData::Streamer(TBuffer &R__b)
{
   // Stream an object of class HiRACalibratedData.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(HiRACalibratedData::Class(),this);
   } else {
      R__b.WriteClassBuffer(HiRACalibratedData::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_HiRACalibratedData(void *p) {
      return  p ? new(p) ::HiRACalibratedData : new ::HiRACalibratedData;
   }
   static void *newArray_HiRACalibratedData(Long_t nElements, void *p) {
      return p ? new(p) ::HiRACalibratedData[nElements] : new ::HiRACalibratedData[nElements];
   }
   // Wrapper around operator delete
   static void delete_HiRACalibratedData(void *p) {
      delete ((::HiRACalibratedData*)p);
   }
   static void deleteArray_HiRACalibratedData(void *p) {
      delete [] ((::HiRACalibratedData*)p);
   }
   static void destruct_HiRACalibratedData(void *p) {
      typedef ::HiRACalibratedData current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::HiRACalibratedData

//______________________________________________________________________________
void HiRACalibratedBuffer::Streamer(TBuffer &R__b)
{
   // Stream an object of class HiRACalibratedBuffer.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(HiRACalibratedBuffer::Class(),this);
   } else {
      R__b.WriteClassBuffer(HiRACalibratedBuffer::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_HiRACalibratedBuffer(void *p) {
      return  p ? new(p) ::HiRACalibratedBuffer : new ::HiRACalibratedBuffer;
   }
   static void *newArray_HiRACalibratedBuffer(Long_t nElements, void *p) {
      return p ? new(p) ::HiRACalibratedBuffer[nElements] : new ::HiRACalibratedBuffer[nElements];
   }
   // Wrapper around operator delete
   static void delete_HiRACalibratedBuffer(void *p) {
      delete ((::HiRACalibratedBuffer*)p);
   }
   static void deleteArray_HiRACalibratedBuffer(void *p) {
      delete [] ((::HiRACalibratedBuffer*)p);
   }
   static void destruct_HiRACalibratedBuffer(void *p) {
      typedef ::HiRACalibratedBuffer current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::HiRACalibratedBuffer

namespace {
  void TriggerDictionaryInitialization_HiRACalibratedDict_Impl() {
    static const char* headers[] = {
"HiRACalibratedRootEvent.h",
0
    };
    static const char* includePaths[] = {
"./include",
"./Nuclear_Masses",
"./HTRunInfo",
"/mnt/misc/sw/x86_64/Debian/8/root/gnu/6.04.02/include/root",
"/projects/hira/zhukuan/E15190/GitHub_E15190-Unified-Analysis-Framework/E15190-Unified-Analysis-Framework/",
0
    };
    static const char* fwdDeclCode = 
R"DICTFWDDCLS(
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$HiRACalibratedRootEvent.h")))  HiRACalibratedData;
class __attribute__((annotate("$clingAutoload$HiRACalibratedRootEvent.h")))  HiRACalibratedBuffer;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "HiRACalibratedRootEvent.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"HiRACalibratedBuffer", payloadCode, "@",
"HiRACalibratedData", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("HiRACalibratedDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_HiRACalibratedDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_HiRACalibratedDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_HiRACalibratedDict() {
  TriggerDictionaryInitialization_HiRACalibratedDict_Impl();
}
