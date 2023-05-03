#pragma once

#include <glm/glm.hpp>

namespace graphics {

    class Vertex
    {
    public:



        Vertex(const glm::vec3& aPoint, const glm::vec3& aColor, const glm::vec3& aNormal) :
            point(aPoint), color(aColor), normal(aNormal)
        {
            
        }  


        glm::vec3 point;
        glm::vec3 color;
        glm::vec3 normal;
        
    };

}
