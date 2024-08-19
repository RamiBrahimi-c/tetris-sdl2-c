#include <SDL2/SDL.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#define WINDOW_HEIGHT 480
#define WINDOW_WIDTH 640
#define GRID_SIZE 30
#define GRID_DIM 300
#define GRID_DIM_WIDTH 200
#define GRID_DIM_HEIGHT 350
#define row 20
#define col 10
#define cellSize 20
#define colorNum 8

typedef struct Position
{
    int rows ;
    int column ;
}Position;

typedef struct Shape
{
    char id ;
    Position position[4][4];
    int rotationState;
    int colorShape ;
    bool move;
}Shape;
typedef struct Direction
{
    bool right;
    bool left;
}Direction;



void initializeGrid( int grid[row][col]);
void render_grid(SDL_Renderer *renderer , int x , int y ,int grid[row][col] , SDL_Color *Colors);
void printGrid( int grid[row][col]); 
void setColors(SDL_Color *arr , int length);
void setIdShapes(char *idShapes )
{
    idShapes[0] = 'I' ;
    idShapes[1] = 'O' ;
    idShapes[2] = 'L' ;
    idShapes[3] = 'J' ;
    idShapes[4] = 'S' ;
    idShapes[5] = 'Z' ;
    idShapes[6] = 'T' ;
}
void createShapes(int gridShape[4][4] , char *idShapes  )
{
    char id = idShapes[1] ;
    int num  =  (3 ) + 1;
    switch (id)
    {
    case 'I':
        gridShape[0][2] = num ;
        gridShape[1][2] = num ;
        gridShape[2][2] = num ;
        gridShape[3][2] = num ;
        break;
    
    case 'O':
        gridShape[1][1] = num ;
        gridShape[1][2] = num ;
        gridShape[2][1] = num ;
        gridShape[2][2] = num ;

        break;
    
    case 'L':
        gridShape[1][2] = num ;
        gridShape[2][2] = num ;
        gridShape[3][2] = num ;
        gridShape[3][3] = num ;

        break;
    
    case 'J':
        gridShape[1][2] = num ;
        gridShape[2][2] = num ;
        gridShape[3][2] = num ;
        gridShape[3][1] = num ;

        break;
    
    case 'S':
        gridShape[2][1] = num ;
        gridShape[2][2] = num ;
        gridShape[1][2] = num ;
        gridShape[1][3] = num ;

        break;
    
    case 'Z':
        gridShape[1][0] = num ;
        gridShape[1][1] = num ;
        gridShape[2][1] = num ;
        gridShape[2][2] = num ;

        break;
    
    case 'T':
        gridShape[1][0] = num ;
        gridShape[1][1] = num ;
        gridShape[1][2] = num ;
        gridShape[2][1] = num ;

        break;
    
    default:
        gridShape[0][0]=0;
        break;
    }
}
void renderShape(SDL_Renderer *renderer , int x , int y ,Shape *shape , SDL_Color  *Colors);
void createShapesA(Shape *shape);



