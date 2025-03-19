//%%writefile cheapest_insertion.cpp

#include <iostream>
#include <cmath>
#include <vector>

struct Coordinate{
  float x;
  float y;
  bool was_visited;
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
  for(int i=0;i<number_of_coordinates;i++){
    std::cin >> coordinates[i].x >> coordinates[i].y;
    coordinates[i].was_visited = false;   // Set false to all coordinates in the beginning
  }

  // Get the two coordinates that are furthest of each other
  float biggest_distance_between_two_coordinates = -1;
  int begin_coordinate, end_coordinate;
  for(int i=0;i<number_of_coordinates-1;i++)
    for(int j=i+1;j<number_of_coordinates;j++){
      float current_distance_between_two_coordinates = distanceBetweenCoordinates(coordinates[i], coordinates[j]);
      if(current_distance_between_two_coordinates > biggest_distance_between_two_coordinates){
        begin_coordinate = i;
        end_coordinate = j;
        biggest_distance_between_two_coordinates = current_distance_between_two_coordinates;
      }
    }

  // Create and start the route using the two coordinates
  std::vector<Coordinate*> route;
  route.push_back(&coordinates[begin_coordinate]);   // Set coordinate in the right position
  coordinates[begin_coordinate].was_visited = true;   // Set coordinate as visited
  route.push_back(&coordinates[end_coordinate]);
  coordinates[end_coordinate].was_visited = true;

  int number_of_remaining_paths = number_of_coordinates-2;  // Number of times that it takes to calculate the best path between 3 coordinates
  while(number_of_remaining_paths > 0){

    float route_total_distance_currently = 0;
    for(int i=0;i<route.size()-1;i++)   // Calculate route total distance currently
        route_total_distance_currently += distanceBetweenCoordinates(*route[i], *route[i+1]);

    float smallest_path_distance = 100000;  // Auxiliary variable to compare distance bewtween 3 coordinates

    int tip_coordinate_1;   // Auxiliary variables
    int inserted_coordinate;
    int tip_coordinate_2;

    // Get all pairs of coordinates available in "route" (first and second for loop)
    // And analyze which one has a coordinate between them which adds the smallest value of distance to the route (third for loop)
    for(int i=0;i<route.size()-1;i++){
      for(int k=0;k<number_of_coordinates;k++){
        if(coordinates[k].was_visited == true)  // Ignore coordinates that were visited
          continue;

        // Calculate distance between the three current variables
        float path_option_distance = 0;
        path_option_distance += route_total_distance_currently;
        path_option_distance -= distanceBetweenCoordinates(*route[i], *route[i+1]);
        path_option_distance += distanceBetweenCoordinates(*route[i], coordinates[k]);
        path_option_distance += distanceBetweenCoordinates(coordinates[k], *route[i+1]);

        // Check if this path is the best path
        if(path_option_distance < smallest_path_distance){
          tip_coordinate_1 = i;
          inserted_coordinate = k;
          tip_coordinate_2 = i+1;
          smallest_path_distance = path_option_distance;
        }
      }
    }

    // The best path is inserted in the route
    route.insert(route.begin() + tip_coordinate_1 + 1, &coordinates[inserted_coordinate]);          //Check

    // The new coordinate in the route is set as visited
    coordinates[inserted_coordinate].was_visited = true;

    number_of_remaining_paths--;  // Calculate the next insertion
  }

  route.push_back(route[0]);  // Make the connection between the first coordinate and the last one

  // Diplay the coordinates organized in the best calculated route
  std::cout << "(" << route[0]->x << ", " << route[0]->y << ")";
  for(int i=1;i<number_of_coordinates+1;i++){
    std::cout << ",\n(" << route[i]->x << ", " << route[i]->y << ")";
  }

  std::cout << "\n\n";

  // Calculate total distance
  float route_total_distance = 0;
  for(int i=0;i<route.size()-1;i++)
    route_total_distance += distanceBetweenCoordinates(*route[i], *route[i+1]);

  // Display the total distance of the route
  std::cout << "Total distance of the route: " << route_total_distance << std::endl;

  return 0;
}