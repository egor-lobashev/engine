#include <SFML/Graphics.hpp>
#include <cmath>
#include "Singleton.h"
#include "GameObject.h"
#include "API.h"
/////////////
#include "Vector3f.h"
#include "CheckPointInParallelogram.h"

///////////////////////
bool areCrossing(Vector3f first_point_hitbox,Vector3f  second_point_hitbox,Vector3f old_point_hitbox ,Vector3f new_point_hitbox , std::vector<float>& angle  )
{   
    Vector3f

    v11 = first_point_hitbox,
    v12 = second_point_hitbox,

    v21 = old_point_hitbox,
    v22 = new_point_hitbox;

    Vector3f cut1 = (v12 - v11);
    Vector3f cut2 = (v22 - v21);

    Vector3f 

    prod1 = cross(cut1 , v21 - v11 ),
    prod2 = cross(cut1 , v22 - v11 );

    if( prod1[2]*prod2[2] > 0  or prod1[2] == 0 or prod2[2] == 0)//здесь  удалил проверку на равенство 0 составляющей по оси z я считаю это столкновением
    {
        return false;
    }

    prod1 = cross(cut2 , (v11-v21));
    prod2 = cross(cut2 , (v12-v21));

    if( prod1[2]*prod2[2] > 0  or prod1[2] == 0 or prod2[2] == 0)//здесь  удалил проверку на равенство 0 составляющей по оси z я считаю это столкновением
    {
        return false;
    }  

    // float 

    // x_coor_point_new = new_point_hitbox[0],
    // y_coor_point_new = new_point_hitbox[1],

    // x_coor_point_old = old_point_hitbox[0],
    // y_coor_point_old = old_point_hitbox[1];


    // Vector3f crossing;

    // crossing[0] = v11[0] + cut1[0]*fabs(prod1[2])/fabs(prod2[2]-prod1[2]);
    // crossing[1] = v11[1] + cut1[1]*fabs(prod1[2])/fabs(prod2[2]-prod1[2]);

   

    float sin = 0;
    float cos = 0;

    
    
    if (v11[0] == v12[0])
    {
        if (v11[1] < v12[1])
        {
            sin = 1;
            cos = 0;
        }
        else 
        {
            sin = -1;
            cos = 0;
        }
    }
    else 
    {
        float k = (v12[1] - v11[1]) / (v12[0] - v11[0]);
        sin = k / (sqrt(pow(k, 2) + 1));
        cos = 1 / (sqrt(pow(k, 2) + 1));
    }
  
    angle = {cos,-sin};

    return true;
}

std::vector<float> findCrossingLineSegments(std::vector < std::vector <float> > absol_hit_coord_1 , std::vector < std::vector <float> > new_absol_hit_coord_2 , std::vector < std::vector <float> > old_absol_hit_coord_2 )
{
    int quantity_of_points_1 = absol_hit_coord_1.size();
    int quantity_of_points_2 = new_absol_hit_coord_2.size();
    Vector3f collision;

    for( int i = 0 ; i < quantity_of_points_1 ; ++i)
    {
        for( int j = 0 ; j < quantity_of_points_2 ; ++j)
        {
            if( i == quantity_of_points_1 - 1 )
            {
                Vector3f
                first_point_hitbox = {absol_hit_coord_1[i][0] ,absol_hit_coord_1[i][1] ,0 } ,
                second_point_hitbox = {absol_hit_coord_1[0][0] ,absol_hit_coord_1[0][1] ,0 } , 

                old_point_hitbox = {old_absol_hit_coord_2[j][0],old_absol_hit_coord_2[j][1],0},
                new_point_hitbox = {new_absol_hit_coord_2[j][0],new_absol_hit_coord_2[j][1],0};

                std::vector<float> angle = {0,0};
                


                if(areCrossing(first_point_hitbox,second_point_hitbox,old_point_hitbox,new_point_hitbox,angle))
                {   
                    std::cout << "this is "<< j << " point from moving hitbox"<< std::endl;
                    return angle;
                }

            }
            else
            {   
                Vector3f
                first_point_hitbox = {absol_hit_coord_1[i][0] ,absol_hit_coord_1[i][1] ,0 } ,
                second_point_hitbox = {absol_hit_coord_1[i+1][0] ,absol_hit_coord_1[i+1][1] ,0 } , 

                old_point_hitbox = {old_absol_hit_coord_2[j][0],old_absol_hit_coord_2[j][1],0},
                new_point_hitbox = {new_absol_hit_coord_2[j][0],new_absol_hit_coord_2[j][1],0};

                std::vector<float> angle = {0,0};

                if(areCrossing(first_point_hitbox,second_point_hitbox,old_point_hitbox,new_point_hitbox,angle))
                {   
                    std::cout << "this is "<< j << " point from moving hitbox"<< std::endl;
                    return angle;
                }
                
            }
            
        }

    }

    return {0,0};

}

