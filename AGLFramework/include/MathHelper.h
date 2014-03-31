#ifndef __AIEMATH_H_
#define __AIEMATH_H_
//////////////////////////////////////////////////////////////////////////
#include <math.h>

const float PI					= 3.14159265359f;
const float	TWOPI     			= 6.28318530717958657692f;
const float HALFPI				= 1.57079632679489661923f;
const float THREEHALFPI			= 4.71238898038468985769f;

const float	EPSILON				= 0.00000000001f;
const float	DEG2RAD             = 0.01745329251994329577f;
const float	RAD2DEG             = 57.2957795130823208768f;
//\=====================================================================================
/// Reciprocal function
//\=====================================================================================
inline float Recipf( float x )
{ 
	return (1.0f/x); 
}
//\=====================================================================================
/// Min & Max functions
//\=====================================================================================
inline int  Max( int x, int y ){ return (x > y) ? x : y; }
inline int  Min( int x, int y ){ return (x < y) ? x : y; }
inline float  Maxf( float x, float y ){ return (x > y) ? x : y; }
inline float  Minf( float x, float y ){ return (x < y) ? x : y; }
//\=====================================================================================
/// Clamp function (between 0.0f and 1.0f)
//\=====================================================================================
inline float  Clampf( float x )
{ 
	return (x > 1.0f) ? 1.0f : ((x < 0.0f) ? 0.0f : x ); 
}
//\=====================================================================================
/// Clamp function (between MIN and MAX)
//\=====================================================================================
inline float  Clampf( float x, float minx, float maxx )
{ 
	return (x > maxx) ? maxx : ((x < minx) ? minx : x ); 
}
inline int  Clamp( int x, int minx, int maxx )
{ 
	return (x > maxx) ? maxx : ((x < minx) ? minx : x ); 
}
//\=====================================================================================
/// Linearly interpolate a float
//\=====================================================================================
inline float  Lerp( float fA, float fB, float fT ) 
{ 
	return ( fB - fA ) * fT + fA;  
}
//\=====================================================================================
//\=====================================================================================
inline float  SmoothStep( float fValue ) 
{ 
	return ( fValue * fValue * ( 3.0f - 2.0f * fValue ) ); 
}
//////////////////////////////////////////////////////////////////////////
class vec4
{
public:

	float x, y, z, w;

