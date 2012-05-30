#pragma once
#include "Utility.h"

namespace Utility
{
namespace Effect
{
class IntVariable 
{
public:
	
	IntVariable(ID3D10Effect* effect, const std::string& name)
	{
		m_variable =  effect->GetVariableByName(name.c_str())->AsScalar();
	}

	IntVariable& operator = ( int i)
	{
		m_variable->SetInt( i);
		return *this;
	}
private:
	ID3D10EffectScalarVariable*  m_variable;
};


class FloatVariable 
{
public:
	
	FloatVariable(ID3D10Effect* effect, const std::string& name)
	{
		m_variable =  effect->GetVariableByName(name.c_str())->AsScalar();
	}

	FloatVariable& operator = ( float f)
	{
		m_variable->SetFloat( f);
		return *this;
	}

	operator float()
	{
		float result;
		m_variable->GetFloat(&result);
		return result;
	}
private:
	ID3D10EffectScalarVariable*  m_variable;
};

class BoolVariable 
{
public:
	
	BoolVariable(ID3D10Effect* effect, const std::string& name)
	{
		m_variable =  effect->GetVariableByName(name.c_str())->AsScalar();
	}

	BoolVariable& operator = ( BOOL b)
	{
		m_variable->SetBool( b);
		return *this;
	}
private:
	ID3D10EffectScalarVariable*  m_variable;
};
class MatrixVariable 
{
public:
	
	MatrixVariable(ID3D10Effect* effect, const std::string& name)
	{
		m_variable =  effect->GetVariableByName(name.c_str())->AsMatrix();
	}

	MatrixVariable& operator = ( const D3DXMATRIX& matrix)
	{
		m_variable->SetMatrix( D3DXMATRIX(matrix));
		return *this;
	}

	operator D3DXMATRIX()
	{
		D3DXMATRIX result;
		m_variable->GetMatrix(result);
		return result;
	}
private:
	ID3D10EffectMatrixVariable*  m_variable;
};


class ShaderResourceVariable 
{
public:
	
	ShaderResourceVariable(ID3D10Effect* effect, const std::string& name)
	{
		m_variable =  effect->GetVariableByName(name.c_str())->AsShaderResource();
	}
	ShaderResourceVariable& operator = ( const   ID3D10ShaderResourceView * shader_resource)
	{
		m_variable->SetResource(const_cast< ID3D10ShaderResourceView *>(shader_resource));
		return *this;
	}

	operator ID3D10EffectShaderResourceVariable*()
	{
		return m_variable;
	}
private:
	ID3D10EffectShaderResourceVariable*  m_variable;
};


class Vector2Variable 
{
public:
	
	Vector2Variable(ID3D10Effect* effect, const std::string& name)
	{
		m_variable =  effect->GetVariableByName(name.c_str())->AsVector();
	}

	Vector2Variable& operator = ( const D3DXVECTOR2& v)
	{
		m_variable->SetFloatVector( D3DXVECTOR2(v));
		return *this;
	}
private:
	ID3D10EffectVectorVariable*  m_variable;
};


class Vector3Variable 
{
public:
	
	Vector3Variable(ID3D10Effect* effect, const std::string& name)
	{
		m_variable =  effect->GetVariableByName(name.c_str())->AsVector();
	}

	Vector3Variable& operator = ( const D3DXVECTOR3& v)
	{
		m_variable->SetFloatVector( D3DXVECTOR3(v));
		return *this;
	}
private:
	ID3D10EffectVectorVariable*  m_variable;
};


class Vector4Variable 
{
public:
	
	Vector4Variable(ID3D10Effect* effect, const std::string& name)
	{
		m_variable =  effect->GetVariableByName(name.c_str())->AsVector();
	}

	Vector4Variable& operator = ( const D3DXVECTOR4& v)
	{
		m_variable->SetFloatVector( D3DXVECTOR4(v));
		return *this;
	}
private:
	ID3D10EffectVectorVariable*  m_variable;
};

class ConstantBuffer
{
public:
	
	ConstantBuffer(ID3D10Effect* effect, const std::string& name)
	{
		m_buffer = effect->GetConstantBufferByName(name.c_str());
	}

	template<typename T>
	ConstantBuffer& operator = (const T& data)
	{
		m_buffer->SetRawValue(const_cast<T*>(&data), 0, sizeof(T));
		return *this;
	}

	operator ID3D10EffectConstantBuffer*()
	{
		return m_buffer;
	}
private:
	ID3D10EffectConstantBuffer*  m_buffer;
};
} // Effect
} // Utility