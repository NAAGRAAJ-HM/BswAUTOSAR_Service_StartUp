/******************************************************************************/
/* File   : StartUp.cpp                                                       */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Module.hpp"
#include "CfgStartUp.hpp"
#include "StartUp_core.hpp"
#include "infStartUp_Exp.hpp"
#include "infStartUp_Imp.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define STARTUP_AR_RELEASE_VERSION_MAJOR                                       4
#define STARTUP_AR_RELEASE_VERSION_MINOR                                       3

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/
#if(STARTUP_AR_RELEASE_VERSION_MAJOR != STD_AR_RELEASE_VERSION_MAJOR)
   #error "Incompatible STARTUP_AR_RELEASE_VERSION_MAJOR!"
#endif

#if(STARTUP_AR_RELEASE_VERSION_MINOR != STD_AR_RELEASE_VERSION_MINOR)
   #error "Incompatible STARTUP_AR_RELEASE_VERSION_MINOR!"
#endif

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
class module_StartUp:
      INTERFACES_EXPORTED_STARTUP
      public abstract_module
   ,  public class_StartUp_Functionality
{
   private:
/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
            Std_TypeReturn          IsInitDone{E_NOT_OK};
      const CfgModule_TypeAbstract* lptrCfg{(CfgModule_TypeAbstract*)NULL_PTR};

   public:
      module_StartUp(Std_TypeVersionInfo lVersionInfo) : abstract_module(lVersionInfo){
      }
      FUNC(void, STARTUP_CODE) InitFunction(
         CONSTP2CONST(CfgModule_TypeAbstract, STARTUP_CONFIG_DATA, STARTUP_APPL_CONST) lptrCfgModule
      );
      FUNC(void, STARTUP_CODE) DeInitFunction (void);
      FUNC(void, STARTUP_CODE) MainFunction   (void);
      STARTUP_CORE_FUNCTIONALITIES
};

extern VAR(module_StartUp, STARTUP_VAR) StartUp;

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/
CONSTP2VAR(infEcuMClient, STARTUP_VAR, STARTUP_CONST) gptrinfEcuMClient_StartUp = &StartUp;
CONSTP2VAR(infDcmClient,  STARTUP_VAR, STARTUP_CONST) gptrinfDcmClient_StartUp  = &StartUp;
CONSTP2VAR(infSchMClient, STARTUP_VAR, STARTUP_CONST) gptrinfSchMClient_StartUp = &StartUp;

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
VAR(module_StartUp, STARTUP_VAR) StartUp(
   {
#if(STD_ON == _ReSIM)
         "StartUp",
#else
#endif
         STARTUP_AR_RELEASE_VERSION_MAJOR
      ,  STARTUP_AR_RELEASE_VERSION_MINOR
      ,  0x00
      ,  0xFF
      ,  0x01
      ,  '0'
      ,  '1'
      ,  '0'
   }
);

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
FUNC(void, STARTUP_CODE) module_StartUp::InitFunction(
   CONSTP2CONST(CfgModule_TypeAbstract, STARTUP_CONFIG_DATA, STARTUP_APPL_CONST) lptrCfgModule
){
#if(STD_ON == StartUp_InitCheck)
   if(
         E_OK
      != IsInitDone
   ){
#endif
      if(NULL_PTR != lptrCfgModule){
         if(STD_HIGH){
            lptrCfg = lptrCfgModule;
         }
         else{
            lptrCfg = &PBcfgStartUp;
         }
      }
      else{
#if(STD_ON == StartUp_DevErrorDetect)
         Det_ReportError(
               0 //TBD: IdModule
            ,  0 //TBD: IdInstance
            ,  0 //TBD: IdApi
            ,  0 //TBD: IdError
         );
#endif
      }
#if(STD_ON == StartUp_InitCheck)
      IsInitDone = E_OK;
   }
   else{
#if(STD_ON == StartUp_DevErrorDetect)
      Det_ReportError(
            0 //TBD: IdModule
         ,  0 //TBD: IdInstance
         ,  0 //TBD: IdApi
         ,  STARTUP_E_UNINIT
      );
#endif
   }
#endif
}

FUNC(void, STARTUP_CODE) module_StartUp::DeInitFunction(void){
#if(STD_ON == StartUp_InitCheck)
   if(
         E_OK
      == IsInitDone
   ){
#endif
#if(STD_ON == StartUp_InitCheck)
      IsInitDone = E_NOT_OK;
   }
   else{
#if(STD_ON == StartUp_DevErrorDetect)
      Det_ReportError(
            0 //TBD: IdModule
         ,  0 //TBD: IdInstance
         ,  0 //TBD: IdApi
         ,  STARTUP_E_UNINIT
      );
#endif
   }
#endif
}

FUNC(void, STARTUP_CODE) module_StartUp::MainFunction(void){
#if(STD_ON == StartUp_InitCheck)
   if(
         E_OK
      == IsInitDone
   ){
#endif
#if(STD_ON == StartUp_InitCheck)
   }
   else{
#if(STD_ON == StartUp_DevErrorDetect)
      Det_ReportError(
            0 //TBD: IdModule
         ,  0 //TBD: IdInstance
         ,  0 //TBD: IdApi
         ,  STARTUP_E_UNINIT
      );
#endif
   }
#endif
}

typedef enum{
      E_SHUTDOWN_NORMAL
   ,  E_SHUTDOWN_ABNORMAL
}t_Shutdown;

t_Shutdown e_Shutdown = E_SHUTDOWN_NORMAL;

#include "infEcuM_StartUp.hpp"

#if(STD_ON == _ReSIM)
#include <iostream>
using namespace std;
#else
#endif

int main(
#if(STD_ON == _ReSIM)
      int   argc
   ,  char* argv[]
#else
   void
#endif
){
#if(STD_ON == _ReSIM)
   if(0 >= argc){
      cout<<"USAGE: TBD"<<endl;
   }
   else{
      cout<<endl<<argv[0]<<" Version: R"<<STARTUP_AR_RELEASE_VERSION_MAJOR<<"."<<STARTUP_AR_RELEASE_VERSION_MINOR;
   }
#else
#endif

   gptrinfEcuM_StartUp->InitFunction();

   return e_Shutdown;
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

