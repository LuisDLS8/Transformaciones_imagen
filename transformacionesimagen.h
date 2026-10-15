#ifndef TRANSFORMACIONESIMAGEN_H
#define TRANSFORMACIONESIMAGEN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern void inv_hor_color(const char *input_filename, const char *output_filename){
    FILE *image, *outputImage;
    image = fopen("pajaros.bmp", "rb");
    outputImage = fopen("horizontal_color.bmp", "wb");
    unsigned char r, g, b;
    unsigned char xx[54];

    for(int i = 0; i < 54; i++){ //Lee los metadatos
    xx[i] = fgetc(image);
    }

    // Leer ancho usando 4 bytes (Para imagenes grandes)
    long ancho = (long)xx[21]*16777216 + (long)xx[20]*65536 + (long)xx[19]*256 + (long)xx[18];
    long alto = (long)xx[25]*16777216 +(long)xx[24]*65536 + (long)xx[23]*256 + (long)xx[22];
    long inicio_pixel = (long)xx[13] * 16777216 + (long)xx[12] * 65536 + (long)xx[11] * 256 + (long)xx[10];
    
    rewind(image);//Copia desde el inicio
    for(int i = 0; i < inicio_pixel; i++){ //Cabecera e informacion extra antes del inicio del pixel
        int informacion = fgetc(image);
        fputc(informacion, outputImage);
    }
    
    printf("Ancho: %ld\n", ancho);
    printf("Alto: %ld\n", alto);

    // Padding (verifica que funcione para cualquier imagen)
    int padding = (4 - (ancho * 3) % 4) % 4;

    // Arreglos de color
    unsigned char *arr_in_b =(unsigned char*)malloc(ancho*alto*sizeof(unsigned char));
    unsigned char *arr_in_g =(unsigned char*)malloc(ancho*alto*sizeof(unsigned char));
    unsigned char *arr_in_r =(unsigned char*)malloc(ancho*alto*sizeof(unsigned char));

    long j = 0;

    // Leer todos los pixeles
    for(long altura = 0; altura < alto; altura++){
        for(long anchura = 0; anchura < ancho; anchura++){
            b = fgetc(image);
            g = fgetc(image);
            r = fgetc(image);

            arr_in_b[j] = b;
            arr_in_g[j] = g;
            arr_in_r[j] = r;
            j++;
        }
        for(int i = 0; i < padding; i++){
            fgetc(image);
        }
    }

    // Espejo horizontal
    for(long altura = 0; altura < alto; altura++){
        for(long anchura = ancho - 1; anchura >= 0; anchura--){
            fputc(arr_in_b[altura*ancho + anchura], outputImage);
            fputc(arr_in_g[altura*ancho + anchura], outputImage);
            fputc(arr_in_r[altura*ancho + anchura], outputImage);
        }
        for(int i = 0; i < padding; i++){
            fputc(0, outputImage);
        }
    }

    free(arr_in_b);
    free(arr_in_g);
    free(arr_in_r);
    fclose(image);
    fclose(outputImage);
    printf("Imagen volteada horizontalmente a color.\n");
}

