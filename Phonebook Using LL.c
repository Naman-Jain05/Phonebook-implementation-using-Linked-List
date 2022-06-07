/*	BT20CSE087 Naman Jain

	compiled on DEV-C++ 5.11
			or
	https://www.onlinegdb.com/online_c_compiler
	
	enter name without space everywhere 
	 name should be case sensititve
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct detail_node
{
	int noCall;
	char contName[50];
	int duration;				//in minutes
	struct detail_node *below;
	char lastDate[20];
};

struct per_cont_node
{
	long long int phoneNo;
	char name[50];
	char last_name[50];
	char mail[50];
	int type;
	struct per_cont_node *next;
	struct detail_node *down;		//linked list of link list
	
};

struct prof_cont_node
{
	long long int phoneNo;
	char name[50];
	char last_name[50];
	char mail[50];
	int officeNo;
	char address[50];
	int type;
	char institute[50];
	struct prof_cont_node *next;
	
};

void add_detail(struct per_cont_node** head_personal,int dur,int nCall,char nam[50],char per_name[50],char date[20])
{
	int done=0;
	
	struct per_cont_node *head_per=*head_personal;
	struct per_cont_node *per_ptr=head_per;
	
	if(head_per==NULL)		//if personal contact list is empty
	{
		printf("empty list\n");
		return ;
	}
	
	while(strcmp(per_ptr->name,per_name)!=0&&per_ptr->next!=NULL)
	{
		per_ptr=per_ptr->next;
	}
	
	if(strcmp(per_ptr->name,per_name)!=0)		//if no user given name exist
	{
		printf("No such name in personal contact exist type correct name pls!!!\n");
		return;
	}
	
	struct detail_node *head_det=per_ptr->down;
	struct detail_node *nod=NULL,*ptr=head_det;
	
	nod=(struct detail_node* )malloc(sizeof(struct detail_node));
	nod->duration=dur;
	nod->noCall=nCall;
	strcpy(nod->contName,nam);
	strcpy(nod->lastDate,date);
	nod->below=NULL;
	
	if(head_det==NULL)		//if detail list is empty
	{
		head_det=nod;
		done=1;
	}
	else if(head_det->below==NULL) 	//if detail list has single element
	{
		if(head_det->duration>nod->duration)
		{
			head_det->below=nod;
			done=1;
		}
		else
		{
			nod->below=head_det;
			head_det=nod;
			done=1;
		}
	}
	else			//if detail list has 2 or more element
	{
		while(done!=1&&ptr->below!=NULL)
		{
			if(ptr->below->duration<nod->duration)
			{
				nod->below=ptr->below;
				ptr->below=nod;
				done=1;
			}
		}
		if(done==0)
		{
			ptr->below=nod;		//insert at end
		}
		
	}
	per_ptr->down=head_det;
			
	*head_personal=head_per;
	printf("\ndetails has been added\n");
	
}

//a caller calls to many many callee
//linked list (caller) of linked list (callee) 

void display_phonebook(struct per_cont_node* head_per,char per_name[50])
{
	
	struct per_cont_node *per_ptr=head_per;
	if(head_per==NULL)			//if personal contact list is empty
	{
		printf("empty list\n");
		return ;
	}
	while(strcmp(per_ptr->name,per_name)!=0&&per_ptr->next!=NULL)
	{
		per_ptr=per_ptr->next;
	}
	if(strcmp(per_ptr->name,per_name)!=0)		//if no user given name exist
	{
		printf("No such name in personal contact type correct name pls!!!\n");
		return;
	}
	
	struct detail_node *head_det=per_ptr->down;
	struct detail_node *ptr=head_det;
	
	if(ptr==NULL)
	{
		printf("empty\n");
	}
	else
	{
		printf("\ngiven caller detail:\n");
		printf("%s %s :%s %lld\n",per_ptr->name,per_ptr->last_name,per_ptr->mail,per_ptr->phoneNo);
		printf("\ncallee details:\n");
		printf("duration: number-of-calls :contact_name:last-date-called\n");
		while(ptr!=NULL)
		{
			printf("%d  :%d   %s   :%s\n",ptr->duration,ptr->noCall,ptr->contName,ptr->lastDate);
			ptr=ptr->below;
		}
	}
	printf("\n");
	
}

void insertPersonal(struct per_cont_node** head_personal,char nam[30],char eml[50],char ln[50],long long int no)
{
	int done=0;
	struct per_cont_node *head_per=*head_personal;
	struct per_cont_node *ptr=head_per;
    struct per_cont_node *nod=NULL;
    nod=(struct per_cont_node* )malloc(sizeof(struct per_cont_node));
    nod->phoneNo=no;
    strcpy(nod->name,nam);
    strcpy(nod->last_name,ln);
    strcpy(nod->mail,eml);
    nod->type=0;
    nod->next=NULL;
    
    if(head_per==NULL)  //empty list case
    {
        head_per=nod;
        done=1;
    }
	else if(strcmp(head_per->name,nod->name)>0)		//comparing with head
	{
		nod->next=head_per;
		head_per=nod;
		done=1;
	}
	else if(strcmp(head_per->name,nod->name)==0)	//comparing with head
	{
		if(head_per->phoneNo<nod->phoneNo)
    		{
    			nod->next=head_per->next;
    			head_per->next=nod;
    			done=1;
			}
		else
			{
				nod->next=head_per;
    			head_per=nod;
    			done=1;
			}
	}
    else 		//2 or more node case insert in sorted manner
    {
    	while(ptr->next!=NULL&&done!=1)
    	{
    		if(strcmp(ptr->next->name,nod->name)>0)
    		{
    		nod->next=ptr->next;
    		ptr->next=nod;
    		done=1;
			}
		
			else if(strcmp(ptr->next->name,nod->name)==0) 		//if same name then insert by checking phone number
    		{
    			if(ptr->next->phoneNo>nod->phoneNo)
    			{
    				nod->next=ptr->next;
    				ptr->next=nod;
    				done=1;
				}
				
			}
			ptr=ptr->next;
		}
		if(done==0)
		{
			ptr->next=nod;
		}
		
	}
	
	*head_personal=head_per;
	printf("\npersonal Contact has been created\n");	
	return ;
}

void insertProfessional(struct prof_cont_node** head_professional,char* n,char* ln,char* em,char* ad,char* inst ,long long int i,int ofNo)
{
	int done=0;
	struct prof_cont_node *head_prof=*head_professional;
	struct prof_cont_node *ptr=head_prof;
    struct prof_cont_node *nod=NULL;
    nod=(struct prof_cont_node* )malloc(sizeof(struct prof_cont_node));
    
    strcpy(nod->name,n);
    strcpy(nod->last_name,ln);
    strcpy(nod->mail,em);
    strcpy(nod->address,ad);
    strcpy(nod->institute,inst);
    nod->phoneNo=i;
    nod->officeNo=ofNo;
    nod->type=1;
    
    if(head_prof==NULL)  	//empty list case
    {
        head_prof=nod;
        done=1;
    }
    
	else if(strcmp(head_prof->name,nod->name)>0)		//comparing with head
	{
		nod->next=head_prof;
		head_prof=nod;
		done=1;
	}
	else if(strcmp(head_prof->name,nod->name)==0)		//comparing with head
	{
		if(head_prof->phoneNo<nod->phoneNo)
    		{
    			nod->next=head_prof->next;
    			head_prof->next=nod;
    			done=1;
			}
			else
			{
				nod->next=head_prof;
    			head_prof=nod;
    			done=1;
			}
	}
    else			//2 or more node case insert in sorted manner
    {
    	while(ptr->next!=NULL&&done!=1)
    	{
    		if(strcmp(ptr->next->name,nod->name)>0)
    		{
    		nod->next=ptr->next;
    		ptr->next=nod;
    		done=1;
			}
		
			else if(strcmp(ptr->next->name,nod->name)==0) 	//if same name then insert by checking phone number
    		{
    			if(ptr->next->phoneNo>nod->phoneNo)
    			{
    				nod->next=ptr->next;
    				ptr->next=nod;
    				done=1;
				}
				
			}
			ptr=ptr->next;
		}
		if(done==0)
		{
			ptr->next=nod;
		}
		
	}
	*head_professional=head_prof;
	printf("\nprofessional Contact has been created\n");	
	return ;
		
}

void edit_per(struct per_cont_node** head_personal,char* n,char* eml,long long int no)
{
	struct per_cont_node *head_per=*head_personal;
	struct per_cont_node *ptr=head_per;
	int done=0;
	while(ptr!=NULL&&done!=1)
	{
		if(strcmp(ptr->name,n)==0)   //modifying contact with given name
		{
			ptr->phoneNo=no;
			strcpy(ptr->mail,eml);
			done=1;
		}
		ptr=ptr->next;
	}
	
	*head_personal=head_per;
	if(done==1)
	{
		printf("personal Contact has been edited\n");
	}
	else
	{
		printf("No such element exist first insert it\n");
	}
}

void edit_prof(struct prof_cont_node** head_professional,char* n,char* em,char* ad,char* inst ,long long int i,int ofNo)
{
	struct prof_cont_node *head_prof=*head_professional;
	struct prof_cont_node *ptr=head_prof;
	int done=0;
	while(ptr!=NULL&&done!=1)
	{
		if(strcmp(ptr->name,n)==0) 		//modifying contact with given name
		{
    		strcpy(ptr->mail,em);
    		strcpy(ptr->address,ad);
    		strcpy(ptr->institute,inst);
			ptr->phoneNo=i;
			ptr->officeNo=ofNo;
			done=1;
		}
		ptr=ptr->next;
	}
	
	*head_professional=head_prof;
	if(done==1)
	{
		printf("\nprofessional Contact has been edited\n");
	}
	else
	{
		printf("No such element exist first insert it\n");
	}
}

void dele_per(struct per_cont_node** head_personal,long long int num)
{
	struct per_cont_node *head_per=*head_personal;
	struct per_cont_node *ptr=head_per;
	struct per_cont_node *temp=NULL;
	int done=0;
	
	if(head_per!=NULL)						//if list is not empty
	{
		if((head_per->phoneNo)==num)		//deleting contact with given number and if its head node
		{
			temp=head_per;
			head_per=head_per->next;
			done=1;
		}
	
		while(ptr->next!=NULL&&done!=1)
		{
		if(ptr->next->phoneNo==num) 		//deleting contact with given number
		{
			temp=ptr->next;
			ptr->next=temp->next;
			done=1;
		}
		if(ptr->next!=NULL)
		{
			ptr=ptr->next;
		}
		}
	
		*head_personal=head_per;
	}
	if(done==0)
	{
		printf("No such phoneNo exist\n");
	}
	else
	{
		free(temp);
		printf("\npersonal Contact has been deleted\n");
	}
	
}

void dele_prof(struct prof_cont_node** head_professional,long long int num)
{
	struct prof_cont_node *head_prof=*head_professional;
	struct prof_cont_node *ptr=head_prof;
	struct prof_cont_node *temp=NULL;
	
	int done=0;
	
	if(head_prof!=NULL)						//if list is not empty
	{
		if((head_prof->phoneNo)==num) 		//deleting contact with given number and if its head node
		{
			temp=head_prof;
			head_prof=head_prof->next;
			done=1;
		}
	
		while(ptr->next!=NULL&&done!=1)
		{
		if(ptr->next->phoneNo==num) 		//deleting contact with given number 
		{
			temp=ptr->next;
			ptr->next=temp->next;
			done=1;
		}
		if(ptr->next!=NULL)
		{
			ptr=ptr->next;
		}
		}
	
		*head_professional=head_prof;
	}
	if(done==0)
	{
		printf("No such phoneNo exist\n");
	}
	else
	{
		free(temp);
		printf("\nprofessinal Contact has been deleted\n");
	}
}

void search_per(struct per_cont_node* head_per,char* n,long long int num)
{
	int done=0;
	struct per_cont_node *ptr=head_per;
	while(ptr!=NULL&&done!=1)
	{
		if((ptr->phoneNo==num)&&(strcmp(ptr->name,n)==0))		//searching contact with given number and name
		{
			printf("search result:name , mobileNo , email:\n");
			printf("%s %s    :%lld      :%s\n",ptr->name,ptr->last_name,ptr->phoneNo,ptr->mail);
			done=1;
		}
		ptr=ptr->next;
	}
	if(done==0)
	{
		printf("No such element exist\n");
	}
	
}

void search_prof(struct prof_cont_node* head_prof,char* n,long long int num)
{
	int done=0;
	struct prof_cont_node *ptr=head_prof;
	while(ptr!=NULL&&done!=1)
	{
		
		if((ptr->phoneNo==num)&&(strcmp(ptr->name,n)==0))		//searching contact with given number and name
		{
			printf("search result:name : lastname : mail : adress : inst :  mobileNo : offNo:\n");
			printf("%s %s :%s :%s :%s :%lld :%d\n",ptr->name,ptr->last_name,ptr->mail,ptr->address,ptr->institute,ptr->phoneNo,ptr->officeNo);
			done=1;
		}
		ptr=ptr->next;
	}
	if(done==0)
	{
		printf("No such element exist\n");
	}

}

void reverse_per(struct per_cont_node** head_personal)		//reversing personal contact
{
    struct per_cont_node* prev = NULL;
    struct per_cont_node* current = *head_personal;
    struct per_cont_node* nexts = NULL;
    while (current != NULL)
	{
        nexts = current->next;
        current->next = prev;
        prev = current;
        current = nexts;
    }
    *head_personal = prev;
}

void reverse_prof(struct prof_cont_node** head_professional)	//reversing professional contact
{
    struct prof_cont_node* prev = NULL;
    struct prof_cont_node* current = *head_professional;
    struct prof_cont_node* nexts = NULL;
    while (current != NULL) 
	{
        nexts = current->next;
        current->next = prev;
        prev = current;
        current = nexts;
    }
    *head_professional = prev;
}

void sort()
{
	printf("both list are already sorted check the display!!\n");
}

void display_per(struct per_cont_node* head_per)		//displaying personal contact
{
	struct per_cont_node *ptr=head_per;
	
	if(head_per==NULL)
	{
		printf("personal list is empty\n");
	}
	else
	{
		printf("name:  mobileNo:  email:\n");
	}
	while(ptr!=NULL)
	{
		printf("%s %s    :%lld     :%s\n",ptr->name,ptr->last_name,ptr->phoneNo,ptr->mail);
		ptr=ptr->next;
	} 
	 
}

void display_per_rev(struct per_cont_node* ptr)				//displaying personal contact in reverse
{
	struct per_cont_node *ptrs=ptr;
	if(ptrs==NULL)
	{
		printf("personal list is empty\n");
		return;
	}
	if(ptr->next!=NULL)
	{
		display_per_rev(ptr->next);
	}
	
	printf("%s %s    :%lld      :%s\n",ptr->name,ptr->last_name,ptr->phoneNo,ptr->mail);
	
}

void display_prof_rev(struct prof_cont_node* ptr)		//displaying professional contact in reverse
{
	struct prof_cont_node *ptrs=ptr;
	if(ptrs==NULL)
	{
		printf("professional list is empty\n");
		return;
	}
	if(ptr->next!=NULL)
	{
		display_prof_rev(ptr->next);
	}
	printf("%s %s :%s :%s :%s :%lld :%d\n",ptr->name,ptr->last_name,ptr->mail,ptr->address,ptr->institute,ptr->phoneNo,ptr->officeNo);
	
	
}

void display_prof(struct prof_cont_node* head_prof)		//displaying professional contact
{
	struct prof_cont_node *ptr=head_prof;
	
	if(head_prof==NULL)
	{
		printf("personal list is empty\n");
	}
	else
	{
		printf("name : lastname : mail : adress : inst :  mobileNo : offNo:\n");
	}
	
	while(ptr!=NULL)
	{
		printf("%s %s :%s :%s :%s :%lld :%d\n",ptr->name,ptr->last_name,ptr->mail,ptr->address,ptr->institute,ptr->phoneNo,ptr->officeNo);
		ptr=ptr->next;
	 } 
}

struct per_cont_node* merge_per(struct per_cont_node* head_per,struct per_cont_node* other_head_per)
{
	struct per_cont_node* ptr=NULL,*a=head_per,*b=other_head_per,*p=NULL;
	
	if(head_per==NULL)		//if one or both list are empty
	{
		ptr=other_head_per;
	}
	else if(other_head_per==NULL)	//if other list is empty
	{
		ptr=head_per;
	}
	else					//if both are non empty
	{
		if(strcmp(head_per->name,other_head_per->name)<0)
		{
			ptr=head_per;
			a=a->next;
		}
		else if(strcmp(head_per->name,other_head_per->name)==0)		//if both name are same compare with number
		{
			if(head_per->phoneNo>other_head_per->phoneNo)
			{
				ptr=other_head_per;
				b=b->next;
			}
			else
			{
				ptr=head_per;
				a=a->next;
			}
		}
		else
		{
			ptr=other_head_per;
			b=b->next;
		}
		p=ptr;						//initialising
		while(a!=NULL&&b!=NULL)
		{
			if(strcmp(a->name,b->name)<0)	
			{
				p->next=a;
				p=p->next;
				a=a->next;
			}
			
			else if(strcmp(a->name,b->name)==0)		//if both name are same compare with number
			{
				if(a->phoneNo>b->phoneNo)
				{
					p->next=b;
					p=p->next;
					b=b->next;
				}
				else
				{
					p->next=a;
					p=p->next;
					a=a->next;
				}
			}
			
			else
			{
				p->next=b;
				p=p->next;
				b=b->next;
			}
		}
		if(b!=NULL)		//inserting remaining at end
		{
			p->next=b;
		}
		if(a!=NULL)		//inserting remaining at end
		{
			p->next=a;
		}
	}
	
	return ptr;
}

struct prof_cont_node* merge_prof(struct prof_cont_node* head_prof,struct prof_cont_node* other_head_prof)
{
	struct prof_cont_node* ptr=NULL,*a=head_prof,*b=other_head_prof,*p=NULL;
	
	if(head_prof==NULL)		//if one or both list are empty
	{
		ptr=other_head_prof;
	}
	else if(other_head_prof==NULL)	//if other list is empty
	{
		ptr=head_prof;
	}
	else					//if both are non empty
	{
		if(strcmp(head_prof->name,other_head_prof->name)<0)
		{
			ptr=head_prof;
			a=a->next;
		}
		else if(strcmp(head_prof->name,other_head_prof->name)==0)		//if both name are same compare with number
		{
			if(head_prof->phoneNo>other_head_prof->phoneNo)
			{
				ptr=other_head_prof;
				b=b->next;
			}
			else
			{
				ptr=head_prof;
				a=a->next;
			}
		}
		else
		{
			ptr=other_head_prof;
			b=b->next;
		}
		p=ptr;						//initialising
		while(a!=NULL&&b!=NULL)
		{
			if(strcmp(a->name,b->name)<0)	
			{
				p->next=a;
				p=p->next;
				a=a->next;
			}
			
			else if(strcmp(a->name,b->name)==0)		//if both name are same compare with number
			{
				if(a->phoneNo>b->phoneNo)
				{
					p->next=b;
					p=p->next;
					b=b->next;
				}
				else
				{
					p->next=a;
					p=p->next;
					a=a->next;
				}
			}
			
			else
			{
				p->next=b;
				p=p->next;
				b=b->next;
			}
		}
		if(b!=NULL)		//inserting remaining at end
		{
			p->next=b;
		}
		if(a!=NULL)		//inserting remaining at end
		{
			p->next=a;
		}
	}
	
	return ptr;
}

void rmvDuplicates_per(struct per_cont_node** head_personal)	//remove duplicates from personal contact
{
	struct per_cont_node *head_per=*head_personal;
	struct per_cont_node *ptr=head_per;
	struct per_cont_node *temp=head_per;
	
	if(head_per!=NULL)	//if list is not empty
	{
		if(head_per->next!=NULL)	//if there are more than 1 contact
		{
			while(ptr->next!=NULL)
			{
				if(strcmp(ptr->name,ptr->next->name)==0)		//assume first contact is the correct contact
				{
					temp=ptr->next;
					ptr->next=temp->next;
					free(temp);
				}
				if(ptr->next!=NULL&&strcmp(ptr->name,ptr->next->name)!=0)
				{
					ptr=ptr->next;
				}
				
			}
		}
	}
	*head_personal=head_per;
	printf("\nduplicates(same name many contacts) from personal Contact has been deleted\n");
}

void rmvDuplicates_prof(struct prof_cont_node** head_professional)	//remove duplicates from professional contact
{
	struct prof_cont_node *head_prof=*head_professional;
	struct prof_cont_node *ptr=head_prof;
	struct prof_cont_node *temp=head_prof;
	
	if(head_prof!=NULL)	//if list is not empty
	{
		if(head_prof->next!=NULL)	//if there are more than 1 contact
		{
			while(ptr->next!=NULL)
			{
				if(strcmp(ptr->name,ptr->next->name)==0)		//assume first contact is the correct contact
				{
					temp=ptr->next;
					ptr->next=temp->next;
					free(temp);
				}
				
				if(ptr->next!=NULL&&strcmp(ptr->name,ptr->next->name)!=0)
				{
					ptr=ptr->next;
				}
				
			}
		}
	}
	
	*head_professional=head_prof;
	printf("\nduplicates(same name many contacts) from personal Contact has been deleted\n");
}



int main() //driver function
{ 
	int run=1,choice,t,i,dur,nCall;
	char name[50];
	char per_name[50];
	char date[20];
	struct per_cont_node* head_per=NULL;
	struct per_cont_node* other_head_per=NULL;
	struct prof_cont_node* head_prof=NULL;
	struct prof_cont_node* other_head_prof=NULL;

	while(run!=0)
  	{
	
	printf("\npress\t1 to insert \t 2 to edit \t 3 to delete\n \t4 to search \t 5 to sort \t 6 to display\n"
	 "\t7 to merge \t 8 to remove duplicates \n\t9 to create linked list of linked list\n\n");
	printf("enter choice:");
	scanf("%d",&choice);
	
	switch(choice)
		{
		case 1:
			printf("choose 0 for personal 1 for professional:\n");
			scanf("%d",&t);
			if(t==0)
			{
				printf("enter your name,last name,email,mobileNo:\n");
				char n[50];
				scanf("%s",n);
				char ln[50];
				scanf("%s",ln);
				char e[50];
				scanf("%s",e);
				long long int i;
				scanf("%lld",&i);
				insertPersonal(&head_per,n,e,ln,i);
			}
			else
			{
				printf("enter your name,last name,email,address,institute,mobileNo,officeNo:\n");
				long long int i;
				char n[50],ln[50],em[50],ad[50],inst[50];
				int ofNo;
				scanf("%s%s%s%s%s%lld%d",n,ln,em,ad,inst,&i,&ofNo);
				insertProfessional(&head_prof,n,ln,em,ad,inst,i,ofNo);
			}
			printf("\n");
			break;
			
		case 2:
			printf("choose 0 to edit personal 1 to edit professional:\n");
			scanf("%d",&t);
			printf("enter first name of contact which is to be edited:\n");
			char na[50];
			scanf("%s",na);
			if(t==0)
			{
				char e[50];
				long long int i;
				printf("enter edited mobileNo,email:\n");
				scanf("%lld%s",&i,e);
				rmvDuplicates_per(&head_per);		//first removing all duplicates then editing
				edit_per(&head_per,na,e,i);
			}
			else
			{
				printf("enter edited email,address,institute,mobileNo,officeNo:\n");
				long long int i;
				char ln[50],em[50],ad[50],inst[50];
				int ofNo;
				scanf("%s%s%s%s%lld%d",ln,em,ad,inst,&i,&ofNo);
				rmvDuplicates_prof(&head_prof);			//first removing all duplicates then editing
				edit_prof(&head_prof,na,em,ad,inst,i,ofNo);
			}
			printf("\n");
			break;
			
		case 3:
			printf("choose 0 to delete personal 1 to delete professional:\n");
			scanf("%d",&t);
			printf("enter number whose contact has to be deleted:\n");
			long long int mobNo;
			scanf("%lld",&mobNo);
			if(t==0)
			{
				dele_per(&head_per,mobNo);
			}
			else
			{
				dele_prof(&head_prof,mobNo);
			}
			printf("\n");
			break;
			
		case 4:
			printf("choose 0 to search personal 1 to search professional:\n");
			scanf("%d",&t);
			printf("enter name,mobile number:\n");
			char nam[50];
			scanf("%s",nam);
			long long int i;
			
			scanf("%lld",&i);
			if(t==0)
			{
				search_per(head_per,nam,i);
			}
			else
			{
				search_prof(head_prof,nam,i);
			}
			printf("\n");
			break;
			
		case 5:
			printf("choose 0 to sort personal in ascending 1 sort personal in descending\n"
			" choose 2 to sort professional in ascending 3 sort professional in descending:\n");
			scanf("%d",&t);
			if(t==0)
			{
				display_per(head_per);
			}
			else if(t==1)
			{
				printf("name: \t mobileNo: \t email:\n");
				display_per_rev(head_per);		//by recursion
				
				//reverse_per(&head_per);       //or can reverse completely 		remove comment and can check
				//display_per(head_per);
				//reverse_per(&head_per);
			}
			else if(t==2)
			{
				display_prof(head_prof);
			}
			else
			{
				printf("name : lastname : mail : adress : inst :  mobileNo : offNo:\n");
				display_prof_rev(head_prof);		//by recursion
				
				//reverse_prof(&head_prof);         //or can reverse completely 		remove comment and can check
				//display_prof(head_prof);
				//reverse_prof(&head_prof);
			}
			printf("\n");
			break;
			
		case 6:
			printf("choose 0 to display personal 1 to display professional:\n");
			scanf("%d",&t);
			if(t==0)
			{
				display_per(head_per);
			}
			else
			{
				display_prof(head_prof);
			}
			printf("\n");
			break;
			
		case 7:
			printf("choose 0 to merge two personal 1 to merge two professional:\n");
			scanf("%d",&t);
			if(t==0)
			{
				printf("one list can be made by our normal insertion\n\nnow create second list\n"
				"enter number of entries in second list:");
				scanf("%d",&t);
				char n[50],ln[50],em[50];
				long long int pNo;
				for(i=0;i<t;i++)
				{
					printf("enter your name,last name,email,mobileNo:\n");
					scanf("%s%s%s%lld",n,ln,em,&pNo);
					insertPersonal(&other_head_per,n,em,ln,pNo);
				}
				
				printf("\ntwo lists are:\n\n");
				display_per(head_per);
				printf("\n");
				display_per(other_head_per);
				struct per_cont_node* new_per=merge_per(head_per,other_head_per);
				printf("\nnew list after merging is:\n\n");
				display_per(new_per);
			}
			else
			{
				printf("one list can be made by our normal insertion\n\nnow create second list\n"
				"enter number of entries in second list:");
				scanf("%d",&t);
				
				long long int i;
				char n[50],ln[50],em[50],ad[50],inst[50];
				int ofNo;
				for(i=0;i<t;i++)
				{
					printf("enter your name,last name,email,address,institute,mobileNo,officeNo:\n");
					scanf("%s%s%s%s%s%lld%d",n,ln,em,ad,inst,&i,&ofNo);
					insertProfessional(&other_head_prof,n,ln,em,ad,inst,i,ofNo);
				}
				
				printf("\ntwo lists are:\n\n");
				display_prof(head_prof);
				printf("\n");
				display_prof(other_head_prof);
				struct prof_cont_node* new_prof=merge_prof(head_prof,other_head_prof);
				printf("\nnew list after merging is:\n");
				display_prof(new_prof);
			}
			printf("\n");
			break;
			
		case 8:
			printf("choose 0 to remove duplicates from personal 1 to remove duplicates from professional:\n");
			scanf("%d",&t);
			if(t==0)
			{
				rmvDuplicates_per(&head_per);
			}
			else
			{
				rmvDuplicates_prof(&head_prof);
			}
			printf("\n");
			break;						
		
		case 9:
			
			printf("enter number of callee you want to add:\n");
			scanf("%d",&t);
        	for(i=0;i<t;i++)
        	{
        		printf("enter your duration,number,callee_name,person name,last-date-called:\n");
        		scanf("%d%d%s%s%s",&dur,&nCall,name,per_name,date);
        		add_detail(&head_per,dur,nCall,name,per_name,date);
        		
			}
			printf("enter person name whose list you want to see:\n");
			scanf("%s",per_name);
			display_phonebook(head_per,per_name);
        	printf("\n");
		    break;
		
		default:
			printf("\nWrong argument try next time :)\n\n");
			break;		
		}
	
    printf("press 0 to exit 1 to continue:");
    scanf("%d",&run);	
    printf("\n");
	}
	
	printf("\nThank you !!!!!!!!!!!!!!!!!!!!\n");
	return  0;
	
}
