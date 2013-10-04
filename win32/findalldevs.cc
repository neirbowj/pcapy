/*
 * Copyright (c) 2003 CORE Security Technologies
 *
 * This software is provided under under a slightly modified version
 * of the Apache Software License. See the accompanying LICENSE file
 * for more information.
 *
 * Enumerate interfaces in Windows. Taken from WinPcap dev pack
 * examples for compatibility with WinPcap 2.3.
 *
 * $Id: findalldevs.cc,v 1.2 2003/10/23 20:00:54 jkohen Exp $
 */

#include <packet32.h>
#include <Python.h>

#define MAX_NUM_ADAPTERS 10

extern PyObject *PcapError;


PyObject*
findalldevs(PyObject* self, PyObject* args)
{
  PyObject* tuple;
  ULONG		AdapterLength=4096;

  DWORD dwVersion;
  DWORD dwWindowsMajorVersion;

  //unicode strings (winnt)
  WCHAR		AdapterName[8192]; //  a list of the network adapters
  WCHAR		*temp;

  //ascii strings (win95)
  char		AdapterNamea[8192]; //  a list of the network adapters
  char		*tempa;

  memset(AdapterName, 0, sizeof(AdapterName));
  // data returned by PacketGetAdapterNames is different in Win95 and in WinNT.
  // We have to check the os on which we are running
  dwVersion=GetVersion();
  dwWindowsMajorVersion =  (DWORD)(LOBYTE(LOWORD(dwVersion)));
  if (!(dwVersion >= 0x80000000 && dwWindowsMajorVersion >= 4))
    {  // Windows NT
      if(PacketGetAdapterNames((char*)&AdapterName,&AdapterLength)==FALSE){
	PyErr_SetString(PcapError, "Unable to retrieve the list of valid adapters!");
	return NULL;
      }
		
      temp=AdapterName;
      if(*temp==NULL)
	{
	  PyErr_SetString(PcapError, "No valid interfaces to open");
	  return NULL;	
	}  

      tuple = PyList_New(0);
      while(*temp)
	{
	  PyList_Append(tuple, Py_BuildValue("u", temp));
	  while(*temp) temp++;
	  temp++;
	}
    }
  
  else	//windows 95
    {
      if(PacketGetAdapterNames(AdapterNamea,&AdapterLength)==FALSE){
	PyErr_SetString(PcapError, "Unable to retrieve the list of valid adapters!");
	return NULL;
      }
      tempa=(char*)&AdapterName;
      if(*tempa==NULL)
	{
	  PyErr_SetString(PcapError, "No valid interfaces to open");
	  return NULL;	
	}  

      tuple = PyList_New(0);
      while(*tempa)
	{
	  PyList_Append(tuple, Py_BuildValue("s", tempa));
	  while(*tempa) tempa++;
	  tempa++;
	}
    }

  return tuple;
}