void printArrayofPos(Position *arr)
{
    for (int i = 0 ; i <4 ; i++)
    printf("arr[%d].i = %d arr[%d].col = %d \n", i , arr[i].rows , i , arr[i].column);
}
void setPositionArray(Shape *shape , Position *arr )
{
    
    switch (shape->id)
    {
    case 0:
        
        if (shape->rotationState == 0)
        {
            arr[0].rows = shape->position[0][3].rows; arr[0].column = shape->position[0][3].column;
        }
        else
        {
            
                                                    
            arr[0].rows = shape->position[1][0].rows;arr[0].column = shape->position[1][0].column;            
            arr[1].rows = shape->position[1][1].rows; arr[1].column = shape->position[1][1].column;            
            arr[2].rows = shape->position[1][2].rows; arr[2].column = shape->position[1][2].column;            
            arr[3].rows = shape->position[1][3].rows; arr[3].column = shape->position[1][3].column;            
           // printArrayofPos(arr);
        }
        
        break;
    
    default:
    arr[0].column=0;
        break;
    }
}
bool isThereaBlockbelow(Shape *shape , int grid[row][col], Position arrPositionLastRow[4])
{
    int i = shape->rotationState , iGrid = arrPositionLastRow[0].rows  , jGrid = arrPositionLastRow[0].column;
 switch (shape->id)
 {
    case 0:
        if (shape->rotationState==0)
            return (grid[shape->position[0][3].rows+1][ shape->position[0][3].column]>0)?false : true ;
        if (shape->rotationState==1)
            return (grid[shape->position[1][0].rows+1][shape->position[1][0].column] > 0 ||grid[shape->position[1][1].rows+1][shape->position[1][1].column] > 0 || grid[shape->position[1][2].rows+1][shape->position[1][2].column] > 0 || grid[shape->position[1][3].rows+1][shape->position[1][3].column] > 0) ? false : true; 
        
        
        break;
    case 1 :
        if (shape->rotationState ==0)
            return (grid[shape->position[0][1].rows+1][ shape->position[0][1].column]>0 || grid[shape->position[0][2].rows+1][ shape->position[0][2].column]>0  || grid[shape->position[0][3].rows+1][ shape->position[0][3].column]>0)?false : true ;
        if(shape->rotationState==1)
            return (grid[shape->position[1][2].rows+1][ shape->position[1][2].column]>0 || grid[shape->position[1][3].rows+1][ shape->position[1][3].column]>0) ? false : true ;
        if(shape->rotationState==2)
            return (grid[shape->position[2][0].rows+1][ shape->position[2][0].column]>0 || grid[shape->position[2][2].rows+1][ shape->position[2][2].column]>0 || grid[shape->position[2][3].rows+1][ shape->position[2][3].column]>0) ? false :true;
        if(shape->rotationState==3)
            return (grid[shape->position[3][0].rows+1][ shape->position[3][0].column]>0 || grid[shape->position[3][3].rows+1][ shape->position[3][3].column]>0) ? false :true;
            break;
    case 2 :
        return (grid[shape->position[0][2].rows+1][ shape->position[0][2].column]>0 || grid[shape->position[0][3].rows+1][ shape->position[0][3].column]>0) ? false : true ;        
        break;
    case 3:
        if(shape->rotationState==0)
        return (grid[shape->position[0][0].rows+1][ shape->position[0][0].column]>0 || grid[shape->position[0][1].rows+1][ shape->position[0][1].column]>0 || grid[shape->position[0][2].rows+1][ shape->position[0][2].column]>0) ? false :true;        
        if(shape->rotationState==1)
        return (grid[shape->position[1][2].rows+1][ shape->position[1][2].column]>0 || grid[shape->position[1][3].rows+1][ shape->position[1][3].column]>0 ) ? false :true;        
        if(shape->rotationState==2)
        return (grid[shape->position[2][1].rows+1][ shape->position[2][1].column]>0 || grid[shape->position[2][2].rows+1][ shape->position[2][2].column]>0 || grid[shape->position[2][3].rows+1][ shape->position[2][3].column]>0) ? false :true;        
        if(shape->rotationState==3)
        return (grid[shape->position[3][0].rows+1][ shape->position[3][0].column]>0 || grid[shape->position[3][3].rows+1][ shape->position[3][3].column]>0 ) ? false :true;        
                
        break;
    case 4:
        if(shape->rotationState==0)
        return (grid[shape->position[0][1].rows+1][ shape->position[0][1].column]>0 || grid[shape->position[0][3].rows+1][ shape->position[0][3].column]>0 || grid[shape->position[0][0].rows+1][shape->position[0][0].column] >0) ? false :true;
        if(shape->rotationState==1)
        return (grid[shape->position[1][1].rows+1][ shape->position[1][1].column]>0 || grid[shape->position[1][3].rows+1][ shape->position[1][3].column]>0 ) ? false :true;

        break;
    case 5 :
        if(shape->rotationState==0)
        return (grid[shape->position[0][0].rows+1][ shape->position[0][0].column]>0 || grid[shape->position[0][1].rows+1][ shape->position[0][1].column]>0 || grid[shape->position[0][3].rows+1][shape->position[0][3].column] >0) ? false :true;
        if(shape->rotationState==1)
        return (grid[shape->position[1][0].rows+1][ shape->position[1][0].column]>0 || grid[shape->position[1][2].rows+1][ shape->position[1][2].column]>0 ) ? false :true;

        break;
    case 6:
        if(shape->rotationState==0)
        return (grid[shape->position[0][0].rows+1][ shape->position[0][0].column]>0 || grid[shape->position[0][2].rows+1][ shape->position[0][2].column]>0 || grid[shape->position[0][3].rows+1][ shape->position[0][3].column]>0) ? false :true;        
        if(shape->rotationState==1)
        return (grid[shape->position[1][2].rows+1][ shape->position[1][2].column]>0 || grid[shape->position[1][3].rows+1][ shape->position[1][3].column]>0 ) ? false :true;        
        if(shape->rotationState==2)
        return (grid[shape->position[2][0].rows+1][ shape->position[2][0].column]>0 || grid[shape->position[2][1].rows+1][ shape->position[2][1].column]>0 || grid[shape->position[2][2].rows+1][ shape->position[2][2].column]>0) ? false :true;        
        if(shape->rotationState==3)
        return (grid[shape->position[3][2].rows+1][ shape->position[3][2].column]>0 || grid[shape->position[3][3].rows+1][ shape->position[3][3].column]>0 ) ? false :true;        

        break;               
    default:
    break;
 }   
}
void setiGrid(Shape shape,int *iGrid )
{
    switch (shape.id)
    {
    case 0:
        *iGrid= (shape.rotationState==0) ? shape.position[0][3].rows : shape.position[1][3].rows;
        break;
    case 1 : 
        if (shape.rotationState==0)
        *iGrid= shape.position[0][3].rows;
        if (shape.rotationState==1)
        *iGrid= shape.position[1][3].rows;
        if (shape.rotationState==2)
        *iGrid= shape.position[2][0].rows;
        if (shape.rotationState==3)
        *iGrid= shape.position[3][3].rows;
        break;
    case 2:
        if (shape.rotationState==0)
        *iGrid=shape.position[0][3].rows;
        break;
    case 3:
        if(shape.rotationState==0)
        *iGrid=shape.position[0][0].rows;        
        if(shape.rotationState==1)
        *iGrid=shape.position[1][3].rows;        
        if(shape.rotationState==2)
        *iGrid=shape.position[2][3].rows;        
        if(shape.rotationState==3)
        *iGrid=shape.position[3][3].rows;        
        break; 
    case 4:
        if(shape.rotationState==0)
        *iGrid=shape.position[0][1].rows;           
        if(shape.rotationState==1)
        {
            *iGrid=shape.position[1][3].rows;
        }

        break; 
    case 5:
        if(shape.rotationState==0)
        *iGrid=shape.position[0][1].rows;                  
        if(shape.rotationState==1)
        *iGrid=shape.position[1][0].rows; 
        break;
    case 6:
        if(shape.rotationState==0)
        *iGrid=shape.position[0][3].rows;        
        if(shape.rotationState==1)
        *iGrid=shape.position[1][2].rows;        
        if(shape.rotationState==2)
        *iGrid=shape.position[2][0].rows;        
        if(shape.rotationState==3)
        *iGrid=shape.position[3][2].rows;        
        break;                         
    default:
        *iGrid=55;
        break;
    }
}
void moveShapeVertically(Shape *shape , int grid[row][col] ,  Position arrPositionLastRow[4])
{
    int i= shape->rotationState, iGrid;

    setiGrid(*shape , &iGrid );

    if (iGrid  < row -1 && isThereaBlockbelow(shape,grid , arrPositionLastRow)  ) 
    {
        //printf("valid %d\n", iGrid);
        shape->move = true ;
        for (int k =0 ; k <4 ; k++)
        shape->position[i][k].rows++ ;      
    } else 
    {
        shape->move = false ;

    }
}

