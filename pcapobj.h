/*
 * Copyright (c) 2003 CORE Security Technologies
 *
 * This software is provided under under a slightly modified version
 * of the Apache Software License. See the accompanying LICENSE file
 * for more information.
 *
 * $Id: pcapobj.h,v 1.3 2003/10/23 20:00:53 jkohen Exp $
 */

#ifndef __pcapobj__
#define __pcapobj__


PyObject*
new_pcapobject(pcap_t *pcap, bpf_u_int32 net, bpf_u_int32 mask);

extern PyTypeObject Pcaptype;

#endif /* __pcapobj__ */
