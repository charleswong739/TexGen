//
//  perlin.hpp
//  TexGen
//
//  Created by Charles Wong on 2020-04-03.
//  Copyright © 2020 Charles Wong. All rights reserved.
//

#ifndef perlin_hpp
#define perlin_hpp

class Noise
{
private:
    const static int p [512];
    
    inline static double fade(double t) {return t * t * t * (t * (t * 6 - 15) + 10);}
    inline static double lerp(double value, double min, double max) {
        return min + value * (max - min);}
    static double grad (int hash, double x, double y, double z);
    
public:
    
    static double noise(double x, double y, double z);
    static double octaveNoise(double x, double y, double z, int octaves, double persistance);
};

#endif /* perlin_hpp */