bool isThereABlockOnRight(Shape *shape , int grid[row][col])
{
    switch (shape->id)
    {
    case 0:
        if(shape->rotationState==0)
        return (grid[shape->position[0][0].rows][shape->position[0][0].column+1]>0 ||grid[shape->position[0][1].rows][shape->position[0][1].column+1]>0 || grid[shape->position[0][2].rows][shape->position[0][2].column+1]>0 || grid[shape->position[0][3].rows][shape->position[0][3].column+1]>0) ? false:true;
        if(shape->rotationState==1)
        return (grid[shape->position[1][3].rows][shape->position[1][3].column+1]>0 ) ? false:true;

        break;
    case 1:
        if(shape->rotationState==0)
        return (grid[shape->position[0][0].rows][shape->position[0][0].column+1]>0 ||grid[shape->position[0][3].rows][shape->position[0][3].column+1]>0 ) ? false:true;
        if(shape->rotationState==1)
        return (grid[shape->position[1][3].rows][shape->position[1][3].column+1]>0 ) ? false:true;
        if(shape->rotationState==2)
        return (grid[shape->position[2][3].rows][shape->position[2][3].column+1]>0 ) ? false:true;
        if(shape->rotationState==3)
        return (grid[shape->position[3][1].rows][shape->position[3][1].column+1]>0 || grid[shape->position[3][2].rows][shape->position[3][2].column+1]>0 || grid[shape->position[3][3].rows][shape->position[3][3].column+1]>0 ) ? false:true;

        break;    
    case 2:
        if(shape->rotationState==0)
        return (grid[shape->position[0][1].rows][shape->position[0][1].column+1]>0 ||grid[shape->position[0][3].rows][shape->position[0][3].column+1]>0 ) ? false:true;
        break;    
    case 3:
        if(shape->rotationState==0)
        return (grid[shape->position[0][0].rows][shape->position[0][0].column+1]>0 ||grid[shape->position[0][3].rows][shape->position[0][3].column+1]>0 ) ? false:true;
        if(shape->rotationState==1)
        return (grid[shape->position[1][0].rows][shape->position[1][0].column+1]>0 || grid[shape->position[1][1].rows][shape->position[1][1].column+1]>0 || grid[shape->position[1][2].rows][shape->position[1][2].column+1]>0 ) ? false:true;
        if(shape->rotationState==2)
        return (grid[shape->position[2][3].rows][shape->position[2][3].column+1]>0 ) ? false:true;
        if(shape->rotationState==3)
        return (grid[shape->position[3][0].rows][shape->position[3][0].column+1]>0 ) ? false:true;
        break;
    case 4:
        if(shape->rotationState==0)
        return (grid[shape->position[0][3].rows][shape->position[0][3].column+1]>0 ) ? false:true;
        if(shape->rotationState==1)
        return (grid[shape->position[1][2].rows][shape->position[1][2].column+1]>0 ||grid[shape->position[1][3].rows][shape->position[1][3].column+1]>0 ) ? false:true;
        break;
    case 5:
        if(shape->rotationState==0)
        return (grid[shape->position[0][3].rows][shape->position[0][3].column+1]>0 ) ? false:true;
        if(shape->rotationState==1)
        return (grid[shape->position[1][2].rows][shape->position[1][2].column+1]>0 ||grid[shape->position[1][3].rows][shape->position[1][3].column+1]>0 ) ? false:true;
        break;
    case 6:
        if(shape->rotationState==0)
        return (grid[shape->position[0][2].rows][shape->position[0][2].column+1]>0) ? false:true;
        if(shape->rotationState==1)
        return (grid[shape->position[1][0].rows][shape->position[1][0].column+1]>0 || grid[shape->position[1][1].rows][shape->position[1][1].column+1]>0 || grid[shape->position[1][2].rows][shape->position[1][2].column+1]>0 ) ? false:true;
        if(shape->rotationState==2)
        return (grid[shape->position[2][2].rows][shape->position[2][2].column+1]>0 ) ? false:true;
        if(shape->rotationState==3)
        return (grid[shape->position[3][3].rows][shape->position[3][3].column+1]>0 ) ? false:true;
        break;        
    default:
        break;
    }
}

bool isThereABlockOnLeft(Shape *shape , int grid[row][col]);
void setjGrid(Shape shape,int *jGridRight , int *jGridLeft );
void moveShapeHorizantaly(Shape *shape , int grid[row][col] , Direction *direction);








int main(int argc, char* argv[]) {
    srand(time(0));
    Shape shape ;
        Position arrPositionLastRow[4] ;

    shape.id=6;
    shape.rotationState=3;
    int grid[row][col] ;
    int gridShape[4][4] ;
    char idShapes[7];

   // setIdShapes(idShapes);
         createShapesA( &shape   );



   // printArrayofPos(arrPositionLastRow);




    SDL_Color Colors[colorNum] ;
    setColors(Colors , colorNum);


    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,WINDOW_HEIGHT , SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED) ;



    bool running = true ;
    SDL_Event event ;


    initializeGrid(grid);
   // printGrid(grid);

    grid[8][col-1] = 4;
    grid[9][col-1] = 4;
    grid[10][col-1] = 4;
    grid[11][col-1] = 4;
    
    grid[8][0] = 5;
    grid[9][0] = 5;
    grid[10][0] = 5 ; 
    grid[11][0] = 5 ; 
                  
              
//         createShapesA( &shape   );
    Direction direction ;
    direction.left=false;
    direction.right=false;
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false ;
                break;
            }
            else if(event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                    running=false ;                   
                    break;
                    case SDLK_RIGHT:
                        direction.right=true;
                        moveShapeHorizantaly(&shape, grid,&direction);
                    break;                                                                                        
                    case SDLK_LEFT:
                        direction.left=true;
                        moveShapeHorizantaly(&shape, grid,&direction);
                    break;                                                                                        


                }
                
            }
        }
        
        SDL_SetRenderDrawColor(renderer , 128,128,127,255) ;  // darkBlue
        SDL_RenderClear(renderer);

        // start

            setPositionArray(&shape , arrPositionLastRow);
        moveShapeVertically(&shape , grid ,   arrPositionLastRow) ;

        render_grid(renderer , WINDOW_WIDTH/2-GRID_DIM/2,WINDOW_HEIGHT/2-GRID_DIM/2 , grid , Colors) ;
        renderShape(renderer , 0,0,&shape , Colors);
        // end
        
        SDL_RenderPresent(renderer) ;

        SDL_Delay(400) ;
        
    }


    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer) ;
    SDL_Quit();

    return 0;
}

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

