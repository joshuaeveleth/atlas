
// ATLAS: Adaptable Tool Library for Advanced Simulation
//
// Copyright 2015 University of Central Florida
//
//
// This library provides many fundamental capabilities used in creating
// virtual environment simulations.  It includes elements such as vectors,
// matrices, quaternions, containers, communication schemes (UDP, TCP, DIS,
// HLA, Bluetooth), and XML processing.  It also includes some extensions
// to allow similar code to work in Linux and in Windows.  Note that support
// for iOS and Android development is also included.
//
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#ifndef AT_BLUETOOTH_H
#define AT_BLUETOOTH_H


// Because bluetooth implementations build it on top of the socket
// libraries, we can't doubly define here (or we get linking errors)
// so we will reference the networking stuff (from atNetwork.c++) here 
// and then only define Bluetooth-specific elements here (constants, etc.)
#include "atNetwork.h++"
#include "atSymbols.h++"


// Under Windows, define stuff that we need
#ifdef _MSC_VER
   #define WIN32_LEAN_AND_MEAN
   #include <bthsdpdef.h>
   #include <bluetoothapis.h>
   #include <winsock2.h>
   #include <ws2bth.h>
   #undef WIN32_LEAN_AND_MEAN

   #define AF_BLUETOOTH     AF_BTH
   #define BTPROTO_RFCOMM   BTHPROTO_RFCOMM
   #define BTPROTO_L2CAP    BTHPROTO_L2CAP

   #define bdaddr_t         BTH_ADDR

   typedef SOCKADDR_BTH   BluetoothSockAddr;

   // FUNCTIONS
   #ifdef __cplusplus
      extern "C"
      {
         ATLAS_SYM int ba2str(const bdaddr_t * btaddr, char * straddr);
         ATLAS_SYM int str2ba(const char * straddr, bdaddr_t * btaddr);
      }
   #else
      ATLAS_SYM int ba2str(const bdaddr_t * btaddr, char * straddr);
      ATLAS_SYM int str2ba(const char * straddr, bdaddr_t * btaddr);
   #endif
#elif __ANDROID__
   // Android has no Bluetooth support
#elif __IOS__
   // iOS has no Bluetooth support
#else
    #include <bluetooth/bluetooth.h>
    #include <bluetooth/rfcomm.h>
    #include <bluetooth/l2cap.h>
    #include <bluetooth/hci.h>
    #include <bluetooth/hci_lib.h>
    #include <bluetooth/sdp.h>
    #include <bluetooth/sdp_lib.h>
    #include <stdlib.h>

    typedef sockaddr_rc   BluetoothSockAddr;
#endif


// Android and iOS have no Bluetooth support
#if !defined(__ANDROID__) && !defined(__IOS__)
   typedef struct
   {
      char   address[256];
      char   name[256];
   } BluetoothDevice;
   
   
   #ifdef __cplusplus
      extern "C"
      {
         #ifdef _MSC_VER
            ATLAS_SYM int   ba2str(const bdaddr_t * btaddr, char * straddr);
            ATLAS_SYM int   str2ba(const char * straddr, bdaddr_t * btaddr);
         #endif
   
         ATLAS_SYM void   getBTDevices(BluetoothDevice * devices,
                                       u_long * maxDevices);
   
         ATLAS_SYM void   setBTAddress(BluetoothSockAddr * btAddr, 
                                       char * address, u_char channel);
         ATLAS_SYM void   getBTAddress(BluetoothSockAddr * btAddr, 
                                       char * address);
         ATLAS_SYM void   getBTChannel(BluetoothSockAddr * btAddr, 
                                       u_char * channel);
      }
   
      // These are defined in atNetwork.c++
      extern "C"
      {
         ATLAS_SYM void   initNetwork();
         ATLAS_SYM void   cleanupNetwork();
   
         ATLAS_SYM Socket   openSocket(int domain, int type, int protocol);
         ATLAS_SYM void     closeSocket(Socket socket);
   
         ATLAS_SYM void   setBlockingFlag(Socket socket, bool block);
         ATLAS_SYM bool   getBlockingFlag(Socket socket);
      }
   #else
      #ifdef _MSC_VER
         ATLAS_SYM int   ba2str(const bdaddr_t * btaddr, char * straddr);
         ATLAS_SYM int   str2ba(const char * straddr, bdaddr_t * btaddr);
      #endif
   
      ATLAS_SYM void   getBTDevices(BluetoothDevice * devices,
                                    u_long * maxDevices);
   
      ATLAS_SYM void   setBTAddress(BluetoothSockAddr * btAddr, 
                                    char * address, u_char channel);
      ATLAS_SYM void   getBTAddress(BluetoothSockAddr * btAddr, char * address);
      ATLAS_SYM void   getBTChannel(BluetoothSockAddr * btAddr, u_char * channel);
   
      // These are defined in atNetwork.c++
      extern
      {
         ATLAS_SYM void   initNetwork();
         ATLAS_SYM void   cleanupNetwork();
   
         ATLAS_SYM Socket   openSocket(int domain, int type, int protocol);
         ATLAS_SYM void     closeSocket(Socket socket);
   
         ATLAS_SYM void   setBlockingFlag(Socket socket, bool block);
         ATLAS_SYM bool   getBlockingFlag(Socket socket);
      }
   #endif
#endif


#endif

