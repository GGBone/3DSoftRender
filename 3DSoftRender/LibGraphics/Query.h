#pragma once

#include "Core\Object.h"
namespace Hikari
{
	class Query : public Object
	{
	public:

		enum class QueryType
		{
			Timer,
			CountSamples,
			CountSamplesPredicate,
			CountPrimitives,
			CountTransformFeedbackPrimitives,
		};

		struct QueryResult
		{
			union
			{
				double   ElapsedTime;                   // Valid for QueryType::Timer queries. Returns the elapsed time in seconds between Query::Begin and Query::End.
				uint64_t PrimitivesGenerated;           // Valid for QueryType::CountPrimitives. Returns the number of primitives generated between Query::Begin and Query::End.
				uint64_t TransformFeedbackPrimitives;   // Valid for QueryType::CountTransformFeedbackPrimitives. Returns the number of primtives written to stream out or transform feedback buffers.
				uint64_t NumSamples;                    // Valid for QueryType::CountSamples. Returns the number of samples written by the fragment shader between Query::Begin and Query::End.
				bool     AnySamples;                    // Valid for QueryType::CountSamplesPredicate. Returns true if any samples were written by the fragment shader between Query::Begin and Query::End.
			};
		
			bool IsValid;
		};

		virtual void Begin(int64_t frame = 0L) = 0;


		virtual void End(int64_t frame = 0L) = 0;

		
		virtual bool QueryResultAvailable(int64_t frame = 0L) = 0;

	
		virtual QueryResult GetQueryResult(int64_t frame = 0L) = 0;

		virtual uint8_t GetBufferCount() const = 0;
	};
}