#include "PhysicsManager.h"
#include "GameObject.h"
#include <cmath>

float getMaxElement(const std::vector < float > vector)
{
    float max = vector[0];

    for(auto element : vector){

        if( element >= max )
        {
            max = element;
        }

    }
    return max;
}

float getMinElement(const std::vector < float > vector)
{
    float min = vector[0];

    for(auto element : vector){

        if( element <= min )
        {
            min = element;
        }

    }
    return min;
}

bool checkOneObject( std::vector < std::vector < float > > absolute_points_coordinates_of_first_obj_clockwise , int quantity_of_points_first , std::vector < std::vector < float > > absolute_points_coordinates_of_second_obj_clockwise , int quantity_of_points_second )
{
    for ( int i = 0 ; i < quantity_of_points_first ; ++i ){

        bool tg_inf = false;
        float cos = 0;
        float sin = 1;

        if( i == quantity_of_points_first - 1 )
        {   
            float x1 = absolute_points_coordinates_of_first_obj_clockwise[i][0];
            float y1 = absolute_points_coordinates_of_first_obj_clockwise[i][1];

            float x2 = absolute_points_coordinates_of_first_obj_clockwise[0][0];
            float y2 = absolute_points_coordinates_of_first_obj_clockwise[0][1];

            if ( x1 == x2 )
            {
                tg_inf = true;
            }
            else
            {
                float tg = ( y1 - y2 ) / (x1 - x2);

                cos = sqrt( 1/( 1 + tg*tg ) );
                sin = sqrt( 1 - cos*cos );
            }
        }   
        else
        {
            float x1 = absolute_points_coordinates_of_first_obj_clockwise[i][0];
            float y1 = absolute_points_coordinates_of_first_obj_clockwise[i][1];

            float x2 = absolute_points_coordinates_of_first_obj_clockwise[i+1][0];
            float y2 = absolute_points_coordinates_of_first_obj_clockwise[i+1][1];

            if ( x1 == x2 )
            {
                tg_inf = true;
            }
            else
            {
                float tg = ( y1 - y2 ) / (x1 - x2);

                cos = sqrt( 1/( 1 + tg*tg ) );
                sin = sqrt( 1 - cos*cos );
            }
        }


        std::vector < float > points_proection_on_new_axis_for_first_obj;
        std::vector < float > points_proection_on_new_axis_for_second_obj;

        for ( int i = 0 ; i < quantity_of_points_first ; ++i){
            points_proection_on_new_axis_for_first_obj.push_back( absolute_points_coordinates_of_first_obj_clockwise[i][0]*sin + absolute_points_coordinates_of_first_obj_clockwise[i][1]*cos );
        }

        for ( int i = 0 ; i < quantity_of_points_second ; ++i){
            points_proection_on_new_axis_for_second_obj.push_back( absolute_points_coordinates_of_second_obj_clockwise[i][0]*sin + absolute_points_coordinates_of_second_obj_clockwise[i][1]*cos );
        }

        float max1 = getMaxElement(points_proection_on_new_axis_for_first_obj);
        float min1 = getMinElement(points_proection_on_new_axis_for_first_obj);

        float max2 = getMaxElement(points_proection_on_new_axis_for_second_obj);
        float min2 = getMinElement(points_proection_on_new_axis_for_second_obj);

        if ( max1 < min2 or max2 < min1)
        {
            return false;
        }
    }

    return true;
}

PhysicsManager* PhysicsManager::instance = nullptr;

PhysicsManager* PhysicsManager::getInstance(){

    if(!instance){
        instance = new PhysicsManager;
    }
    return instance;
}

bool PhysicsManager::addCollider(Component* new_collider){

    try
    {
        collider_objects.push_back(static_cast<Collider*>(new_collider));
        return true;
    }
    catch(...)
    { 
        return false;
    }
}

bool PhysicsManager::removeCollider(Component* removing_collider){

    for(int i = 0 ; i < collider_objects.size() ; i++){

        if(collider_objects[i] == removing_collider)
        {
            collider_objects.erase(collider_objects.begin() + i );
            return true;
        }

        return false;
    }
}

void PhysicsManager::checkForCollide( Collider* first , Collider* second )
{   
    //////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////

    std::vector < std::vector < float > > absolute_points_coordinates_of_first_obj_clockwise;
    std::vector < std::vector < float > > absolute_points_coordinates_of_second_obj_clockwise;

    int quantity_of_points_first = first ->  getQuantityOfBodyPoints();
    int quantity_of_points_second = second -> getQuantityOfBodyPoints();

    float x_coordinate_of_first = first -> owner -> position[0];
    float y_coordinate_of_first = first -> owner -> position[1];

    float x_coordinate_of_second = second -> owner -> position[0];
    float y_coordinate_of_second = second -> owner -> position[1];

    for ( int i = 0 ; i < quantity_of_points_first ; ++i)
    {
        float x_coordinate_of_point = first -> getPointByIndex(i)[0];
        float y_coordinate_of_point = first -> getPointByIndex(i)[1];

        absolute_points_coordinates_of_first_obj_clockwise.push_back( { x_coordinate_of_first + x_coordinate_of_point , y_coordinate_of_first + y_coordinate_of_point } );
    }

    for ( int i = 0 ; i < quantity_of_points_second ; ++i)
    {
        float x_coordinate_of_point = second -> getPointByIndex(i)[0];
        float y_coordinate_of_point = second -> getPointByIndex(i)[1];

        absolute_points_coordinates_of_second_obj_clockwise.push_back( { x_coordinate_of_second + x_coordinate_of_point , y_coordinate_of_second + y_coordinate_of_point } );
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////

    if(checkOneObject( absolute_points_coordinates_of_first_obj_clockwise,quantity_of_points_first , absolute_points_coordinates_of_second_obj_clockwise,quantity_of_points_second)
        or checkOneObject( absolute_points_coordinates_of_second_obj_clockwise,quantity_of_points_second , absolute_points_coordinates_of_first_obj_clockwise,quantity_of_points_first))
    {
        std::cout << first->owner->id_in_data_storage << " has collided with " << second->owner->id_in_data_storage << std::endl;
    }
}

void PhysicsManager::checkAllCollisions()
{
    for (int i = 0; i < collider_objects.size(); i++)
    {
        for (int j = 0; j < collider_objects.size(); j++)
        {
            if (i > j)
            {
                checkForCollide(collider_objects[i], collider_objects[j]);
            }
        }
    }
}