void render_grid(SDL_Renderer *renderer , int x , int y ,int grid[row][col] , SDL_Color *Colors) 
{
    x = 20 ;
    y = 20 ;
#if 1
    int cell_size = cellSize  ;
    //int cell_size = GRID_DIM/GRID_SIZE  ;
    SDL_Rect cell ;
    cell.w = cell_size -1;
    cell.h = cell_size -1;

    for (size_t i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            int cellValue = grid[i][j];
            SDL_SetRenderDrawColor(renderer ,Colors[cellValue].r,Colors[cellValue].g,Colors[cellValue].b,Colors[cellValue].a) ;
            cell.x = j*cell_size +2;
            cell.y= i*cell_size+2;
            if (cellValue > -1)
            SDL_RenderFillRect(renderer, &cell) ;
            else
            SDL_RenderDrawRect(renderer,&cell) ;
        }
        
    }
#else 
    SDL_Rect playground ;
    playground.x = x ;
    playground.y = y ;
    playground.h = GRID_DIM_HEIGHT ;
    playground.w = GRID_DIM_WIDTH ;
    SDL_RenderDrawRect(renderer , &playground);
#endif    
}

void initializeGrid( int grid[row][col]) 
{
    for (size_t i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            grid[i][j]=0;
        }
        
    }
    
}

void printGrid( int grid[row][col])
{
    for (size_t i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf("%d ",grid[i][j] );
        }
        printf("\n");
    }
}

void setColors(SDL_Color *arr , int length)
{
    arr[0].r = 26 ;arr[0].g = 31 ; arr[0].b = 40 ;  // darkgrey
    arr[1].r = 47 ;arr[1].g = 230 ; arr[1].b = 23 ;  // green 
    arr[2].r = 232 ;arr[2].g = 18 ; arr[2].b = 18 ;   // red
    arr[3].r = 226 ;arr[3].g = 116 ; arr[3].b = 17 ;   // orange
    arr[4].r = 237 ;arr[4].g = 234 ; arr[4].b = 4 ;   // yellow
    arr[5].r = 166 ;arr[5].g = 0 ; arr[5].b = 247 ;   // purple
    arr[6].r = 21 ;arr[6].g = 204 ; arr[6].b = 209 ;   // cyan 
    arr[7].r = 13 ;arr[7].g = 64 ; arr[7].b = 216 ;   // blue
    for (int i=0 ; i < length ; i++)
        arr[i].a=255;
}




void renderShape(SDL_Renderer *renderer , int x , int y ,Shape *shape , SDL_Color  *Colors)
{

    SDL_Rect rect ;
    rect.w = cellSize-1;
    rect.h = cellSize-1 ;

        for (int j = 0; j < 4; j++)
        {
            int cellValue = shape->colorShape;
            SDL_SetRenderDrawColor(renderer ,Colors[cellValue].r,Colors[cellValue].g,Colors[cellValue].b,Colors[cellValue].a) ;
            rect.x = shape->position[shape->rotationState][j].column *cellSize +2;
            rect.y= shape->position[shape->rotationState][j].rows *cellSize+2;

            SDL_RenderFillRect(renderer,&rect) ;
        }
        

    
}


