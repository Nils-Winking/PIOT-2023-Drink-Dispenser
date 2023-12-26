//
// Created by Emilia on 24.12.2023.
//

#include "Ingredient.h"

int Ingredient::getAmount() {
    return amount;
}

int Ingredient::getId() {
    return id;
}

Ingredient::Ingredient(int id, int amount) : id(id), amount(amount) {}