std::vector<float> findCollisionByCheckPoints(std::vector < std::vector <float> > new_absol_hit_coord_moving, std::vector < std::vector <float> > old_absol_hit_coord_moving , std::vector < std::vector <float> > new_absol_hit_coord_2 , std::vector < std::vector <float> > old_absol_hit_coord_2 )
{   
    int size_of_moving = new_absol_hit_coord_moving.size();
    int other_size = new_absol_hit_coord_2.size();

    for(int i = 0 ; i < size_of_moving ; ++i)
    {
        if( i == size_of_moving - 1 )
        {
            std::vector<std::vector<float>> points_clockwise;
            points_clockwise.push_back({old_absol_hit_coord_moving[i]});
            points_clockwise.push_back({old_absol_hit_coord_moving[0]});
            points_clockwise.push_back({new_absol_hit_coord_moving[0]});
            points_clockwise.push_back({new_absol_hit_coord_moving[i]});

            for( int j = 0 ; j < other_size ; ++j)
            {
                std::vector<float> old_point = old_absol_hit_coord_2[j];
                std::vector<float> new_point = new_absol_hit_coord_2[j];
                if( CheckPointInParallelogram(old_point,points_clockwise) or CheckPointInParallelogram(new_point,points_clockwise))
                {//// сюда зайдет в том случае если есть пересечение 100%
                    float 
                    sin = 0,
                    cos = 0;

                    if ( old_absol_hit_coord_moving[i][0] == old_absol_hit_coord_moving[0][0])
                    {
                        if (old_absol_hit_coord_moving[i][1] < old_absol_hit_coord_moving[0][1])
                        {
                            sin = 1;
                            cos = 0;
                        }
                        else 
                        {
                            sin = -1;
                            cos = 0;
                        }
                    }
                    else {
                        float k = (old_absol_hit_coord_moving[0][1] - old_absol_hit_coord_moving[i][1]) / (old_absol_hit_coord_moving[0][0] - old_absol_hit_coord_moving[i][0]);
                        sin = k / (sqrt(pow(k, 2) + 1));
                        cos = 1 / (sqrt(pow(k, 2) + 1));
                    }


                    return {cos,-sin};
                 
                }

                
            }

        }
        else
        {
            std::vector<std::vector<float>> points_clockwise;
            points_clockwise.push_back({old_absol_hit_coord_moving[i]});
            points_clockwise.push_back({old_absol_hit_coord_moving[i+1]});
            points_clockwise.push_back({new_absol_hit_coord_moving[i+1]});
            points_clockwise.push_back({new_absol_hit_coord_moving[i]});

            for( int j = 0 ; j < other_size ; ++j)
            {
                std::vector<float> old_point = old_absol_hit_coord_2[j];
                std::vector<float> new_point = new_absol_hit_coord_2[j];
                if( CheckPointInParallelogram(old_point,points_clockwise) or CheckPointInParallelogram(new_point,points_clockwise))
                {//// сюда зайдет в том случае если есть пересечение 100%
                    float 
                    sin = 0,
                    cos = 0;

                    if ( old_absol_hit_coord_moving[i][0] == old_absol_hit_coord_moving[i+1][0])
                    {
                        if (old_absol_hit_coord_moving[i][1] < old_absol_hit_coord_moving[i+1][1])
                        {
                            sin = 1;
                            cos = 0;
                        }
                        else 
                        {
                            sin = -1;
                            cos = 0;
                        }
                    }
                    else {
                        float k = (old_absol_hit_coord_moving[i+1][1] - old_absol_hit_coord_moving[i][1]) / (old_absol_hit_coord_moving[i+1][0] - old_absol_hit_coord_moving[i][0]);
                        sin = k / (sqrt(pow(k, 2) + 1));
                        cos = 1 / (sqrt(pow(k, 2) + 1));
                    }

                    return {cos,-sin};
                     
                }



            }

        }

    }

    return{0,0};

}