void createShapesA(Shape *shape     )
{
   // shape->id = idShapes[rand() % 7] ;
   // shape->id = 0 ;
    shape->move=true;
    shape->colorShape = (rand() % 7 ) + 1 ; 
    switch (shape->id)
    {
    case 0: // rotationState=0             'I'
                shape->position[0][0].rows = 0 ; shape->position[0][0].column = 2 ;
                shape->position[0][1].rows = 1 ; shape->position[0][1].column = 2 ;
                shape->position[0][2].rows = 2 ; shape->position[0][2].column = 2 ;
                shape->position[0][3].rows = 3 ; shape->position[0][3].column = 2 ;
                // rotationState=1
                shape->position[1][0].rows = 1 ; shape->position[1][0].column = 0 ;
                shape->position[1][1].rows = 1 ; shape->position[1][1].column = 1 ;
                shape->position[1][2].rows = 1 ; shape->position[1][2].column = 2 ;
                shape->position[1][3].rows = 1 ; shape->position[1][3].column = 3 ;


        break;
    case 1: //             'L'
                // rotationState=0
                shape->position[0][0].rows = 0 ; shape->position[0][0].column = 2 ;
                shape->position[0][1].rows = 1 ; shape->position[0][1].column = 0 ;
                shape->position[0][2].rows = 1 ; shape->position[0][2].column = 1 ;
                shape->position[0][3].rows = 1 ; shape->position[0][3].column = 2 ;

                // rotationState=1
                shape->position[1][0].rows = 0 ; shape->position[1][0].column = 1 ;
                shape->position[1][1].rows = 1 ; shape->position[1][1].column = 1 ;
                shape->position[1][2].rows = 2 ; shape->position[1][2].column = 1 ;
                shape->position[1][3].rows = 2 ; shape->position[1][3].column = 2 ;

                // rotationState=2
                shape->position[2][0].rows = 2 ; shape->position[2][0].column = 0 ;
                shape->position[2][1].rows = 1 ; shape->position[2][1].column = 0 ;
                shape->position[2][2].rows = 1 ; shape->position[2][2].column = 1 ;
                shape->position[2][3].rows = 1 ; shape->position[2][3].column = 2 ;

                // rotationState=3
                shape->position[3][0].rows = 0 ; shape->position[3][0].column = 0 ;
                shape->position[3][1].rows = 0 ; shape->position[3][1].column = 1 ;
                shape->position[3][2].rows = 1 ; shape->position[3][2].column = 1 ;
                shape->position[3][3].rows = 2 ; shape->position[3][3].column = 1 ;


        break;
    case 2 : //   'O'
                shape->position[0][0].rows = 1; shape->position[0][0].column = 1;
                shape->position[0][1].rows = 1; shape->position[0][1].column = 2;
                shape->position[0][2].rows = 2; shape->position[0][2].column = 1;
                shape->position[0][3].rows = 2; shape->position[0][3].column = 2;

        break;  
    case 3: //             'J'
                // rotationState=0
                shape->position[0][0].rows = 2 ; shape->position[0][0].column = 2 ;
                shape->position[0][1].rows = 1 ; shape->position[0][1].column = 0 ;
                shape->position[0][2].rows = 1 ; shape->position[0][2].column = 1 ;
                shape->position[0][3].rows = 1 ; shape->position[0][3].column = 2 ;

                // rotationState=1
                shape->position[1][0].rows = 0 ; shape->position[1][0].column = 1 ;
                shape->position[1][1].rows = 1 ; shape->position[1][1].column = 1 ;
                shape->position[1][2].rows = 2 ; shape->position[1][2].column = 1 ;
                shape->position[1][3].rows = 2 ; shape->position[1][3].column = 0 ;

                // rotationState=2
                shape->position[2][0].rows = 0 ; shape->position[2][0].column = 0 ;
                shape->position[2][1].rows = 1 ; shape->position[2][1].column = 0 ;
                shape->position[2][2].rows = 1 ; shape->position[2][2].column = 1 ;
                shape->position[2][3].rows = 1 ; shape->position[2][3].column = 2 ;

                // rotationState=3
                shape->position[3][0].rows = 0 ; shape->position[3][0].column = 2 ;
                shape->position[3][1].rows = 0 ; shape->position[3][1].column = 1 ;
                shape->position[3][2].rows = 1 ; shape->position[3][2].column = 1 ;
                shape->position[3][3].rows = 2 ; shape->position[3][3].column = 1 ;


        break;
    case 4: //             'S'
                // rotationState=0
                shape->position[0][0].rows = 1 ; shape->position[0][0].column = 0 ;
                shape->position[0][1].rows = 1 ; shape->position[0][1].column = 1 ;
                shape->position[0][2].rows = 0 ; shape->position[0][2].column = 1 ;
                shape->position[0][3].rows = 0 ; shape->position[0][3].column = 2 ;

                // rotationState=1
                shape->position[1][0].rows = 0 ; shape->position[1][0].column = 0 ;
                shape->position[1][1].rows = 1 ; shape->position[1][1].column = 0 ;
                shape->position[1][2].rows = 1 ; shape->position[1][2].column = 1 ;
                shape->position[1][3].rows = 2 ; shape->position[1][3].column = 1 ;

        break;
    case 5: //             'Z'
                // rotationState=0
                shape->position[0][0].rows = 0 ; shape->position[0][0].column = 0 ;
                shape->position[0][1].rows = 1 ; shape->position[0][1].column = 1 ;
                shape->position[0][2].rows = 0 ; shape->position[0][2].column = 1 ;
                shape->position[0][3].rows = 1 ; shape->position[0][3].column = 2 ;

                // rotationState=1
                shape->position[1][0].rows = 2 ; shape->position[1][0].column = 0 ;
                shape->position[1][1].rows = 1 ; shape->position[1][1].column = 0 ;
                shape->position[1][2].rows = 1 ; shape->position[1][2].column = 1 ;
                shape->position[1][3].rows = 0 ; shape->position[1][3].column = 1 ;

        break;
    case 6: //             'T'
                // rotationState=0
                shape->position[0][0].rows = 0 ; shape->position[0][0].column = 0 ;
                shape->position[0][1].rows = 0 ; shape->position[0][1].column = 1 ;
                shape->position[0][2].rows = 0 ; shape->position[0][2].column = 2 ;
                shape->position[0][3].rows = 1 ; shape->position[0][3].column = 1 ;

                // rotationState=1
                shape->position[1][0].rows = 0 ; shape->position[1][0].column = 2 ;
                shape->position[1][1].rows = 1 ; shape->position[1][1].column = 2 ;
                shape->position[1][2].rows = 2 ; shape->position[1][2].column = 2 ;
                shape->position[1][3].rows = 1 ; shape->position[1][3].column = 1 ;
                // rotationState=2
                shape->position[2][0].rows = 2 ; shape->position[2][0].column = 0 ;
                shape->position[2][1].rows = 2 ; shape->position[2][1].column = 1 ;
                shape->position[2][2].rows = 2 ; shape->position[2][2].column = 2 ;
                shape->position[2][3].rows = 1 ; shape->position[2][3].column = 1 ;
                // rotationState=3
                shape->position[3][0].rows = 0 ; shape->position[3][0].column = 0 ;
                shape->position[3][1].rows = 1 ; shape->position[3][1].column = 0 ;
                shape->position[3][2].rows = 2 ; shape->position[3][2].column = 0 ;
                shape->position[3][3].rows = 1 ; shape->position[3][3].column = 1 ;

        break;                                   
    default://typeshi
        shape->position[0][0].rows=0;
        break;
    }
}

