#include "MyVector2.h"

/// <summary>
/// get length of vector using sqrt of the sum of the squares
/// </summary>
/// <param name="t_vector">input vector</param>
/// <returns>length</returns>
float vectorLength(sf::Vector2f t_vector)
{
	float sumOfSquares = (t_vector.x * t_vector.x ) + (t_vector.y * t_vector.y);
	const float length = std::sqrt(sumOfSquares);
	return length;
}

float vectorLengthSquared(sf::Vector2f t_vector)
{
	//x2 + y2
	float answer = (t_vector.x * t_vector.x + t_vector.y * t_vector.y);

	return answer;
}

float vectorCorssProduct(sf::Vector2f t_vectorA, sf::Vector2f t_VectorB)
{
	float answer = (t_vectorA.x * t_VectorB.y - t_vectorA.y * t_VectorB.x);

	return answer;
}

float vectorDotProduct(sf::Vector2f t_vectorA, sf::Vector2f t_VectorB)
{
	float dotProduct = (t_vectorA.x * t_VectorB.y + t_vectorA.y * t_VectorB.x);

	return dotProduct ;
}

float vectorAngleBetween(sf::Vector2f t_vectorA, sf::Vector2f t_VectorB)
{

	float answer = acosf((vectorCorssProduct (t_vectorA, t_VectorB)) / (vectorLength(t_vectorA) * vectorLength(t_VectorB)));


	return answer;
}

sf::Vector2f vectorRotateBy(sf::Vector2f t_vector, float t_angleRadians)
{
	float mainAng = atanf(t_vector.y / t_vector.x);
	t_vector.x = vectorLength(t_vector) * cos(mainAng + t_angleRadians);
	t_vector.y = vectorLength(t_vector) * sin(mainAng + t_angleRadians);
	return sf::Vector2f();
}


sf::Vector2f vectorProjection(sf::Vector2f t_vector, sf::Vector2f t_onto)
{
	sf::Vector2f answer = vectorScalarProjection(t_vector, t_onto) * vectorUnitVector(t_onto);

	
	return answer;
}

sf::Vector2f vectorRejection(sf::Vector2f t_vector, sf::Vector2f t_onto)
{
	sf::Vector2f answer = (t_vector)-(vectorLength(t_vector) * vectorAngleBetween(t_vector, t_onto)) * vectorUnitVector(t_onto);


	return answer;
}

float vectorScalarProjection(sf::Vector2f t_vector, sf::Vector2f t_onto)
{
	float answer = vectorDotProduct(t_vector, t_onto) / vectorLength(t_onto);

	return answer;
}

sf::Vector2f vectorUnitVector(sf::Vector2f t_vector)
{
	float sumOfSquares = (t_vector.x * t_vector.x) + (t_vector.y * t_vector.y);
	float magnatitude = std::sqrt(sumOfSquares);
	float length = vectorLength(t_vector);
	float XCoOrd = t_vector.x / magnatitude;
	float yCoOrd = t_vector.y / magnatitude;

	return sf::Vector2f{ XCoOrd,yCoOrd };
}
