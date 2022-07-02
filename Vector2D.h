#pragma once
class Vector2D
{
private:
	

public:
	double x;
	double y;
	Vector2D();
	Vector2D(double x, double y);
	Vector2D(const Vector2D& vec);
	Vector2D operator+(const Vector2D& otherV) const;//µ¡¼À
	Vector2D operator-(const Vector2D& otherV) const;//»¬¼À
	double dot(const Vector2D& rhs);//³»Àû
	double cross(const Vector2D& rhs);//¿ÜÀû
	Vector2D operator*(double n);//½ºÄ®¶ó¿ÍÀÇ °ö
	Vector2D operator/(double n);//½ºÄ®¶ó¿ÍÀÇ ³ª´°¼À
	Vector2D& operator=(const Vector2D& rhs);
	Vector2D rotate(double radian);//È¸Àü
	Vector2D rotate(const Vector2D& otherV, double radian); //Ãà ±âÁØ È¸Àü 
	Vector2D normalize();//Á¤±ÔÈ­(´ÜÀ§º¤ÅÍÈ­)
	double getlength();
	double getlengthsq();
};

