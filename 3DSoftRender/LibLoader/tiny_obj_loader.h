#pragma once
#include <cmath>
#include "Core\CoreLib.h"
#include "Math\Algebra\Vector3.h"
namespace Hikari
{
	typedef struct
	{
		std::string name;
		float ambient[3];
		float diffuse[3];
		float specular[3];
		float transmittance[3];
		float emission[3];
		float shininess;
		float ior;	//index of refraction
		float dissolve;	//1==opaque 0 == fuull transparent
		int illum;
		int dummy;

		std::string ambient_texname;
		std::string diffuse_texname;
		std::string specular_highlight_texname;
		std::string bump_texname;
		std::string displacement_texname;
		std::string alpha_texname;
		std::map<std::string, std::string> unknow_parameter;

	}material_t;

	typedef struct
	{
		std::string name;
		std::vector<int> intValues;
		std::vector<float> floatValue;
		std::vector<std::string> stringValue;
	}tag_t;

	typedef struct
	{
		std::vector<float> positions;
		std::vector<float> normals;
		std::vector<float> texcoords;
		std::vector<unsigned int> indices;
		std::vector<unsigned char> num_vertices;
		std::vector<int> material_ids;
		std::vector<tag_t> tags;
	}mesh_t;

	typedef struct
	{
		std::string name;
		mesh_t mesh;
	}shape_t;

	typedef enum
	{
		triangulation = 1,
		calculate_normals = 2,

	}load_flags_t;

	class MaterialReader
	{
	public:
		MaterialReader(){}
		virtual ~MaterialReader();

		virtual bool operator()(const std::string& matId,
			std::vector<material_t>& materials,
			std::map<std::string, int>& matMap,
			std::string& err) = 0;
	};
	
	class MaterialFileReader : public MaterialReader
	{
	public:
		MaterialFileReader(const std::string& mt_basepath)
			: m_mtlBasePath(mt_basepath) {}
		virtual ~MaterialFileReader() {}
		virtual bool operator()(const std::string& matId, std::vector<material_t>
			&materials, std::map<std::string, int>& matMap, std::string& error);
	private:
		std::string m_mtlBasePath;
	};

	bool LoadObj(std::vector<shape_t>&shapes,//output
		std::vector<material_t>& materials,//output
		std::string& err,	//output
		std::istream& inStream, MaterialReader& readMatFn,
		unsigned int flags = 1);

	void LoadMtl(std::map<std::string, int>& meterial_map,
		std::vector<material_t>& materials,
		std::istream& inStream);

	struct vertex_index
	{
		int v_idx, vt_idx, vn_idx;
		vertex_index() :v_idx(-1), vt_idx(-1), vn_idx(-1) {}
		explicit vertex_index(int idx) :v_idx(idx), vt_idx(idx), vn_idx(idx) {}
		vertex_index(int vidx, int vtidx, int vnidx) :
			v_idx(vidx), vt_idx(vt_idx), vn_idx(vnidx) {}

	};
	
	struct tag_sizes
	{
		tag_sizes() :num_ints(0), num_floats(0), num_strings(0) {}
		int num_ints;
		int num_floats;
		int num_strings;
	};

	static inline bool operator<(const vertex_index& a, const vertex_index& b)
	{
		return false;
	}

	static std::istream& safeGetline(std::istream& is, std::string& t)
	{
		t.clear();

		std::istream::sentry se(is, true);
		std::streambuf* sb = is.rdbuf();
		for (;;)
		{
			int c = sb->sbumpc();
			switch (c)
			{
			case '\n':
				return is;
			case '\r':
				if (sb->sgetc() == '\n')
					sb->sbumpc();
				return is;
			case EOF:
				if (t.empty())
					is.setstate(std::ios::eofbit);
				return is;
			default:
				t += char(c);
			}
		}
	}
#define IS_SPACE (x) (((x == ' ') || (x) == '\t'))
#define IS_DIGIT(x) ((unsigned int)((x) - '0')<(unsigned int)10)
#define IS_NEW_LINE(x) (((x) == '\r') || ((x) == '\n') || ((x) == '\0'))

	static inline int fixIndex(int idx, int n)
	{
		if (idx > 0)
			return idx - 1;
		if (idx == 0)
			return 0;
		return n + idx;
	}
	
	static inline std::string parseString(const char* &token)
	{
		std::string s;
		token += strspn(token, " \t");
		size_t e = strcspn(token, " \t\r");
		s = std::string(token, &token[e]);
		token += e;
		return s;
	}

	static inline int parseInt(const char*& token)
	{
		token += strspn(token, " \t");
		int i = atoi(token);
		token += strcspn(token, " \t\r");
		return i;
	}

	static bool tryParseDouble(const char* s, const char* s_end, double* result)
	{
		if (s >= s_end)
			return false;
		double mantissa = 0.0f;

		int exponent = 0;
		char sign = '+';
		char const* curr = s;

	}
}