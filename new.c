#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // Added for boolean type

#define MAX_NODES 100 // Adjust as needed

int number_of_nodes;
int adjacency_matrix[MAX_NODES][MAX_NODES];
bool visited[MAX_NODES];

int getFriendsCount(int user_id)
{
    int friend_count = 0;
    for (int i = 0; i < number_of_nodes; i++)
    {
        if (adjacency_matrix[user_id][i] == 1)
        {
            friend_count++;
        }
    }
    return friend_count;
}

void printFriendList(int user_id)
{
    int friend_count = getFriendsCount(user_id);
    printf("Your friends are: ");
    for (int i = 0; i < number_of_nodes; i++)
    {
        if (adjacency_matrix[user_id][i] == 1 && i != user_id) // Exclude user from their own friend list
        {
            printf("%d, ", i);
        }
    }
    printf("\n");
}

bool isVisited(int node)
{
    return visited[node];
}

void markVisited(int node)
{
    visited[node] = true;
}

void resetVisited()
{
    for (int i = 0; i < number_of_nodes; i++)
    {
        visited[i] = false;
    }
}

void getRecommendationsRecursive(int user_id, int *recommendations, int *current_size, bool *visited)
{
    visited[user_id] = true; // Mark current node as visited

    for (int i = 0; i < number_of_nodes; i++)
    {
        if (adjacency_matrix[user_id][i] == 1 && !visited[i])
        {
            recommendations[*current_size] = i;
            (*current_size)++;
            getRecommendationsRecursive(i, recommendations, current_size, visited);
            visited[i] = false; // Unmark for further exploration in this call
        }
    }
}

void getRecommendations(int user_id, int *recommendations)
{
    bool visited[MAX_NODES]; // Temporary visited array for this recommendation call
    resetVisited();          // Clear visited flags for main logic

    int current_size = 0;
    getRecommendationsRecursive(user_id, recommendations, &current_size, visited);
}

int main()
{
    printf("\t\t\t\t\t\t  Project Based Learning\n\n\n");
    printf("\t\t\t\t\t\t    Topic: Friend Suggestion\n\n\n");
    printf("\t\t\t\t\t\t\t WELCOME\n\n\n");

    printf("Enter total number of nodes (maximum %d): ", MAX_NODES);
    if (scanf("%d", &number_of_nodes) != 1 || number_of_nodes <= 0 || number_of_nodes > MAX_NODES)
    {
        fprintf(stderr, "Error: Invalid number of nodes.\n");
        return 1;
    }

    printf("Enter 1 if friend and 0 if not a friend.\n");
    for (int i = 0; i < number_of_nodes; i++)
    {
        for (int j = 0; j < number_of_nodes; j++)
        {
            printf("Is %d friend of %d : ", i, j);
            if (scanf("%d", &adjacency_matrix[i][j]) != 1 || (adjacency_matrix[i][j] != 0 && adjacency_matrix[i][j] != 1))
            {
                fprintf(stderr, "Error: Invalid input for friend connection.\n");
                return 1;
            }
        }
    }

    while (1)
    {
        printf("\nEnter operation to perform : ");
        printf("\n1. My friends.\n2. Recommend me friends\n3. Exit\n");
        int choice;
        if (scanf("%d", &choice) != 1)
        {
            fprintf(stderr, "Error: Invalid input for operation.\n");
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            int user_id; // Declaration moved here
            printf("Who are you : ");
            if (scanf("%d", &user_id) != 1 || user_id < 0 || user_id >= number_of_nodes)
            {
                fprintf(stderr, "Error: Invalid user ID.\n");
                continue;
            }
            printFriendList(user_id);
            break;
        }
        case 2:
        {
            int user_id; // Declaration moved here
            if (scanf("%d", &user_id) != 1 || user_id < 0 || user_id >= number_of_nodes)
            {
                fprintf(stderr, "Error: Invalid user ID.\n");
                continue;
            }

            int recommendations[MAX_NODES]; // Allocate enough space for all possible recommendations
            getRecommendations(user_id, recommendations);

            printf("\nRecommendations : ");
            for (int i = 0; i < number_of_nodes; i++)
            {
                if (recommendations[i] != user_id && recommendations[i] != -1) // Exclude the user and invalid recommendations
                {
                    printf("%d, ", recommendations[i]);
                }
            }
            printf("\n");
            break;
        }

        case 3:
            exit(0);

        default:
            printf("Enter valid option\n");
        }
    }

    printf("Edge List:\n");
    for (int i = 0; i < number_of_nodes; i++)
    {
        for (int j = i + 1; j < number_of_nodes; j++)
        {
            if (adjacency_matrix[i][j] == 1)
            {
                printf("%d -- %d\n", i, j);
            }
        }
    }
}
