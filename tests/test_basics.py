#!/usr/bin/env python

import unittest
import pcapy

__doc__ = """
    Unit test suite for basic pcapy capabilities

    Note: If the user has insufficient permission on any capture
    devices, tests that interact with them will probably fail. It is
    not the fault of the library or the bindings.

    TODO: Make some tests conditional, when possible.
"""

class TestBasics(unittest.TestCase):
    "Performs sanity checks on the core API"

    def test_have_default_device(self):
        "lookupdev() returns a non-empty string"

        defaultdev = pcapy.lookupdev()
        self.assertIsInstance(defaultdev, str)
        self.assertNotEqual(defaultdev, "")


    def test_alldevs(self):
        "findalldevs() returns a list of strings including the default device"

        # the return value of this call is a list
        alldevs = pcapy.findalldevs()
        self.assertIsInstance(alldevs, list)

        # each member of the list is a string
        for devname in alldevs:
            self.assertIsInstance(devname, str)

        # the default device is one of all the devices
        defaultdev = pcapy.lookupdev()
        self.assertIn(defaultdev, alldevs)
