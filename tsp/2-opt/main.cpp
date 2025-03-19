#include <iostream>
#include <cmath>

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

    Coordinate coordinates[number_of_coordinates];  //  Coordinates storage
    for(int i=0;i<number_of_coordinates;i++){   // Reads coordinates
        std::cin >> coordinates[i].x >> coordinates[i].y;
    }

    // Calculate total distance of the current route
    float current_route_total_distance = 0;
    for(int i=0;i<number_of_coordinates-1;i++){
        current_route_total_distance += distanceBetweenCoordinates(coordinates[i],coordinates[i+1]);
    }

    for(int i=0;i<number_of_coordinates-2;i++){
        for(int j=i+1;j<number_of_coordinates;j++){
            if(j == i+1 || j == number_of_coordinates-1)    //  Ignores the "neighbour" of the coordinate analyzed and when j cannot inverse the j+1 element
                continue;

            // Index of coordinates that will be traded
            int inversed_coordinate_index_1 = i+1;
            int inversed_coordinate_index_2 = j+1;

            // Change coordinates local
            Coordinate auxiliary = coordinates[inversed_coordinate_index_1];
            coordinates[inversed_coordinate_index_1] = coordinates[inversed_coordinate_index_2];
            coordinates[inversed_coordinate_index_2] = auxiliary;

            float new_route_total_distance = 0;
            for(int k=0;k<number_of_coordinates;k++)    // Calculate new route
                new_route_total_distance += distanceBetweenCoordinates(coordinates[k],coordinates[k+1]);
            
            if(new_route_total_distance < current_route_total_distance){
            // Keeps new route, update total distance of current_route to the new_route total distance and re-start the 2-opt with the new_route (by setting i = 0 and break the loop)

                current_route_total_distance = new_route_total_distance;
                i = 0;
                break;
            } else {
            // Change back the coordinates to the old version and go to next iteration

                coordinates[inversed_coordinate_index_2] = coordinates[inversed_coordinate_index_1];
                coordinates[inversed_coordinate_index_1] = auxiliary;
            }
        }
    }

    // Diplay the coordinates organized in the best calculated route
    std::cout << "(" << coordinates[0].x << ", " << coordinates[0].y << ")";
    for(int i=1;i<number_of_coordinates;i++){
        std::cout << ",\n(" << coordinates[i].x << ", " << coordinates[i].y << ")";
    }
    std::cout << ",\n(" << coordinates[0].x << ", " << coordinates[0].y << ")";  // Repeats first coordinate to "go back" to it

    std::cout << "\n\n";

    current_route_total_distance += distanceBetweenCoordinates(coordinates[number_of_coordinates-1], coordinates[0]);   // Adds distance to "go back to the beggining"
    std::cout << current_route_total_distance << std::endl;

    return 0;
}