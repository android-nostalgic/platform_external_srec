/*---------------------------------------------------------------------------*
 *  WorkerQueueFactory.cpp                                                   *
 *                                                                           *
 *  Copyright 2007, 2008 Nuance Communciations, Inc.                               *
 *                                                                           *
 *  Licensed under the Apache License, Version 2.0 (the 'License');          *
 *  you may not use this file except in compliance with the License.         *
 *                                                                           *
 *  You may obtain a copy of the License at                                  *
 *      http://www.apache.org/licenses/LICENSE-2.0                           *
 *                                                                           *
 *  Unless required by applicable law or agreed to in writing, software      *
 *  distributed under the License is distributed on an 'AS IS' BASIS,        *
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. *
 *  See the License for the specific language governing permissions and      *
 *  limitations under the License.                                           *
 *                                                                           *
 *---------------------------------------------------------------------------*/


//Memory leak detection
#if defined(_DEBUG) && defined(_WIN32)
#include "crtdbg.h"
#define new new( _CLIENT_BLOCK, __FILE__, __LINE__)
#endif

#ifdef UAPI_WIN32
// Do not warn on "while(true)"
#  pragma warning (disable: 4127)
#endif

#include "WorkerQueueFactory.h"


namespace android
{
  namespace speech
  {
    namespace recognition
    {
      namespace utilities
      {
        WorkerQueueFactory::WorkerQueueFactory()
        {}
        
        WorkerQueueFactory::~WorkerQueueFactory()
        {}
      }
    }
  }
}
