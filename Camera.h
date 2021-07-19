#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera
{
private:
    glm::mat4 m_perspective;
    glm::vec3 m_position;
    glm::vec3 m_forward;
    glm::vec3 m_up;
public:
    Camera(const glm::vec3 pos,float fov,float aspect,float near,float far):
        m_position(pos),m_forward(glm::vec3(0,0,1)),m_up(glm::vec3(0,1,0))
    {
        m_perspective = glm::perspective(fov,aspect,near,far);
    }
    ~Camera(){}

    glm::mat4 getviewproj() const{
        return m_perspective * glm::lookAt(m_position,glm::vec3(0.0f),m_up);
    }

    void setpos(const glm::vec3 n_pos) {m_position = n_pos;}
};
