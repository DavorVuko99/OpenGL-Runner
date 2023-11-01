#include "rect.h"
#include "circle.h"

Rect::Rect(Shader & shader, vec2 pos, vec2 size, struct color color)
    : Shape(shader, pos, size, color) {
    initVectors();
    initVAO();
    initVBO();
    initEBO();
}

Rect::Rect(Rect const& other) : Shape(other) {
    initVectors();
    initVAO();
    initVBO();
    initEBO();
}

Rect::~Rect() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Rect::draw() const {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Rect::initVectors() {
    this->vertices.insert(vertices.end(), {
        -0.5f, 0.5f,   // Top left
         0.5f, 0.5f,   // Top right
        -0.5f, -0.5f,  // Bottom left
         0.5f, -0.5f   // Bottom right
    });

    this->indices.insert(indices.end(), {
        0, 1, 2, // First triangle
        1, 2, 3  // Second triangle
    });
}
// Overridden Getters from Shape
float Rect::getLeft() const        { return pos.x - (size.x / 2); }
float Rect::getRight() const       { return pos.x + (size.x / 2); }
float Rect::getTop() const         { return pos.y + (size.y / 2); }
float Rect::getBottom() const      { return pos.y - (size.y / 2); }

bool Rect::isOverlapping(const Rect &r1, const Rect &r2) {
    // Calculate the right and left edges of each rectangle
    float r1Left = r1.getLeft();
    float r1Right = r1.getRight();
    float r2Left = r2.getLeft();
    float r2Right = r2.getRight();

    // Calculate the top and bottom edges of each rectangle
    float r1Top = r1.getTop();
    float r1Bottom = r1.getBottom();
    float r2Top = r2.getTop();
    float r2Bottom = r2.getBottom();

    // Check if one rectangle is to the left of the other
    if (r1Right < r2Left || r2Right < r1Left) {
        // They are to the left of each other, so not overlapping
        return false;
    }

    // Check if one rectangle is above the other
    if (r1Top < r2Bottom || r2Top < r1Bottom) {
        // They are above each other, so not overlapping
        return false;
    }

    // If the above conditions are not met, the rectangles are overlapping
    return true;
}


bool Rect::isOverlapping(const Rect &other) const {
    return isOverlapping(*this, other);
}

bool Rect::isOverlapping(const Shape &other) const {
    // Dynamic cast to check if the other shape is a Rect
    const Rect* otherRect = dynamic_cast<const Rect*>(&other);
    if (otherRect) {
        return isOverlapping(*this, *otherRect);
    }
    return false;
}