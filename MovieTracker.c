#include <stdio.h>
#include <string.h>

/*
    Constants
    These make the program easier to maintain because
    we can change the sizes in one place.
*/
#define MAX_MOVIES 100
#define TITLE_SIZE 100
#define GENRE_SIZE 50
#define FILE_NAME "movies.txt"


/*
    Movie structure
    Stores all information associated with one movie.
*/
struct Movie
{
    char title[TITLE_SIZE];
    char genre[GENRE_SIZE];
    int downloads;
};


/*
    Function prototypes
    These tell the compiler about each function before
    the main function uses them.
*/
void addMovie(struct Movie movies[], int *movieCount);
void displayMovies(struct Movie movies[], int movieCount);
void searchMovie(struct Movie movies[], int movieCount);
void updateMovie(struct Movie movies[], int movieCount);
void deleteMovie(struct Movie movies[], int *movieCount);
void saveMovies(struct Movie movies[], int movieCount);
void loadMovies(struct Movie movies[], int *movieCount);

int getInteger(const char prompt[]);
void getString(const char prompt[], char string[], int size);
int confirmAction(const char prompt[]);


/*
    Main function

    Controls the menu and calls the appropriate
    function based on the user's choice.
*/
int main(void)
{
    struct Movie movies[MAX_MOVIES];

    int movieCount = 0;
    int choice = 0;

    /*
        Load previously saved movies when the
        program starts.
    */
    loadMovies(movies, &movieCount);

    /*
        Continue displaying the menu until
        the user chooses option 7.
    */
    while (choice != 7)
    {
        printf("\n====================================\n");
        printf("       MOVIE TRACKING SYSTEM\n");
        printf("====================================\n");
        printf("1. Add Movie\n");
        printf("2. Display Movies\n");
        printf("3. Search for Movie\n");
        printf("4. Update Movie\n");
        printf("5. Delete Movie\n");
        printf("6. Save Movies\n");
        printf("7. Exit\n");
        printf("====================================\n");

        /*
            Get and validate the user's menu choice.
        */
        choice = getInteger("Enter your choice: ");

        /*
            Add a new movie.
        */
        if (choice == 1)
        {
            addMovie(movies, &movieCount);
        }

        /*
            Display all movies.
        */
        else if (choice == 2)
        {
            displayMovies(movies, movieCount);
        }

        /*
            Search for a movie.
        */
        else if (choice == 3)
        {
            searchMovie(movies, movieCount);
        }

        /*
            Update an existing movie.
        */
        else if (choice == 4)
        {
            updateMovie(movies, movieCount);
        }

        /*
            Delete an existing movie.
        */
        else if (choice == 5)
        {
            deleteMovie(movies, &movieCount);
        }

        /*
            Manually save the movies.
        */
        else if (choice == 6)
        {
            saveMovies(movies, movieCount);
        }

        /*
            Save automatically before exiting.
        */
        else if (choice == 7)
        {
            saveMovies(movies, movieCount);

            printf("\nThank you for using the Movie Tracking System.\n");
        }

        /*
            Handle invalid menu choices.
        */
        else
        {
            printf("\nInvalid choice.\n");
            printf("Please enter a number from 1 to 7.\n");
        }
    }

    return 0;
}


/*
    addMovie()

    Adds a new movie to the movie array.

    A pointer to movieCount is used because this
    function needs to change the number of movies.
*/
void addMovie(struct Movie movies[], int *movieCount)
{
    /*
        Check whether the array is full.
    */
    if (*movieCount >= MAX_MOVIES)
    {
        printf("\nThe movie list is full.\n");
        return;
    }

    printf("\n========== ADD MOVIE ==========\n");

    /*
        Get the movie title.
    */
    getString(
        "Enter movie title: ",
        movies[*movieCount].title,
        TITLE_SIZE
    );

    /*
        Get the movie genre.
    */
    getString(
        "Enter movie genre: ",
        movies[*movieCount].genre,
        GENRE_SIZE
    );

    /*
        Get the number of downloads.
    */
    movies[*movieCount].downloads =
        getInteger("Enter number of downloads: ");

    /*
        Increase movieCount because a new movie
        has been added.
    */
    (*movieCount)++;

    printf("\nMovie added successfully!\n");
}


/*
    displayMovies()

    Displays every movie currently stored
    in the array.
*/
void displayMovies(struct Movie movies[], int movieCount)
{
    int i = 0;

    /*
        Check whether the movie list is empty.
    */
    if (movieCount == 0)
    {
        printf("\nThere are no movies to display.\n");
        return;
    }

    printf("\n================ MOVIE LIST ================\n");

    /*
        Use a while loop to display each movie.
    */
    while (i < movieCount)
    {
        printf("\nMovie #%d\n", i + 1);
        printf("---------------------------------------------\n");
        printf("Title:      %s\n", movies[i].title);
        printf("Genre:      %s\n", movies[i].genre);
        printf("Downloads:  %d\n", movies[i].downloads);

        i++;
    }

    printf("\n=============================================\n");
    printf("Total Movies: %d\n", movieCount);
}


