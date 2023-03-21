#include "queue.h"
#include "dll.h"
#include "music_player.h"
#include <stdio.h>
#include <stdlib.h>

playlist_t* create_playlist() // return a newly created doubly linked list
{
	// DO NOT MODIFY!!!
	playlist_t* playlist = (playlist_t*)malloc(sizeof(playlist_t));
	playlist->list = create_list();
	playlist->num_songs = 0;
	playlist->last_song = NULL;
	return playlist;
}

void delete_playlist(playlist_t* playlist) // delete the playlist
{
	// DO NOT MODIFY!!!
	delete_list(playlist->list);
	free(playlist);
}

music_queue_t* create_music_queue() // return a newly created queue
{
	// DO NOT MODIFY!!!
	return create_queue();
}

void clear_music_queue(music_queue_t* q) // clear the queue q
{	
	// DO NOT MODIFY!!!
	delete_queue(q);
}

void add_song(playlist_t* playlist, int song_id, int where) // TODO: add a song id to the end of the playlist
{
    struct node*temp=(struct node*)malloc(sizeof(struct node));
    temp->data=song_id;
    if (playlist->list->head==NULL)
    {
        playlist->list->head=temp;
        playlist->list->tail=temp;
        temp->prev=NULL;
        temp->next=NULL;
    }
    else if (where==-1)
    {
        temp->next=playlist->list->head;
        if (playlist->list->head!=NULL)
        playlist->list->head->prev=temp;
        temp->prev=NULL;
        playlist->list->head=temp;
    }
    else if (where==-2)
    {
        temp->prev=playlist->list->tail;
        if (playlist->list->tail!=NULL)
        playlist->list->tail->next=temp;
        playlist->list->tail=temp;
        temp->next=NULL;
    }
    else 
    {
        struct node*present=playlist->list->head;
        while(present!=NULL && present->data!=where)
        {
            present=present->next;
        }
        if (present==NULL);
        else
        {
            temp->next=present->next;
            temp->prev=present;
            present->next=temp;
            if (temp->next!=NULL)
            temp->next->prev=temp;
            else {
                playlist->list->tail=temp;
            }
        }
    }
    playlist->num_songs++;
    playlist->list->size++;
}

void delete_song(playlist_t* playlist, int song_id) // TODO: remove song id from the playlist
{
    struct node*present=playlist->list->head;
    while (present!=NULL && present->data!=song_id)
    {
        present=present->next;
    }
    if (present==NULL);
	else
	{
		if (present->prev!=NULL)
		{
			present->prev->next=present->next;
		}
		else {
			playlist->list->head=present->next;
		}
		if (present->next!=NULL)
		{
			present->next->prev=present->prev;
		}
		else{
			playlist->list->tail=present->prev;
		}
        playlist->num_songs--;
        playlist->list->size--;
	}
    if (playlist->last_song==NULL);
    else
    {
        if (playlist->last_song->data==song_id)
        playlist->last_song=NULL;
        else;
    }
}

song_t* search_song(playlist_t* playlist, int song_id) // TODO: return a pointer to the node where the song id is present in the playlist
{
    struct node*present=playlist->list->head;
    while (present!=NULL && present->data!=song_id)
    {
        present=present->next;
    }
    if (present==NULL);
    else{
        return present;
    }
}

void search_and_play(playlist_t* playlist, int song_id) // TODO: play the song with given song_id from the list(no need to bother about the queue. Call to this function should always play the given song and further calls to play_next and play_previous)
{
    struct node*present=playlist->list->head;
    while (present!=NULL && present->data!=song_id)
    {
        present=present->next;
    }
    if (present==NULL);
    else {
        play_song(song_id);
        playlist->last_song=present;
    }
}

void play_next(playlist_t* playlist, music_queue_t* q) // TODO: play the next song in the linked list if the queue is empty. If the queue if not empty, play from the queue
{
    if (q->front==NULL)
    {
        if (playlist->list->head!=NULL){
        if (playlist->last_song!=NULL){
        playlist->last_song=playlist->last_song->next;
        if (playlist->last_song==NULL)
        {
            playlist->last_song=playlist->list->head;
            play_song(playlist->last_song->data);
        }
        else 
        {
            play_song(playlist->last_song->data);
        }}
        else 
        {
            play_song(playlist->list->head->data);
            playlist->last_song=playlist->list->head;
        }
        }
        else;
    }
    else 
    {
        play_song(q->front->data);
        q->front=q->front->next;
        q->list->head=q->front;
        q->size--;
        q->list->size--;
    }

}