	vec4() {}
	vec4(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {}
	~vec4() {}

	void Normalise()
	{
		float fMag = sqrtf(x*x + y*y + z*z);
		x /= fMag;
		y /= fMag;
		z /= fMag;
		w = 0;
	}

	float Magnitude() const
	{
		return sqrtf(x*x + y*y + z*z);
	}

	float MagnitudeSqr() const
	{
		return x * x + y * y + z * z;
	}

	void Invert()
	{
		x *= -1;
		y *= -1;
		z *= -1;
	}

	float Dot(const vec4& v) const
	{
		return x * v.x + y * v.y + z * v.z;
	}

	vec4 Cross(const vec4& v) const
	{
		return vec4(y * v.z - v.y * z, z * v.x - v.z * x, x * v.y - v.x * y, 0);
	}

	vec4 operator + (const vec4& v) const
	{
		return vec4(x + v.x, y + v.y, z + v.z, w);
	}

	vec4& operator += (const vec4& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	vec4& operator -= (const vec4& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	vec4 operator - (const vec4& v) const
	{
		return vec4(x - v.x, y - v.y, z - v.z, w);
	}

	vec4 operator * (float f) const
	{
		return vec4(x *f,y*f,z*f,0);
	}

	vec4& operator *= (float f)
	{
		x *= f;
		y *= f;
		z *= f;
		return *this;
	}

	vec4& operator = (const vec4& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
		return *this;
	}

	operator float* ()
	{
		return &x;
	}
};

//////////////////////////////////////////////////////////////////////////
class vec2
{
public:

	float x, y;

	vec2() {}
	vec2(float a, float b) : x(a), y(b) {}
	~vec2() {}

	void Normalise()
	{
		float fMag = sqrtf(x*x + y*y);
		x /= fMag;
		y /= fMag;
	}

	float Magnitude() const
	{
		return sqrtf(x*x + y*y);
	}

	float MagnitudeSqr() const
	{
		return x * x + y * y;
	}

	void Invert()
	{
		x *= -1;
		y *= -1;
	}

	float Dot(const vec2& v) const
	{
		return x * v.x + y * v.y;
	}

	vec2 operator + (const vec2& v) const
	{
		return vec2(x + v.x, y + v.y);
	}

	vec2 operator - (const vec2& v) const
	{
		return vec2(x - v.x, y - v.y);
	}

	vec2 operator * (float f) const
	{
		return vec2(x * f, y * f);
	}

	vec2& operator -= (const vec2& v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}

	vec2& operator += (const vec2& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	vec2& operator *= (float f)
	{
		x *= f;
		y *= f;
		return *this;
	}

	operator float* ()
	{
		return &x;
	}
};

inline float Dot(const vec2& v0, const vec2& v1)
{
	return v0.Dot(v1);
}

inline float Dot(const vec4& v0, const vec4& v1)
{
	return v0.Dot(v1);
}

inline vec4 Cross(const vec4& v0, const vec4& v1)
{
	return v0.Cross(v1);
}

//////////////////////////////////////////////////////////////////////////
class mat4
{
public:
	// warning 4201 can be ignored as unnamed structs/unions is allowed in this case
	union
	{
		float mm[4][4];
		float m[16];
		struct  
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		struct  
		{
			vec4 row0, row1, row2, row3;
		};
	};

	mat4() {}
	mat4(float a, float b, float c, float d,
		float e, float f, float g, float h,
		float i, float j, float k, float l,
		float m, float n, float o, float p)
		: _11(a), _12(b), _13(c), _14(d),
		_21(e), _22(f), _23(g), _24(h),
		_31(i), _32(j), _33(k), _34(l),
		_41(m), _42(n), _43(o), _44(p)
	{

	}
	~mat4() {}

	void ViewLookAt(const vec4& eye, const vec4& to, const vec4& up)
	{
		vec4 vForward = to - eye;
		vForward.Normalise();

		vec4 vLeft = up.Cross(vForward);
		vLeft.Normalise();

		vec4 vUp = vForward.Cross(vLeft);

		_11 = vLeft.x; 
		_21 = vLeft.y; 
		_31 = vLeft.z; 
		_41 = -(vLeft.Dot(eye));   

		_12 = vUp.x;
		_22 = vUp.y;
		_32 = vUp.z;
		_42 = -(vUp.Dot(eye));  

		_13 = vForward.x; 
		_23 = vForward.y; 
		_33 = vForward.z; 
		_43 = -(vForward.Dot(eye));   

		_14 = 0.0f;
		_24 = 0.0f;
		_34 = 0.0f;
		_44 = 1.0f;
	}

	void Orthographic(float a_fWidth, float a_fHeight, float a_fNear, float a_fFar)
	{
		_11 = 2 / a_fWidth;
		_12 = 0;
		_13 = 0;
		_14 = 0;

		_21 = 0;
		_22 = 2 / a_fHeight;
		_23 = 0;
		_24 = 0;

		_31 = 0;
		_32 = 0;
		_33 = 1 / (a_fFar - a_fNear);
		_34 = 0;

		_41 = 0;
		_42 = 0;
		_43 = a_fNear / (a_fNear - a_fFar);
		_44 = 1;
	}

	void Perspective(float a_fUpFOV, float a_fAspectRatio, float a_fNear, float a_fFar)
	{
		float halfAngleRadians = 0.5f * a_fUpFOV;
		float cot = 1 / tanf(halfAngleRadians);

		_11 = cot / a_fAspectRatio;
		_12 = 0;
		_13 = 0;
		_14 = 0;

		_21 = 0;
		_22 = cot;
		_23 = 0;
		_24 = 0;

		_31 = 0;
		_32 = 0;
		_33 = a_fFar / (a_fFar - a_fNear);
		_34 = 1;

		_41 = 0;
		_42 = 0;
		_43 = a_fNear * a_fFar / (a_fNear - a_fFar);
		_44 = 0;
	}

	mat4 Transpose() const
	{
		return mat4(_11, _21, _31, _41,
					_12, _22, _32, _42,
					_13, _23, _33, _43,
					_14, _24, _34, _44);
	}

	void RotateX(float rad)
	{
		_11 = 1;	_12 = 0;			_13 = 0;			_14 = 0;
		_21 = 0;	_22 = cosf(rad);	_23 = -sinf(rad);	_24 = 0;
		_31 = 0;	_32 = sinf(rad);	_33 = cosf(rad);	_34 = 0;
		_41 = 0;	_42 = 0;			_43 = 0;			_44 = 1;
	}
	void RotateY(float rad)
	{
		_11 = cosf(rad);	_12 = 0;	_13 = -sinf(rad);	_14 = 0;
		_21 = 0;			_22 = 1;	_23 = 0;			_24 = 0;
		_31 = sinf(rad);	_32 = 0;	_33 = cosf(rad);	_34 = 0;
		_41 = 0;			_42 = 0;	_43 = 0;			_44 = 1;
	}
	void RotateZ(float rad)
	{
		_11 = cosf(rad);	_12 = -sinf(rad);	_13 = 0;	_14 = 0;
		_21 = sinf(rad);	_22 = cosf(rad);	_23 = 0;	_24 = 0;
		_31 = 0;			_32 = 0;			_33 = 1;	_34 = 0;
		_41 = 0;			_42 = 0;			_43 = 0;	_44 = 1;
	}

	mat4 operator * (const mat4& a_rRHS) const
	{
		return mat4(	mm[0][0] * a_rRHS.mm[0][0] + mm[0][1] * a_rRHS.mm[1][0] + mm[0][2] * a_rRHS.mm[2][0] + mm[0][3] * a_rRHS.mm[3][0],
			mm[0][0] * a_rRHS.mm[0][1] + mm[0][1] * a_rRHS.mm[1][1] + mm[0][2] * a_rRHS.mm[2][1] + mm[0][3] * a_rRHS.mm[3][1],
			mm[0][0] * a_rRHS.mm[0][2] + mm[0][1] * a_rRHS.mm[1][2] + mm[0][2] * a_rRHS.mm[2][2] + mm[0][3] * a_rRHS.mm[3][2],
			mm[0][0] * a_rRHS.mm[0][3] + mm[0][1] * a_rRHS.mm[1][3] + mm[0][2] * a_rRHS.mm[2][3] + mm[0][3] * a_rRHS.mm[3][3],

			mm[1][0] * a_rRHS.mm[0][0] + mm[1][1] * a_rRHS.mm[1][0] + mm[1][2] * a_rRHS.mm[2][0] + mm[1][3] * a_rRHS.mm[3][0],
			mm[1][0] * a_rRHS.mm[0][1] + mm[1][1] * a_rRHS.mm[1][1] + mm[1][2] * a_rRHS.mm[2][1] + mm[1][3] * a_rRHS.mm[3][1],
			mm[1][0] * a_rRHS.mm[0][2] + mm[1][1] * a_rRHS.mm[1][2] + mm[1][2] * a_rRHS.mm[2][2] + mm[1][3] * a_rRHS.mm[3][2],
			mm[1][0] * a_rRHS.mm[0][3] + mm[1][1] * a_rRHS.mm[1][3] + mm[1][2] * a_rRHS.mm[2][3] + mm[1][3] * a_rRHS.mm[3][3],

			mm[2][0] * a_rRHS.mm[0][0] + mm[2][1] * a_rRHS.mm[1][0] + mm[2][2] * a_rRHS.mm[2][0] + mm[2][3] * a_rRHS.mm[3][0],
			mm[2][0] * a_rRHS.mm[0][1] + mm[2][1] * a_rRHS.mm[1][1] + mm[2][2] * a_rRHS.mm[2][1] + mm[2][3] * a_rRHS.mm[3][1],
			mm[2][0] * a_rRHS.mm[0][2] + mm[2][1] * a_rRHS.mm[1][2] + mm[2][2] * a_rRHS.mm[2][2] + mm[2][3] * a_rRHS.mm[3][2],
			mm[2][0] * a_rRHS.mm[0][3] + mm[2][1] * a_rRHS.mm[1][3] + mm[2][2] * a_rRHS.mm[2][3] + mm[2][3] * a_rRHS.mm[3][3],

			mm[3][0] * a_rRHS.mm[0][0] + mm[3][1] * a_rRHS.mm[1][0] + mm[3][2] * a_rRHS.mm[2][0] + mm[3][3] * a_rRHS.mm[3][0],
			mm[3][0] * a_rRHS.mm[0][1] + mm[3][1] * a_rRHS.mm[1][1] + mm[3][2] * a_rRHS.mm[2][1] + mm[3][3] * a_rRHS.mm[3][1],
			mm[3][0] * a_rRHS.mm[0][2] + mm[3][1] * a_rRHS.mm[1][2] + mm[3][2] * a_rRHS.mm[2][2] + mm[3][3] * a_rRHS.mm[3][2],
			mm[3][0] * a_rRHS.mm[0][3] + mm[3][1] * a_rRHS.mm[1][3] + mm[3][2] * a_rRHS.mm[2][3] + mm[3][3] * a_rRHS.mm[3][3]);
	}

	vec4 operator * (const vec4& v) const
	{
		return vec4(mm[0][0] * v.x + mm[0][1] * v.y + mm[0][2] * v.z + mm[0][3] * v.w,
					mm[1][0] * v.x + mm[1][1] * v.y + mm[1][2] * v.z + mm[1][3] * v.w,
					mm[2][0] * v.x + mm[2][1] * v.y + mm[2][2] * v.z + mm[2][3] * v.w,
					mm[3][0] * v.x + mm[3][1] * v.y + mm[3][2] * v.z + mm[3][3] * v.w);
	}

	operator float* ()
	{
		return &_11;
	}
};

#endif // __AIEMATH_H_