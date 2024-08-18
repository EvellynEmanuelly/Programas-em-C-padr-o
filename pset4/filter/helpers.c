#include "helpers.h"
#include <string.h>
#include <math.h>

// Função para garantir que um valor esteja no intervalo [0, 255]
int cap(int value)
{
    if (value < 0)
    {
        return 0;
    }
    else if (value > 255)
    {
        return 255;
    }
    else
    {
        return value;
    }
}

// Função para converter uma imagem em tons de cinza
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calcula a média dos valores de vermelho, verde e azul
            int avg = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3;
            // Define todos os componentes de cor com o valor médio
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
}

// Função para refletir uma imagem horizontalmente
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Troca os pixels da esquerda com os pixels da direita
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
}

// Função para aplicar um filtro de desfoque à imagem
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Cria uma cópia temporária da imagem original
    RGBTRIPLE temp[height][width];
    memcpy(temp, image, sizeof(RGBTRIPLE) * height * width);

    // Percorre todos os pixels da imagem, exceto os pixels na borda
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumRed = 0, sumGreen = 0, sumBlue = 0;
            int count = 0;

            // Percorre a vizinhança do pixel para calcular a média
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;

                    // Verifica se a vizinhança está dentro dos limites da imagem
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        sumRed += temp[ni][nj].rgbtRed;
                        sumGreen += temp[ni][nj].rgbtGreen;
                        sumBlue += temp[ni][nj].rgbtBlue;
                        count++;
                    }
                }
            }

            // Calcula a média dos valores de cor
            image[i][j].rgbtRed = cap(round((float)sumRed / count));
            image[i][j].rgbtGreen = cap(round((float)sumGreen / count));
            image[i][j].rgbtBlue = cap(round((float)sumBlue / count));
        }
    }
}

// Função para detectar bordas na imagem
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Kernels para detecção de bordas
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Cria uma cópia temporária da imagem original
    RGBTRIPLE temp[height][width];
    memcpy(temp, image, sizeof(RGBTRIPLE) * height * width);

    // Percorre todos os pixels da imagem, exceto os pixels na borda
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            int Gx_red = 0, Gy_red = 0, Gx_green = 0, Gy_green = 0, Gx_blue = 0, Gy_blue = 0;

            // Percorre a vizinhança do pixel para calcular Gx e Gy
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;

                    // Calcula as contribuições Gx e Gy para cada canal de cor
                    Gx_red += temp[ni][nj].rgbtRed * Gx[di + 1][dj + 1];
                    Gy_red += temp[ni][nj].rgbtRed * Gy[di + 1][dj + 1];
                    Gx_green += temp[ni][nj].rgbtGreen * Gx[di + 1][dj + 1];
                    Gy_green += temp[ni][nj].rgbtGreen * Gy[di + 1][dj + 1];
                    Gx_blue += temp[ni][nj].rgbtBlue * Gx[di + 1][dj + 1];
                    Gy_blue += temp[ni][nj].rgbtBlue * Gy[di + 1][dj + 1];
                }
            }

            // Calcula o valor final do pixel
            int red = cap(round(sqrt(Gx_red * Gx_red + Gy_red * Gy_red)));
            int green = cap(round(sqrt(Gx_green * Gx_green + Gy_green * Gy_green)));
            int blue = cap(round(sqrt(Gx_blue * Gx_blue + Gy_blue * Gy_blue)));

            // Define os componentes de cor do pixel com os valores calculados
            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
        }
    }
}