void play_previous(playlist_t* playlist) // TODO: play the previous song from the linked list
{   if (playlist->list->head!=NULL){
    if (playlist->last_song!=NULL)
    {
        if (playlist->last_song->prev!=NULL)
        {
            playlist->last_song=playlist->last_song->prev;
            play_song(playlist->last_song->data);
        }
        else 
        {
            playlist->last_song=playlist->list->tail;
            play_song(playlist->last_song->data);
        }     
        }
        else {
            playlist->last_song=playlist->list->tail;
            play_song(playlist->last_song->data);
        }
    }
    else;

}

void play_from_queue(music_queue_t* q) // TODO: play a song from the queue
{
    if (q->front==NULL);
    else {
        play_song(q->front->data);
        q->front=q->front->next;
        q->size--;
    }
}

void insert_to_queue(music_queue_t* q, int song_id) // TODO: insert a song id to the queue
{
     if (q->front==NULL)
     {
        q->rear=(struct node*)malloc(sizeof(struct node));
        q->rear->data=song_id;
        q->front=q->rear;
        q->size++;
     }
     else {
        q->rear->next=(struct node*)malloc(sizeof(struct node));
        q->rear=q->rear->next;
        q->rear->next=NULL;
        q->rear->data=song_id;
        q->size++;
     }
}

void reverse(playlist_t* playlist) // TODO: reverse the order of the songs in the given playlist. (Swap the nodes, not data)
{
    if (playlist->list->head!=NULL){
    struct node*present=playlist->list->head;
    struct node*temp;
    while (present!=NULL)
    {
        temp=present->next;
        present->next=present->prev;
        present->prev=temp;
        present=present->prev;
    }
    temp=playlist->list->tail;
    playlist->list->tail=playlist->list->head;
    playlist->list->head=temp;}
    else;
}

void k_swap(playlist_t* playlist, int k) // TODO: swap the node at position i with node at position i+k upto the point where i+k is less than the size of the linked list
{
    int i=0;
    int j=i;cvop
    int l;
    int n=playlist->num_songs;
    struct node*present=playlist->list->head;
    struct node*temp=present;
    struct node*g;
    struct node*e;
    struct node*f;
    while (i+k<n){
    while (temp!=NULL && j<i+k)
    {
       temp=temp->next;
       j++;
    }
    if (temp==NULL)
    break;
    e=temp->next;
    f=present->prev;
    if (present->next!=temp)
    temp->next=present->next;
    else 
    temp->next=present;
    if (temp->prev!=present)
    present->prev=temp->prev;
    else
    present->prev=temp;
    present->next=e;
    temp->prev=f;
    if (temp->prev!=NULL)
    temp->prev->next=temp;
    else
    playlist->list->head=temp;
    if (temp->next!=NULL)
    temp->next->prev=temp;
    else
    playlist->list->tail=temp;
    if (present->prev!=NULL)
    present->prev->next=present;
    else
    playlist->list->head=present;
    if (present->next!=NULL)
    present->next->prev=present;
    else
    playlist->list->tail=present;

    i++;
    j=i;
    temp=temp->next;
    present=temp;
    temp=present;
    }
    
}

void shuffle(playlist_t* playlist, int k) // TODO: perform k_swap and reverse
{
    k_swap(playlist,k);
    reverse(playlist);
}

song_t* debug(playlist_t* playlist) // TODO: if the given linked list has a cycle, return the start of the cycle, else return null. Check cycles only in forward direction i.e with the next pointer. No need to check for cycles in the backward pointer.
{
    struct node*present=playlist->list->head;
    struct node*temp=present;
    while (present!=NULL && present->next!=NULL)
    {
        present=present->next->next;
        temp=temp->next;
        if (present==temp)
        break;
    }
    if (present==NULL || present->next==NULL)
    {
        return NULL;
    }
    else 
    {
        temp=playlist->list->head;
        while (temp!=present)
        {
            temp=temp->next;
            present=present->next;
        }
        return temp;
    }
}

void display_playlist(playlist_t* p) // Displays the playlist
{
	// DO NOT MODIFY!!!
	display_list(p->list);
}

void play_song(int song_id)
{
	// DO NOT MODIFY!!!
	printf("Playing: %d\n", song_id);
}
