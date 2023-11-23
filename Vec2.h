#pragma once
class Vec2
{
    public:
    // Attributes
    float x = 0;
    float y = 0;

    // Constructor
    Vec2();
    Vec2(float xin, float yin);

    bool operator == (const Vec2 & rhs) const;
    bool operator != (const Vec2 & rhs) const;

    Vec2 operator + (const Vec2 & rhs) const;
    Vec2 operator - (const Vec2 & rhs) const;
    Vec2 operator * (const float val) const;
    Vec2 operator / (const float val) const;

    void operator += (const Vec2 & rhs);
    void operator -= (const Vec2 & rhs);
    void operator *= (const float val);
    void operator /= (const float val);

    // Distance between two Vec2s
    float distance(const Vec2 & rhs) const;

};