bool isThereaBlockbelow(Shape *shape , int grid[row][col], Position arrPositionLastRow[4])
{
    int i = shape->rotationState , iGrid = arrPositionLastRow[0].rows  , jGrid = arrPositionLastRow[0].column;
 switch (shape->id)
 {
    case 0:
        if (shape->rotationState==0)
            return (grid[shape->position[0][3].rows+1][ shape->position[0][3].column]>0)?false : true ;
        if (shape->rotationState==1)
            return (grid[shape->position[1][0].rows+1][shape->position[1][0].column] > 0 ||grid[shape->position[1][1].rows+1][shape->position[1][1].column] > 0 || grid[shape->position[1][2].rows+1][shape->position[1][2].column] > 0 || grid[shape->position[1][3].rows+1][shape->position[1][3].column] > 0) ? false : true; 
        
        
        break;
    case 1 :
        if (shape->rotationState ==0)
            return (grid[shape->position[0][1].rows+1][ shape->position[0][1].column]>0 || grid[shape->position[0][2].rows+1][ shape->position[0][2].column]>0  || grid[shape->position[0][3].rows+1][ shape->position[0][3].column]>0)?false : true ;
        if(shape->rotationState==1)
            return (grid[shape->position[1][2].rows+1][ shape->position[1][2].column]>0 || grid[shape->position[1][3].rows+1][ shape->position[1][3].column]>0) ? false : true ;
        if(shape->rotationState==2)
            return (grid[shape->position[2][0].rows+1][ shape->position[2][0].column]>0 || grid[shape->position[2][2].rows+1][ shape->position[2][2].column]>0 || grid[shape->position[2][3].rows+1][ shape->position[2][3].column]>0) ? false :true;
        if(shape->rotationState==3)
            return (grid[shape->position[3][0].rows+1][ shape->position[3][0].column]>0 || grid[shape->position[3][3].rows+1][ shape->position[3][3].column]>0) ? false :true;
            break;
    case 2 :
        return (grid[shape->position[0][2].rows+1][ shape->position[0][2].column]>0 || grid[shape->position[0][3].rows+1][ shape->position[0][3].column]>0) ? false : true ;        
        break;
    case 3:
        if(shape->rotationState==0)
        return (grid[shape->position[0][0].rows+1][ shape->position[0][0].column]>0 || grid[shape->position[0][1].rows+1][ shape->position[0][1].column]>0 || grid[shape->position[0][2].rows+1][ shape->position[0][2].column]>0) ? false :true;        
        if(shape->rotationState==1)
        return (grid[shape->position[1][2].rows+1][ shape->position[1][2].column]>0 || grid[shape->position[1][3].rows+1][ shape->position[1][3].column]>0 ) ? false :true;        
        if(shape->rotationState==2)
        return (grid[shape->position[2][1].rows+1][ shape->position[2][1].column]>0 || grid[shape->position[2][2].rows+1][ shape->position[2][2].column]>0 || grid[shape->position[2][3].rows+1][ shape->position[2][3].column]>0) ? false :true;        
        if(shape->rotationState==3)
        return (grid[shape->position[3][0].rows+1][ shape->position[3][0].column]>0 || grid[shape->position[3][3].rows+1][ shape->position[3][3].column]>0 ) ? false :true;        
                
        break;
    case 4:
        if(shape->rotationState==0)
        return (grid[shape->position[0][1].rows+1][ shape->position[0][1].column]>0 || grid[shape->position[0][3].rows+1][ shape->position[0][3].column]>0 || grid[shape->position[0][0].rows+1][shape->position[0][0].column] >0) ? false :true;
        if(shape->rotationState==1)
        return (grid[shape->position[1][1].rows+1][ shape->position[1][1].column]>0 || grid[shape->position[1][3].rows+1][ shape->position[1][3].column]>0 ) ? false :true;

        break;
    case 5 :
        if(shape->rotationState==0)
        return (grid[shape->position[0][0].rows+1][ shape->position[0][0].column]>0 || grid[shape->position[0][1].rows+1][ shape->position[0][1].column]>0 || grid[shape->position[0][3].rows+1][shape->position[0][3].column] >0) ? false :true;
        if(shape->rotationState==1)
        return (grid[shape->position[1][0].rows+1][ shape->position[1][0].column]>0 || grid[shape->position[1][2].rows+1][ shape->position[1][2].column]>0 ) ? false :true;

        break;
    case 6:
        if(shape->rotationState==0)
        return (grid[shape->position[0][0].rows+1][ shape->position[0][0].column]>0 || grid[shape->position[0][2].rows+1][ shape->position[0][2].column]>0 || grid[shape->position[0][3].rows+1][ shape->position[0][3].column]>0) ? false :true;        
        if(shape->rotationState==1)
        return (grid[shape->position[1][2].rows+1][ shape->position[1][2].column]>0 || grid[shape->position[1][3].rows+1][ shape->position[1][3].column]>0 ) ? false :true;        
        if(shape->rotationState==2)
        return (grid[shape->position[2][0].rows+1][ shape->position[2][0].column]>0 || grid[shape->position[2][1].rows+1][ shape->position[2][1].column]>0 || grid[shape->position[2][2].rows+1][ shape->position[2][2].column]>0) ? false :true;        
        if(shape->rotationState==3)
        return (grid[shape->position[3][2].rows+1][ shape->position[3][2].column]>0 || grid[shape->position[3][3].rows+1][ shape->position[3][3].column]>0 ) ? false :true;        

        break;               
    default:
    break;
 }   
}
void setiGrid(Shape shape,int *iGrid )
{
    switch (shape.id)
    {
    case 0:
        *iGrid= (shape.rotationState==0) ? shape.position[0][3].rows : shape.position[1][3].rows;
        break;
    case 1 : 
        if (shape.rotationState==0)
        *iGrid= shape.position[0][3].rows;
        if (shape.rotationState==1)
        *iGrid= shape.position[1][3].rows;
        if (shape.rotationState==2)
        *iGrid= shape.position[2][0].rows;
        if (shape.rotationState==3)
        *iGrid= shape.position[3][3].rows;
        break;
    case 2:
        if (shape.rotationState==0)
        *iGrid=shape.position[0][3].rows;
        break;
    case 3:
        if(shape.rotationState==0)
        *iGrid=shape.position[0][0].rows;        
        if(shape.rotationState==1)
        *iGrid=shape.position[1][3].rows;        
        if(shape.rotationState==2)
        *iGrid=shape.position[2][3].rows;        
        if(shape.rotationState==3)
        *iGrid=shape.position[3][3].rows;        
        break; 
    case 4:
        if(shape.rotationState==0)
        *iGrid=shape.position[0][1].rows;           
        if(shape.rotationState==1)
        {
            *iGrid=shape.position[1][3].rows;
        }

        break; 
    case 5:
        if(shape.rotationState==0)
        *iGrid=shape.position[0][1].rows;                  
        if(shape.rotationState==1)
        *iGrid=shape.position[1][0].rows; 
        break;
    case 6:
        if(shape.rotationState==0)
        *iGrid=shape.position[0][3].rows;        
        if(shape.rotationState==1)
        *iGrid=shape.position[1][2].rows;        
        if(shape.rotationState==2)
        *iGrid=shape.position[2][0].rows;        
        if(shape.rotationState==3)
        *iGrid=shape.position[3][2].rows;        
        break;                         
    default:
        *iGrid=55;
        break;
    }
}
void moveShapeVertically(Shape *shape , int grid[row][col] ,  Position arrPositionLastRow[4])
{
    int i= shape->rotationState, iGrid;

    setiGrid(*shape , &iGrid );

    if (iGrid  < row -1 && isThereaBlockbelow(shape,grid , arrPositionLastRow)  ) 
    {
        //printf("valid %d\n", iGrid);
        shape->move = true ;
        for (int k =0 ; k <4 ; k++)
        shape->position[i][k].rows++ ;      
    } else 
    {
        shape->move = false ;

    }
}

