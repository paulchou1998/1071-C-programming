#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Date
{
    int year;
    int month;
    int day;
};

/* self-referential structure */
struct ListNode
{
    int id;             // lotto id
    Date date;   // opening date
    int num[6];         // winning numbers
    ListNode *nextPtr; /* pointer to next node*/
}; /* end structure listNode */

//typedef struct listNode ListNode; /* synonym for struct listNode */
typedef ListNode *ListNodePtr; /* synonym for ListNode* */

/* display program instructions to user */
void instructions( void )
{
    printf( "Enter your choice:\n"
            "   1 to insert an element into the list.\n"
            "   2 to delete an element from the list.\n"
            "   3 to end.\n" );
} /* end function instructions */

/* Insert a new value into the list in sorted order */
void insert( ListNode **sPtr, int id, int year, int month, int day )
{
    ListNodePtr newPtr; /* pointer to new node */
    ListNodePtr previousPtr; /* pointer to previous node in list */
    ListNodePtr currentPtr; /* pointer to current node in list */

    newPtr = (ListNode *) malloc( sizeof( ListNode ) ); /* create node */

    if ( newPtr != NULL )   /* is space available */
    {
        newPtr->id = id; /* place value in node */
        newPtr->date.year = year; /* place value in node */
        newPtr->date.month= month; /* place value in node */
        newPtr->date.day = day; /* place value in node */
        srand(time(NULL));
            for(int i=0; i<6; i++)
            {
                newPtr->num[i] = rand()%49+1;
            }
        newPtr->nextPtr = NULL; /* node does not link to another node */

        previousPtr = NULL;
        currentPtr = *sPtr;

        /* loop to find the correct location in the list */
        while ( currentPtr != NULL && id > currentPtr->id )
        {
            previousPtr = currentPtr; /* walk to ...   */
            currentPtr = currentPtr->nextPtr; /* ... next node */
        } /* end while */

        /* insert new node at beginning of list */
        if ( previousPtr == NULL )
        {
            newPtr->nextPtr = *sPtr;
            *sPtr = newPtr;
        } /* end if */
        else   /* insert new node between previousPtr and currentPtr */
        {
            previousPtr->nextPtr = newPtr;
            newPtr->nextPtr = currentPtr;
        } /* end else */
    } /* end if */
    else
    {
        printf( "%c not inserted. No memory available.\n", id );
    } /* end else */
} /* end function insert */

/* Delete a list element */
int del( ListNodePtr *sPtr, int value )
{
    ListNodePtr previousPtr; /* pointer to previous node in list */
    ListNodePtr currentPtr; /* pointer to current node in list */
    ListNodePtr tempPtr; /* temporary node pointer */

    /* delete first node */
    if ( value == ( *sPtr )->id )
    {
        tempPtr = *sPtr; /* hold onto node being removed */
        *sPtr = ( *sPtr )->nextPtr; /* de-thread the node */
        free( tempPtr ); /* free the de-threaded node */
        return value;
    } /* end if */
    else
    {
        previousPtr = *sPtr;
        currentPtr = ( *sPtr )->nextPtr;

        /* loop to find the correct location in the list */
        while ( currentPtr != NULL && currentPtr->id != value )
        {
            previousPtr = currentPtr; /* walk to ...   */
            currentPtr = currentPtr->nextPtr; /* ... next node */
        } /* end while */

        /* delete node at currentPtr */
        if ( currentPtr != NULL )
        {
            tempPtr = currentPtr;
            previousPtr->nextPtr = currentPtr->nextPtr;
            free( tempPtr );
            return value;
        } /* end if */
    } /* end else */

    return '\0';
} /* end function delete */

/* Return 1 if the list is empty, 0 otherwise */
int isEmpty( ListNodePtr sPtr )
{
    return sPtr == NULL;
} /* end function isEmpty */

/* Print the list */
void printList( ListNodePtr currentPtr )
{
    /* if list is empty */
    if ( currentPtr == NULL )
    {
        printf( "List is empty.\n\n" );
    } /* end if */
    else
    {
        printf( "The list is:\n\n" );

        /* while not the end of the list */
        while ( currentPtr != NULL )
        {
            printf( "Lotto ID: %d\n", currentPtr->id );
            printf("   Date: %d/%02d/%02d\n",currentPtr->date.year,currentPtr->date.month,currentPtr->date.day);
            printf("   Six winning numbers: ");
            for(int i=0; i<6; i++)
            {
                printf("%02d ", currentPtr->num[i]);
            }
            printf("\n\n");
            currentPtr = currentPtr->nextPtr;
        } /* end while */

        printf( "NULL\n\n" );
    } /* end else */
} /* end function printList */



int main( void )
{
    ListNodePtr startPtr = NULL; /* initially there are no nodes */
    int choice; /* user's choice */
    ListNode listnode;

    instructions(); /* display the menu */
    printf( "? " );
    scanf( "%d", &choice );

    /* loop while user does not choose 3 */
    while ( choice != 3 )
    {

        switch ( choice )
        {
        case 1:
            printf( "Enter ID: ");
            scanf( "%d", &listnode.id );
            printf( "Enter the year: ");
            scanf( "%d", &listnode.date.year );
            printf( "Enter the month: ");
            scanf( "%d", &listnode.date.month );
            printf( "Enter the day: ");
            scanf( "%d", &listnode.date.day );
            printf("Random generating 6 lotto numbers ...");

            printf("\n");
            insert( &startPtr, listnode.id, listnode.date.year, listnode.date.month, listnode.date.day);  /* insert item in list */
            printList( startPtr );
            break;
        case 2:
            /* if list is not empty */
            if ( !isEmpty( startPtr ) )
            {
                printf( "Enter ID to be deleted: " );
                scanf( "\n%d", &listnode.id );

                /* if character is found, remove it */
                if ( del( &startPtr, listnode.id ) )   /* remove item */
                {
                    printf( "%c deleted.\n", listnode.id );
                    printList( startPtr );
                } /* end if */
                else
                {
                    printf( "%c not found.\n\n", listnode.id );
                } /* end else */
            } /* end if */
            else
            {
                printf( "List is empty.\n\n" );
            } /* end else */

            break;
        default:
            printf( "Invalid choice.\n\n" );
            instructions();
            break;
        } /* end switch */

        printf( "? " );
        scanf( "%d", &choice );
    } /* end while */

    printf( "End of run.\n" );
    return 0; /* indicates successful termination */
} /* end main */