extern void inv_hor_bn(const char *input_filename, const char *output_filename){
    FILE *image, *outputImage;
    image = fopen("pajaros.bmp", "rb");
    outputImage = fopen("horizontal_gris.bmp", "wb");
    unsigned char r, g, b;
    unsigned char xx[54];

    for(int i = 0; i < 54; i++){ //Lee los metadatos
    xx[i] = fgetc(image);
    }

    // Leer ancho usando 4 bytes (Para imagenes grandes)
    long ancho = (long)xx[21]*16777216 + (long)xx[20]*65536 + (long)xx[19]*256 + (long)xx[18];
    long alto = (long)xx[25]*16777216 +(long)xx[24]*65536 + (long)xx[23]*256 + (long)xx[22];
    long inicio_pixel = (long)xx[13] * 16777216 + (long)xx[12] * 65536 + (long)xx[11] * 256 + (long)xx[10];
    
    rewind(image);//Copia desde el inicio
    for(int i = 0; i < inicio_pixel; i++){ //Cabecera e informacion extra antes del inicio del pixel
        int informacion = fgetc(image);
        fputc(informacion, outputImage);
    }
    
    printf("Ancho: %ld\n", ancho);
    printf("Alto: %ld\n", alto);

    // Padding (verifica que funcione para cualquier imagen)
    int padding = (4 - (ancho * 3) % 4) % 4;

    unsigned char *arr_in = (unsigned char*)malloc(ancho * alto * sizeof(unsigned char));

    long j = 0;

    // Leer píxeles y convertirlos a escala de grises
    for(long altura = 0; altura < alto; altura++){
        for(long anchura = 0; anchura < ancho; anchura++){
            b = fgetc(image);
            g = fgetc(image);
            r = fgetc(image);
            unsigned char pixel = 0.21*r + 0.72*g + 0.07*b;

            arr_in[j] = pixel;
            j++;
        }
        for(int i = 0; i < padding; i++){
            fgetc(image);
        }
    }

    // Espejo horizontal en escala de grises
    for(long altura = 0; altura < alto; altura++){
        for(long anchura = ancho - 1; anchura >= 0; anchura--){
            fputc(arr_in[altura * ancho + anchura], outputImage);
            fputc(arr_in[altura * ancho + anchura], outputImage);
            fputc(arr_in[altura * ancho + anchura], outputImage);
        }
        for(int i = 0; i < padding; i++){
            fputc(0, outputImage);
        }
    }

    free(arr_in);
    fclose(image);
    fclose(outputImage);
    printf("Imagen espejeada horizontalmente en escala de grises.\n");
}

extern void inv_ver_color(const char *input_filename, const char *output_filename){
    FILE *image, *outputImage;
    image = fopen("pajaros.bmp", "rb");
    outputImage = fopen("vertical_color.bmp", "wb");
    unsigned char r, g, b;
    unsigned char xx[54];

    for(int i = 0; i < 54; i++){ //Lee los metadatos
    xx[i] = fgetc(image);
    }

    // Leer ancho usando 4 bytes (Para imagenes grandes)
    long ancho = (long)xx[21]*16777216 + (long)xx[20]*65536 + (long)xx[19]*256 + (long)xx[18];
    long alto = (long)xx[25]*16777216 +(long)xx[24]*65536 + (long)xx[23]*256 + (long)xx[22];
    long inicio_pixel = (long)xx[13] * 16777216 + (long)xx[12] * 65536 + (long)xx[11] * 256 + (long)xx[10];
    
    rewind(image);//Copia desde el inicio
    for(int i = 0; i < inicio_pixel; i++){ //Cabecera e informacion extra antes del inicio del pixel
        int informacion = fgetc(image);
        fputc(informacion, outputImage);
    }
    
    printf("Ancho: %ld\n", ancho);
    printf("Alto: %ld\n", alto);

    // Padding (verifica que funcione para cualquier imagen)
    int padding = (4 - (ancho * 3) % 4) % 4;

    // Arreglos de color
    unsigned char *arr_in_b =(unsigned char*)malloc(ancho*alto*sizeof(unsigned char));
    unsigned char *arr_in_g =(unsigned char*)malloc(ancho*alto*sizeof(unsigned char));
    unsigned char *arr_in_r =(unsigned char*)malloc(ancho*alto*sizeof(unsigned char));

    long j = 0;

    // Leer todos los pixeles
    for(long altura = 0; altura < alto; altura++){
        for(long anchura = 0; anchura < ancho; anchura++){
            b = fgetc(image);
            g = fgetc(image);
            r = fgetc(image);

            arr_in_b[j] = b;
            arr_in_g[j] = g;
            arr_in_r[j] = r;
            j++;
        }
        for(int i = 0; i < padding; i++){
            fgetc(image);
        }
    }

    // Volteo vertical
    for(long altura = alto - 1; altura >= 0; altura--){
        for(long anchura = 0; anchura < ancho; anchura++){
            fputc(arr_in_b[altura*ancho + anchura], outputImage);
            fputc(arr_in_g[altura*ancho + anchura], outputImage);
            fputc(arr_in_r[altura*ancho + anchura], outputImage);
        }
        for(int i = 0; i < padding; i++){
            fputc(0, outputImage);
        }
    }

    free(arr_in_b);
    free(arr_in_g);
    free(arr_in_r);
    fclose(image);
    fclose(outputImage);
    printf("Imagen invertida de cabeza a color.\n");
}

