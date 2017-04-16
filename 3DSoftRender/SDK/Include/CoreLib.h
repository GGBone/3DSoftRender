#ifndef CORELIB_H
#define CORELIB_H

#include <climits>
#include <stdint.h>

//Standard library headers
#include <cassert>
#include <cctype>
#include <cfloat>
#include <climits>
#include <cmath>
#include <cstring>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>


// Common STL headers.
#include <algorithm>
#include <deque>
#include <functional>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>

#include <Windows.h>
#define UNUSED(variable) (void)variable
//
//#include <boost/uuid/uuid.hpp>
//#include <boost/uuid/uuid_generators.hpp>
//
//#include <boost/foreach.hpp>
//#define foreach BOOST_FOREACH
//#include <boost/math/special_functions/round.hpp>
//
//#include <boost/filesystem.hpp>
//#include <boost/filesystem/fstream.hpp>
//namespace fs = boost::filesystem;
//
//#include <boost/bind.hpp>
//#include <boost/function.hpp>
//#include <boost/signals2.hpp>
//#include <boost/any.hpp>

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_wiarchive.hpp>
#include <boost/archive/xml_woarchive.hpp>
#include <boost/serialization/vector.hpp>


// Assimp
#include <assimp/DefaultLogger.hpp>
#include <assimp/importer.hpp>
#include <assimp/Exporter.hpp>
#include <assimp/ProgressHandler.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/mesh.h>

//#pragma comment(lib, "assimp.lib")

// FreeImage
#define FREEIMAGE_LIB // Static linking
#include <FreeImage.h>

//#pragma comment(lib, "FreeImageLib.lib")

#endif