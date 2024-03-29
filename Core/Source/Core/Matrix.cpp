//
// Copyright (c) 2012-2017 Jimmy Lord http://www.flatheadgames.com
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#include "Matrix.h"

namespace Saz
{
	const Matrix Matrix::Identity(
		1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f);

	void Matrix::SetIdentity()
	{
		m12 = m13 = m14 = m21 = m23 = m24 = m31 = m32 = m34 = m41 = m42 = m43 = 0;
		m11 = m22 = m33 = m44 = 1;
	}

	void Matrix::SetAxesView(const Vector3& right, const Vector3& up, const Vector3& at, const Vector3& pos)
	{
		m11 = right.x; m21 = right.y; m31 = right.z; m41 = pos.x;
		m12 = up.x;    m22 = up.y;    m32 = up.z;    m42 = pos.y;
		m13 = at.x;    m23 = at.y;    m33 = at.z;    m43 = pos.z;
		m14 = 0;       m24 = 0;       m34 = 0;       m44 = 1;
	}

	void Matrix::SetAxesWorld(const Vector3& right, const Vector3& up, const Vector3& at, const Vector3& pos)
	{
		m11 = right.x; m21 = up.x; m31 = at.x; m41 = pos.x;
		m12 = right.y; m22 = up.y; m32 = at.y; m42 = pos.y;
		m13 = right.z; m23 = up.z; m33 = at.z; m43 = pos.z;
		m14 = 0;       m24 = 0;    m34 = 0;    m44 = 1;
	}

	void Matrix::SetTranslation(Vector3 pos)
	{
		m41 = pos.x;
		m42 = pos.y;
		m43 = pos.z;
	}

	void Matrix::SetTranslation(float x, float y, float z)
	{
		m41 = x;
		m42 = y;
		m43 = z;
	}

	void Matrix::CreateScale(float scale)
	{
		m12 = m13 = m14 = m21 = m23 = m24 = m31 = m32 = m34 = m41 = m42 = m43 = 0;
		m11 = m22 = m33 = scale;
		m44 = 1;
	}

	void Matrix::CreateScale(float x, float y, float z)
	{
		m12 = m13 = m14 = m21 = m23 = m24 = m31 = m32 = m34 = m41 = m42 = m43 = 0;
		m11 = x;
		m22 = y;
		m33 = z;
		m44 = 1;
	}

	void Matrix::CreateScale(Vector3 scale)
	{
		m12 = m13 = m14 = m21 = m23 = m24 = m31 = m32 = m34 = m41 = m42 = m43 = 0;
		m11 = scale.x;
		m22 = scale.y;
		m33 = scale.z;
		m44 = 1;
	}

	void Matrix::CreateRotation(Vector3 eulerdegrees)
	{
		SetIdentity();
		Rotate(eulerdegrees.z, 0, 0, 1); // roll
		Rotate(eulerdegrees.x, 1, 0, 0); // pitch
		Rotate(eulerdegrees.y, 0, 1, 0); // yaw
	}

	void Matrix::CreateTranslation(float x, float y, float z)
	{
		m12 = m13 = m14 = m21 = m23 = m24 = m31 = m32 = m34 = 0;
		m11 = m22 = m33 = m44 = 1;
		m41 = x;
		m42 = y;
		m43 = z;
	}

	void Matrix::CreateTranslation(Vector3 pos)
	{
		m12 = m13 = m14 = m21 = m23 = m24 = m31 = m32 = m34 = 0;
		m11 = m22 = m33 = m44 = 1;
		m41 = pos.x;
		m42 = pos.y;
		m43 = pos.z;
	}

	void Matrix::CreateSRT(float scale, Vector3 rot, Vector3 pos)
	{
		SetIdentity();
		Scale(scale);
		Rotate(rot.z, 0, 0, 1); // roll
		Rotate(rot.x, 1, 0, 0); // pitch
		Rotate(rot.y, 0, 1, 0); // yaw
		Translate(pos.x, pos.y, pos.z);
	}

