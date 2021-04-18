

#include <string>
#include "RenderSystem.h"
#include "../OpenGL.h"
#include "../Components/Shape.h"
#include "../Components/Line.h"
#include "../Components/Health.h"
#include "../Components/HealthBar.h"
#include "../Components/Particle.h"
#include "../Components/Text.h"
#include "../GameModel.h"
#include "../Components/Helpers.h"
#include "../Components/Kinematics.h"

void RenderSystem::update(EntityManager &entities, double dt) {
    drawScore();
    drawEntities(entities);
}

void RenderSystem::drawEntities(EntityManager &entities) {
    for (Entity* entity: entities.getEntitiesWith<Transform, Texture>()) {
        Transform *transform = entity->get<Transform>();
        Texture *texture = entity->get<Texture>();

        if (entity->has<Health, HealthBar>()) {
            drawHealthBars(entity);
        }

        glPushMatrix();
            glTranslatef(transform->position.x, transform->position.y, 0);
            glRotatef(transform->rotation, 0, 0, 1);
            glScalef(transform->scale.x, transform->scale.y, 1);
            glColor3f(texture->red, texture->green, texture->blue);

            if (entity->has<Shape>()) {
                drawShape(entity);
            } else if (entity->has<Line>()) {
                drawLine(entity);
            } else if (entity->has<Particle>()) {
                drawParticle(entity);
            }
        glPopMatrix();
    }
}

void RenderSystem::drawScore() {
    glColor3f(1, 1, 1);
    int arenaSize = gameModel.arenaSize;
    renderString(-arenaSize, arenaSize + 2, "Score: " + std::to_string(gameModel.score),
                 TextAlignment::LEFT);

    renderString(0, arenaSize + 2, "Wave: " + std::to_string(gameModel.waveCount),
                 TextAlignment::CENTER);

    renderString(arenaSize, arenaSize + 2, "Time: " + formatTime(gameModel.elapsedTime),
                 TextAlignment::RIGHT);
}

void
RenderSystem::renderString(GLdouble x, GLdouble y, const std::string &string,
                           TextAlignment alignment)
{
    double width = 0;
    for (int n = 0; n < string.size(); ++n) {
        width += glutBitmapWidth(GLUT_BITMAP_HELVETICA_18, string[n]);
    }

    width = width / gameModel.getWorldToPixelRatioWidth();

    double offset = 0;
    if (alignment == TextAlignment::CENTER) {
        offset = width / 2;
    } else if (alignment == TextAlignment::RIGHT) {
        offset = width;
    }

    glRasterPos2d(x - offset, y);
    for (int n = 0; n < string.size(); ++n) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[n]);
    }
}



void RenderSystem::drawParticle(Entity *entity) const {
    int size = entity->get<Particle>()->size;
    glPointSize(size);
    glBegin(GL_POINTS);
    glVertex3f(0, 0, 0);
    glEnd();
}

void RenderSystem::drawLine(Entity *entity) const {
    Line *line = entity->get<Line>();
    glLineWidth(2.0);
    glBegin(GL_LINES);
    {
        glVertex3f(line->start.x, line->start.y, 0);
        glVertex3f(line->end.x, line->end.y, 0);
    }
    glEnd();
}

void RenderSystem::drawShape(Entity *entity) const {
    Shape *shape = entity->get<Shape>();

    glLineWidth(2.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_POLYGON);
    {
        for(Vec2 vertex: shape->vertices) {
            glVertex3f(vertex.x, vertex.y, 0);
        }
    }
    glEnd();
}

void RenderSystem::drawHealthBars(Entity *entity) const {
    Transform *transform = entity->get<Transform>();

    glPushMatrix();
    glTranslatef(transform->position.x, transform->position.y, 0);
    glScalef(transform->scale.x, transform->scale.y, 1);

    int width = 10;
    Health *health = entity->get<Health>();
    double healthWidth = width * ((double) health->health / (double) health->maxHealth);

    glBegin(GL_POLYGON);
    {
        glColor3f(1, 1, 1);
        glVertex3f(-5, -0.2, 0);
        glVertex3f(5, -0.2, 0);
        glVertex3f(5, 0.2, 0);
        glVertex3f(-5, 0.2, 0);

        glColor3f(1, 0, 0);
        glVertex3f(-5, -0.2, 0);
        glVertex3f(healthWidth - 5, -0.2, 0);
        glVertex3f(healthWidth - 5, 0.2, 0);
        glVertex3f(-5, 0.2, 0);
    }
    glEnd();
    glPopMatrix();
}

