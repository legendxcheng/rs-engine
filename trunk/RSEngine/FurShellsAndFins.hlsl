Texture2DArray furTextureArray;
Texture2DArray furOffsetArray;
Texture2D finTexture;
Texture2D finOffset;
Texture2D colorTexture;

cbuffer cbChangesOften
{
    int shell = 0;
    float3 combVector = float3(0,0,1);
    float combStrength = 0;
    int numShells = 16;
    float shellIncrement = 0.005;
    float maxOpacity = 0.9;
}

cbuffer cbChangesEveryFrame
{
    matrix World;
    matrix WorldViewProj;
    vector Eye;   //eye in object space
    vector Light; //light in object space
};

cbuffer cbImmutable
{
   float textureTilingFactor = 10.0; 
   float finThreshold = 0.25;
}


BlendState AlphaBlending
{
    AlphaToCoverageEnable = FALSE;
    BlendEnable[0] = TRUE;
    SrcBlend = SRC_ALPHA;
    DestBlend = INV_SRC_ALPHA;
    BlendOp = ADD;
    SrcBlendAlpha = ONE;
    DestBlendAlpha = ONE;
    BlendOpAlpha = ADD;
    RenderTargetWriteMask[0] = 0x0F;
};

BlendState NoBlending
{
    AlphaToCoverageEnable = FALSE;
    BlendEnable[0] = FALSE;
    RenderTargetWriteMask[0] = 0x0F;
};


DepthStencilState EnableDepth
{
    DepthEnable = true;
    DepthWriteMask = ALL;
    DepthFunc = Less;
    StencilEnable = false;
 };

DepthStencilState EnableDepthTestingOnly
{
    DepthEnable = true;
    DepthWriteMask = 0x00;
    DepthFunc = Less;
    StencilEnable = false;
};

DepthStencilState DisableDepth
{
    DepthEnable = false;
    DepthWriteMask = 0x00;
    DepthFunc = Less;
    StencilEnable = false;
 };

SamplerState samLinear
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};


//--------------------------------------------------------------------------------------
// Vertex Shaders
//--------------------------------------------------------------------------------------


struct VS_INPUT_SCENE
{
    float3 Position          : POSITION;
    float3 Normal            : NORMAL;  
    float2 Texture           : TEXCOORD;
    float3 Tangent           : TANGENT;
    float3 Binormal          : BINORMAL;

};

//for the fins
struct VS_OUTPUT_FINS
{
    float4 Position          : SV_POSITION;
    float3 Normal            : TEXCOORD0;
    float2 Texture           : TEXCOORD1;
};

//for the shells
struct VS_OUTPUT_SCENE
{
    float4 Position          : SV_POSITION;
    float3 Normal            : TEXCOORD0;
    float2 Texture           : TEXCOORD1;
    float3 LightVector       : TEXCOORD2;
    float3 ViewVector        : TEXCOORD3;
    float3 CombVector        : TEXCOORD4;
    int shellNumber          : SHELLNUM;
};

struct VS_INPUT_ARROW
{ 
    float3 Position          : POSITION;
    float3 Normal            : NORMAL;
    float2 Texture           : TEXCOORD;

};
struct VS_OUTPUT_ARROW
{
    float4 Position          : SV_POSITION;
    float3 Normal            : NORMAL;
    float3 LightVec          : TEXCOORD0;
    float2 Texture           : TEXCOORD1;
};

void Resize(inout VS_INPUT_SCENE input )
{
	input.Position.xyz *= 15.0f;
}

//pass through vertex shader for the fins
VS_OUTPUT_FINS VSFins( VS_INPUT_SCENE input )
{
    Resize(input);
	
	VS_OUTPUT_FINS output = (VS_OUTPUT_FINS)0;
    output.Position = float4(input.Position,1);
    output.Normal   = input.Normal;
    output.Texture  = input.Texture;
    
    return output;
}