extern void inv_ver_bn(const char *input_filename, const char *output_filename){
    FILE *image, *outputImage;
    image = fopen("pajaros.bmp", "rb");
    outputImage = fopen("vertical_gris.bmp", "wb");
    unsigned char r, g, b;
    unsigned char xx[54];

    for(int i = 0; i < 54; i++){ //Lee los metadatos
    xx[i] = fgetc(image);
    }

    // Leer ancho usando 4 bytes (Para imagenes grandes)
    long ancho = (long)xx[21]*16777216 + (long)xx[20]*65536 + (long)xx[19]*256 + (long)xx[18];
    long alto = (long)xx[25]*16777216 +(long)xx[24]*65536 + (long)xx[23]*256 + (long)xx[22];
    long inicio_pixel = (long)xx[13] * 16777216 + (long)xx[12] * 65536 + (long)xx[11] * 256 + (long)xx[10];
    
    rewind(image);//Copia desde el inicio
    for(int i = 0; i < inicio_pixel; i++){ //Cabecera e informacion extra antes del inicio del pixel
        int informacion = fgetc(image);
        fputc(informacion, outputImage);
    }
    
    printf("Ancho: %ld\n", ancho);
    printf("Alto: %ld\n", alto);

    // Padding (verifica que funcione para cualquier imagen)
    int padding = (4 - (ancho * 3) % 4) % 4;

    unsigned char *arr_in = (unsigned char*)malloc(ancho * alto * sizeof(unsigned char));

    long j = 0;

    // Leer píxeles y convertirlos a escala de grises
    for(long altura = 0; altura < alto; altura++){
        for(long anchura = 0; anchura < ancho; anchura++){
            b = fgetc(image);
            g = fgetc(image);
            r = fgetc(image);
            unsigned char pixel = 0.21*r + 0.72*g + 0.07*b;

            arr_in[j] = pixel;
            j++;
        }
        for(int i = 0; i < padding; i++){
            fgetc(image);
        }
    }

    // Volteo vertical en escala de grises
    for(long altura = alto - 1; altura >= 0; altura--){
        for(long anchura = 0; anchura < ancho; anchura++){
            fputc(arr_in[altura * ancho + anchura], outputImage);
            fputc(arr_in[altura * ancho + anchura], outputImage);
            fputc(arr_in[altura * ancho + anchura], outputImage);
        }
        for(int i = 0; i < padding; i++){
            fputc(0, outputImage);
        }
    }

    free(arr_in);
    fclose(image);
    fclose(outputImage);
    printf("Imagen invertida de cabeza en escala de grises.\n");
}

