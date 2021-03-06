# Voxel

This is the main repository for Voxel software. It contains general purpose
functionality that is used in other, more specific, Voxel libraries. Most code 
in this library is code which was initially implemented for a specific purpose, but was then brought here as it's likely useful in multiple places.

## Installation

Voxel uses Cmake for installation. Some of the applications in the ```apps/```
directory are used to generate output which can be parsed by Cmake to generate
definitions which are used to generate ```constexpr``` functions. If Voxel is
not already installed, then the application binaries will not be found. When
installing Voxel for the first time, the installation script compiles
the ```SystemInformation``` application so that the information can be added into the C++ source code.

### Linux or OSX

The following are the most basic options for installation:

| Variable             | Description                       | Options       |
|:---------------------|:----------------------------------|:--------------|
| CMAKE_BUILD_TYPE     | The build type                    | Debug/Release |
| CMAKE_INSTALL_PREFIX | Path to install directory         | User defined  |
| BUILD_SHARED_LIBS    | Build libraries as shared         | ON/NONE	   |

__Note:__ The build script automatically appends ```Voxel``` to
	        to ```CMAKE_INSTALL_PREFIX``` if it __is not__ part of the variable. So ```-DCMAKE_INSTALL_PREFIX=/opt``` will install all software
          to ```/opt/Voxel```. If ```Voxel``` __is__ found in the
	        the ```CMAKE_INSTALL_PREFIX``` variable then the build script
          __does not__ modify the variable, and it is used __as is__. For
          example, ```-DCMAKE_INSTALL_PREFIX=/opt```
          and ```-DCMAKE_INSTALL_PREFIX=/opt/Voxel```will both install
          to ```/opt/Voxel```.

To build Voxel with __static__ libraries:

~~~py
# From the root directory:
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release  \
      -DCMAKE_INSTALL_PREFIX=/opt \
      ..
sudo make install
~~~

To build Voxel with __shared__ libraries:

~~~py
# From the root directory:
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release  \
      -DCMAKE_INSTALL_PREFIX=/opt \
      -DBUILD_SHARED_LIBS=BOOL:ON \
      ..
sudo make install
~~~

Which will install the library to ```/opt/Voxel```, after
which ```make {component}``` will make any of the components.

## CMake FindPackage

When installing Voxel, a VoxelConfig.cmake file is generated and installed
in ```CMAKE_INSTALL_PREFIX/lib/cmake/Voxel```, which allows other libraries to 
use Voxel. To ensure that the VoxelConfig.cmake package is found, either make
sure that Voxel is installed somewhere on the ``CMAKE_INSTALL_PREFIX`` path,
for example (when building the library using voxel):

~~~cmake
cmake -DCMAKE_INSTALL_PREFIX=/opt ..
~~~

if Voxel is installed at ``/opt/Voxel``. Alternatively, you can explicity add
the installation prefix for Voxel to the to the ```CMAKE_PREFIX_PATH```
variable in the CMakeLists.txt file before calling ``find_package``. For
example:

~~~cmake
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH} VOXEL_INSTALL_PREFIX")
find_package(Voxel)
~~~

to allow CMake to find Voxel, where ```VOXEL_INSTALL_PREFIX``` is the
installation prefix for Voxel. 

Voxel's configuration file defines the following variables after
calling ```find_package```:

| Variable             | Description                                              |
|:---------------------|:---------------------------------------------------------|
| Voxel_INCLUDE_DIRS   | The include directories for compilation               |
| Voxel_LIBRARIES      | All of the voxel libraries to link                    |
| Voxel_LIBS           | Only libraries corresponding to those used with COMPONENTS with cmake ```find_package```                                       |
| Voxel_DEFINITIONS    | Required compiler definitions for Voxel               |
| Voxel_CMAKE_DIR      | The directory where Voxel's CMake packages are installed.                                                                     |
| Voxel_CUDA_SUPPORT   | If cuda is supported on the system and Voxel has been built with support for cuda                                                    |

The following is a list of definitions added by Voxel:

| Definition          | Description                   | Defined in Source Code |
|:--------------------|:------------------------------|:-----------------------|
| -DVoxxCudaSupported | If cuda is supported by the system   | Yes |
| -std=c++1z          | Support for C++17                    | No  |
| -O3                 | Aggressive optimization              | No  |
| --cuda-path={PATH}  | Path to cuda in system, if installed | No  |
| --cude-gpu-arch={arch} | GPU architecture version          | No  |

__Note__: Voxel will search for cuda and add the apropriate flags, include
           and link directories, and libraries for cuda. Thus, when using Voxel
          via ``find_package(Voxel)``, if the system supports cuda, then
          anything which uses voxel will be compiled with cuda support.

### Linking

Assuming that ```find_packge(Voxel ...)``` has been run, to link against a
single library from cmake, simple do (see list of components below):

~~~
target_link_libraries(Target Voxx::ComponentName)
~~~

where ```ComponentName``` is the component to link against. Alternatively,
to link against numerous components, list the components when
using ```find_package```:

~~~
find_package(Voxel COMPONENTS SystemInfo Thread)
~~~

which populates the ```Voxel_LIBS``` cmake variable with the appropriate library
definitions. A target can then be linked as follows:

~~~
target_link_libraries(Target ${Voxel_LIBS})
~~~

Finally, to link against all the Voxel libraries, use ```Voxel_LIBRARIES```:

