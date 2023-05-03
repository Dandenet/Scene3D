#pragma once

namespace graphics {

    struct Vector3D
    {
        float a[3];

        Vector3D(float x, float y, float z)
        {
            a[0] = x;
            a[1] = y;
            a[2] = z;
        }

        Vector3D(const Vector3D& other)
        {
            a[0] = other.a[0];
            a[1] = other.a[1];
            a[2] = other.a[2];

        }

        Vector3D& operator= (const Vector3D& other)
        {
            a[0] = other.a[0];
            a[1] = other.a[1];
            a[2] = other.a[2];

            return *this;
        }
    };

    class Vertex
    {
    public:



        Vertex(const Vector3D& aPoint, const Vector3D& aColor, const Vector3D& aNormal) :
            point(aPoint), color(aColor), normal(aNormal)
        {
            
        }  


        Vector3D point;
        Vector3D color;
        Vector3D normal;
        
    };

}
