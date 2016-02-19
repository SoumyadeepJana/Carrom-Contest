#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<fstream.h>
#include<dos.h>

struct names
{
   char name[40];
   names *next;
};
names *head=NULL;


void entry()
{
    names *node=new names;

    if(node==NULL)
       cout<<"Memory error"<<endl;
    else
    {
       cout<<"Enter the name of participant:";
       gets(node->name);
       node->next=NULL;

       if(head==NULL)
	 head=node;
       else
       {
	  names *ptr=head;
	  while(ptr->next!=NULL)
	     ptr=ptr->next;
	  ptr->next=node;
       }

    }
}

void shuffle()
{
   int len=0;
   char temp[40];
   names *ptr=head;

   while(ptr!=NULL)
   {
      len++;
      ptr=ptr->next;
   }
   names *trav;
   names * trav1=head;

   for(int i=0;i<len-1;i++)
   {     trav=trav1;

       for(int j=0;j<len-1-i;j++)
       {
	    if(strlen(trav->name)>strlen(trav->next->name))
		{
		    strcpy(temp,trav->name);
		    strcpy(trav->name,trav->next->name);
		    strcpy(trav->next->name,temp);
		}
		trav=trav->next;
       }
       trav1=trav1->next;
   }
}

void view_team()
{
   clrscr();
   names *ptr=head;
   gotoxy(27,2);
   cout<<"TEAMS"<<endl;
   int num=0;
   while(ptr!=NULL)
   {
       num++;
       ptr=ptr->next;
   }
   if(num%2==0&&num>0)
   {
     ptr=head;

     while(ptr!=NULL)
     {
	cout<<ptr->name<<"----> "<<ptr->next->name<<endl;
	cout<<"----------------------------------"<<endl;
	ptr=ptr->next->next;
     }
   }
   else
      cout<<"More participant required"<<endl;
}

void view_participant()
{
   clrscr();
   if(head==NULL)
     cout<<"list empty"<<endl;
   else
   {
     names *ptr=head;

     while(ptr!=NULL)
     {
	cout<<ptr->name<<endl;
	cout<<"---------------------"<<endl;
	ptr=ptr->next;
     }
   }
}

Delete()
{
   char s[40];
   cout<<"Enter name to delete:";
   gets(s);
   names *ptr=head;
   names *prev=NULL;
   int stat=0;
   if(head!=NULL)
   {
     while(ptr!=NULL)
     {
	if(strcmpi(ptr->name,s)==0)
	{
		  if(prev==NULL)
		  head=head->next;
		  else
		  {
		    prev->next=ptr->next;
	}
	  cout<<"Deletion Successfull"<<endl;
	  stat=1;
	  break;
      }
	prev=ptr;
	ptr=ptr->next;
   }
   if(stat==0)
     cout<<"Name not found"<<endl;
 }
 else
   cout<<"List empty"<<endl;
}

void Delete_all()
{
    if(head==NULL)
       cout<<"List Empty"<<endl;
    else
    {
       head=NULL;
       cout<<"All names deleted successfully"<<endl;
    }
    remove("carrom.dat");
}




void end()
{

     ofstream  fout;
     fout.open("carrom.dat",ios::binary);

     while(head != NULL)
     {
	  fout.write((char *)head,sizeof(names));
	  head = head->next;
     }
     fout.close();

}


void start()
{
   ifstream fin;

   fin.open("carrom.dat",ios::binary);
   fin.seekg(0,ios::end);
   int len=fin.tellg();
   if(len>0)
   {
      int i=0;
      fin.seekg(0,ios::beg);
      while(i<(len/sizeof(names)))
      {
	i++;
	names *node = new names;
	fin.read((char *)node,sizeof(names));
	node->next=NULL;

	if(head == NULL)
	   head =  node;
	else
	{

	    names *ptr = head;
	    while(ptr->next != NULL)
	       ptr = ptr->next;
	    ptr->next = node;
	}
      }
   }
   fin.close();

}



void main()
{
    clrscr();
    int ch;
    start();
     do
   {  clrscr();
      gotoxy(25,1);
      cout<<"__________________________"<<endl;
      gotoxy(27,2);
      textcolor(RED);
      cprintf("CARROM CONTEST-2016");
      cout<<endl;
      gotoxy(25,3);
      cout<<"__________________________"<<endl;
      gotoxy(10,5);
      textcolor(CYAN);
      cprintf("Press 1 to Add Participant");
      cout<<endl;
      gotoxy(50,5);
      textcolor(GREEN);
      cprintf("Press 2 to View Participants");
      cout<<endl;
      gotoxy(10,7);
      textcolor(YELLOW);
      cprintf("Press 3 to Delete Participant");
      cout<<endl;
      gotoxy(50,7);
      cprintf("Press 4 to Delete all");
      gotoxy(35,9);
      cout<<"Press 5 to QUIT"<<endl;
      gotoxy(2,18);
      cout<<"Enter your choice : ";
      cin>>ch;

      switch(ch)
      {
	 case 1:
	       clrscr();
	       entry();
	       break;


	 case 2:
	       clrscr();
	       view_participant();
	       getch();
	       break;



	 case 3:
	       clrscr();
	       Delete();
	       getch();
	       break;

    case 4:
           clrscr();
           Delete_all();
           getch();
           break;

	case 5:
	      clrscr();
	      gotoxy(40,12);
	      textcolor(RED);
	      cprintf("_________");
	      gotoxy(40,13);
	      cprintf("GOOD BYE");
	      gotoxy(40,14);
	      cprintf("_________");
	      cout<<endl;
	      sleep(2);
	      break;






	default:
	   cout<<"Wrong choice"<<endl;
      }

   }while(ch != 5);
   shuffle();
   view_team();
   getch();

   end();
}