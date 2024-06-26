﻿#pragma once
#include "ILightSource.h"
#include "libgl/CMatrix4.h"
#include "libgl/CVector4.h"

/*
Реализация методов, общих для различных типов источников света
*/
class CLightSourceImpl :
	public ILightSource
{
public:
	/*
	Получение матрицы трансформации источника света
	*/
	CMatrix4d const& GetTransform()const
	{
		return m_transform;
	}

	/*
	Установка матрицы трансформации источника света
	*/
	void SetTransform(CMatrix4d const& transform)
	{
		m_transform = transform;
	}

	/*
	Установка интенсивности диффузной составляющей света
	*/
	virtual void SetDiffuseIntensity(CVector4f const& diffuseIntensity)
	{
		m_diffuseIntensity = diffuseIntensity;
	}

	/*
	Получение интенсивности диффузной составляющей источника света
	*/
	virtual CVector4f const& GetDiffuseIntensity()const
	{
		return m_diffuseIntensity;
	}

	virtual void SetAmbientIntensity(CVector4f const& ambientIntensity)
	{
		m_ambientIntensity = ambientIntensity;
	}

	virtual CVector4f const& GetAmbientIntensity() const
	{
		return m_ambientIntensity;
	}

	virtual void SetSpecularIntensity(CVector4f const& specularIntesity)
	{
		m_specularIntesity = specularIntesity;
	}

	virtual CVector4f const& GetSpecularIntensity() const
	{
		return m_specularIntesity;
	}

protected:
	CLightSourceImpl(CMatrix4d const& transform = CMatrix4d())
		:m_transform(transform)
	{
	}

private:
	CVector4f m_specularIntesity;
	CVector4f m_ambientIntensity;
	CVector4f m_diffuseIntensity;
	CMatrix4d m_transform;

};