extern void blur_color(const char* input_path, const char* name_output, int kernel_size) {
    FILE *image, *outputImage;
    char output_path[100] = "./";
    strcat(output_path, name_output);
    strcat(output_path, ".bmp");
    printf("%s\n", output_path);
    image = fopen(input_path, "rb");
    outputImage = fopen(output_path, "wb");

    if (!image || !outputImage) {
        printf("Error abriendo archivos.\n");
        return;
    }

    unsigned char header[54];
    fread(header, sizeof(unsigned char), 54, image);

    long width = (long)header[21] * 16777216 + (long)header[20] * 65536 + (long)header[19] * 256 + (long)header[18];
    long height = (long)header[25] * 16777216 + (long)header[24] * 65536 + (long)header[23] * 256 + (long)header[22];
    long inicio_pixel =(long)header[13] * 16777216+ (long)header[12] * 65536+ (long)header[11] * 256+ (long)header[10];

    // Regresar al inicio
    rewind(image);

    // Copiar toda la cabecera e informacion extra
    for(long i = 0; i < inicio_pixel; i++){
        int informacion = fgetc(image);
        fputc(informacion, outputImage);
    }
    long row_padded = (width * 3 + 3) & (~3);

    unsigned char** input_rows = (unsigned char**)malloc(height * sizeof(unsigned char*));
    unsigned char** output_rows = (unsigned char**)malloc(height * sizeof(unsigned char*));
    unsigned char** temp_rows = (unsigned char**)malloc(height * sizeof(unsigned char*));

    for (int i = 0; i < height; i++) {
        input_rows[i] = (unsigned char*)malloc(row_padded);
        output_rows[i] = (unsigned char*)malloc(row_padded);
        temp_rows[i] = (unsigned char*)malloc(row_padded);
        fread(input_rows[i], sizeof(unsigned char), row_padded, image);
    }

    int k = kernel_size / 2;

    // Paso intermedio: desenfoque horizontal
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int sumB = 0, sumG = 0, sumR = 0, count = 0;

            for (int dx = -k; dx <= k; dx++) {
                int nx = x + dx;
                if (nx >= 0 && nx < width) {
                    int idx = nx * 3;
                    sumB += input_rows[y][idx + 0];
                    sumG += input_rows[y][idx + 1];
                    sumR += input_rows[y][idx + 2];
                    count++;
                }
            }

            int index = x * 3;
            temp_rows[y][index + 0] = sumB / count;
            temp_rows[y][index + 1] = sumG / count;
            temp_rows[y][index + 2] = sumR / count;
        }

        // Copiar padding sin modificar
        for (int p = width * 3; p < row_padded; p++) {
            temp_rows[y][p] = input_rows[y][p];
        }
    }

    // Paso final: desenfoque vertical
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int sumB = 0, sumG = 0, sumR = 0, count = 0;

            for (int dy = -k; dy <= k; dy++) {
                int ny = y + dy;
                if (ny >= 0 && ny < height) {
                    int idx = x * 3;
                    sumB += temp_rows[ny][idx + 0];
                    sumG += temp_rows[ny][idx + 1];
                    sumR += temp_rows[ny][idx + 2];
                    count++;
                }
            }

            int index = x * 3;
            output_rows[y][index + 0] = sumB / count;
            output_rows[y][index + 1] = sumG / count;
            output_rows[y][index + 2] = sumR / count;
        }

        // Copiar padding sin modificar
        for (int p = width * 3; p < row_padded; p++) {
            output_rows[y][p] = temp_rows[y][p];
        }
    }

    // Escritura final
    for (int i = 0; i < height; i++) {
        fwrite(output_rows[i], sizeof(unsigned char), row_padded, outputImage);
        free(input_rows[i]);
        free(temp_rows[i]);
        free(output_rows[i]);
    }

    // Escritura en archivo de registro
    FILE *outputLog = fopen("output_log.txt", "a");
    if (outputLog == NULL) {
        fprintf(stderr, "Error: No se pudo crear o abrir el archivo de registro.\n");
        fclose(image);
        fclose(outputImage);
        return;
    }
    printf("Desenfoque de imagen a escala de grises\n");

    fprintf(outputLog, "Función: desenfoque, con %s\n", input_path);
    fprintf(outputLog, "Localidades totales leídas: %d\n", width * height);
    fprintf(outputLog, "Localidades totales escritas: %d\n", width * height);
    fprintf(outputLog, "-------------------------------------\n");
    fclose(outputLog);

    free(input_rows);
    free(temp_rows);
    free(output_rows);
    fclose(image);
    fclose(outputImage);
}

