#include <raytracing/integrator.h>

Integrator::Integrator():
    max_depth(1)
{
    scene = NULL;
    intersection_engine = NULL;
}

glm::vec3 ComponentMult(const glm::vec3 &a, const glm::vec3 &b)
{
    return glm::vec3(a.x * b.x, a.y * b.y, a.z * b.z);
}

void Integrator::SetDepth(unsigned int depth)
{
    max_depth = depth;
}

glm::vec3 Integrator::TraceRay(Ray r, unsigned int depth)
{
    glm::vec3 color(0);
    QList<Intersection> isx = intersection_engine->GetAllIntersections(r);
    int isx_num = isx.size();

    if(!isx_num) return color;
    else{
        if(isx[0].object_hit->material->is_light_source)
            return isx[0].object_hit->material->base_color*isx[0].object_hit->material->intensity*isx[0].texture_color;

        std::mt19937 mg(std::chrono::system_clock::now().time_since_epoch().count());
        std::uniform_real_distribution<float> u(-0.5, 0.5);

        for(int i = 0;i < scene->lights.size();i++)//for each light source
            for(int j = 0;j < sample;j++)//for each sample of specific light source
            {
                Geometry* light = scene->lights[i];
                glm::vec2 rand(u(mg), u(mg));
                glm::vec3 light_point = light->SampleLight(rand);

                float transparency(1.0f), transparency_light(1.0f);
                int cloud_num(0);

                while(cloud_num < isx_num && QString::compare(isx[cloud_num].object_hit->name, QString("Cloud")) == 0)
                {
                    color += RayMarch(isx[cloud_num++], light, light_point, r.direction, transparency);
                }

                if(cloud_num < isx_num){
                if(isx[cloud_num].object_hit->material->is_light_source)
                {
                    color += transparency*isx[cloud_num].object_hit->material->base_color*isx[cloud_num].object_hit->material->intensity*isx[cloud_num].texture_color;
                    continue;
                }

                glm::vec3 light_feeler_direction = glm::normalize(light_point - isx[cloud_num].point);
                Ray light_feeler(isx[cloud_num].point + epsilon*isx[cloud_num].normal, light_feeler_direction);//generate a feeler ray towards light source
                QList<Intersection> light_isx = intersection_engine->GetAllIntersections(light_feeler);
                int light_cloud_num(0), light_isx_num = light_isx.size();

                while(light_cloud_num < light_isx_num && QString::compare(light_isx[light_cloud_num].object_hit->name, QString("Cloud")) == 0) light_cloud_num++;
//                {
//                    RayMarch(isx[light_cloud_num++], light, light_point, light_feeler.direction, transparency_light);
//                }

                if(light_cloud_num < light_isx_num && light_isx[light_cloud_num].object_hit == light)
                {
                    float pdf = light->RayPDF(light_isx[light_cloud_num], light_feeler);
                    if(pdf)
                    {
                    glm::vec3 radiance = light->material->EvaluateScatteredEnergy(light_isx[light_cloud_num], r.direction, -light_feeler.direction);
                    glm::vec3 BRDF = isx[cloud_num].object_hit->material->EvaluateScatteredEnergy(isx[cloud_num], r.direction, light_feeler.direction);
                    color += transparency*transparency_light*BRDF*radiance*isx[cloud_num].object_hit->material->base_color*isx[cloud_num].texture_color*glm::abs(glm::dot(light_feeler.direction, isx[cloud_num].normal))/pdf;
                    }
                }
            }
        }
        return color/float(sample);
    }
}

glm::vec3 Integrator::RayMarch(Intersection isx, Geometry *light, glm::vec3 light_position, glm::vec3 march_direction, float &transparency)
{
    Cloud *cloud = dynamic_cast<Cloud*>(isx.object_hit);
    float range = glm::distance(isx.point, isx.pointL)/epsilon;
    glm::vec3 ray_march = isx.point, cloud_color = cloud->material->base_color, light_color = light->material->base_color, color(0);

    for(int i = 0;i < range;i++){
        ray_march += march_direction*epsilon;

        float density = cloud->GetDensity(ray_march);
        if (!density) continue;

        float dT = expf(-damp*epsilon*density);
        transparency *= dT;

        glm::vec3 light_direction = glm::normalize(light_position - ray_march);
        glm::vec3 light_march = ray_march;

        Ray r(light_march, light_direction);
        QList<Intersection> light_isx = intersection_engine->GetAllIntersections(r);
        int cloud_num(0), light_isx_num = light_isx.size();

        while(cloud_num < light_isx_num && QString::compare(light_isx[cloud_num].object_hit->name, QString("Cloud")) == 0) cloud_num++;

        if(cloud_num < light_isx_num && light_isx[cloud_num].object_hit == light)
        {
            int scope = glm::distance(light_position, light_march)/epsilon;
            float Q = 0;
            for (int i = 0; i < scope; i++)
            {
                light_march += light_direction*epsilon;
                float density_2 = cloud->GetDensity(light_march);
                if (density_2) Q += density_2;
            }
            color += (1 - dT)/damp*transparency*cloud_color*light_color*expf(-damp*epsilon*Q);
        }
    }
    return color;
}
