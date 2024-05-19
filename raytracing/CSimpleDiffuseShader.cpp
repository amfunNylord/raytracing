#include "stdafx.h"
#include "CSimpleDiffuseShader.h"
#include "libgl/CVector4.h"
#include "libgl/CScene.h"
#include "libgl/CShadeContext.h"
#include "ILightSource.h"
#include "libgl/VectorMath.h"

CSimpleDiffuseShader::CSimpleDiffuseShader(void)
{
}

/*
Запоминаем параметры материала, связанного с шейдером
*/
void CSimpleDiffuseShader::SetMaterial(CSimpleMaterial const& material)
{
	m_material = material;
}

CVector4f CSimpleDiffuseShader::Shade(CShadeContext const & shadeContext)const
{
	/*
	Получаем сцену из контекста закрашивания для того, чтобы вычислить вклад
	каждого из источников света в освещенность обрабатываемой точки
	*/
	CScene const& scene = shadeContext.GetScene();

	// Результирующий цвет
	CVector4f shadedColor;

	const size_t numLights = scene.GetLightsCount();

	// Пробегаемся по всем источникам света в сцене
	for (size_t i = 0; i < numLights; ++i)
	{
		// Получаем источник света
		ILightSource const& light = scene.GetLight(i);

		// Вычисляем вектор направления на источник света из текущей точке
		CVector3d lightDirection = light.GetDirectionFromPoint(shadeContext.GetSurfacePoint());

		// Вычисляем интенсивность света в направлении от источника к текущей точке
		double lightIntensity = light.GetIntensityInDirection(-lightDirection);

		// Получаем нормаль к поверхности в обрабатываемой точке
		CVector3d const& n = shadeContext.GetSurfaceNormal();

		// Вычисляем скалярное произведение нормали и орт-вектора направления на источник света
		double nDotL = Max(Dot(n, Normalize(lightDirection)), 0.0);
		
		// Вычисляем диффузный цвет точки
		CVector4f diffuseColor = static_cast<float>(nDotL * lightIntensity) * light.GetDiffuseIntensity() * m_material.GetDiffuseColor();

		// К результирующему цвету прибавляется вычисленный диффузный цвет
		shadedColor += diffuseColor;

		CVector4f ambientColor = light.GetAmbientIntensity() * m_material.GetAmbientColor();
		shadedColor += ambientColor;

		// вектор отраженного света R
		CVector3d reflectedLightVector = 2 * Dot(n, Normalize(lightDirection)) * n - lightDirection;
		CVector4f specularColor = m_material.GetSpecularColor() * light.GetSpecularIntensity() * pow(Max(0.0, Dot(reflectedLightVector, lightDirection)), m_material.GetShiness()); // мб здесь траблы

		shadedColor += specularColor;

	}	// Проделываем данные действия для других источников света

	// Возвращаем результирующий цвет точки
	return shadedColor;
}