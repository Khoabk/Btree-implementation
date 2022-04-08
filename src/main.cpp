#include <iostream>
#include "Btree.h"

using namespace std;


int main()
{
	//cout<<"Btree degree is 5\n";
	
	int degree = 4;
	
	cout<<"Insert the degree for btree\n";
	
	cin >> degree;
	
	auto *new_tree = new Btree(degree);
	
//	
//	for(int i = 1; i < 30; i++)
//	{
//		new_tree->Insert(i);
//	}
//
//
//
//	new_tree->Print_Btree();
//
//	cout<<"Delete 6\n";
//
//	new_tree->Delete(6);
//
//
//	new_tree->Print_Btree();


	int mode = 0;
	
	bool break_loop = false;
	
	while(1)
	{
		switch(mode)
		{
			case 0:
			{
				//Idle mode;
				
				cout<<"\nPlease insert operation mode:\n";
				
				cout<<"Insertion: 1\n";
				
				cout<<"Deletetion: 2\n";
				
				cout<<"Print Btree: 3\n";
				
				cout<<"Type any other number to quit.\n\n";
				
				cin >> mode;
				
				break;	
			}
			
			case 1:
			{
				//Insert mode
				
				cout<<"\nplease specify inserted number:\n";
				
				int get = 0;
				
				cin >> get;
				
				if(new_tree->Insert(get)) cout<<"\nNumber had already been inserted before.\n";
				
				else cout<<"Insert successfully\n\n";
				
				mode = 0;
				
				break;
			}
			
			case 2:
			{
				//Delete mode
			
				cout<<"\nplease specify deleted number:\n";
				
				int get = 0;
				
				cin >> get;
				
				if(new_tree->Delete(get) == 1) cout<<"\nDelete successfully\n";
				
				else cout<<"\nError occurs\n";
				
				mode = 0;
			
				break;
			}
			
			case 3:
			{
				//Print mode
				
				new_tree->Print_Btree();
			
				mode = 0;
				
				break;
			}
		
			default:
			{
				//Quit
			
				cout<<"\nEnd program.\n";
			
				break_loop = true;
			}
		}
		
	if(break_loop) break;
}
	
	delete new_tree;
		
	return 0;
}
