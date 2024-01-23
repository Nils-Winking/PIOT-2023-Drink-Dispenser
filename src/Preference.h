//
// Created by Emilia on 24.12.2023.
//
#ifndef PIOT_2023_DRINK_DISPENSER_PREFERENCE_H
#define PIOT_2023_DRINK_DISPENSER_PREFERENCE_H

#include "Ingredient.h"
#include <Arduino.h>

#define maxIngredients 10

class Preference {
public:
    explicit Preference(const String &fromString);
    Ingredient getIngredient(int index);
    int getIngredientCount();
private:
    int ingredientCount;
    Ingredient ingredients[maxIngredients];
};

bool isValidAndSet(const String &preferenceString);

#endif //PIOT_2023_DRINK_DISPENSER_PREFERENCE_H
