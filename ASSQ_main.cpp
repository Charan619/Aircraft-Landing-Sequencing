#include <iostream>
#include <unistd.h>
#include <time.h>
using namespace std;

// Structure representing a aircraft
struct aircraft
{
	int flid;
	int sc;
	int pr;
	struct aircraft *link;
}*te;

void delay(int number_of_seconds)
{
	// Converting time into milli_seconds
	int milli_seconds = 1000 * number_of_seconds;

	// Stroing start time
	clock_t start_time = clock();

	// looping till required time is not acheived
	while (clock() < start_time + milli_seconds)
		;
}

static int c1, c2, c3, c4;

class stack
{
    public:
	int pri;
        struct aircraft* bottom;
	struct aircraft* top;
        stack(int p)
        {
	    pri = p;
            bottom = top = NULL;
        }   
        void enqueue(int fl, int s, int pr)
        {
		if(bottom==NULL)
		{
			struct aircraft* temp=new Node;
			temp->sc = s;
			temp->pr = pr;
			temp->flid = fl;
			temp->link = NULL;
			top = temp;
			bottom = temp;
		}
		else
		{
			struct aircraft* temp=new Node;
			temp->sc = s;
			temp->pr = pr;
			temp->flid = fl;
			temp->link = NULL;
			top->link = temp;
			top = temp;				
		}
        }

        void dequeue()
        {
            if(bottom==NULL)
                cout<<"All aircraft landed. Continuing to the next stack"<<endl;
            else
            {
                struct aircraft* temp=bottom;
                bottom=bottom->link;
		int ch;
		cout<<"All aircraft leaving the stack shall slow down to 160 KIAS on short final, 10 miles to the runway"<<endl<<endl;
		cout<<"In case of a specialized request by the pilot owing to weather/technical reasons, the aircraft will be"<<endl;
		cout<<"allowed to perform a Touch-and-go. In this case, it shall return to the top of the stack."<<endl;
		if(temp->sc==1)
		{
			delay(180);
			cout<<"Controller permission:"<<"\n1 - Full Stop\n 2 - Touch and go"<<endl;
			cin>>ch;
			if(ch==1)
			{
				if(pri==1||pri==2)
				{
					cout<<"Aircraft touched down on runway 09. Waiting period: 82 seconds"<<endl;
					delay(82);
				}
				else if(pri==3||pri==4)
				{
					cout<<"Aircraft touched down on runway 27. Waiting period: 82 seconds"<<endl;
					delay(82);
				}
			}
			else if(ch==2)
			{
				enqueue(temp->flid, temp->sc, temp->pr);
			}
		}
		else if(temp->sc==2)
		{
			delay(180);
			cout<<"Controller permission:"<<"\n1 - Full Stop\n 2 - Touch and go"<<endl;
			cin>>ch;
			if(ch==1)
			{
				if(pri==1||pri==2)
				{
					cout<<"Aircraft touched down on runway 09. Waiting period: 82 seconds"<<endl;
					delay(131);
				}
				else if(pri==3||pri==4)
				{
					cout<<"Aircraft touched down on runway 27. Waiting period: 82 seconds"<<endl;
					delay(131);
				}
			}
			else if(ch==2)
			{
				enqueue(temp->flid, temp->sc, temp->pr);
			}
		}
		else if(temp->sc==3)
		{
			delay(180);
			cout<<"Controller permission:"<<"\n1 - Full Stop\n 2 - Touch and go"<<endl;
			cin>>ch;
			if(ch==1)
			{
				if(pri==1||pri==2)
				{
					cout<<"Aircraft touched down on runway 09. Waiting period: 82 seconds"<<endl;
					delay(196);
				}
				else if(pri==3||pri==4)
				{
					cout<<"Aircraft touched down on runway 27. Waiting period: 82 seconds"<<endl;
					delay(196);
				}
			}
			else if(ch==2)
			{
				enqueue(temp->flid, temp->sc, temp->pr);
			}
		}
                cout<<"Next aircraft set to short final"<<endl;
                delete(temp);
            }
        }

        void display()
        {
            if(bottom==NULL)
                cout<<"Queue is empty\n";
            else
            {
                struct aircraft* temp=bottom;
                while(temp!=NULL)
                {
                    cout<<temp->flid<<"->";
                    temp=temp->link;
                }
		cout<<endl;
            }
        }
};

 
int main(int argc, char const *argv[])
{

    LinkedQueue q;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(40);
    q.dequeue();
    q.dequeue();
    q.dequeue();
    q.enqueue(100);
    q.display();
    return 0;
}
