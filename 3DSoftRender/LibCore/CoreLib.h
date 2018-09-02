#ifndef CORE_LIB_H
#define CORE_LIB_H
#pragma warning(disable : 4996)

#pragma warning(disable : 4251)

#ifdef _DEBUG
#define HKR_USE_ASSERT
#define HKR_USE_ASSERT_WRITE_TO_OUTPUT_WINDOW
#define HKR_USE_ASSERT_WRITE_TO_MESSAGE_BOX

#endif

#ifdef _DEBUG
#define WM5_FILEIO_VALIDATE_OPERATION
#define WM5_BUFFERIO_VALIDATE_OPERATION
#endif

#define UNUSED(variable) (void)variable

#ifdef ENABLE_BOOST
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH
#include <boost/math/special_functions/round.hpp>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
namespace fs = boost::filesystem;

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/signals2.hpp>
#include <boost/any.hpp>

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_wiarchive.hpp>
#include <boost/archive/xml_woarchive.hpp>
#include <boost/serialization/vector.hpp>
#endif

#ifdef ENABLE_ASSIMP
// Assimp
#include <assimp/DefaultLogger.hpp>
#include <assimp/importer.hpp>
#include <assimp/Exporter.hpp>
#include <assimp/ProgressHandler.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/mesh.h>

#pragma comment(lib, "assimp.lib")
#endif

// FreeImage
#ifdef FREEIMAGE_LIB // Static linking
#include <FreeImage.h>

#pragma comment(lib, "FreeImageLib.lib")
#endif
#endif
