/*Welcome to the Aircraft Sequencing and Scheduling program (landing problem only)*/

/*This program intends to use a linked priority queue, or in other words, a priority queue implemented using a linked
data structure. It intends to automate the landing system on a given runway in both directions to assimilate the
traffic on a priority basis with minimum intervention from the controller.*/

#include <iostream>
#include <unistd.h>
#include <time.h>
#include <fstream>
using namespace std;

// Structure representing a aircraft. It contains the flight identification data, its size and priority.
struct aircraft
{
	int flid;
	int sc;
	int pr;
	struct aircraft *link;
}*te;

/* This function is used to simulate the time delay between landings */
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

class stack //This is a class definiton for a linked queue.
{
    public:
        //This definition contains 3 data members, pri refers to priority of the stack
        //The other two data members are pointers to the bottom and top of the linked priority stack.
		int pri;
        struct aircraft* bottom;
		struct aircraft* top;
        stack(int p)
        {
			pri = p;
            bottom = top = NULL;
        }
        //This function is used to enqueue the flight into the stack.
        void enqueue(int fl, int s, int pr)
        {
			if(bottom==NULL)
			{
				struct aircraft* temp=new aircraft();
				temp->sc = s;
				temp->pr = pr;
				temp->flid = fl;
				temp->link = NULL;
				top = temp;
				bottom = temp;
			}
			else
			{
				struct aircraft* temp=new aircraft();
				temp->sc = s;
				temp->pr = pr;
				temp->flid = fl;
				temp->link = NULL;
				top->link = temp;
				top = temp;
			}
        }
        //This function is used to dequeue the aircraft from the stack.
        void dequeue()
        {
            //This constitutes a condition that if the stack is empty, then the flow of control terminates within the block
            if(bottom==NULL)
            {
                cout<<"All aircraft landed. Continuing to the next stack"<<endl;
                return;
            }
            else
            {
                struct aircraft* temp=bottom;
                bottom=bottom->link;
				int ch;
				cout<<"All aircraft leaving the stack shall slow down to 160 KIAS on short final, 10 miles to the runway"<<endl<<endl;
				cout<<"In case of a specialized request by the pilot owing to weather/technical reasons, the aircraft will be"<<endl;
				cout<<"allowed to perform a Touch-and-go. In this case, it shall return to the top of the stack."<<endl;
				//This condition constitutes the dequeue process depending the size category of the aircraft.
				if(temp->sc==1)
				{
					delay(180);
					//This is a uniform delay from the bottom of a stack to the base of a runway. The distance is visualized
					//to be about 10 miles and the speed assigned to each aircraft is 160 knots on average.
					cout<<"Controller permission:"<<"\n1 - Full Stop\n2 - Touch and go"<<endl;
					cin>>ch;
					//This input is taken from the user to determine the necessity to either continue on a full stop landing
					//or stop the landing process owing to whatever reason and proceed with a touch and go.
					if(ch==1)
					{
						if(pri==1||pri==2)
						{
							cout<<"Flight "<<temp->flid<<" touched down on runway 09. Waiting period: 82 seconds"<<endl;
							delay(82);
						}
						else if(pri==3||pri==4)
						{
							cout<<"Flight "<<temp->flid<<" touched down on runway 27. Waiting period: 82 seconds"<<endl;
							delay(82);
						}
					}
					//In the case of a touch and go, it is pushed back into the top of the stack in the same priority.
					else if(ch==2)
					{
						enqueue(temp->flid, temp->sc, temp->pr);
					}
				}
				else if(temp->sc==2)
				{
					delay(180);
					cout<<"Controller permission:"<<"\n1 - Full Stop\n2 - Touch and go"<<endl;
					cin>>ch;
					if(ch==1)
					{
						if(pri==1||pri==2)
						{
							cout<<"Flight "<<temp->flid<<" touched down on runway 09. Waiting period: 131 seconds"<<endl;
							delay(131);
						}
						else if(pri==3||pri==4)
						{
							cout<<"Flight "<<temp->flid<<" touched down on runway 27. Waiting period: 131 seconds"<<endl;
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
					cout<<"Controller permission:"<<"\n1 - Full Stop\n2 - Touch and go"<<endl;
					cin>>ch;
					if(ch==1)
					{
						if(pri==1||pri==2)
						{
							cout<<"Flight "<<temp->flid<<" touched down on runway 09. Waiting period: 196 seconds"<<endl;
							delay(196);
						}
						else if(pri==3||pri==4)
						{
							cout<<"Flight "<<temp->flid<<" touched down on runway 27. Waiting period: 196 seconds"<<endl;
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
        //This function display() is a user-convinient function in the case the user needs to know
        //which aircraft is next in line for the short final approach.
};


int main(int argc, char const *argv[])
{
	stack s1(1), s2(2), s3(3), s4(4);
	//This is used to create the 4 required stacks with the requisite priorities
	ifstream fdat;
	fdat.open("assq.txt");
	//This file "assq.txt" contains the data required to be testing the program.
	//The data in the file is in a 5-digit format, the first 3 digits correspond to the flight identification number
	//while the fourth digit corresponds to the size category of the aircraft.
	//1 stands for small size, 2 for mid size and 3 for large size aircraft
	//The fifth and final digit is used to determine the priority of the aircraft.
	cout<<"---------Welcome to a demonstration of the aircraft sequencing and scheduling program (landing problem)-------------"<<endl;
    cout<<endl;
    cout<<"This program intends to use a linked priority queue, or in other words, a priority queue implemented using a linked"<<endl;
    cout<<"data structure. It intends to automate the landing system on a given runway in both directions to assimilate the "<<endl;
    cout<<"traffic on a priority basis with minimum intervention from the controller."<<endl;
    cout<<endl;
    cout<<"Each aircraft is assigned to an oval stack with an average perimeter of 21 nautical miles, traveling at 210 knots per hour."<<endl;
    cout<<"Every aircraft shall descend to the requisite altitude of 6000 ft at a uniform rate before exiting the stack."<<endl;
    cout<<"Upon each aircraft exiting the stack, its speed is reduced to 160 knots per hour, 10 miles from the runway."<<endl;
    cout<<"That roughly translates to a delay of 3 minutes between exiting the stack and touch down on either runway."<<endl;
    cout<<"Upon touch down, if the pilot makes a specific request to touch-and-go for whatever reason, his aircraft "<<endl;
    cout<<"shall fly out again and climb back to the top of the stack. Else, they will come to a full stop on the runway."<<endl;
    cout<<endl;
    cout<<"There are 3 categories of aircraft that may queue up for approach: "<<endl;
    cout<<"1. Small size Aircraft (Narrow-body aircraft)"<<endl;
    cout<<"2. Mid-size Aircraft (Larger narrow-body / capable wide-body aircraft)"<<endl;
    cout<<"3. Large size Aircraft (Large Wide-body aircraft)"<<endl;
    cout<<endl;
    cout<<"Each category of aircraft translates to a unique time delay while on the runway."<<endl;
    cout<<endl;
    cout<<"The data required for initiating the entry into the stack will be derived from a file."<<endl;
    cout<<"The process shall begin now"<<endl;
    cout<<endl;
	int a;
	int fid;
	int sc;
	int pr;
    while(fdat>>a)
    {
        pr = a%10;
        sc = (a%100)/10;
        fid = a/100;
        if(pr==1)
        {
            s1.enqueue(fid, sc, pr);
            cout<<"Flight "<<fid<<" lined up for approach on Runway 09 - Priority 1"<<endl;
        }
        else if(pr==2)
        {
            s2.enqueue(fid, sc, pr);
            cout<<"Flight "<<fid<<" lined up for approach on Runway 09 - Priority 2"<<endl;
        }
        else if(pr==3)
        {
            s3.enqueue(fid, sc, pr);
            cout<<"Flight "<<fid<<" lined up for approach on Runway 27 - Priority 3"<<endl;
        }
        else if(pr==4)
        {
            s4.enqueue(fid, sc, pr);
            cout<<"Flight "<<fid<<" lined up for approach on Runway 27 - Priority 4"<<endl;
        }
    }
    int crr = 0, pr = 1;
    cout<<"\nFlight data entered into the stack. Landing process shall begin momentarily.\n"<<endl;
    while(s1.bottom!=NULL && s2.bottom!=NULL && s3.bottom!=NULL && s4.bottom!=NULL)
    {
        if(pr==1)
        {
            s1.dequeue();
            pr=2;
            continue;
        }
        else if(pr==2)
        {
            s2.dequeue();
            if(crr==0)
            {
                pr=1;
                crr=1;
                continue;
            }
            else if(crr==1)
            {
                pr=3;
                crr=0;
                continue;
            }
        }
        else if(pr==3)
        {
            s3.dequeue();
            pr=4;
            continue;
        }
        else if(pr==4)
        {
            s4.dequeue();
            pr=1;
            continue;
        }
    }
	return 0;
}
