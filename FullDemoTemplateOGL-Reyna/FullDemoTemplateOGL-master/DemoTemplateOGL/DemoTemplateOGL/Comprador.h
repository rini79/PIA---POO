#pragma once
#ifndef COMPRADOR_H
#define COMPRADOR_H

#include "Base/model.h"
#include "Producto.h"
#include <iostream>

class Comprador :
	public Model {
private: 
	float Compras;
   /*virtual*/ int Producto; /** getCompras() = 0;*/

public:
    // Constructor del jugador
    Comprador(const std::string& path, glm::vec3 position, Camera* camera, float Compras)
        : Model(path, camera), Compras(Compras) {
        setTranslate(&position);
    }

    // Verifica si el jugador está colisionando con un producto
    bool checkCollision(Model& model) {
        if (this->colisionaCon(model)) {
            MessageBox(NULL, L"Me lo llevo!", L"Producto adquirido", MB_OK | MB_ICONEXCLAMATION);
            return true;
        }
        return false;
    }

    float getCompras() const {
        return Compras;
    }
};


#endif
