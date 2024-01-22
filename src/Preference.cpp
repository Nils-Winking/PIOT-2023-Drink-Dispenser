//
// Created by Emilia on 24.12.2023.
//

#include "Preference.h"
//#define debug

int getNumberOfIngredients(const String &preferenceString){
    int num=0;
    for (const auto &item: preferenceString){
        if (item == ':'){
            ++num;
        }
    }
    return num;
}

Ingredient getNIngredient(char *preferenceString, int n){
//    int pos=0;
//    for (int i = 0; i < n+1; ++i){
//        preferenceString.indexOf('_', pos);
//    }
    auto piece = strtok(preferenceString, "_");
    for (int i = 0; i < n+1; ++i){
#ifdef debug
        Serial.println(piece);
#endif
        piece = strtok(nullptr, "_");
    }
#ifdef debug
    Serial.println(piece);
#endif
    auto keyValue = strtok(piece, ":");
#ifdef debug
    Serial.print("id: ");
    Serial.println(keyValue);
#endif
    auto ingredientID = atoi(keyValue);
    keyValue = strtok(nullptr, ":");
#ifdef debug
    Serial.print("p: ");
    Serial.println(keyValue);
#endif
    auto ingredientPercentage = atoi(keyValue);
    auto ingredient = new Ingredient(ingredientID, ingredientPercentage);
    return *ingredient;
}

Ingredient Preference::getIngredient(int index) {
    return ingredients[index];
}


int Preference::getIngredientCount() {
    return ingredientCount;
}

Preference::Preference(const String &fromString) {
    this->ingredientCount = getNumberOfIngredients(fromString);

    for (int i = 0; i < ingredientCount; ++i){
        auto length = fromString.length()+1;
        char *buffer= new char[length];
        fromString.toCharArray(buffer, length);
        this->ingredients[i] = getNIngredient(buffer, i);
    }
}

bool isValidAndSet(const String &preferenceString) {
    return preferenceString.startsWith("1");
}
