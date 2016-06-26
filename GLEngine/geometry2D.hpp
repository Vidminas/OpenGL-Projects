class Vector
{
    friend class Point;
private:
    float x, y, z;

public:
    Vector();
    Vector (float x, float y, float z);

    Vector operator+ (const Vector& rhs);
    Vector operator-  (const Vector& rhs);
    Vector yaw   (float angle);
    Vector pitch (float angle);
    Vector roll    (float angle);
    Vector scale (float xFactor, float yFactor, float zFactor);
};

class Point
{
private:
    float x, y, z;
    float r, g, b;

public:
    Point();
    Point (float x, float y, float z);
    Point (float x, float y, float z, float r, float g, float b);

    void     operator= (const Point& rhs);
    Point   operator+ (const Point& rhs);
    Vector operator-  (const Point& rhs);
    Point   operator+ (const Vector& rhs);
    Point   operator-  (const Vector& rhs);

    const float getX() const;
    const float getY() const;
    const float getZ() const;
    const float getR() const;
    const float getG() const;
    const float getB() const;
};
