#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <errno.h>
#define BADEXIT 1
#define GOODEXIT 0

typedef struct Points
{
	int x,y;
} Points;

typedef struct Pond {
	int **grid;
	int size;
	int max;
} Pond;

Points xAndYValues[8] = {{-2,-1}, {-1, -2}, {1, -2}, {2,-1}, {2,1}, {1,2}, {-1, 2}, {-2, 1}};

int find_path(Pond *pond, Points a, int currentJump, int prevKind);
void print_Pond(Pond *Pond);


int main (int argc, char *argv[])
{

char *num;
	if(argc != 4)
		{

			fprintf(stderr, "USAGE: %s [size] [Start X] [Start Y] \n", argv[0]);
			return BADEXIT;
		}
	if(!isdigit(argv[1]) || !isdigit(argv[2]) || !isdigit(argv[3]))	
	{

			fprintf(stderr, "All values must be integers between 0 and 9 \n");
			return BADEXIT;
	}
	int size = strtol(argv[1],&num, 10);
	int start_y = strtol(argv[2],&num, 10);
	int start_x = strtol(argv[3],&num, 10);
	
	
	if(size > 9 || size < 0)
	{
			fprintf(stderr, "size must be less than 9 and greater than 0");
			return BADEXIT;
	}
	if(start_x >= size || start_x < 0)
	{
			fprintf(stderr, "Start_X must be less than the size and greater than 0");
			return BADEXIT;
	}
	if(start_y >= size || start_y < 0)
	{
			fprintf(stderr, "Start_Y must be less than the size and greater than 0");
			return BADEXIT;
	}
	
	Pond *pond;
	pond = malloc(sizeof(Pond));
	pond->grid = calloc(size, sizeof(int *));
	pond->size = size;
	for(int i = 0; i < size; i++)
	{
		pond->grid[i] = calloc(size, sizeof(int));
	}
	pond->max = size * size;
	
	Points start;
	start.x = start_x;
	start.y = start_y;
	
	int result = find_path(pond,start,1,0);
	if(result) print_Pond(pond);
	else printf("Path not found");
	}
	
	
int find_path(Pond *pond, Points a,int currentJump, int prevKind)
{
	pond->grid[a.x][a.y] = currentJump;
	if(currentJump == pond->max) return 0;
	else
	{
		for(int i = 0; i < 8; i++)
			{
				if( i == prevKind) continue;
				int x = a.x + xAndYValues[i].x;
				int y = a.y + xAndYValues[i].y;
				Points newA = (Points){x,y};
				if(newA.x < pond->size && newA.x >= 0 && newA.y < pond->size && newA.y >= 0 && !pond->grid[x][y]) return find_path(pond,newA,currentJump+1,i);		
			}
			pond->grid[a.x][a.y] = 0;
	return 1;
	
	}
}

void print_Pond(Pond *pond)
{
	for(int i = 0; i < pond->size; i++)
	{
		for(int j = 0; j < pond->size; j++)
		{
			int num = pond->grid[i][j];
			if(num <10) printf(" "); //print out extra line to align text
			printf("%d ",num);
		}
	printf("\n");
	}

}