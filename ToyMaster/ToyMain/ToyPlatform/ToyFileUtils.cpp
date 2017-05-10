//
//  ToyFileUtils.cpp
//  Toy
//
//  Created by LongZhao on 2017/4/30.
//  Copyright © 2017年 ZerLon. All rights reserved.
//

#include "ToyFileUtils.h"

unsigned char *ToyFileUtils::read(const char *filePath, long *size) {
    if (!filePath) {
        printf("Error: Failed to read file NULL.\n");
        return 0;
    }
    FILE *fp = fopen(filePath, "rb");
    if (!fp) {
        printf("Error: Failed to open file '%s' for read\n", filePath);
        return 0;
    }
    fseek(fp, 0, SEEK_END);
    long usize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    unsigned char *data = (unsigned char *)malloc((usize + 1) * sizeof(unsigned char));
    if (!data) {
        printf("Error: Failed to alloc memory for read file '%s'\n", filePath);
        fclose(fp);
        return 0;
    }
    data[usize] = 0;
    usize = fread(data, usize, sizeof(unsigned char), fp);
    if (size) *size = usize;
    fclose(fp);
    return data;
}

bool ToyFileUtils::write(const char *filePath, unsigned char *data, long usize) {
    if (!filePath) {
        printf("Error: Failed to write file NULL.\n");
        return false;
    }
    FILE *fp = fopen(filePath, "wb");
    if (!fp) {
        printf("Error: Failed to open file '%s' for write\n", filePath);
        return false;
    }
    fwrite(data, usize, 1, fp);
    fclose(fp);
    return true;
}