////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////


void qqq::runGame(int window_width, int window_height, std::string window_name)
{
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), window_name);

    qqqP::Singleton* singleton = qqqP::Singleton::getInstance();
    sf::Event event;
    while (window.isOpen())
    {
        singleton->dt = singleton->clock.getElapsedTime().asSeconds();
        singleton->clock.restart();

        singleton->script_manager.updateAll();
        singleton->physics_manager.checkAllCollisions();
        
        
        window.clear(sf::Color(255, 255, 255));
        singleton->graphics_manager.drawAll(window);

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    delete singleton;
}

qqq::GameObject* qqq::getObject(std::string name)
{
    qqqP::Singleton* singleton = qqqP::Singleton::getInstance();
    return singleton->data_storage.getObject(name);
}

float qqq::absoluteTime()
{
    qqqP::Singleton* singleton = qqqP::Singleton::getInstance();
    return singleton->clock.getElapsedTime().asSeconds();
}

float qqq::relativeTime()
{
    qqqP::Singleton* singleton = qqqP::Singleton::getInstance();
    return singleton->dt;
}

void qqq::BallReflection::update()  // move this function to PhysicsManager or somwhere else
{
    float dt = qqq::relativeTime();
    owner -> moveVdt();
}

void qqq::BallReflection::ifCollision(qqq::GameObject* another)
{
    double sin = -1;
    double cos = 0;

    if (this -> owner -> position[0] == another -> position[0])
    {
        if (this -> owner -> position[1] < another -> position[1])
        {
            sin = 1;
            cos = 0;
        }
        else 
        {
            sin = -1;
            cos = 0;
        }
    }
    else {
        double k = (another -> position[1] - this -> owner -> position[1]) / (another -> position[0] - this -> owner -> position[0]);
        sin = k / (sqrt(pow(k, 2) + 1));
        cos = 1 / (sqrt(pow(k, 2) + 1));
    }

    // зададим через матрицу перехода свзять координат в разных СО
    float V_csi_before_1_obj = cos * this -> owner -> velocity[0] + sin * this -> owner -> velocity[1];
    float V_eta_before_1_obj = (-1) * sin * this -> owner -> velocity[0] + cos * this -> owner -> velocity[1];

    float V_csi_before_2_obj = cos * another -> velocity[0] + sin * another -> velocity[1];
    float V_eta_before_2_obj = (-1) * sin * another -> velocity[0] + cos * another -> velocity[1];

    float csi_coord_1_obj =  cos * this -> owner -> position[0] + sin * this -> owner -> position[1];
    float eta_coord_1_obj = (-1) * sin * this -> owner -> position[0] + cos * this -> owner -> position[1];

    float csi_coord_2_obj =  cos * another -> position[0] + sin * another -> position[1];
    float eta_coord_2_obj = (-1) * sin * another -> position[0] + cos * another -> position[1];
    // выразил скорости в новой СК , теперь поменяем нормальные составляющие и проверим, требуется ли в данном 
    // рассталкивать эти обьекты

    if (    (csi_coord_2_obj > csi_coord_1_obj and V_csi_before_2_obj <= 0 and V_csi_before_1_obj >= 0) or
            (csi_coord_2_obj < csi_coord_1_obj and V_csi_before_2_obj >= 0 and V_csi_before_1_obj <= 0) or
            (csi_coord_2_obj > csi_coord_1_obj and V_csi_before_1_obj - V_csi_before_2_obj > 0)       or
            (csi_coord_2_obj < csi_coord_1_obj and V_csi_before_1_obj - V_csi_before_2_obj < 0)           )
    {
        float tmp = V_csi_before_1_obj;
        V_csi_before_1_obj = V_csi_before_2_obj;
        V_csi_before_2_obj = tmp;

        // теперь переходим к старым координатам

        double V_x_1_obj_after_hitting = cos * V_csi_before_1_obj - sin * V_eta_before_1_obj;
        double V_y_1_obj_after_hitting = sin * V_csi_before_1_obj + cos * V_eta_before_1_obj;
        double V_x_2_obj_after_hitting = cos * V_csi_before_2_obj - sin * V_eta_before_2_obj;
        double V_y_2_obj_after_hitting = sin * V_csi_before_2_obj + cos * V_eta_before_2_obj;
        
        this -> owner -> velocity[0] = V_x_1_obj_after_hitting;
        this -> owner -> velocity[1] = V_y_1_obj_after_hitting;

        another->velocity[0] = V_x_2_obj_after_hitting;
        another->velocity[1] = V_y_2_obj_after_hitting;
    }
}


