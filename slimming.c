#include <stdio.h>
#include <stdlib.h>
#include "slimming.h"

// calcule du niveau d'énergie d'un pixel
float getPixelEnergy(const PNMImage* image, size_t x, size_t y);
float getRedPixelEnergy(const PNMImage* image, size_t x, size_t y);
float getGreenPixelEnergy(const PNMImage* image, size_t x, size_t y);
float getBluePixelEnergy(const PNMImage* image, size_t x, size_t y);

// calcule de la carte d'énergie
float** createEnergyMap(const PNMImage* image);
void freeEnergyMap(float** energyMap, const PNMImage* image);


// structure retenan le chemin du sillon le plus cour
typedef struct sillon_energie_path
{
   float energy;
   size_t* path; 
} Sillon_energie_path;

PNMImage* reduceImageWidth(const PNMImage* image, size_t k)
{
    // calcule la map d'énergie
    float** energyMap = createEnergyMap(image);

    // réduit la taille de l'image


    // libére la map d'énergie
    freeEnergyMap(energyMap, image);

    return (PNMImage*)image;
}

float getPixelEnergy(const PNMImage* image, size_t x, size_t y)
{
    // calcule le niveau d'énerfie d'un pixel
    return getRedPixelEnergy(image, x, y) + getGreenPixelEnergy(image, x, y) + getBluePixelEnergy(image, x, y);
}

float getRedPixelEnergy(const PNMImage* image, size_t x, size_t y)
{
    float energy = 0;
    // calcule le niveau d'énergie d'un pixel

    // calacule l'énergie du membre de droite de l'équation
    float tmp_energy = 0;
    if (x == 0)
    {
        tmp_energy = (*image).data[x * (*image).width + y].red;
    }
    else
    {
        tmp_energy = (*image).data[(x - 1) * (*image).width + y].red;
    }

    if (x == (*image).width)
    {
        tmp_energy = abs((*image).data[x * (*image).width + y].red - tmp_energy);
    }
    else
    {
        tmp_energy = abs((*image).data[(x + 1) * (*image).width + y].red - tmp_energy);
    }
    energy += (float)tmp_energy / 2;

    // calacule l'énergie du membre de gauche de l'équation
    tmp_energy = 0;
    if (y == 0)
    {
        tmp_energy = (*image).data[x * (*image).width + y].red;
    }
    else
    {
        tmp_energy = (*image).data[x * (*image).width + (y - 1)].red;
    }

    if (y == (*image).height)
    {
        tmp_energy = abs((*image).data[x * (*image).width + y].red - tmp_energy);
    }
    else
    {
        tmp_energy = abs((*image).data[x * (*image).width + (y + 1)].red - tmp_energy);
    }
    energy += (float)tmp_energy / 2;

    return energy;
}

float getGreenPixelEnergy(const PNMImage* image, size_t x, size_t y)
{
    float energy = 0;
    // calcule le niveau d'énergie d'un pixel

    // calacule l'énergie du membre de droite de l'équation
    float tmp_energy = 0;
    if (x == 0)
    {
        tmp_energy = (*image).data[x * (*image).width + y].green;
    }
    else
    {
        tmp_energy = (*image).data[(x - 1) * (*image).width + y].green;
    }

    if (x == (*image).width)
    {
        tmp_energy = abs((*image).data[x * (*image).width + y].green - tmp_energy);
    }
    else
    {
        tmp_energy = abs((*image).data[(x + 1) * (*image).width + y].green - tmp_energy);
    }
    energy += (float)tmp_energy / 2;

    // calacule l'énergie du membre de gauche de l'équation
    tmp_energy = 0;
    if (y == 0)
    {
        tmp_energy = (*image).data[x * (*image).width + y].green;
    }
    else
    {
        tmp_energy = (*image).data[x * (*image).width + (y - 1)].green;
    }

    if (y == (*image).height)
    {
        tmp_energy = abs((*image).data[x * (*image).width + y].green - tmp_energy);
    }
    else
    {
        tmp_energy = abs((*image).data[x * (*image).width + (y + 1)].green - tmp_energy);
    }
    energy += (float)tmp_energy / 2;

    return energy;
}

float getBluePixelEnergy(const PNMImage* image, size_t x, size_t y)
{

    float energy = 0;
    // calcule le niveau d'énergie d'un pixel

    // calacule l'énergie du membre de droite de l'équation
    float tmp_energy = 0;
    if (x == 0)
    {
        tmp_energy = (*image).data[x * (*image).width + y].blue;
    }
    else
    {
        tmp_energy = (*image).data[(x - 1) * (*image).width + y].blue;
    }

    if (x == (*image).width)
    {
        tmp_energy = abs((*image).data[x * (*image).width + y].blue - tmp_energy);
    }
    else
    {
        tmp_energy = abs((*image).data[(x + 1) * (*image).width + y].blue - tmp_energy);
    }
    energy += (float)tmp_energy / 2;

    // calacule l'énergie du membre de gauche de l'équation
    tmp_energy = 0;
    if (y == 0)
    {
        tmp_energy = (*image).data[x * (*image).width + y].blue;
    }
    else
    {
        tmp_energy = (*image).data[x * (*image).width + (y - 1)].blue;
    }

    if (y == (*image).height)
    {
        tmp_energy = abs((*image).data[x * (*image).width + y].blue - tmp_energy);
    }
    else
    {
        tmp_energy = abs((*image).data[x * (*image).width + (y + 1)].blue - tmp_energy);
    }
    energy += (float)tmp_energy / 2;

    return energy;
}

// calcule de la carte d'énergie
float** createEnergyMap(const PNMImage* image)
{
    // alloue la mémoire
    float** energyMap = (float**)malloc(sizeof(float*) * (*image).width);
    for (size_t i=0; i < (*image).width; i++)
    {
        // alloue de la mémoire pour la rangée
        energyMap[i] = (float*)malloc(sizeof(float) * (*image).height);
    }


    for (size_t i=0; i < (*image).width; i++)
    {
        for (size_t j=0; j < (*image).height; j++)
        {
            // ajoute l'énergie a la carte
            energyMap[i][j] = getPixelEnergy(image, j, i);
            
        }
    }
    return energyMap;
}

void freeEnergyMap(float** energyMap, const PNMImage* image)
{
    // libère la mémoire de la map
    for (size_t i=0; i < (*image).width; i++)
    {
        // libére la mémoire pour la rangée
        free(energyMap[i]);
    }   
    free(energyMap);
}
