#pragma once
#ifndef PRODUCTO_H
#define PRODUCTO_H

#include "Base/model.h"
#include "Comprador.h"
#include <iostream>

class Producto :
	public Model {
private:
	float disponible;

public:
    // Constructor del jugador
    Producto(const std::string& path, glm::vec3 position, Camera* camera, float disponible = 0)
        : Model(path, camera), disponible(disponible) {
        setTranslate(&position);
    }

    // Verifica si el jugador está colisionando con otro objeto
    bool checkCollision(Model& model) {
        if (this->colisionaCon(model)) {
            return true;
        }
        return false;
    }

    float getDisponible() const {
        return disponible;
    }

};

#endif