//////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
void qqq::PolygonReflection::update()
{
    float dt = qqq::relativeTime();
    owner -> moveVdt();
}

void qqq::PolygonReflection::ifCollision(qqq::GameObject* another)
{
    
    ///сделаем массив старых положений хитбоксов и новых  для этого обьекта /////
    qqq::Collider* owner_collider = static_cast<qqq::Collider*>(owner->colliders[0]);
    qqq::Collider* another_collider = static_cast<qqq::Collider*>(another->colliders[0]);

    int this_points_quantity_1 = owner_collider->getQuantityOfBodyPoints();
    std::vector < std::vector <float>> rel_hitbox_coord_1 = owner_collider->getRelativeHitboxCoordinates();

    std::vector < std::vector <float> > new_absol_hit_coord_1;
    std::vector < std::vector <float> > old_absol_hit_coord_1;

    for( int i = 0 ; i < this_points_quantity_1 ; ++i )
    {
        new_absol_hit_coord_1.push_back({ rel_hitbox_coord_1[i][0]+owner->position[0] , rel_hitbox_coord_1[i][1]+owner->position[1] });
        old_absol_hit_coord_1.push_back({ rel_hitbox_coord_1[i][0]+owner->old_position[0] , rel_hitbox_coord_1[i][1]+owner->old_position[1] });

    }

    ///сделаем массив старых положений хитбоксов и новых  для другого обьекта /////

    int this_points_quantity_2 = static_cast<qqq::Collider*>(another->colliders[0])->getQuantityOfBodyPoints();
    std::vector < std::vector <float>> rel_hitbox_coord_2 = static_cast<qqq::Collider*>(another->colliders[0])->getRelativeHitboxCoordinates();

    std::vector < std::vector <float> > new_absol_hit_coord_2;
    std::vector < std::vector <float> > old_absol_hit_coord_2;

    for( int i = 0 ; i < this_points_quantity_2 ; ++i )
    {
        new_absol_hit_coord_2.push_back({ rel_hitbox_coord_2[i][0]+another->position[0] , rel_hitbox_coord_2[i][1]+another->position[1] });
        old_absol_hit_coord_2.push_back({ rel_hitbox_coord_2[i][0]+another->old_position[0] , rel_hitbox_coord_2[i][1]+another->old_position[1] });

    }
    
    ////////////////////////////////////////////////////////////////////////////////
    // теперь нужно проверить пересечение всех приращений со сторонами хитбокса для обоих обьектов  ////

    std::vector<float> angle = {0,0};

    float
    sin = 0,
    cos = 0;
    
    if(owner->velocity != std::vector<float>{0,0} and another->velocity != std::vector<float>{0,0} )
    {   
        angle = findCollisionByCheckPoints(new_absol_hit_coord_2,old_absol_hit_coord_2,new_absol_hit_coord_1,old_absol_hit_coord_1);
        angle = findCollisionByCheckPoints(new_absol_hit_coord_1,old_absol_hit_coord_1,new_absol_hit_coord_2,old_absol_hit_coord_2);

        sin = angle[0];
        cos = angle[1];
    }
    else if(owner->velocity != std::vector<float>{0,0} and another->velocity == std::vector<float>{0,0} )   
    {
        angle = findCrossingLineSegments(new_absol_hit_coord_2,new_absol_hit_coord_1,old_absol_hit_coord_1);
        angle = findCollisionByCheckPoints(new_absol_hit_coord_1,old_absol_hit_coord_1,new_absol_hit_coord_2,old_absol_hit_coord_2);

        sin = angle[0];
        cos = angle[1];

    }
    else if(owner->velocity == std::vector<float>{0,0} and another->velocity != std::vector<float>{0,0} )   
    {
        angle = findCrossingLineSegments(new_absol_hit_coord_1,new_absol_hit_coord_2,old_absol_hit_coord_2);
        angle = findCollisionByCheckPoints(new_absol_hit_coord_2,old_absol_hit_coord_2,new_absol_hit_coord_1,old_absol_hit_coord_1);

        sin = angle[0];
        cos = angle[1];
    }


    ///////////////////////////////////////////////////////////////////////
    ///// сделать проверку на то что полученный вектор синусов и косинусов не равен 0 

    if( cos != 0 or sin != 0 )
    {   
        std::cout << "sin = "<<sin<<' '<< "cos = "<< cos<<std::endl;
        
    


        // ////////////////////////////////////////////////////////////////////////////////////
        // //// меняем скорости

        // //////зададим через матрицу перехода свзять координат в разных СО
        float V_csi_before_1_obj = cos * this -> owner -> velocity[0] + sin * this -> owner -> velocity[1];
        float V_eta_before_1_obj = (-1) * sin * this -> owner -> velocity[0] + cos * this -> owner -> velocity[1];

        float V_csi_before_2_obj = cos * another -> velocity[0] + sin * another -> velocity[1];
        float V_eta_before_2_obj = (-1) * sin * another -> velocity[0] + cos * another -> velocity[1];

        
        // // // выразил скорости в новой СК , теперь поменяем нормальные составляющие и проверим, требуется ли в данном 
        // // // рассталкивать эти обьекты

        owner->position = owner->old_position;
        another->position = another->old_position;


    
       
        float tmp = V_csi_before_1_obj;
        V_csi_before_1_obj = V_csi_before_2_obj;
        V_csi_before_2_obj = tmp;

        // теперь переходим к старым координатам

        double V_x_1_obj_after_hitting = cos * V_csi_before_1_obj - sin * V_eta_before_1_obj;
        double V_y_1_obj_after_hitting = sin * V_csi_before_1_obj + cos * V_eta_before_1_obj;
        double V_x_2_obj_after_hitting = cos * V_csi_before_2_obj - sin * V_eta_before_2_obj;
        double V_y_2_obj_after_hitting = sin * V_csi_before_2_obj + cos * V_eta_before_2_obj;
        
        this -> owner -> velocity[0] = V_x_1_obj_after_hitting;
        this -> owner -> velocity[1] = V_y_1_obj_after_hitting;

        another->velocity[0] = V_x_2_obj_after_hitting;
        another->velocity[1] = V_y_2_obj_after_hitting;

        }
    
}