bool isThereABlockOnRight(Shape *shape , int grid[row][col])
{
    switch (shape->id)
    {
    case 0:
        if(shape->rotationState==0)
        return (grid[shape->position[0][0].rows][shape->position[0][0].column+1]>0 ||grid[shape->position[0][1].rows][shape->position[0][1].column+1]>0 || grid[shape->position[0][2].rows][shape->position[0][2].column+1]>0 || grid[shape->position[0][3].rows][shape->position[0][3].column+1]>0) ? false:true;
        if(shape->rotationState==1)
        return (grid[shape->position[1][3].rows][shape->position[1][3].column+1]>0 ) ? false:true;

        break;
    case 1:
        if(shape->rotationState==0)
        return (grid[shape->position[0][0].rows][shape->position[0][0].column+1]>0 ||grid[shape->position[0][3].rows][shape->position[0][3].column+1]>0 ) ? false:true;
        if(shape->rotationState==1)
        return (grid[shape->position[1][3].rows][shape->position[1][3].column+1]>0 ) ? false:true;
        if(shape->rotationState==2)
        return (grid[shape->position[2][3].rows][shape->position[2][3].column+1]>0 ) ? false:true;
        if(shape->rotationState==3)
        return (grid[shape->position[3][1].rows][shape->position[3][1].column+1]>0 || grid[shape->position[3][2].rows][shape->position[3][2].column+1]>0 || grid[shape->position[3][3].rows][shape->position[3][3].column+1]>0 ) ? false:true;

        break;    
    case 2:
        if(shape->rotationState==0)
        return (grid[shape->position[0][1].rows][shape->position[0][1].column+1]>0 ||grid[shape->position[0][3].rows][shape->position[0][3].column+1]>0 ) ? false:true;
        break;    
    case 3:
        if(shape->rotationState==0)
        return (grid[shape->position[0][0].rows][shape->position[0][0].column+1]>0 ||grid[shape->position[0][3].rows][shape->position[0][3].column+1]>0 ) ? false:true;
        if(shape->rotationState==1)
        return (grid[shape->position[1][0].rows][shape->position[1][0].column+1]>0 || grid[shape->position[1][1].rows][shape->position[1][1].column+1]>0 || grid[shape->position[1][2].rows][shape->position[1][2].column+1]>0 ) ? false:true;
        if(shape->rotationState==2)
        return (grid[shape->position[2][3].rows][shape->position[2][3].column+1]>0 ) ? false:true;
        if(shape->rotationState==3)
        return (grid[shape->position[3][0].rows][shape->position[3][0].column+1]>0 ) ? false:true;
        break;
    case 4:
        if(shape->rotationState==0)
        return (grid[shape->position[0][3].rows][shape->position[0][3].column+1]>0 ) ? false:true;
        if(shape->rotationState==1)
        return (grid[shape->position[1][2].rows][shape->position[1][2].column+1]>0 ||grid[shape->position[1][3].rows][shape->position[1][3].column+1]>0 ) ? false:true;
        break;
    case 5:
        if(shape->rotationState==0)
        return (grid[shape->position[0][3].rows][shape->position[0][3].column+1]>0 ) ? false:true;
        if(shape->rotationState==1)
        return (grid[shape->position[1][2].rows][shape->position[1][2].column+1]>0 ||grid[shape->position[1][3].rows][shape->position[1][3].column+1]>0 ) ? false:true;
        break;
    case 6:
        if(shape->rotationState==0)
        return (grid[shape->position[0][2].rows][shape->position[0][2].column+1]>0) ? false:true;
        if(shape->rotationState==1)
        return (grid[shape->position[1][0].rows][shape->position[1][0].column+1]>0 || grid[shape->position[1][1].rows][shape->position[1][1].column+1]>0 || grid[shape->position[1][2].rows][shape->position[1][2].column+1]>0 ) ? false:true;
        if(shape->rotationState==2)
        return (grid[shape->position[2][2].rows][shape->position[2][2].column+1]>0 ) ? false:true;
        if(shape->rotationState==3)
        return (grid[shape->position[3][3].rows][shape->position[3][3].column+1]>0 ) ? false:true;
        break;        
    default:
        break;
    }
}

