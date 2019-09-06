#include "cloud.h"

Cloud::Cloud() : freq(0.125), octaves(6), amp(2.0f), seed(1)
{
    Perlin perl(octaves, freq, amp, seed);

    for(int i = 0;i < NUM;i++)
        for(int j = 0;j < NUM;j++)
            for(int k = 0;k < NUM;k++){
                float den = perl.Get(j - NUM/2, k - NUM/2, i - NUM/2) + 1 - glm::length(glm::vec3(j, k, i)/float(NUM) - bb.maxBound)/radius;
                int index = i*NUM*NUM + j*NUM + k;
                voxel[index] = glm::max(den, 0.0f);
            }
    bb.minBound = glm::vec3(transform.T()*glm::vec4(bb.minBound,1));
    bb.maxBound = glm::vec3(transform.T()*glm::vec4(bb.maxBound,1));
}

float Cloud::GetDensity(glm::vec3 point)
{
    glm::vec3 pointL(transform.invT()*glm::vec4(point, 1.0f));
    if(glm::all(glm::lessThan(pointL, bb.maxBound)) && glm::all(glm::greaterThan(pointL, bb.minBound)))
    {
        glm::vec3 tmp = (pointL - bb.minBound)*float(NUM);
        int index = tmp[1]*NUM*NUM + tmp[2]*NUM + tmp[0];
        return voxel[index%TOTAL];
    }
    return 0.0f;
}

glm::vec4 Cloud::ComputeNormal(const glm::vec4 &P)
{
    int idx = 0;
    float val = -1;
    for(int i = 0; i < 3; i++){
        if(glm::abs(P[i]) > val){
            idx = i;
            val = glm::abs(P[i]);
        }
    }
    glm::vec4 N(0,0,0,0);
    N[idx] = glm::sign(P[idx]);
    return N;
}

Intersection Cloud::GetIntersection(Ray r)
{
    //Transform the ray
    Ray r_loc = r.GetTransformedCopy(transform.invT());
    Intersection result;

    float t_n = -1000000;
    float t_f = 1000000;
    for(int i = 0; i < 3; i++){
        //Ray parallel to slab check
        if(r_loc.direction[i] == 0){
            if(r_loc.origin[i] < bb.minBound[i] || r_loc.origin[i] > bb.maxBound[i]){
                return result;
            }
        }
        //If not parallel, do slab intersect check
        float t0 = (bb.minBound[i] - r_loc.origin[i])/r_loc.direction[i];
        float t1 = (bb.maxBound[i] - r_loc.origin[i])/r_loc.direction[i];
        if(t0 > t1){
            float temp = t1;
            t1 = t0;
            t0 = temp;
        }
        if(t0 > t_n){
            t_n = t0;
        }
        if(t1 < t_f){
            t_f = t1;
        }
    }
    float t_final = -1;
    if(t_n < t_f)
    {
        if(t_n >= 0)
        {
            t_final = t_n;
        }
        else if(t_f >= 0)
        {
            t_final = t_f;
        }
    }
    if(t_final >= 0)
    {
        //Lastly, transform the point found in object space by T
        glm::vec4 P = glm::vec4(r_loc.origin + t_final*r_loc.direction, 1);
        result.normal = glm::normalize(glm::vec3(transform.invTransT() * ComputeNormal(P)));
        result.point = glm::vec3(transform.T() * P);

        glm::vec4 PL = glm::vec4(r_loc.origin + glm::max(t_f, t_n)*r_loc.direction, 1);
        result.pointL = glm::vec3(transform.T() * PL);

        result.t = glm::distance(result.point, r.origin);
        result.object_hit = this;
    }
    return result;
}

glm::vec2 Cloud::GetUVCoordinates(const glm::vec3 &point)
{return glm::vec2(0);}

glm::vec3 Cloud::SampleLight(glm::vec2 rand)
{return glm::vec3(0);}