	void Matrix::CreateSRT(Vector3 scale, Vector3 rot, Vector3 pos)
	{
		CreateScale(scale.x, scale.y, scale.z);
		Rotate(rot.z, 0, 0, 1); // roll
		Rotate(rot.x, 1, 0, 0); // pitch
		Rotate(rot.y, 0, 1, 0); // yaw
		Translate(pos.x, pos.y, pos.z);
	}

	void Matrix::CreateSRT(Vector3 scale, Quaternion rot, Vector3 pos)
	{
		SetIdentity();
		Scale(scale.x, scale.y, scale.z);
		Rotate(rot);
		Translate(pos.x, pos.y, pos.z);
	}

	Matrix::Matrix(const Vector3& translate, const Quaternion& rotate, const float scale) noexcept
	{
		CreateSRT(scale, rotate, translate);
	}

	void Matrix::Scale(float scale)
	{
		m11 *= scale; m21 *= scale; m31 *= scale; m41 *= scale;
		m12 *= scale; m22 *= scale; m32 *= scale; m42 *= scale;
		m13 *= scale; m23 *= scale; m33 *= scale; m43 *= scale;
	}

	void Matrix::Scale(float sx, float sy, float sz)
	{
		m11 *= sx; m21 *= sx; m31 *= sx; m41 *= sx;
		m12 *= sy; m22 *= sy; m32 *= sy; m42 *= sy;
		m13 *= sz; m32 *= sz; m33 *= sz; m43 *= sz;
	}

	void Matrix::Scale(Vector3 scale)
	{
		m11 *= scale.x; m21 *= scale.x; m31 *= scale.x; m41 *= scale.x;
		m12 *= scale.y; m22 *= scale.y; m32 *= scale.y; m42 *= scale.y;
		m13 *= scale.z; m32 *= scale.z; m33 *= scale.z; m43 *= scale.z;
	}

	void Matrix::Rotate(float angle, float x, float y, float z)
	{
		float sinAngle, cosAngle;
		float mag = sqrtf(x * x + y * y + z * z);

		sinAngle = sinf(angle * PI / 180.0f);
		cosAngle = cosf(angle * PI / 180.0f);
		if (mag > 0.0f)
		{
			float xx, yy, zz, xy, yz, zx, xs, ys, zs;
			float oneMinusCos;

			x /= mag;
			y /= mag;
			z /= mag;

			xx = x * x;
			yy = y * y;
			zz = z * z;
			xy = x * y;
			yz = y * z;
			zx = z * x;
			xs = x * sinAngle;
			ys = y * sinAngle;
			zs = z * sinAngle;
			oneMinusCos = 1.0f - cosAngle;

			Matrix rotMat;
			rotMat.m11 = (oneMinusCos * xx) + cosAngle;
			rotMat.m12 = (oneMinusCos * xy) - zs;
			rotMat.m13 = (oneMinusCos * zx) + ys;
			rotMat.m14 = 0.0f;

			rotMat.m21 = (oneMinusCos * xy) + zs;
			rotMat.m22 = (oneMinusCos * yy) + cosAngle;
			rotMat.m23 = (oneMinusCos * yz) - xs;
			rotMat.m24 = 0.0f;

			rotMat.m31 = (oneMinusCos * zx) - ys;
			rotMat.m32 = (oneMinusCos * yz) + xs;
			rotMat.m33 = (oneMinusCos * zz) + cosAngle;
			rotMat.m34 = 0.0f;

			rotMat.m41 = 0.0f;
			rotMat.m42 = 0.0f;
			rotMat.m43 = 0.0f;
			rotMat.m44 = 1.0f;

			*this = rotMat * *this;
		}
	}

