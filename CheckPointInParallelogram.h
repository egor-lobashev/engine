#include <vector>


bool CheckPointInParallelogram( std::vector<float> point , std::vector< std::vector<float> > points_clockwise  )
{
    std::vector<float> vector;
    std::vector<std::vector<float>> T = points_clockwise;

    for(int i = 0 ; i < 4 ; ++i)
    {
        if( i == 3 )
        {
            float a = (T[0][0] - T[i][0])*(point[1] - T[i][1]) - (T[0][1] - T[i][1])*( point[0] - T[i][0] );
            vector.push_back(a);

        }
        else
        {   
            float a = (T[i+1][0] - T[i][0])*(point[1] - T[i][1]) - (T[i+1][1] - T[i][1])*( point[0] - T[i][0] );
            vector.push_back(a);

        }
    }
    
    int iter_plus = 0;
    int iter_minus = 0;
    for ( auto item : vector )
    {   
        if( item > 0 )
        {
            iter_plus ++ ;
            
        }
        else if ( item < 0 )
        {
            iter_minus ++;
            
        }
        else if( item == 0 )
        {
            return true;
        }
    }
    if(iter_plus == 4)
    {
        return true;
    }
    else if (iter_minus == 4 )
    {
        return true;
    }
    
    return false;
}