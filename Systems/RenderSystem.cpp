//
// Created by Karl Rombauts on 14/3/21.
//

#include "RenderSystem.h"
#include "../Components/Transform.h"
#include "../Components/Rotation.h"
#include "../OpenGL.h"

void RenderSystem::update(EntityManager &entities, double dt) {
    for (Entity* entity: entities.getEntitiesWith<Transform>()) {
        Transform *transform = entity->get<Transform>();

        glColor3f(1.0, 1.0, 1.0);
        glPushMatrix();
        glTranslatef(transform->position.x, transform->position.y, 0);
        glRotatef(transform->rotation, 0, 0, 1);
        glBegin(GL_POLYGON);
        {
            glVertex3f(-0.1, -0.1, 0);
            glVertex3f(0.1, -0.1, 0);
            glVertex3f(0.1, 0.1, 0);
            glVertex3f(-0.1, 0.1, 0);
        }
        glEnd();
        glPopMatrix();
    }
}