void setjGrid(Shape shape,int *jGridRight , int *jGridLeft )
{
    switch (shape.id)
    {
    case 0:
        *jGridRight= (shape.rotationState==0) ? shape.position[0][0].column : shape.position[1][3].column;
        *jGridLeft= (shape.rotationState==0) ? shape.position[0][0].column : shape.position[1][0].column;

        break;
    case 1 : 
        if (shape.rotationState==0)
        {
            *jGridRight=  shape.position[0][3].column ;
            *jGridLeft=  shape.position[0][1].column ;
        }
        if (shape.rotationState==1)
        {
            *jGridRight=  shape.position[1][3].column ;
            *jGridLeft=  shape.position[1][0].column ;
        }
        if (shape.rotationState==2)
        {
            *jGridRight=  shape.position[2][3].column ;
            *jGridLeft=  shape.position[2][0].column ;
        }
        if (shape.rotationState==3)
        {
            *jGridRight=  shape.position[3][3].column ;
            *jGridLeft=  shape.position[3][0].column ;
        }
        break;
    case 2:
        if (shape.rotationState==0)
            *jGridRight=  shape.position[0][1].column ;
            *jGridLeft=  shape.position[0][0].column ;            
        break;
    case 3:
        if(shape.rotationState==0)
        {
            *jGridRight=  shape.position[0][3].column ;
            *jGridLeft=  shape.position[0][1].column ;
        }        
        if(shape.rotationState==1)
        {
            *jGridRight=  shape.position[1][0].column ;
            *jGridLeft=  shape.position[1][3].column ;
        }        
        if(shape.rotationState==2)
        {
            *jGridRight=  shape.position[2][3].column ;
            *jGridLeft=  shape.position[2][0].column ;
        }        
        if(shape.rotationState==3)
        {
            *jGridRight=  shape.position[3][0].column ;
            *jGridLeft=  shape.position[3][1].column ;
        }        
        break; 
    case 4:
        if(shape.rotationState==0)
        {
            *jGridRight=  shape.position[0][3].column ;
            *jGridLeft=  shape.position[0][0].column ;
        }        
        if(shape.rotationState==1)
        {
            *jGridRight=  shape.position[1][3].column ;
            *jGridLeft=  shape.position[1][0].column ;
        }
        break; 
    case 5:
        if(shape.rotationState==0)
        {
            *jGridRight=  shape.position[0][3].column ;
            *jGridLeft=  shape.position[0][0].column ;
        }        
        if(shape.rotationState==1)
        {
            *jGridRight=  shape.position[1][3].column ;
            *jGridLeft=  shape.position[1][0].column ;
        }
        break;
    case 6:
        if(shape.rotationState==0)
        {
            *jGridRight=  shape.position[0][2].column ;
            *jGridLeft=  shape.position[0][0].column ;
        }        
        if(shape.rotationState==1)
        {
            *jGridRight=  shape.position[1][0].column ;
            *jGridLeft=  shape.position[1][3].column ;
        }
        if(shape.rotationState==2)
        {
            *jGridRight=  shape.position[2][2].column ;
            *jGridLeft=  shape.position[2][0].column ;
        }        
        if(shape.rotationState==3)
        {
            *jGridRight=  shape.position[3][3].column ;
            *jGridLeft=  shape.position[3][0].column ;
        }                
        break;                         
    default:
        *jGridRight=55;*jGridLeft=55;
        break;
    }
}
void moveShapeHorizantaly(Shape *shape , int grid[row][col] , Direction *direction)
{
    int i = shape->rotationState ,jGridRight , jGridLeft;
    setjGrid(*shape , &jGridRight , &jGridLeft);
    if (direction->right && !direction->left && shape->move  && jGridRight < col -1 && isThereABlockOnRight(shape , grid))
    {
        for (int k =0 ; k <4 ; k++)
        shape->position[i][k].column++ ;  
    }

    if (!direction->right && direction->left && shape->move && jGridLeft>0 && isThereABlockOnLeft(shape, grid) )
    {
        for (int k =0 ; k <4 ; k++)
        shape->position[i][k].column-- ;  
    }
    direction->right = false ;
    direction->left = false ;
}

bool isThereABlockOnLeft(Shape *shape , int grid[row][col])
{
    switch (shape->id)
    {
    case 0:
        if(shape->rotationState==0)
        return (grid[shape->position[0][0].rows][shape->position[0][0].column-1]>0 ||grid[shape->position[0][1].rows][shape->position[0][1].column-1]>0 || grid[shape->position[0][2].rows][shape->position[0][2].column-1]>0 || grid[shape->position[0][3].rows][shape->position[0][3].column-1]>0) ? false:true;
        if(shape->rotationState==1)
        return (grid[shape->position[1][0].rows][shape->position[1][0].column-1]>0 ) ? false:true;

        break;
    case 1:
        if(shape->rotationState==0)
        return (grid[shape->position[0][1].rows][shape->position[0][1].column-1]>0 ) ? false:true;
        if(shape->rotationState==1)
        return (grid[shape->position[1][0].rows][shape->position[1][0].column-1]>0 || grid[shape->position[1][1].rows][shape->position[1][1].column-1]>0 || grid[shape->position[1][2].rows][shape->position[1][2].column-1]>0 ) ? false:true;
        if(shape->rotationState==2)
        return (grid[shape->position[2][0].rows][shape->position[2][0].column-1]>0 || grid[shape->position[2][1].rows][shape->position[2][1].column-1]>0 ) ? false:true;
        if(shape->rotationState==3)
        return (grid[shape->position[3][0].rows][shape->position[3][0].column-1]>0 ) ? false:true;

        break;    
    case 2:
        if(shape->rotationState==0)
        return (grid[shape->position[0][0].rows][shape->position[0][0].column-1]>0 ||grid[shape->position[0][2].rows][shape->position[0][2].column-1]>0 ) ? false:true;
        break;    
    case 3:
        if(shape->rotationState==0)
        return (grid[shape->position[0][1].rows][shape->position[0][1].column-1]>0 ) ? false:true;
        if(shape->rotationState==1)
        return (grid[shape->position[1][3].rows][shape->position[1][3].column-1]>0 ) ? false:true;
        if(shape->rotationState==2)
        return (grid[shape->position[2][0].rows][shape->position[2][0].column-1]>0 || grid[shape->position[2][1].rows][shape->position[2][1].column-1]>0 ) ? false:true;
        if(shape->rotationState==3)
        return (grid[shape->position[3][1].rows][shape->position[3][1].column-1]>0 || grid[shape->position[3][2].rows][shape->position[3][2].column-1]>0 || grid[shape->position[3][3].rows][shape->position[3][3].column-1]>0 ) ? false:true;
        break;
    case 4:
        if(shape->rotationState==0)
        return (grid[shape->position[0][0].rows][shape->position[0][0].column-1]>0 ) ? false:true;
        if(shape->rotationState==1)
        return (grid[shape->position[1][0].rows][shape->position[1][0].column-1]>0 ||grid[shape->position[1][1].rows][shape->position[1][1].column-1]>0 ) ? false:true;
        break;
    case 5:
        if(shape->rotationState==0)
        return (grid[shape->position[0][0].rows][shape->position[0][0].column-1]>0 ) ? false:true;
        if(shape->rotationState==1)
        return (grid[shape->position[1][0].rows][shape->position[1][0].column-1]>0 ||grid[shape->position[1][1].rows][shape->position[1][1].column-1]>0 ) ? false:true;
        break;
    case 6:
        if(shape->rotationState==0)
        return (grid[shape->position[0][0].rows][shape->position[0][0].column-1]>0) ? false:true;
        if(shape->rotationState==1)
        return (grid[shape->position[1][3].rows][shape->position[1][3].column-1]>0 ) ? false:true;
        if(shape->rotationState==2)
        return (grid[shape->position[2][0].rows][shape->position[2][0].column-1]>0 ) ? false:true;
        if(shape->rotationState==3)
        return (grid[shape->position[3][0].rows][shape->position[3][0].column-1]>0 || grid[shape->position[3][1].rows][shape->position[3][1].column-1]>0 || grid[shape->position[3][2].rows][shape->position[3][2].column-1]>0 ) ? false:true;
        break;        
    default:
        break;
    }
}