/*
    searchMovie()

    Searches for a movie using its title.
*/
void searchMovie(struct Movie movies[], int movieCount)
{
    char searchTitle[TITLE_SIZE];

    int i = 0;
    int found = 0;

    /*
        There is nothing to search if the list is empty.
    */
    if (movieCount == 0)
    {
        printf("\nThere are no movies to search.\n");
        return;
    }

    printf("\n========== SEARCH MOVIE ==========\n");

    /*
        Get the title the user wants to search for.
    */
    getString(
        "Enter movie title to search: ",
        searchTitle,
        TITLE_SIZE
    );

    /*
        Search until the movie is found or all
        movies have been checked.
    */
    while (i < movieCount && found == 0)
    {
        /*
            strcmp() returns 0 when both strings
            are exactly the same.
        */
        if (strcmp(movies[i].title, searchTitle) == 0)
        {
            printf("\nMovie found!\n");
            printf("--------------------------------\n");
            printf("Title:      %s\n", movies[i].title);
            printf("Genre:      %s\n", movies[i].genre);
            printf("Downloads:  %d\n", movies[i].downloads);

            /*
                Set found to 1 so the while loop
                will stop on its next condition check.
            */
            found = 1;
        }

        i++;
    }

    /*
        Display a message if the movie was not found.
    */
    if (found == 0)
    {
        printf("\nMovie not found.\n");
    }
}


/*
    updateMovie()

    Searches for a movie by title and allows the
    user to change its genre and download count.
*/
void updateMovie(struct Movie movies[], int movieCount)
{
    char searchTitle[TITLE_SIZE];

    int i = 0;
    int found = 0;

    /*
        Make sure there are movies available to update.
    */
    if (movieCount == 0)
    {
        printf("\nThere are no movies to update.\n");
        return;
    }

    printf("\n========== UPDATE MOVIE ==========\n");

    /*
        Get the title of the movie to update.
    */
    getString(
        "Enter movie title to update: ",
        searchTitle,
        TITLE_SIZE
    );

    /*
        Search through the movie array.
    */
    while (i < movieCount && found == 0)
    {
        if (strcmp(movies[i].title, searchTitle) == 0)
        {
            printf("\nMovie found!\n");

            /*
                Display the current genre.
            */
            printf("Current genre: %s\n", movies[i].genre);

            /*
                Replace the current genre.
            */
            getString(
                "Enter new genre: ",
                movies[i].genre,
                GENRE_SIZE
            );

            /*
                Replace the current download count.
            */
            movies[i].downloads =
                getInteger("Enter new number of downloads: ");

            found = 1;

            printf("\nMovie updated successfully!\n");
        }

        i++;
    }

    /*
        Display a message if the movie was not found.
    */
    if (found == 0)
    {
        printf("\nMovie not found.\n");
    }
}


/*
    deleteMovie()

    Deletes a movie from the array.

    After finding the movie, every movie after it
    is shifted one position to the left.
*/
void deleteMovie(struct Movie movies[], int *movieCount)
{
    char searchTitle[TITLE_SIZE];

    int i = 0;
    int j = 0;
    int found = 0;
    int confirmed = 0;

    /*
        Make sure there is a movie to delete.
    */
    if (*movieCount == 0)
    {
        printf("\nThere are no movies to delete.\n");
        return;
    }

    printf("\n========== DELETE MOVIE ==========\n");

    /*
        Get the title of the movie to delete.
    */
    getString(
        "Enter movie title to delete: ",
        searchTitle,
        TITLE_SIZE
    );

    /*
        Search through the movie array.
    */
    while (i < *movieCount && found == 0)
    {
        if (strcmp(movies[i].title, searchTitle) == 0)
        {
            printf("\nMovie found: %s\n", movies[i].title);

            /*
                Ask the user to confirm the deletion.
            */
            confirmed = confirmAction(
                "Are you sure you want to delete it? (y/n): "
            );

            if (confirmed == 1)
            {
                /*
                    Start at the position of the movie
                    that is being deleted.
                */
                j = i;

                /*
                    Shift every movie after the deleted
                    movie one position to the left.
                */
                while (j < *movieCount - 1)
                {
                    movies[j] = movies[j + 1];

                    j++;
                }

                /*
                    Reduce the movie count because
                    one movie was removed.
                */
                (*movieCount)--;

                printf("\nMovie deleted successfully!\n");
            }
            else
            {
                printf("\nDelete cancelled.\n");
            }

            /*
                The movie has been found, so set the
                flag to stop the search loop.
            */
            found = 1;
        }

        i++;
    }

    /*
        Display a message if the movie was not found.
    */
    if (found == 0)
    {
        printf("\nMovie not found.\n");
    }
}


