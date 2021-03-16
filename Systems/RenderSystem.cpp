//
// Created by Karl Rombauts on 14/3/21.
//

#include "RenderSystem.h"
#include "../Components/Transform.h"
#include "../Components/Rotation.h"
#include "../OpenGL.h"
#include "../Components/Texture.h"
#include "../Components/Moveable.h"
#include "../Components/Shape.h"

void RenderSystem::update(EntityManager &entities, double dt) {
    for (Entity* entity: entities.getEntitiesWith<Transform, Texture>()) {
        Transform *transform = entity->get<Transform>();
        Texture *texture = entity->get<Texture>();

        glColor3f(texture->red, texture->green, texture->blue);
        glPushMatrix();
        glTranslatef(transform->position.x, transform->position.y, 0);
        glRotatef(transform->rotation, 0, 0, 1);
        glScalef(transform->scale.x, transform->scale.y, 1);

        if (entity->has<Shape>()) {
            Shape *shape = entity->get<Shape>();

            glPointSize(3.0);
            glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
            glBegin(GL_POLYGON);
            {
                for(Vec2 vertex: shape->vertices) {
                    glVertex3f(vertex.x, vertex.y, 0);
                }
            }
            glEnd();
        }
        else {

            glBegin(GL_POLYGON);
            {
                glVertex3f(-0.1, -0.1, 0);
                glVertex3f(0.1, -0.1, 0);
                glVertex3f(0.1, 0.1, 0);
                glVertex3f(-0.1, 0.1, 0);
            }
            glEnd();
        }
        glPopMatrix();

        if (entity->has<Moveable>()) {

            glColor3f(0.0,0.4,0.2);
            glPointSize(3.0);
            glBegin(GL_LINES);
            {
                Moveable *moveable = entity->get<Moveable>();
                Vec2 start = transform->position;
                Vec2 end = transform->position + moveable->acceleration;

                glVertex3f(start.x, start.y, 10);
                glVertex3f(end.x, end.y, 10);
            }
            glEnd();
        }
    }
}