//vertex shader for the shells and mesh
//extrude the vertices along an extrusion vector by an amount proportional to
//the index of the shell and the desired length of fur at this place (lengthFraction)
//the extrusion vector is an average of the normal and the comb vector, weighted by the comb strength
VS_OUTPUT_SCENE VS( VS_INPUT_SCENE input )
{
     Resize(input);

	 VS_OUTPUT_SCENE output = (VS_OUTPUT_SCENE)0;
     
     float4 color = colorTexture.SampleLevel(samLinear,input.Texture,0);
     // the alpha channel specifies the length of hair 
     float lengthFraction = color.a;
     //if(lengthFraction < 0.2) 
		 lengthFraction = 1.0f;  
     float3 CombVector = combStrength*combVector;
     float3 pos = input.Position.xyz + (input.Normal + CombVector)*shellIncrement*shell*lengthFraction;
     output.Position = mul( float4(pos,1) , WorldViewProj );
     output.Normal = normalize(mul( input.Normal, World ));
     output.Texture = input.Texture;

     //transform the light and eye vectors to tangent space for per pixel lighting 
     float3 eyeVector = Eye - pos;
     output.ViewVector.x = dot(input.Tangent, eyeVector);
     output.ViewVector.y = dot(input.Binormal,eyeVector);
     output.ViewVector.z = dot(input.Normal,  eyeVector);
     float3 lightVector = Light - pos;
     output.LightVector.x = dot(input.Tangent,  lightVector);
     output.LightVector.y = dot(input.Binormal, lightVector);
     output.LightVector.z = dot(input.Normal,   lightVector);
     //transform the comb vector aswell, since this is going to be needed for 
     //transforming the fur tangent in the lighting calculations
      output.CombVector.x = dot(input.Tangent,  CombVector);
     output.CombVector.y = dot(input.Binormal, CombVector);
     output.CombVector.z = dot(input.Normal,   CombVector);

     output.shellNumber = shell-1;
     
     return output;
}

//--------------------------------------------------------------------------------------
// Geometry shader
//--------------------------------------------------------------------------------------

struct GS_OUTPUT_FINS
{
    float4 Position    : SV_POSITION;  
    float2 TextureMesh : TEXCOORD0;
    float2 TextureFin  : TEXCOORD1;
    float  Opacity     : OPACITY;
};

//extrude an edge into two triangles if we determine that its a silhouette edge or almost a silhouette edge
void makeFin(VS_OUTPUT_FINS v1, VS_OUTPUT_FINS v2, inout TriangleStream<GS_OUTPUT_FINS> TriStream)
{    
       
    float opacity = maxOpacity;   
    float texcoord[2] = {1,0.1};
    float furLengths[2];
    float4 color = colorTexture.SampleLevel(samLinear,v1.Texture,0);
    furLengths[0] = 1.0f;//color.a;
    color = colorTexture.SampleLevel(samLinear,v2.Texture,0);
    furLengths[1] = 1.0f;//color.a;
 
    // Extrude silhouette to create two new triangles for the fin
    GS_OUTPUT_FINS Out = (GS_OUTPUT_FINS)0;
        
    Out.TextureMesh = v1.Texture;
    Out.Opacity = opacity;
    for(int v=0; v<2; v++)
    {
        Out.Position = mul(v1.Position + v*float4(normalize(v1.Normal) +
            combStrength*combVector,0)*numShells*shellIncrement*furLengths[0], WorldViewProj );
        Out.TextureFin = float2(0,texcoord[v]);
        TriStream.Append(Out);
    }

    Out.TextureMesh = v2.Texture;
    Out.Opacity = opacity;
    for(int w=0; w<2; w++)
    {
        Out.Position = mul(v2.Position + w*float4(normalize(v2.Normal) +
            combStrength*combVector,0)*numShells*shellIncrement*furLengths[1], WorldViewProj );
        Out.TextureFin = float2(1,texcoord[w]);
        TriStream.Append(Out);
    }
        
    TriStream.RestartStrip();
}


//GS shader for the fins
[maxvertexcount(4)]
void GSFinsLineAdj( triangle VS_OUTPUT_FINS input[3], inout TriangleStream<GS_OUTPUT_FINS> TriStream )
{
     //output some fins if necessary
     float3 eyeVec = normalize( Eye - (input[0].Position+input[1].Position+input[2].Position)/3 );

     if(abs(dot(eyeVec,input[0].Normal)) > finThreshold)
	 {
		 return;
	 }

	 float dot01 = abs(dot(eyeVec,normalize(input[0].Position-input[1].Position)));
	 float dot02 = abs(dot(eyeVec,normalize(input[0].Position-input[2].Position)));
	 float dot21 = abs(dot(eyeVec,normalize(input[2].Position-input[1].Position)));

	 if(dot01 <= dot02 && dot01 <= dot21)
	 {
		makeFin(input[0],input[1], TriStream);
		return;
	 }
     if(dot02 <= dot01 && dot02 <= dot21)
	 {
		makeFin(input[0],input[2], TriStream);
		return;
	 }
	 if(dot21 <= dot02 && dot21 <= dot01)
	 {
		makeFin(input[2],input[1], TriStream);
		return;
	 }
}


//--------------------------------------------------------------------------------------
// Pixel Shaders
//--------------------------------------------------------------------------------------

struct PS_OUTPUT
{
    float4 RGBColor : SV_Target;  
};

