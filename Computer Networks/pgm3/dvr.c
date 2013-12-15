#include <stdio.h>

int size;

int main(){
    int l, k, neighb, update[10], router, ans = 1, j, i, dwn, choice, via[10];
    int mat[10][10];

    while(ans){ //As long as the users answer is yes

        // User Input
        printf("\nEnter size of matrix: ");
        scanf("%d", &size);
        printf("Enter the Router name: ");
        scanf("%d", &router);
        printf("Enter the number of  neighbour nodes: ");
        scanf("%d", &neighb);
        printf("Size = %d\n");
        printf("No. of neighbours = %d\n Router = %d", size, neighb, router);

        /********* Initialisation ***********/
        for(i = 1; i <= size; i++){
            mat[router][i] = 999; // Initialise mat[][] to infinity
            via[i] = 0; 
            /* Initialise via - no intermediate node b/w router and 
               other nodes, hence all via[] initialised to 0 */
        }
        //Distance of from a router to itself is zero
        mat[router][router] = 0;


        /********* Receiving updates ********/
        k = 1;  // To index update. Update from kth neighbour

        printf("\nEnter available table entries of neighbours:\n");
        //For each neighbour
        for(i = 1; i <= neighb; i++){
            // Identifying router providing the update using update[]
            printf("Enter node neighbour no %d:  ",k);
            scanf("%d", &update[k]);

            //Update matrix
            printf("Enter table values for node %d ", update[k]);
            for(j = 1; j <= size; j++){
                printf("\n%d | ", j);
                scanf("%d", &mat[update[k]][j]);
            }

            //Enter distance from router to update[k]
            printf("Enter weight for %d (router) to %d (node neighbour) ->  ", router, update[k]);
            scanf("%d", &mat[router][update[k]]);
            k++;
        }
        k--;

        /******* Optimise distance matrix *********/
        for(i = 1; i <= size; i++){
            for(j = 1; j <= k; j++)
                if((mat[router][i]) > (mat[router][update[j]] + mat[update[j]][i])){
                    mat[router][i] = mat[router][update[j]] + mat[update[j]][i];
                    via[i] = update[j];
                }
        }
        //Printing distances from Router
        printf("Table for %d",router);
        for(i = 1; i <= size; i++){
            
            //This will make it look like this: node | router | Direct link
            printf("\n%d | %d | ", i, mat[router][i]); 
            if(i == router)
                printf("%c", '-');
            else  if(via[i] == 0)
                printf("Direct Link");
            else
                printf("%d", via[i]);
        }

        k = 1;

        /***** Take a router down and see the changes in the tables *****/
        printf("\nRouter UP/DOWN 1/0 ? : ");
        scanf("%d", &choice);
        if(choice == 0){
            //[doubt] what is make a router down?
            printf("\nEnter the router to make down: ");
            scanf("%d", &dwn);

            //Scans for dwn in via matrix and 
            for(l = 1; l <= size; l++)
                if(via[l] == dwn)
                    mat[router][l] = 999;
        }


        /**** Display ****/
        printf("Table for %d",router);
        //Displaying node and the distance from the node
        for(i = 1; i <= size; i++)
            printf("\n%d | %d", i, mat[router][i]);
        printf("\n");

        /*** Repeat again ***/
        printf("\nTake values for next exchange 1/0 ?");
        scanf("%d", &ans);

    }// end while
    return 0;
}
