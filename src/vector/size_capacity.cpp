//File_name: size_capacity.cpp
//Author:    Stax The Engipreneur
//Date:      03 August 2018
//Details:   Size vs Capacity


// size_capacity.cpp
// Vector size versus capacity

/*A vector is a container of elements. Size refers to the number of elements currently contained in the vector
 and capacity refers to the maximum number of elements that CAN be contained before automatic memory allocation
 will be required. 

 Vectors dynamically resize themselves. This means that the capacity of the vector container changes as the size
 reaches the current capacity.
  * 
Every time a vector's capacity is grown the elemnts of the vector will have to be copied. If you amortise this cost
out over a lifetime of a vector it turns out that if you increase the capacity by an exponential factor 
 you end up with an amortised constant cost. 
 ** Amortise - pay off a debt by making regular payments
Every time the capacity jumps, the number of copies goes up by the previous size of the array. 
But because the array has to double in size before the capacity jumps again, the number of copies per
elements is alawys less than 2*/

#include <vector>
#include <iostream>

using namespace std;

int main()
{
    vector<int> vec;
    cout << "vec: size: " << vec.size() 
         << " capacity: " << vec.capacity() << endl;

    for(int i = 0; i < 24; i++) {
        vec.push_back(i);
        cout << "vec: size: " << vec.size() 
             << " capacity: " << vec.capacity() << endl;
    }

    return 0;
}
