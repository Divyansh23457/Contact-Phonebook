#include<iostream>
#include<fstream>
#include <sstream>
using namespace std;
struct Node
{
	string name;                
	long long int phone_number; 
	Node *next;
	Node *prev;
	Node (){}
	Node(string n,int data) : name(n), phone_number(data),next(NULL),prev(NULL) {}
};

class ContactBook
{
	Node *head;
	string x;
	long long int y;
	public:
		ContactBook()
		{
			head=NULL;
			x="";
			y=0;
		}
    	void CreateNode()
	    {		
	    	    cout<<" Enter Name of Contact: ";
		        cin>>x;
    		    cout<<"  Enter Phone Number: ";
	    	    cin>>y;
				Node *temp = new Node(x,y);
		    	if(!head) head = temp;
				else {
					temp->next = head;
					head = temp;
				}
		    	cout<<"  Contact Added!  "<<endl;
		}

    	void Display()
    	{
	    	Node *temp=head;
	    	int count=0;
	    	if(!temp)
	    	{
		    	cout<<"  No Contacts... Please Add Some Contacts first"<<endl;
				return;
	    	}
			cout<<"  Name: "<<"      Number: \n "<<endl;
	        while(temp)
	        	{
	        	    count++;
		        	cout<<"  "<<temp->name;
		        	cout<<"  "<<temp->phone_number<<endl;
    		    	temp=temp->next;		
	        	}
	    	cout<<"\n\n\n  Total contacts: "<<count<<"\n\n\n";
	    }
    	
    	Node* Search()
    	{
			if(!head){
				cout<<"Contact List is empty!!\n Please add some contacts first.\n";
				return NULL;
			}
	    	Node *temp=head;
	    	cout<<"***********"<<endl;
	    	cout<<"Enter the Name or the Phone Number to Search:";
			string find;cin>>find;
			while(temp)
				{
					if(temp->name==find || temp->phone_number == stoll(find))
						{
							cout<<"***********"<<endl;
							cout<<"  Name: "<<temp->name<<endl;
							cout<<"  Phone Number:"<<temp->phone_number<<endl;
							cout<<"***********"<<endl;    
							return temp;
						}
						temp=temp->next;
				}
			return NULL;
		}

	    void DeleteAllContacts()
	    {
	    	Node *temp=head;
	    	Node *temp2;
	    	if(!head) return;
			while(temp)
			{
				temp2=temp;
				temp=temp->next;
				delete temp2;
			}
			head=NULL;
			cout<<"  Successfully Deleted All Contacts ..."<<endl;
	    	cout<<"***********"<<endl;
		}
		
		int DeleteContactBySearch()
    	{
	    	Node *temp = Search();
			if(!temp) {
				cout<<"Contact Not Found!!"<<endl;
			}
			else{
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				delete temp;
				cout<<"Contact Deleted Successfully!!"<<endl;
			}
	    }   	
        
        int EditContacts()
    	{
	    	Node *temp= Search();
			if(!temp) cout<<"Contact Not Found!!";
			else{
				cout<<"Enter new Name for the Contact: ";
				cin>>x;
				cout<<"Enter new Phone number for the contact: ";
				cin>>y;
				temp->name = x;
				temp->phone_number = y;
				cout<<"Contact Edited Successfully!!"<<endl;
			}
	    }
	
    	
    	void OfflineSave()
    	{
    		Node *temp=head;
    		ofstream myfile ("contactbook.txt");
            if (myfile.is_open())
            {
            	while(temp!=NULL)
	        	{
	        	    myfile<<temp->name<<endl;
		        	myfile<<temp->phone_number<<endl;
    		    	temp=temp->next;		
	        	}
                myfile.close();
                Structure();
            }
            else
            {
            	cout<<"  The file is now saved."<<endl;
			}
		}
		
		void reopenCB()
		{
			ifstream myfile ("contactbook.txt");
            if(myfile.is_open() & myfile.peek() != EOF)
            {
                int i=0;
                while(getline(myfile,x))
                {	
                    if(i % 2 == 0)
					{
						if(head==NULL)
	                    {
    	                  Node *newer= new Node;
                          newer->name=x;
		         
	                      newer->next=NULL;
	                      newer->prev==NULL;
	                      head=newer;
		                }
						else
						{
							Node *newer= new Node;
							
							newer->name=x;
							
							newer->next = head;
							head->prev = newer;
							newer->prev = NULL;
							head = newer;	
						} 
                    }
                   else
                    {
                    	Node *temp=head;
                    	if(temp->phone_number==0)
                    	{
                    		 stringstream convert(x);
			       	         convert>>y;
                             temp->phone_number=y;
						}
					

						else
						{
							Node *temp=head;
		                	while(temp->next!=NULL)
		                	{
		                		temp=temp->next;
		                	}
		                	
		                	stringstream convert(x);
			       	        convert>>y;
		                	temp->phone_number=y;
							
						}
				    }
                    i++;
                }
            	myfile.close();
            }
            else
            {
            	cout<<"  File is Empty,Cant open..."<<endl;
			}
		}
		void Structure()
    	{
	    	cout<<"***********"<<endl;
	    	cout<<"  1. Add Contact"<<endl;
	    	cout<<"  2. Edit the Contact"<<endl;
	    	cout<<"  3. Delete Contact"<<endl;
	    	cout<<"  4. Search Contact"<<endl;
	    	cout<<"  5. Display All Contacts"<<endl;
	    	cout<<"  6. Delete All Contacts"<<endl;
	    	cout<<"***********"<<endl;
		
	    	int Scommand;
	    	cout<<"  Enter the Command: ";
	    	cin>>Scommand;
	    	try
	    	{
	    		if(Scommand>=1&&Scommand<=6)
	    		{
	    			if(Scommand==1)
	            	{
	            		CreateNode();
	            		OfflineSave();
	    	        	Structure();
	            	}
	            	else if(Scommand==2)
		        	{
		        		EditContacts();
		        		OfflineSave();
		        		Structure();
			        }
	            	else if(Scommand==3)
	            	{
	    	        	DeleteContactBySearch();
	    	        	Structure();
	            	}
	            	else if(Scommand==4)
	            	{
	            		Search();
	            		Structure();
	            	}
	            	else if(Scommand==5)
	            	{      		
	            		Display();
	            		OfflineSave();
	            		Structure();
	            	}
	            	else if(Scommand==6)
	            	{
	            		DeleteAllContacts();
	            		OfflineSave();
	            		Structure();	
		        	}
				}
				else
				{
					throw(Scommand);
				}
			}
			catch(int Scommand)
			{
				cout<<"  You Enter wrong Command... Run the Code Again"<<endl;
				Structure();
			}	
	    }
    	
};

int main()
{   
    ContactBook cb;
    cb.reopenCB();
	string n;
	cout<<"  What is Your Name: ";
	cin>>n;
    cout<<"***********"<<endl;
	cout<<"  "<<n<<"  WELCOME TO CONTACTBOOK !	     "<<endl;
	cout<<"***********"<<endl;
	cb.Structure();
	return 0;
} 
