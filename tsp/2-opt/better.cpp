#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

struct Coordinate{
  float x;
  float y;
};

float distanceBetweenCoordinates(Coordinate coordinate_1, Coordinate coordinate_2){
  float x_axis = coordinate_1.x - coordinate_2.x;
  float y_axis = coordinate_1.y - coordinate_2.y;
  return sqrt((x_axis*x_axis) + (y_axis*y_axis));
}

int main(){
    int number_of_coordinates;
    std::cin >> number_of_coordinates;

    std::vector<Coordinate> coordinates;  //  Coordinates storage
    for(int i=0;i<number_of_coordinates;i++){   // Reads coordinates
        float x_axis, y_axis;
        std::cin >> x_axis >> y_axis;
        Coordinate coordinate;
        coordinate.x = x_axis;
        coordinate.y = y_axis;
        coordinates.push_back(coordinate);
    }

    // Calculate the route before optimization in order to compare how better it became
    float route_total_distance = 0;
    for(int i=0;i<number_of_coordinates-1;i++)
        route_total_distance += distanceBetweenCoordinates(coordinates[i], coordinates[i+1]);

    for(int i=0;i<number_of_coordinates-2;i++){
        for(int j=i+3;j<number_of_coordinates-1;j++){   // Goes until number_of_coordinates-1 because element j+1 will need to be acessed
            // Index of coordinates that will be traded
            int inversed_coordinate_index_1 = i+1;
            int inversed_coordinate_index_2 = j+1;

            float current_path_distance = 
            distanceBetweenCoordinates(coordinates[i], coordinates[i+1]) + distanceBetweenCoordinates(coordinates[j], coordinates[j+1]);

            float new_path_distance =
            distanceBetweenCoordinates(coordinates[i], coordinates[j]) + distanceBetweenCoordinates(coordinates[j+1], coordinates[i+1]);
            
            if(new_path_distance < current_path_distance){
            // Keeps new route and re-start the 2-opt with the new_route (by setting i = 0 and break the loop)

                current_path_distance = new_path_distance;
                std::reverse(coordinates.begin() + i + 1, coordinates.begin() + j + 1);
                i = 0;
                j = 0;
                break;
            }
        }
    }

    // Diplay the coordinates organized in the best calculated route
    std::cout << "(" << coordinates[0].x << ", " << coordinates[0].y << ")";
    for(int i=1;i<number_of_coordinates;i++){
        std::cout << ",\n(" << coordinates[i].x << ", " << coordinates[i].y << ")";
    }

    std::cout << "\n\n";

    std::cout << "Distance of old route: " << route_total_distance << std::endl;

    route_total_distance = 0;
    for(int i=0;i<number_of_coordinates-1;i++)
        route_total_distance += distanceBetweenCoordinates(coordinates[i], coordinates[i+1]);

    std::cout << "Distance of new route: " << route_total_distance << std::endl;

    return 0;
}