# $Id: setup.py,v 1.6 2003/10/24 19:12:05 jkohen Exp $

from distutils.core import setup, Extension
import sys, os

PACKAGE_NAME = 'pcapy'

# You might want to change these to reflect your specific configuration
include_dirs = []
library_dirs = []
libraries = []

if sys.platform =='win32':
    # VC include files
    include_dirs.append(r'F:\Program Files\Microsoft Visual Studio\VC98\include')
    # WinPcap include files
    include_dirs.append(r'F:\softdown\wpdpack\Include')
    # WinPcap library files
    library_dirs.append(r'F:\softdown\wpdpack\Lib')
    libraries = ['wpcap', 'packet', 'ws2_32']
else:
    libraries = ['pcap']


# end of user configurable parameters
macros = []
sources = ['pcapdumper.cc',
           'pcapy.cc',
           'pcapobj.cc',
           'pcap_pkthdr.cc',
           'bpfobj.cc',
           ]

if sys.platform == 'win32':
    sources.append(os.path.join('win32', 'findalldevs.cc'))
    sources.append(os.path.join('win32', 'dllmain.cc'))
    macros.append(('WIN32', '1'))


setup(name = PACKAGE_NAME,
      version = "0.10.2",
      url = "http://oss.coresecurity.com/pcapy",
      author = "Maximiliano Caceres",
      author_email = "max@coresecurity.com",
      maintainer = "Javier Kohen",
      maintainer_email = "jkohen@coresecurity.com",
      description = "Python pcap extension",
      ext_modules = [Extension(
          name = PACKAGE_NAME,
          sources = sources,
          define_macros = macros,
          include_dirs = include_dirs,
          library_dirs = library_dirs,
          libraries = libraries)],
      data_files = [(os.path.join('share', 'doc', PACKAGE_NAME),
                     ['README', 'LICENSE', 'pcapy.html'])],
      )

