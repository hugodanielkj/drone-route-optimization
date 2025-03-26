#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

struct Coordinate{
    float x;
    float y;
};

float distanceBetweenTwoCoordinates(const Coordinate& a, const Coordinate& b){
    float x_axis = a.x - b.x;
    float y_axis = a.y - b.y;
    return sqrt(x_axis*x_axis + y_axis*y_axis);
}

void CoordinatesSwap(vector<Coordinate>& coordinates, const int& coordinate_a_index, const int& coordinate_b_index){
    Coordinate auxiliary = coordinates[coordinate_a_index];
    coordinates[coordinate_a_index] = coordinates[coordinate_b_index];
    coordinates[coordinate_b_index] = auxiliary;
}

void NearestNeighbour(vector<Coordinate>& coordinates, int number_of_coordinates){
    bool coordinate_visited[number_of_coordinates];     // Auxiliary vector to check if coordinate was visited or not

    for(int i=0;i<number_of_coordinates;i++)    // Setting every coordinate to not visited
        coordinate_visited[i] = false;

    const int begin_coordinate = 39;      // Constant to choose first coordinate to start algorithm
    CoordinatesSwap(coordinates,0,begin_coordinate);    // Reorganizes vector, putting the initial coordinate in the beggining of the vector

    coordinate_visited[0] = true;

    for(int i=0;i<number_of_coordinates-1;i++){
        float smallest_distance_between_two_coordinates = 9999999;
        int index_of_new_coordinate_to_add;

        for(int j=0;j<number_of_coordinates;j++){
            if(coordinate_visited[j] == true)       // Check if the coordinate was already visited
                continue;   

            float current_distance_between_two_coordinates = distanceBetweenTwoCoordinates(coordinates[i], coordinates[j]);
    
            if(current_distance_between_two_coordinates < smallest_distance_between_two_coordinates){   // Store the smallest path between current coordinate and some coordinate
                smallest_distance_between_two_coordinates = current_distance_between_two_coordinates;
                index_of_new_coordinate_to_add = j;
            }
        }

        CoordinatesSwap(coordinates,i+1,index_of_new_coordinate_to_add);    // Reorganizes the vector, putting the new coordinate in the next position in the vector
        coordinate_visited[i+1] = true;     // Setting this selected coordinate as visited
    }
}

vector<vector<Coordinate>> CalculateDroneRoutes(const vector<Coordinate>& coordinates, const float& drone_max_distance_full_charged){
    vector<vector<Coordinate>> routes;

    float route_distance = 0;
    int begin_of_new_route = 1;

    for(int i=0;i<coordinates.size()-1;i++){
        if((route_distance 
        + distanceBetweenTwoCoordinates(coordinates[i], coordinates[i+1])
        + distanceBetweenTwoCoordinates(coordinates[i+1], coordinates[0])
        <= drone_max_distance_full_charged))
        {
            route_distance += distanceBetweenTwoCoordinates(coordinates[i], coordinates[i+1]);
        }
        else if(i == coordinates.size() - 2)  
        {
            cout << route_distance << endl;
            vector<Coordinate> route;
            route.push_back(coordinates[0]);
            for(int j=begin_of_new_route;j<=i;j++){
                route.push_back(coordinates[j]);
            }
            route.push_back(coordinates[0]);
            routes.push_back(route);
        }
        else
        {
            cout << route_distance << endl;
            vector<Coordinate> route;
            route.push_back(coordinates[0]);
            for(int j=begin_of_new_route;j<=i;j++){
                route.push_back(coordinates[j]);
            }
            route.push_back(coordinates[0]);
            routes.push_back(route);
            
            begin_of_new_route = i+1;
            route_distance = 0;
            route_distance += distanceBetweenTwoCoordinates(coordinates[0], coordinates[i+1]);
        }
    }

    return routes;
}

void twoOpt(vector<Coordinate>& route){
    bool improved = true;
    while(improved){
      improved = false;
      for(int i=0;i<route.size()-3;i++){
          for(int j=i+2;j<route.size()-1;j++){   // Goes until number_of_coordinates-1 because element j+1 will need to be acessed
              float current_path_distance =
              distanceBetweenTwoCoordinates(route[i], route[i+1]) + distanceBetweenTwoCoordinates(route[j], route[j+1]);

              float new_path_distance =
              distanceBetweenTwoCoordinates(route[i], route[j]) + distanceBetweenTwoCoordinates(route[j+1], route[i+1]);

              if(new_path_distance < current_path_distance){
              // Keeps new route and re-start the 2-opt with the new_route (by setting i = 0 and break the loop)
                  reverse(route.begin() + i + 1, route.begin() + j + 1);
                  improved = true;
              }
          }
      }
    }
}

int main(){
    int number_of_coordinates;
    cin >> number_of_coordinates;

    vector<Coordinate> coordinates;
    coordinates.resize(number_of_coordinates);

    for(int i=0;i<number_of_coordinates;i++){   // Reading and storing coordinates
        cin >> coordinates[i].x;
        cin >> coordinates[i].y;
    }

    NearestNeighbour(coordinates, number_of_coordinates);  // Coordinates reorganized well enough

    const float drone_max_distance_full_charged = 3000;

    // Routes division limited by a max distance
    vector<vector<Coordinate>> drone_routes = CalculateDroneRoutes(coordinates, drone_max_distance_full_charged);

    for(int i=0;i<drone_routes.size();i++){
        cout << i+1 << "a ROUTE\n\n";

        for(int j=0;j<drone_routes[i].size();j++){
            cout << drone_routes[i][j].x << " " << drone_routes[i][j].y << endl;
        }
        if(i!=drone_routes.size()-1) cout << "\n";
    }

    cout << drone_routes.size() << " routes were generated.\n\n";

    for(int i=0;i<drone_routes.size();i++){         // TwoOpt applied in each drone route
        float route_distance = 0;
        for(int j=0;j<drone_routes[i].size()-1;j++){
            route_distance += distanceBetweenTwoCoordinates(drone_routes[i][j],drone_routes[i][j+1]);
        }
        cout << "Route distance before 2_opt: " << route_distance << endl;
        twoOpt(drone_routes[i]);

        route_distance = 0;
        for(int j=0;j<drone_routes[i].size()-1;j++){
            route_distance += distanceBetweenTwoCoordinates(drone_routes[i][j],drone_routes[i][j+1]);
        }
        cout << "Route distance after 2_opt: " << route_distance << "\n\n";        
    }

    return 0;
}