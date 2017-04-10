#pragma once
#include "GraphicsLib.h"
#include "Object.h"
namespace Hikari
{
	class Shader : public Object
	{
	protected:
		Shader();
		Shader(const std::string & programName, int numInputs, int numOutputs, int numConstants, int numSamples, bool profileOwner);
		
	public:
		virtual ~Shader();
		enum VariableType
		{
			VT_NONE,

			VT_FLOAT,
			VT_FLOAT1, VT_FLOAT2, VT_FLOAT3, VT_FLOAT4,
			VT_FLOAT1X1, VT_FLOAT1X2, VT_FLOAT1X3, VT_FLOAT1X4,
			VT_FLOAT2X1, VT_FLOAT2X2, VT_FLOAT2X3, VT_FLOAT2X4,
			VT_FLOAT3X1, VT_FLOAT3X2, VT_FLOAT3X3, VT_FLOAT3X4,
			VT_FLOAT4X1, VT_FLOAT4X2, VT_FLOAT4X3, VT_FLOAT4X4,

			VT_HALF,
			VT_HALF1, VT_HALF2, VT_HALF3, VT_HALF4,
			VT_HALF1X1, VT_HALF1X2, VT_HALF1X3, VT_HALF1X4,
			VT_HALF2X1, VT_HALF2X2, VT_HALF2X3, VT_HALF2X4,
			VT_HALF3X1, VT_HALF3X2, VT_HALF3X3, VT_HALF3X4,
			VT_HALF4X1, VT_HALF4X2, VT_HALF4X3, VT_HALF4X4,

			VT_INT,
			VT_INT1, VT_INT2, VT_INT3, VT_INT4,
			VT_INT1X1, VT_INT1X2, VT_INT1X3, VT_INT1X4,
			VT_INT2X1, VT_INT2X2, VT_INT2X3, VT_INT2X4,
			VT_INT3X1, VT_INT3X2, VT_INT3X3, VT_INT3X4,
			VT_INT4X1, VT_INT4X2, VT_INT4X3, VT_INT4X4,

			VT_FIXED,
			VT_FIXED1, VT_FIXED2, VT_FIXED3, VT_FIXED4,
			VT_FIXED1X1, VT_FIXED1X2, VT_FIXED1X3, VT_FIXED1X4,
			VT_FIXED2X1, VT_FIXED2X2, VT_FIXED2X3, VT_FIXED2X4,
			VT_FIXED3X1, VT_FIXED3X2, VT_FIXED3X3, VT_FIXED3X4,
			VT_FIXED4X1, VT_FIXED4X2, VT_FIXED4X3, VT_FIXED4X4,

			VT_BOOL,
			VT_BOOL1, VT_BOOL2, VT_BOOL3, VT_BOOL4,
			VT_BOOL1X1, VT_BOOL1X2, VT_BOOL1X3, VT_BOOL1X4,
			VT_BOOL2X1, VT_BOOL2X2, VT_BOOL2X3, VT_BOOL2X4,
			VT_BOOL3X1, VT_BOOL3X2, VT_BOOL3X3, VT_BOOL3X4,
			VT_BOOL4X1, VT_BOOL4X2, VT_BOOL4X3, VT_BOOL4X4,

			VT_QUANTITY
		};

		enum ShaderType
		{
			UnKnownShaderType = 0,
			VertexShader,
			TessellatonControlShader,
			TessellationEvaluationShader,
			GeometryShader,
			PixelShader,
			ComputeShader
		};
		// Semantics for the input and output variables of the shader program.
		enum VariableSemantic
		{
			VS_NONE,
			VS_POSITION,        // ATTR0
			VS_BLENDWEIGHT,     // ATTR1
			VS_NORMAL,          // ATTR2
			VS_COLOR0,          // ATTR3 (and for render targets)
			VS_COLOR1,          // ATTR4 (and for render targets)
			VS_FOGCOORD,        // ATTR5
			VS_PSIZE,           // ATTR6
			VS_BLENDINDICES,    // ATTR7
			VS_TEXCOORD0,       // ATTR8
			VS_TEXCOORD1,       // ATTR9
			VS_TEXCOORD2,       // ATTR10
			VS_TEXCOORD3,       // ATTR11
			VS_TEXCOORD4,       // ATTR12
			VS_TEXCOORD5,       // ATTR13
			VS_TEXCOORD6,       // ATTR14
			VS_TEXCOORD7,       // ATTR15
			VS_FOG,             // same as VS_FOGCOORD (ATTR5)
			VS_TANGENT,         // same as VS_TEXCOORD6 (ATTR14)
			VS_BINORMAL,        // same as VS_TEXCOORD7 (ATTR15)
			VS_COLOR2,          // support for multiple render targets
			VS_COLOR3,          // support for multiple render targets
			VS_DEPTH0,          // support for multiple render targets
			VS_QUANTITY
		};
	

		void SetInput(int i, const std::string & name, VariableType type, VariableSemantic semantic);
		void SetOutput(int i, const std::string & name, VariableType type, VariableSemantic semantic);
		void SetConstant(int i, const std::string & name, int numRegistersUsed);
	
		const std::string& GetInputName(int i) const;
		inline int GetNumConstants()const
		{
			return mNumConstants;
		}
		inline int GetNumInputs()const
		{
			return mNumInputs;
		}
		Shader::VariableType GetInputType(int i) const;
		Shader::VariableSemantic GetInputSemantic(int i) const;
		const std::string & GetConstantName(int i) const;
		const std::string GetFileName() const;

	protected:
		int mNumConstants,
			mNumInputs,
			mNumOutputs,
			mNumSamplers;
		std::string* mInputName;
		std::string* mOutputName;

		VariableType* mInputType;
		VariableType* mOutputType;
		VariableSemantic*	mInputSemantic;
		VariableSemantic* mOutputSemantic;

		ShaderType* mShaderType;
		std::string*	mConstantName;
		int* mNumRegistersUsed;
		std::string	mSamplerName;
		std::string	mprogramFileName;
	};

}