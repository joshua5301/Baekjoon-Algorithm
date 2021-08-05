#19537 전투 시뮬레이션 by joshua5301

#include <cstdio>
#include <queue>
#include <tuple>
using namespace std;

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
int height, width;

bool** calc_engagement(int** unit, int unit_num, int side);
bool is_valid(int i, int j);

bool** calc_engagement(int** unit, int unit_num, int side){
	int i, j;
	bool** matrix = new bool* [height];
	for(i=0; i<height; i++){
		matrix[i] = new bool [width];
		for(j=0; j<width; j++){
			matrix[i][j] = false;
		}
	}
    for(i=0; i<unit_num; i++){
    	if(unit[i][1] != side){
    		matrix[unit[i][2]][unit[i][3]] = true;
    		for(j=0; j<4; j++){
    			if(is_valid(unit[i][2] + dy[j], unit[i][3] + dx[j])){
    				matrix[unit[i][2] + dy[j]][unit[i][3] + dx[j]] = true;
				}
			}
		}
	}
	return matrix;
}
    


bool is_valid(int i, int j){
	if(0 <= i && i <= height - 1 && 0 <= j && j <= width - 1){
		return true;
	}
	else{
		return false;
	}
}

int main(){
	int i, j, k;
	int terrain_num, command_num, unit_num;
	int *terrain_info;
	int **terrain, **unit, **command;
	
	scanf("%d %d %d", &terrain_num, &height, &width);
	terrain = new int* [height];
	for(i=0; i<height; i++){
		terrain[i] = new int [width];
		for(j=0; j<width; j++){
			scanf("%d", &terrain[i][j]);
		}
	}
	terrain_info = new int [terrain_num];
	for(i=0; i<terrain_num; i++){
		scanf("%d", &terrain_info[i]);
	}
	
	scanf("%d", &unit_num);
	unit = new int* [unit_num];
	for(i=0; i<unit_num; i++){
		unit[i] = new int [4];
		scanf("%d %d %d %d", &unit[i][0], &unit[i][1], &unit[i][2], &unit[i][3]);
	}
	
	scanf("%d", &command_num);
	command = new int* [command_num];
	for(i=0; i<command_num; i++){
		command[i] = new int [3];
		scanf("%d %d %d", &command[i][0], &command[i][1], &command[i][2]);
	}
	
	for(k=0; k<command_num; k++){
		int unit_number = command[k][0] - 1;
    	int mobility = unit[unit_number][0];
    	int side = unit[unit_number][1];
    	int start_y = unit[unit_number][2];
    	int start_x = unit[unit_number][3];
    	int end_y = command[k][1];
    	int end_x = command[k][2];
    	
    	bool invalid = false;
    	for(i=0; i<unit_num; i++){
    	 	if(unit[i][2] == end_y && unit[i][3] == end_x){
        	invalid = true;
			}
			if(invalid){
				continue;
			}	
		}
    	bool** engagement = calc_engagement(unit, unit_num, side);

    	priority_queue<int, vector<int>, greater<int> > heap;
    	heap.push(make_tuple(0, start_y, start_x));
    	int** distance = new int* [height];
    	bool** visited = new bool* [height];
    	for(i=0; i<height; i++){
    		distance[i] = new int [width];
			visited[i] = new bool [width];
    		for(j=0; j<width; j++){
    			distance[i][j] = 10000000;
    			visited[i][j] = false;
			}
		}
    	distance[start_y][start_x] = 0;
    	visited[start_y][start_x] = true;

    	while(not heap.empty()){	
    		int cur_distance, cur_y, cur_x;
        	tie(cur_distance, cur_y, cur_x) = heap.top();
        	heap.pop();

        	if(cur_y == end_y && cur_x == end_x){
        		unit[unit_number][2] = end_y;
            	unit[unit_number][3] = end_x;
            	// printf("finished");
				break;
			}

        	for(i=0; i<4; i++){
        		int next_y = cur_y + dy[i];
				int next_x = cur_x + dx[i];
				int next_distance = -1;
			    	if(is_valid(next_y, next_x)){
			    		if(visited[next_y][next_x]){
			    			continue;
						}
            			visited[next_y][next_x] = true;
                		next_distance = cur_distance + terrain_info[terrain[next_y][next_x] - 1];
            		}
                	if(next_distance < cur_distance || next_distance > mobility){
                		continue;
					}
               		if((next_y == end_y && next_x == end_x || not engagement[next_y][next_x]) and distance[next_y][next_x] > next_distance){
                		distance[next_y][next_x] = next_distance;
                    	heap.push(make_tuple(next_distance, next_y, next_x));
					}

			}
		}
	}
	for(i=0; i<unit_num; i++){
		printf("%d %d\n", unit[i][2], unit[i][3]);
	}
	return 0;
}