	void Matrix::Rotate(Quaternion q)
	{
		Matrix rotMat;

		rotMat.m11 = 1.0f - 2.0f * q.y * q.y - 2.0f * q.z * q.z;
		rotMat.m12 = 2.0f * q.x * q.y + 2.0f * q.z * q.w;
		rotMat.m13 = 2.0f * q.x * q.z - 2.0f * q.y * q.w;
		rotMat.m14 = 0.0f;

		rotMat.m21 = 2.0f * q.x * q.y - 2.0f * q.z * q.w;
		rotMat.m22 = 1.0f - 2.0f * q.x * q.x - 2.0f * q.z * q.z;
		rotMat.m23 = 2.0f * q.y * q.z + 2.0f * q.x * q.w;
		rotMat.m24 = 0.0f;

		rotMat.m31 = 2.0f * q.x * q.z + 2.0f * q.y * q.w;
		rotMat.m32 = 2.0f * q.y * q.z - 2.0f * q.x * q.w;
		rotMat.m33 = 1.0f - 2.0f * q.x * q.x - 2.0f * q.y * q.y;
		rotMat.m34 = 0.0f;

		rotMat.m41 = 0.0f;
		rotMat.m42 = 0.0f;
		rotMat.m43 = 0.0f;
		rotMat.m44 = 1.0f;

		*this = rotMat * *this;
	}


	void Matrix::TranslatePreRotScale(Vector3 translate)
	{
		m41 += m11 * translate.x + m21 * translate.y + m31 * translate.z;
		m42 += m12 * translate.x + m22 * translate.y + m32 * translate.z;
		m43 += m13 * translate.x + m23 * translate.y + m33 * translate.z;
		m44 += m14 * translate.x + m24 * translate.y + m34 * translate.z;
	}

	void Matrix::TranslatePreRotScale(float tx, float ty, float tz)
	{
		m41 += m11 * tx + m21 * ty + m31 * tz;
		m42 += m12 * tx + m22 * ty + m32 * tz;
		m43 += m13 * tx + m23 * ty + m33 * tz;
		m44 += m14 * tx + m24 * ty + m34 * tz;
	}

	void Matrix::Translate(Vector3 pos)
	{
		m41 += pos.x;
		m42 += pos.y;
		m43 += pos.z;
	}

	void Matrix::Translate(float x, float y, float z)
	{
		m41 += x;
		m42 += y;
		m43 += z;
	}

	void Matrix::CreateFrustum(float left, float right, float bottom, float top, float nearZ, float farZ)
	{
		float deltaX = right - left;
		float deltaY = top - bottom;
		float deltaZ = farZ - nearZ;

		assert(nearZ > 0.0f && farZ > 0.0f && deltaX > 0.0f && deltaY > 0.0f && deltaZ > 0.0f);

		m11 = 2.0f * nearZ / deltaX;
		m12 = m13 = m14 = 0.0f;

		m22 = 2.0f * nearZ / deltaY;
		m21 = m23 = m24 = 0.0f;

		m31 = (right + left) / deltaX;
		m32 = (top + bottom) / deltaY;
#if MYFW_RIGHTHANDED
		m33 = -(nearZ + farZ) / deltaZ;
		m34 = -1.0f;
#else
		m33 = (nearZ + farZ) / deltaZ;
		m34 = 1.0f;
#endif

		m43 = -2.0f * nearZ * farZ / deltaZ;
		m41 = m42 = m44 = 0.0f;
	}

	void Matrix::CreatePerspectiveVFoV(float vertfovdegrees, float aspect, float nearZ, float farZ)
	{
		float frustumRight, frustumTop;

		frustumTop = tanf(vertfovdegrees / 2 * PI / 180.0f) * nearZ;
		frustumRight = frustumTop * aspect;

		CreateFrustum(-frustumRight, frustumRight, -frustumTop, frustumTop, nearZ, farZ);
	}

	void Matrix::CreatePerspectiveHFoV(float horfovdegrees, float aspect, float nearZ, float farZ)
	{
		float frustumRight, frustumTop;

		frustumRight = tanf(horfovdegrees / 2 * PI / 180.0f) * nearZ;
		frustumTop = frustumRight / aspect;

		CreateFrustum(-frustumRight, frustumRight, -frustumTop, frustumTop, nearZ, farZ);
	}

