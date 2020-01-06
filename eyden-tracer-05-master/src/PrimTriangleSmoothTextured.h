#pragma once

#include "PrimTriangleSmooth.h"

/**
* @brief Smooth triangle primitive with support of textures class interface
*/
class CPrimTriangleSmoothTextured : public CPrimTriangleSmooth
{
public:
	CPrimTriangleSmoothTextured(Vec3f a, Vec3f b, Vec3f c, Vec3f na, Vec3f nb, Vec3f nc, Vec2f ta, Vec2f tb, Vec2f tc, std::shared_ptr<IShader> pShader)
		: CPrimTriangleSmooth(a, b, c, na, nb, nc, pShader)
		, m_ta(ta)
		, m_tb(tb)
		, m_tc(tc)
	{}
	virtual ~CPrimTriangleSmoothTextured(void) = default;
  
	virtual Vec2f getUV(const Ray& ray) const override
	{
		// assume u/v coordinates in ray correspond to beta(u) and gamma(v) barycentric coordinates of 
		// hitpoint on triangle (have to be stored like this in the intersection code !)
		return Vec2f(
					 m_tb.val[0] * ray.u + m_tc.val[0] * ray.v + m_ta.val[0] * (1.0f - ray.u - ray.v),		// x-coord
					 m_tb.val[1] * ray.u + m_tc.val[1] * ray.v + m_ta.val[1] * (1.0f - ray.u - ray.v)		// y-coord
		);
	}


private:
	Vec2f m_ta;	///< vertex a texture coordiante
	Vec2f m_tb;	///< vertex b texture coordiante
	Vec2f m_tc;	///< vertex c texture coordiante 
};	

