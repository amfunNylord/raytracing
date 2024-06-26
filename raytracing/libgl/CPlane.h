﻿#pragma once
#include "CGeometryObjectImpl.h"
#include "CVector4.h"
#include "CMatrix_fwd.h"

/*
Геометрический объект "бесконечная плоскость"
*/
class CPlane : public CGeometryObjectImpl
{
public:
	/*
	Плоскость задается коэффициентами уравления плоскости ax+by+cz+d=0,
	а также матрицей начального преобразования плоскости
	*/
	CPlane(double a, double b, double c, double d, CMatrix4d const & transform = CMatrix4d());

	/*
	Нахождение точки пересечения луча с плоскостью
	*/
	virtual bool Hit(CRay const& ray, CIntersection & intersection)const;
private:
	// Четырехмерный вектор, хранящий коэффициенты уравнения плоскости
	CVector4d m_planeEquation;
};