extern void blur_bn(const char* input_path, const char* name_output, int kernel_size){
    FILE *image, *outputImage;
    char output_path[100] = "./";
    strcat(output_path, name_output);
    strcat(output_path, ".bmp");
    printf("%s\n", output_path);
    image = fopen(input_path, "rb");
    outputImage = fopen(output_path, "wb");

    if (!image || !outputImage) {
        printf("Error abriendo archivos.\n");
        return;
    }

    unsigned char header[54];
    fread(header, sizeof(unsigned char), 54, image);

    long width = (long)header[21] * 16777216 + (long)header[20] * 65536 + (long)header[19] * 256 + (long)header[18];
    long height = (long)header[25] * 16777216 + (long)header[24] * 65536 + (long)header[23] * 256 + (long)header[22];
    long inicio_pixel =(long)header[13] * 16777216+ (long)header[12] * 65536+ (long)header[11] * 256+ (long)header[10];

    // Regresar al inicio
    rewind(image);

    // Copiar toda la cabecera e informacion extra
    for(long i = 0; i < inicio_pixel; i++){
        int informacion = fgetc(image);
        fputc(informacion, outputImage);
    }
    long row_padded = (width * 3 + 3) & (~3);

    unsigned char** input_rows = (unsigned char**)malloc(height * sizeof(unsigned char*));
    unsigned char** output_rows = (unsigned char**)malloc(height * sizeof(unsigned char*));
    unsigned char** temp_rows = (unsigned char**)malloc(height * sizeof(unsigned char*));

    for (int i = 0; i < height; i++) {
        input_rows[i] = (unsigned char*)malloc(row_padded);
        output_rows[i] = (unsigned char*)malloc(row_padded);
        temp_rows[i] = (unsigned char*)malloc(row_padded);
        fread(input_rows[i], sizeof(unsigned char), row_padded, image);
    }

    //Cambio a gris
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = x * 3;
            unsigned char b = input_rows[y][index + 0];
            unsigned char g = input_rows[y][index + 1];
            unsigned char r = input_rows[y][index + 2];

            unsigned char pixel =0.21*r +0.72*g +0.07*b;

            input_rows[y][index + 0] = pixel;
            input_rows[y][index + 1] = pixel;
            input_rows[y][index + 2] = pixel;
        }
    }

    int k = kernel_size / 2;

    // Paso intermedio: desenfoque horizontal
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int sumB = 0, sumG = 0, sumR = 0, count = 0;

            for (int dx = -k; dx <= k; dx++) {
                int nx = x + dx;
                if (nx >= 0 && nx < width) {
                    int idx = nx * 3;
                    sumB += input_rows[y][idx + 0];
                    sumG += input_rows[y][idx + 1];
                    sumR += input_rows[y][idx + 2];
                    count++;
                }
            }

            int index = x * 3;
            temp_rows[y][index + 0] = sumB / count;
            temp_rows[y][index + 1] = sumG / count;
            temp_rows[y][index + 2] = sumR / count;
        }

        // Copiar padding sin modificar
        for (int p = width * 3; p < row_padded; p++) {
            temp_rows[y][p] = input_rows[y][p];
        }
    }

    // Paso final: desenfoque vertical
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int sumB = 0, sumG = 0, sumR = 0, count = 0;

            for (int dy = -k; dy <= k; dy++) {
                int ny = y + dy;
                if (ny >= 0 && ny < height) {
                    int idx = x * 3;
                    sumB += temp_rows[ny][idx + 0];
                    sumG += temp_rows[ny][idx + 1];
                    sumR += temp_rows[ny][idx + 2];
                    count++;
                }
            }

            int index = x * 3;
            output_rows[y][index + 0] = sumB / count;
            output_rows[y][index + 1] = sumG / count;
            output_rows[y][index + 2] = sumR / count;
        }

        // Copiar padding sin modificar
        for (int p = width * 3; p < row_padded; p++) {
            output_rows[y][p] = temp_rows[y][p];
        }
    }

    // Escritura final
    for (int i = 0; i < height; i++) {
        fwrite(output_rows[i], sizeof(unsigned char), row_padded, outputImage);
        free(input_rows[i]);
        free(temp_rows[i]);
        free(output_rows[i]);
    }

    // Escritura en archivo de registro
    FILE *outputLog = fopen("output_log.txt", "a");
    if (outputLog == NULL) {
        fprintf(stderr, "Error: No se pudo crear o abrir el archivo de registro.\n");
        fclose(image);
        fclose(outputImage);
        return;
    }
    printf("Desenfoque de imagen a escala de grises\n");

    fprintf(outputLog, "Función: desenfoque, con %s\n", input_path);
    fprintf(outputLog, "Localidades totales leídas: %d\n", width * height);
    fprintf(outputLog, "Localidades totales escritas: %d\n", width * height);
    fprintf(outputLog, "-------------------------------------\n");
    fclose(outputLog);

    free(input_rows);
    free(temp_rows);
    free(output_rows);
    fclose(image);
    fclose(outputImage);
}

#endif

