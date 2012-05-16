cbuffer LightningStructure
{
	// for ZigZag pattern
	float2 ZigZagFraction;				// determines at which percentage the segment will be broken
	float2 ZigZagDeviationRight;		// min and max of deviation in segments local frame
	float2 ZigZagDeviationUp;			// min and max of deviation in segments local frame
	float  ZigZagDeviationDecay;		// controls how fast the deviation get smaller
	
	// for Fork pattern
	float2 ForkFraction;				// similiar above, but for fork pattern
	float2 ForkZigZagDeviationRight;
	float2 ForkZigZagDeviationUp;
	float  ForkZigZagDeviationDecay;
	
	float2 ForkDeviationRight;
	float2 ForkDeviationUp;
	float2 ForkDeviationForward;
	float  ForkDeviationDecay;

	float2	ForkLength;					// min and max of length of fork segments, in world space
	float	ForkLengthDecay;			// decay of length
};

// decay based on global subdivision level
float Decay(float amount)
{
	return exp(-amount * SubdivisionLevel);
}

// decay based in explicit level
float Decay(float2 amount, uint level)
{
	return  amount.x * exp(-amount.y * level);
}

// Subdivision
struct SubdivideVertex
{
	float3	Start		: Start;		// start of segment
	float3	End			: End;			// end of segment
	float3	Up			: Up;			// up vector, specifying frame of orientation for deviation parameters
	uint	Level		: Level;		// n + 1 for forked segment, n for jittered segments
};

void SubdivideVS( in SubdivideVertex input, out SubdivideVertex output)
{
	output = input;
}


// Random number generation
// found in numerical recipes
// http://www.library.cornell.edu/nr/bookcpdf/c7-1.pdf

// per shader global variable to keep track of the last random number 
int random_x;

#define RANDOM_IA 16807
#define RANDOM_IM 2147483647
#define RANDOM_AM (1.0f/float(RANDOM_IM))
#define RANDOM_IQ 127773
#define RANDOM_IR 2836
#define RANDOM_MASK 123459876

float Random()
{
	int k;
	float ans;
	
	random_x ^= RANDOM_MASK;								//XORing with MASK allows use of zero and other
	k = random_x / RANDOM_IQ;								//simple bit patterns for idum.
	random_x = RANDOM_IA * (random_x - k * RANDOM_IQ ) - RANDOM_IR * k;	//Compute idum=(IA*idum) % IM without overif
	if (random_x < 0) 
		random_x += RANDOM_IM;					//flows by Schrage’s method.
	
	ans = RANDOM_AM * random_x;					//Convert idum to a floating result.
	random_x ^= RANDOM_MASK;					//Unmask before return.
	
	return ans;
}

void RandomSeed (int value)
{
	random_x = value;
	Random();
}

float Random(float low, float high)
{
	float v = Random();
	return low * (1.0f - v) + high * v;
}

float3 Random(float3 low, float3 high)
{
	float3 v = float3(Random(),Random(),Random());
	return low * (1.0f - v) + high * v;
}


// helper data structure for passing stuff around
struct Segment
{
	float3 Start;
	float3 End;

	float3 Center;
	
	float3 Right;
	float3 Up;
	float3 Forward;
	
	uint Level;
	uint Primitive;
};

// make coordinate frame
float3 GetUp(float3 start, float3 end, float3 right)
{
	float3 forward = normalize(end - start);
	return cross(right, forward);
}

// appends vertex representing a segment to stream
void DrawLineRight
(
	float3 start, 
	float3 end, 
	float3 right, 
	uint level, 
	inout PointStream<SubdivideVertex> output)
{
	SubdivideVertex v = {start, end, GetUp(start,end,right), level};
	output.Append(v);
}


// subdivision by splitting segment into two and randomly moving split point
void PatternZigZag(in Segment segment , inout PointStream<SubdivideVertex> output)
{
	float2 delta = Decay(ZigZagDeviationDecay) * float2(Random(ZigZagDeviationRight.x,ZigZagDeviationRight.y), Random(ZigZagDeviationUp.x,ZigZagDeviationUp.y));
	
	float3 	jittered = lerp(segment.Start,segment.End, Random(ZigZagFraction.x, ZigZagFraction.y)) + 
			delta.x * segment.Right + delta.y * segment.Up;
	
	DrawLineRight(segment.Start, jittered, segment.Right, segment.Level,   output);
	DrawLineRight(jittered, segment.End, segment.Right, segment.Level,  output);

}


// subdivision by splitting segment into two and randomly moving split point
// and adding a branch segment between the split position and the random end point
void PatternFork(in Segment segment , inout PointStream<SubdivideVertex> output)
{
	float2 delta = Decay(ForkZigZagDeviationDecay) * float2(Random(ForkZigZagDeviationRight.x,ForkZigZagDeviationRight.y), Random(ForkZigZagDeviationUp.x, ForkZigZagDeviationUp.y));
	
	float3 	jittered = lerp(segment.Start,segment.End, Random(ForkFraction.x, ForkFraction.y)) + 
			delta.x * segment.Right + delta.y * segment.Up;
	
	DrawLineRight(segment.Start, jittered, segment.Right, segment.Level, output);
	DrawLineRight(jittered, segment.End, segment.Right, segment.Level, output);
	

	float3 fork_dir = normalize(segment.Right);

	
	float3 f_delta = Decay(ForkDeviationDecay) * float3(Random(ForkDeviationRight.x,ForkDeviationRight.y), Random(ForkDeviationUp.x, ForkDeviationUp.y),  Random(ForkDeviationForward.x, ForkDeviationForward.y));
	float  f_length = Random(ForkLength.x, ForkLength.y) * Decay(ForkLengthDecay);
	float3 f_jittered = jittered + f_length * normalize(f_delta.x * segment.Right + f_delta.y  * segment.Up + f_delta.z * segment.Forward);
	
	DrawLineRight(jittered, f_jittered, segment.Forward,  segment.Level + 1, output);
	
}


// decides whether to fork or to jitter bases upon uniform parameter
[MaxVertexCount(3)]
void SubdivideGS
(
	in point SubdivideVertex input[1],
	in uint primitive_id : SV_PrimitiveID,
	
	inout PointStream<SubdivideVertex> output
)
{
	RandomSeed(primitive_id + 1 + time * AnimationSpeed);

	float3 center = 0.5f * ( input[0].Start + input[0].End );
	
	Segment segment;
	
	segment.Start = input[0].Start;
	segment.End = input[0].End;
	
	segment.Center = 0.5f * (segment.Start + segment.End);
	
	segment.Up = input[0].Up;
	
	segment.Forward = normalize(segment.End - segment.Start);
	segment.Right = normalize(cross(segment.Forward, segment.Up));
	segment.Up = normalize(cross(segment.Right, segment.Forward));
	

	segment.Level = input[0].Level;
	
	segment.Primitive = primitive_id;

	if(Fork)
		PatternFork(segment, output);	
	else
		PatternZigZag(segment, output);	

}

technique10 Subdivide
{
    pass P0
    {       
		SetVertexShader  (CompileShader(vs_4_0, SubdivideVS()));
        SetGeometryShader(gs_subdivide);
        SetPixelShader(0);
        
        SetDepthStencilState(DisableDepth,0);
    }
}
