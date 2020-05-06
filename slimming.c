#include <stdio.h>
#include <stdlib.h>
#include "slimming.h"

// structure retenant le chemin du sillon le plus cour
typedef struct sillon_energie_path
{
   float energy;
   size_t* path; 
} Sillon_energie_path;


// calcule du niveau d'énergie d'un pixel
float getPixelEnergy(const PNMImage* image, size_t x, size_t y);
float getRedPixelEnergy(const PNMImage* image, size_t x, size_t y);
float getGreenPixelEnergy(const PNMImage* image, size_t x, size_t y);
float getBluePixelEnergy(const PNMImage* image, size_t x, size_t y);

// calcule de la carte d'énergie
float** createEnergyMap(const PNMImage* image);
void freeEnergyMap(float** energyMap, const PNMImage* image);

// calcule de la carte des chemin d'énergie minimal
float** get_less_energy_path_map(const float** energyMap, size_t width, size_t height);

// calcule le sillon d energie minimal
Sillon_energie_path* less_energy_sillon(const float** less_energy_path_map, size_t width, size_t height, size_t i, size_t j);

PNMImage* reduceImageWidth(const PNMImage* image, size_t k)
{
    // calcule la map d'énergie
    float** energyMap = createEnergyMap(image);
    printf("energyMap ok \n");

    // test
    float** less_energy_path_map = get_less_energy_path_map(energyMap, (*image).width, (*image).height);
    printf("less_energy_path_map ok \n");

    Sillon_energie_path* sillon = less_energy_sillon(less_energy_path_map, (*image).width, (*image).height, 100 ,(*image).height - 1);
    printf("sillon energy: %f ok\n", (*sillon).energy);

    for (size_t j = 0; j < (*image).height; j++)
    {
        (*image).data[ j * (*image).width + (*sillon).path[j]].red = 0;
        (*image).data[ j * (*image).width + (*sillon).path[j]].green = 0;
        (*image).data[ j * (*image).width + (*sillon).path[j]].blue = 0;
    }

    // réduit la taille de l'image


    // libére la map d'énergie

    printf("ok\n");

    return (PNMImage*)image;
}

float getPixelEnergy(const PNMImage* image, size_t x, size_t y)
{
    // calcule le niveau d'énergie d'un pixel
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

    if (x == (*image).width - 1)
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

    if (y == (*image).height - 1)
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

    if (x == (*image).width - 1)
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

    if (y == (*image).height - 1)
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

    if (x == (*image).width - 1)
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

    if (y == (*image).height -1 )
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

float** get_less_energy_path_map(const float** energyMap, size_t width, size_t height)
{
    // alloue la mémoire
    float** energyPaths = (float**)malloc(sizeof(float*) * width);
    for (size_t i=0; i < width; i++)
    {
        // alloue de la mémoire pour la rangée
        energyPaths[i] = (float*)malloc(sizeof(float) * height);
    }
    
    for (size_t y = 0; y < height; y++)
    {
        for (size_t x = 0; x < width; x++)
        {
            if (y == 0)
            {
                // crée la premiére ligne
                energyPaths[x][y] = energyMap[x][y];
            }
            else
            {
                // crée les autres lignes
                if(x == 0)
                {
                    if (energyPaths[x][y-1] < energyPaths[x+1][y-1])
                    {
                        energyPaths[x][y] = energyMap[x][y] + energyPaths[x][y-1];
                    } 
                    else
                    {
                        energyPaths[x][y] = energyMap[x][y] + energyPaths[x+1][y-1];
                    }

                }
                else if (x == width - 1)
                {
                    if (energyPaths[x][y-1] < energyPaths[x-1][y-1])
                    {
                        energyPaths[x][y] = energyMap[x][y] + energyPaths[x][y-1];
                    } 
                    else
                    {
                        energyPaths[x][y] = energyMap[x][y] + energyPaths[x-1][y-1];
                    }
                }
                else
                {
                    if ( energyPaths[x-1][y-1] < energyPaths[x][y-1] && energyPaths[x-1][y-1] < energyPaths[x+1][y-1] )
                    {
                        energyPaths[x][y] = energyMap[x][y] + energyPaths[x-1][y-1];
                    }
                    else if ( energyPaths[x][y-1] < energyPaths[x-1][y-1] && energyPaths[x][y-1] < energyPaths[x+1][y-1] )
                    {
                        energyPaths[x][y] = energyMap[x][y] + energyPaths[x][y-1];
                    }
                    else
                    {
                        energyPaths[x][y] = energyMap[x][y] + energyPaths[x+1][y-1];
                    }

                }
            }
        }
    } 

    return energyPaths;
}

Sillon_energie_path* less_energy_sillon(const float** less_energy_path_map, size_t width, size_t height, size_t i, size_t j)
{
    // cas de base
    if ( j == 0)
    {
        // créer le sillon
        Sillon_energie_path* sillon = (Sillon_energie_path*) malloc (sizeof(Sillon_energie_path));
        (*sillon).path = (size_t*) malloc (sizeof(size_t) * height);
        (*sillon).path[0] = i;
        (*sillon).energy = less_energy_path_map[i][j];
        return sillon;
    }

    // trouve les positions suivante du sillon
    Sillon_energie_path* sillon;
    if ( i == 0 )
    {
        if ( less_energy_path_map[i][j-1] <= less_energy_path_map[i+1][j-1] )
        {
            sillon = less_energy_sillon(less_energy_path_map, width, height, i, j-1);
        }
        else
        {
            sillon = less_energy_sillon(less_energy_path_map, width, height, i+1, j-1);
        }
    }
    else if ( i == width - 1)
    {
        if ( less_energy_path_map[i-1][j-1] <= less_energy_path_map[i][j-1] )
        {
            sillon = less_energy_sillon(less_energy_path_map, width, height, i, j-1);
        }
        else
        {
            sillon = less_energy_sillon(less_energy_path_map, width, height, i-1, j-1);
        }
    }
    else
    {
        if ( less_energy_path_map[i-1][j-1] <= less_energy_path_map[i][j-1] && less_energy_path_map[i-1][j-1] <= less_energy_path_map[i+1][j-1] )
        {
            sillon = less_energy_sillon(less_energy_path_map, width, height, i-1, j-1);
        }
        else if ( less_energy_path_map[i][j-1] <= less_energy_path_map[i-1][j-1] && less_energy_path_map[i][j-1] <= less_energy_path_map[i+1][j-1] )
        {
            sillon = less_energy_sillon(less_energy_path_map, width, height, i, j-1);
        }
        else
        {
             sillon = less_energy_sillon(less_energy_path_map, width, height, i+1, j-1);
        }
    }

    // ajoute les élément avant de return
    (*sillon).energy = less_energy_path_map[i][j];
    (*sillon).path[j] = i;

    return sillon;

}