/*
    saveMovies()

    Saves all movies to movies.txt.

    File format:

    title|genre|downloads
*/
void saveMovies(struct Movie movies[], int movieCount)
{
    FILE *file;

    int i = 0;

    /*
        Open the file in write mode.

        "w" creates the file if it does not exist.
        If the file already exists, its contents are
        replaced with the current movie information.
    */
    file = fopen(FILE_NAME, "w");

    /*
        Check whether the file opened successfully.
    */
    if (file == NULL)
    {
        printf("\nError: Could not open the movie file.\n");
        return;
    }

    /*
        Write each movie to the file.
    */
    while (i < movieCount)
    {
        fprintf(
            file,
            "%s|%s|%d\n",
            movies[i].title,
            movies[i].genre,
            movies[i].downloads
        );

        i++;
    }

    /*
        Close the file after writing.
    */
    fclose(file);

    printf("\nMovies saved successfully.\n");
}


/*
    loadMovies()

    Loads movies from movies.txt when the program starts.

    If the file does not exist, the program starts
    with an empty movie list.
*/
void loadMovies(struct Movie movies[], int *movieCount)
{
    FILE *file;

    /*
        Open the file in read mode.
    */
    file = fopen(FILE_NAME, "r");

    /*
        If the file does not exist, this is treated
        as the first time the program is being run.
    */
    if (file == NULL)
    {
        printf("\nNo saved movie file found. Starting fresh.\n");
        return;
    }

    /*
        Read movies from the file until:
        1. The array is full, or
        2. A complete movie cannot be read.
    */
    while (
        *movieCount < MAX_MOVIES &&
        fscanf(
            file,
            " %99[^|]|%49[^|]|%d",
            movies[*movieCount].title,
            movies[*movieCount].genre,
            &movies[*movieCount].downloads
        ) == 3
    )
    {
        /*
            Increase movieCount after successfully
            reading one complete movie.
        */
        (*movieCount)++;
    }

    /*
        Close the file after loading the data.
    */
    fclose(file);

    printf(
        "\n%d movie(s) loaded from file.\n",
        *movieCount
    );
}


/*
    getInteger()

    Gets a valid integer from the user.

    This function rejects input such as:

        25abc
        abc25
        12.5

    Valid examples:

        25
        0
        -10
*/
int getInteger(const char prompt[])
{
    char input[100];

    int value = 0;
    int valid = 0;
    char extra = '\0';

    /*
        Continue asking until valid integer input
        is entered.
    */
    while (valid == 0)
    {
        printf("%s", prompt);

        /*
            Read the entire line of input.
        */
        if (fgets(input, sizeof(input), stdin) != NULL)
        {
            /*
                %d reads the integer.

                %c attempts to read any additional
                non-whitespace character.

                If only the integer is present,
                sscanf() returns 1.

                If something like "25abc" is entered,
                sscanf() returns 2 because %c reads 'a'.
            */
            if (sscanf(input, " %d %c", &value, &extra) == 1)
            {
                valid = 1;
            }
            else
            {
                printf(
                    "Invalid input. Please enter a whole number.\n"
                );
            }
        }
        else
        {
            printf(
                "Unable to read input. Please try again.\n"
            );
        }
    }

    return value;
}


/*
    getString()

    Gets a non-empty string from the user.

    fgets() is used instead of scanf() so that
    spaces can be included in movie titles and genres.
*/
void getString(
    const char prompt[],
    char string[],
    int size
)
{
    int valid = 0;

    /*
        Continue asking until the user enters
        a non-empty string.
    */
    while (valid == 0)
    {
        printf("%s", prompt);

        /*
            Read the user's entire line of input.
        */
        if (fgets(string, size, stdin) != NULL)
        {
            /*
                Remove the newline character that
                fgets() normally stores at the end.
            */
            string[strcspn(string, "\n")] = '\0';

            /*
                Make sure the user entered something.
            */
            if (strlen(string) > 0)
            {
                valid = 1;
            }
            else
            {
                printf(
                    "Input cannot be empty. Please try again.\n"
                );
            }
        }
        else
        {
            printf(
                "Unable to read input. Please try again.\n"
            );
        }
    }
}


/*
    confirmAction()

    Asks the user for a yes/no response.

    Returns:

        1 = Yes
        0 = No
*/
int confirmAction(const char prompt[])
{
    char input[20];

    int valid = 0;
    int confirmed = 0;

    /*
        Continue asking until the user enters
        either Y or N.
    */
    while (valid == 0)
    {
        printf("%s", prompt);

        /*
            Read the user's response.
        */
        if (fgets(input, sizeof(input), stdin) != NULL)
        {
            /*
                Accept uppercase or lowercase Y.
            */
            if (input[0] == 'y' || input[0] == 'Y')
            {
                confirmed = 1;
                valid = 1;
            }

            /*
                Accept uppercase or lowercase N.
            */
            else if (input[0] == 'n' || input[0] == 'N')
            {
                confirmed = 0;
                valid = 1;
            }

            /*
                Reject anything other than Y or N.
            */
            else
            {
                printf("Please enter y or n.\n");
            }
        }
        else
        {
            printf(
                "Unable to read input. Please try again.\n"
            );
        }
    }

    return confirmed;
}
