#include "Vec2.h"
#include "math.h"

// Constructors
Vec2::Vec2(){};
Vec2::Vec2(float xin, float yin)
: x(xin), y(yin) {};

// Equality operations
bool Vec2::operator == (const Vec2 & rhs) const
{
    if(this->x == rhs.x && this->y == rhs.y)
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

bool Vec2::operator != (const Vec2 & rhs) const
{
    if(this->x ==  rhs.x && this->y == rhs.y)
    {
        return false;
    }
    else
    {
        return true;
    }
    
}

// Basic Math Operators
Vec2 Vec2::operator + (const Vec2 & rhs) const
{
    return Vec2(this->x + rhs.x,this->y + rhs.y);
}

Vec2 Vec2::operator - (const Vec2 & rhs) const
{
    return Vec2(this->x - rhs.x, this->y - rhs.y);
}

Vec2 Vec2::operator * (const float val) const
{
    return Vec2(this->x * val, this->y * val);
}

Vec2 Vec2::operator / (const float val) const
{
    return Vec2(this->x / val, this->y / val);
}

// Combination Math Operators
void Vec2::operator += (const Vec2 & rhs) 
{
    this->x = this->x + rhs.x;
    this->y = this->y + rhs.y;
}

void Vec2::operator -= (const Vec2 & rhs) 
{
    this->x = this->x - rhs.x;
    this->y = this->y - rhs.y;
}

void Vec2::operator *= (const float val) 
{
    this->x = this->x * val;
    this->y = this->y * val;
}

void Vec2::operator /= (const float val) 
{
    this->x = this->x / val;
    this->y = this->y / val;
}