float4 PSFins(GS_OUTPUT_FINS In) : SV_Target
{   
    float4 finOpacity = finTexture.Sample( samLinear, In.TextureFin);
    float4 offset   =  finOffset.Sample( samLinear, In.TextureFin);

    //using color from color map
    float2 Texture = In.TextureMesh;
    Texture -= ( offset.xy - 0.5f )*2.0f;
    float4 outputColor =  colorTexture.Sample(samLinear,Texture);
    
    //calculate the opacity
    outputColor.a = finOpacity.a * In.Opacity;
    return outputColor;
}

float4 PSMesh(VS_OUTPUT_SCENE In) : SV_Target
{  
    float kd = 0.2;
    float ka = 0.8;
    float4 outputColor;
      
    float4 baseColor = colorTexture.Sample(samLinear,In.Texture);

    //diffuse light
    float3 normal = float3(0,0,1.0);
    float3 light  = normalize(In.LightVector); 
    float diffuse = saturate( dot( normal,light ));
       
    outputColor = float4(baseColor.xyz * (diffuse*kd + ka), 1.0);
    
    return outputColor;
}


//pixel shader for shells
float4 PSShells(VS_OUTPUT_SCENE In) : SV_Target
{  
    float ka = 0.3;
    float kd = 0.7;
    float ks = 0.2;
    float specPower = 20.0;

    float4 outputColor;
    
    float2 Texture  = In.Texture * textureTilingFactor;
    float4 tangentAndAlpha  = 1.0f;//furTextureArray.SampleLevel( samLinear, float3(Texture, In.shellNumber),0 );
    float4 offset   =  1.0f;//furOffsetArray.SampleLevel( samLinear, float3(Texture, In.shellNumber),0 );

    //get the fur color and local fur density
    Texture -= ( offset.xy - 0.5f )*2.0f;
    Texture /= textureTilingFactor;
    outputColor = colorTexture.Sample(samLinear,Texture);
    
    //discard the parts of the mesh marked as no fur, like the eyes and the feet
    if(outputColor.a < 0.01)
        discard;

    //calculate the opacity for alpha blending
    outputColor.a = tangentAndAlpha.a * offset.a; 
   
    //kajiya and kay lighting
    float3 lightVector  = normalize(In.LightVector);
    float3 viewVector   = normalize(In.ViewVector);
    float3 tangentVector= normalize((tangentAndAlpha.rgb - 0.5f) * 2.0f); //this is the tangent to the strand of fur
    tangentVector = normalize(tangentVector + In.CombVector);
    float TdotL = dot( tangentVector , lightVector);
    float TdotE = dot( tangentVector , viewVector);
    float sinTL = sqrt( 1 - TdotL*TdotL );
    float sinTE = sqrt( 1 - TdotE*TdotE );
    outputColor.xyz = ka*outputColor.xyz + kd*sinTL*outputColor.xyz + 
        ks*pow( abs((TdotL*TdotE + sinTL*sinTE)),specPower).xxx;
      
    //banks selfshadowing:
    float minShadow = 0.8;
    float shadow = (float(In.shellNumber)/float(numShells))*(1-minShadow) + minShadow;
    outputColor.xyz *= shadow;
      
    return outputColor;
}

//--------------------------------------------------------------------------------------
//techniques
//--------------------------------------------------------------------------------------

technique10 RenderMesh
{
    pass P0
    {
        SetVertexShader(    CompileShader( vs_4_0,VS()           ) ); 
        SetGeometryShader(  NULL                                   );
        SetPixelShader(     CompileShader( ps_4_0,PSMesh()       ) );
        
        SetBlendState( NoBlending, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );
        SetDepthStencilState( EnableDepth, 1 );
    }
}

technique10 RenderShells
{
    pass P0
    {
        SetVertexShader(    CompileShader( vs_4_0,VS()           ) ); 
        SetGeometryShader(  NULL                                   );
        SetPixelShader(     CompileShader( ps_4_0,PSShells()     ) );
        
        SetBlendState( AlphaBlending, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );
        SetDepthStencilState( EnableDepthTestingOnly, 0 );
    }
}

technique10 RenderFinsLineAdj
{
    pass P0
    {
        SetVertexShader(    CompileShader( vs_4_0,VSFins()        ) ); 
        SetGeometryShader(  CompileShader( gs_4_0,GSFinsLineAdj() ) );
        SetPixelShader(     CompileShader( ps_4_0,PSFins()        ) );
        
        SetBlendState( AlphaBlending, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );
        SetDepthStencilState( EnableDepthTestingOnly, 0 );
    }
}