	void Matrix::CreateOrtho(float left, float right, float bottom, float top, float nearZ, float farZ)
	{
		float deltaX = (right - left);
		float deltaY = (top - bottom);
		float deltaZ = (farZ - nearZ);

		assert((deltaX != 0.0f) && (deltaY != 0.0f) && (deltaZ != 0.0f));

		m11 = 2.0f / deltaX;
		m12 = m13 = m14 = 0;

		m22 = 2.0f / deltaY;
		m21 = m23 = m24 = 0;

#if MYFW_RIGHTHANDED
		m33 = -2.0f / deltaZ;
#else
		m33 = 2.0f / deltaZ;
#endif
		m31 = m32 = m34 = 0;

		m41 = -(right + left) / deltaX;
		m42 = -(top + bottom) / deltaY;
		m43 = -(farZ + nearZ) / deltaZ;
		m44 = 1;
	}

	void Matrix::CreateLookAtView(const Vector3& eye, const Vector3& up, const Vector3& at)
	{
#if MYFW_RIGHTHANDED
		Vector3 zaxis = (eye - at).Normalize();
#else
		Vector3 zaxis = (at - eye).Normalize();
#endif
		Vector3 xaxis = (up.Cross(zaxis)).Normalize();
		Vector3 yaxis = zaxis.Cross(xaxis);

		Vector3 pos = Vector3(-xaxis.Dot(eye), -yaxis.Dot(eye), -zaxis.Dot(eye));

		SetAxesView(xaxis, yaxis, zaxis, pos);
	}

	void Matrix::CreateLookAtWorld(const Vector3& objpos, const Vector3& up, const Vector3& at)
	{
		Vector3 zaxis = (at - objpos).Normalize();
		Vector3 xaxis = (up.Cross(zaxis)).Normalize();
		Vector3 yaxis = zaxis.Cross(xaxis);

		SetAxesWorld(xaxis, yaxis, zaxis, objpos);
	}

	Vector3 Matrix::GetEulerAngles()
	{
		// from http://www.geometrictools.com/Documentation/EulerAngles.pdf and adapted to fit

		//if( m32 < +1 )
		//{
		//    if( m32 > -1 )
		//    {
		//        float x = asin( m32 );
		//        float y = atan2( -m31, m33 );
		//        float z = atan2( -m12, m22 );
		//        return Vector3( x, y, z );
		//    }
		//    else // m32 = -1
		//    {
		//        // not a unique solution: thetaz - thetay = atan2(-m21,m11)
		//        float x = pi/2;
		//        float y = atan2( m21, m11 );
		//        float z = 0;
		//        return Vector3( x, y, z );
		//    }
		//}
		//else // m32 = +1
		//{
		//    // not a unique solution: thetaz + thetay = atan2(-m21,m11)
		//    float x = -pi/2;
		//    float y = -atan2( m21, m11 );
		//    float z = 0;
		//    return Vector3( x, y, z );
		//}

		// rearranged from above and using FEQUALEPSILON to give special cases more chance of hitting
		if (m32 > 1.0f - EPSILON) // Not a unique solution: thetaZ - thetaY = atan2( -m21, m11 )
		{
			float x = PI / 2;
			float y = atan2f(m21, m11);
			float z = 0.0f;
			return Vector3(x, y, z) * 180.0f / PI;
		}
		else if (m32 < -1.0f + EPSILON) // Not a unique solution: thetaZ + thetaY = atan2( -m21, m11 )
		{
			float x = -PI / 2;
			float y = -atan2f(m21, m11);
			float z = 0.0f;
			return Vector3(x, y, z) * 180.0f / PI;
		}
		else
		{
			float x = asinf(m32);
			float y = atan2f(-m31, m33);
			float z = atan2f(-m12, m22);
			return Vector3(x, y, z) * 180.0f / PI;
		}
	}

	Vector3 Matrix::GetScale()
	{
		Vector3 scale;
		scale.x = Vector3(m11, m12, m13).Length();
		scale.y = Vector3(m21, m22, m23).Length();
		scale.z = Vector3(m31, m32, m33).Length();
		return scale;
	}

	Vector3 Matrix::GetUp()
	{
		return Vector3(m21, m22, m23);
	}

	Vector3 Matrix::GetRight()
	{
		return Vector3(m11, m12, m13);
	}

	Vector3 Matrix::GetAt()
	{
		return Vector3(m31, m32, m33);
	}
}

