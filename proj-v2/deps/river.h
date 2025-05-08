#ifndef RIVER_H_
#define RIVER_H_

class River {
public:
    River(float w, float planeSize, float ax, float az, float bx, float bz);
    void draw();
    float aX, aZ, bX, bZ;
private:
    float width;
    float halfPlane;
    float startX, startZ, endX, endZ;
    static constexpr int segments = 100;
};

#endif
