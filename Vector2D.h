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
	Vector2D operator+(const Vector2D& otherV) const;//����
	Vector2D operator-(const Vector2D& otherV) const;//����
	double dot(const Vector2D& rhs);//����
	double cross(const Vector2D& rhs);//����
	Vector2D operator*(double n);//��Į����� ��
	Vector2D operator/(double n);//��Į����� ������
	Vector2D& operator=(const Vector2D& rhs);
	Vector2D rotate(double radian);//ȸ��
	Vector2D rotate(const Vector2D& otherV, double radian); //�� ���� ȸ�� 
	Vector2D normalize();//����ȭ(��������ȭ)
	double getlength();
	double getlengthsq();
};