~~~
target_link_libraries(Target ${Voxel_LIRARIES})
~~~

## Components

Components are the header files and built libraries that the part of the Voxel
repository. Using them is as simple as including the relevant header
from ```include/Voxel/Component``` and linking against the library, if there is one (as shown above).

### System Info

The system information component (at ```include/Voxel/SystemInfo/```)
defines cross-platform functionality to get information for various components
of the system (such as cpu info, gpu info, etc). The component can be linked
with ```Voxx::SystemInfo``` or through ```find_package```:

~~~
# Find SystemInfo:
find_package(Voxel COMPONENTS SystemInfo)
...

# Link target with SystemInfo:
target_link_libraries(Target Voxx::SystemInfo)
~~~

### Thread

The thread component (at ``include/Voxel/Thread``) provides general purpose
thread related functionality (like thread binding etc). It can be linked
with ``Voxx::Thread`` or through ``find_package``:

~~~
# Find SystemInfo:
find_package(Voxel COMPONENTS Thread)
...

# Link target with SystemInfo:
target_link_libraries(Target Voxx::Thread)
~~~

## Applications

Voxel provides numerous applications as binaries, they can be built using

~~~sh
make ApplicationName
~~~

after running Cmake as shown above.

### System Information

The system information component application (```bin/SystemInformation``` after
installation) displays the system information to the console. Example output
is the following:

~~~
|==--- Cpu Features: --------------------------------------------------------==|
| Cores                     :                                                4 |
| Threads                   :                                                8 |
| Threads Per Core          :                                                2 |
| Hyperthreading            :                                                1 |
| MMX     Instructions      :                                                1 |
| AES     Instructions      :                                                1 |
| SSE     Instructions      :                                                1 |
| SSE2    Instructions      :                                                1 |
| SSE3    Instructions      :                                                1 |
| SSSE3   Instructions      :                                                1 |
| SSE41   Instructions      :                                                1 |
| SSE42   Instructions      :                                                1 |
| AVX     Instructions      :                                                1 |
| AVX2    Instructions      :                                                1 |
| AVX512F Instructions      :                                                0 |
|==--- Thread Information: --------------------------------------------------==|
| APIC ID                   :                                                0 |
| Package Number            :                                                0 |
| Core    Number            :                                                0 |
| Thread  Number            :                                                0 |
|==--------------------------------------------------------------------------==|
| APIC ID                   :                                                2 |
| Package Number            :                                                0 |
| Core    Number            :                                                1 |
| Thread  Number            :                                                0 |
|==--------------------------------------------------------------------------==|
| APIC ID                   :                                                4 |
| Package Number            :                                                0 |
| Core    Number            :                                                2 |
| Thread  Number            :                                                0 |
|==--------------------------------------------------------------------------==|
| APIC ID                   :                                                6 |
| Package Number            :                                                0 |
| Core    Number            :                                                3 |
| Thread  Number            :                                                0 |
|==--------------------------------------------------------------------------==|
| APIC ID                   :                                                1 |
| Package Number            :                                                0 |
| Core    Number            :                                                0 |
| Thread  Number            :                                                1 |
|==--------------------------------------------------------------------------==|
| APIC ID                   :                                                3 |
| Package Number            :                                                0 |
| Core    Number            :                                                1 |
| Thread  Number            :                                                1 |
|==--------------------------------------------------------------------------==|
| APIC ID                   :                                                5 |
| Package Number            :                                                0 |
| Core    Number            :                                                2 |
| Thread  Number            :                                                1 |
|==--------------------------------------------------------------------------==|
| APIC ID                   :                                                7 |
| Package Number            :                                                0 |
| Core    Number            :                                                3 |
| Thread  Number            :                                                1 |
|==--- Cache Information: ---------------------------------------------------==|
| Type                      :                                             Data |
| Level                     :                                                1 |
| Cores per Package         :                                                8 |
| Max Thread Sharing        :                                                2 |
| Size (kB)                 :                                               32 |
| Line Size (B)             :                                               64 |
| Partitions                :                                                1 |
| Associativity             :                                                8 |
| Sets                      :                                               64 |
|==--------------------------------------------------------------------------==|
| Type                      :                                      Instruction |
| Level                     :                                                1 |
| Cores per Package         :                                                8 |
| Max Thread Sharing        :                                                2 |
| Size (kB)                 :                                               32 |
| Line Size (B)             :                                               64 |
| Partitions                :                                                1 |
| Associativity             :                                                8 |
| Sets                      :                                               64 |
|==--------------------------------------------------------------------------==|
| Type                      :                                          Unified |
| Level                     :                                                2 |
| Cores per Package         :                                                8 |
| Max Thread Sharing        :                                                2 |
| Size (kB)                 :                                              256 |
| Line Size (B)             :                                               64 |
| Partitions                :                                                1 |
| Associativity             :                                                4 |
| Sets                      :                                             1024 |
|==--------------------------------------------------------------------------==|
| Type                      :                                          Unified |
| Level                     :                                                3 |
| Cores per Package         :                                                8 |
| Max Thread Sharing        :                                               16 |
| Size (kB)                 :                                             8192 |
| Line Size (B)             :                                               64 |
| Partitions                :                                                1 |
| Associativity             :                                               16 |
| Sets                      :                                             8192 |
|==--------------------------------------------------------------------------==|
~~~

## Licensing

This librarry is licensed under the MIT license, and is completely free -- you
may do whatever you like with it =)

