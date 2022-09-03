#include "bigint.h"
#include <iostream>
#include <string>
#include <climits>
#include <cmath>
using namespace std;

//******************************************************************
//START OF THE CONSTRUCTORS SECTION
//******************************************************************

/*
// Create a default BigInt with base 10.
// This function is complete. You do not have to add anything.
*/
BigInt::BigInt(){
  base = 10;
  isPositive = true;
}

/*
// Create a BigInt with a specified base.
// This function is complete. You do not have to add anything.
*/
BigInt::BigInt(int setbase){
    if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
    }
    base = setbase;
    isPositive = true;
}

/*
// Destructure. You do not have to add anything.
// This function is complete
*/
BigInt::~BigInt(){}

/*
//  Create a BigInt from string.
//  Don't forget to set the base accordingly
//  The input string will contain
//      - numbers (0-9) and/or 
//      - uppercase letters (A-Z) [A=10, B=11, ... , Z=35]
//  The input string may contain
//      - a negative sign ('-') to signify that the number is negative.
//  Note: char '0' = int 48 (see ASCII table)
//  Note: char 'A' = int 65
*/
BigInt::BigInt(const string &s, int setbase){
    if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
    }
    /************* You complete *************/
    
    base = setbase;
    for(int i = s.length() - 1; i >= 0; i--){ // Reverse string into a vector
        if(s[i] == '-'){ // Check for negative sign
            isPositive = false;
        }
        else if(s[i] >= 'A'){ // Adds element to end of the list depending on the char
            vec.push_back(s[i] - '0' - 7); // '0' char equals 48 int
        }
        else{
            vec.push_back((int)(s[i]) - 48); // Add item to the end of
            // list while converting from char to int
        }
    }
}


/*
//  Create a BigInt from int (base 10).
//  - Convert the int (base 10) input into a specified base (setbase).
//  - Don't forget to set the base accordingly
//  For example:
//     BigInt k(6,2) <- int 6 base 10 to BigInt base 2
//          - Result:  BigInt k with value 110 (base 2)
//     BigInt k(154,16) <- 154 base 10 to BigInt base 16
//          - Result: BigInt k with value 9A (base 16)
*/
BigInt::BigInt(int input,int setbase){
    if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
    }
    /************* You complete *************/
    
    base = setbase;
    if(input < 0){
        isPositive = false;
        input *= -1; // Convert to positive for algorithm after this to work
    }
    if(input == 0){ // I forgot about this earlier and while condition skips it
        // (learn from this mistake).
        vec.push_back(0);
    }
    while(input != 0){
        int ones_digit = input % base; // Isolate the ones digit
        input /= base; // Get rid of the ones digit from the input
        if(ones_digit >= base){
            input += ones_digit / base; // Carries over a number
            vec.push_back(ones_digit % base);
        }
        else{
            vec.push_back(ones_digit);
        }
    }


}

/*
//  Create a BigInt from another BigInt.
//  This is a copy constructor.
//  Simply call the assignment operator (=) below.
// (You can also think of this function as the same as the assignment operator (=))
// (but without a return statement because you are overriding the current object)
*/
BigInt::BigInt(const BigInt &b){

    /************* You complete *************/
    
    vec = b.vec;
    isPositive = b.isPositive;
    base = b.base;
    
    
    // If working with arrays, may need to use a for loop to fully
    // copy, especially if using dynamic memory

}

/*
//  Assignment operator. (i.e., BigInt a = b;)
//  OVERRIDING a's data with BigInt b's data
//       - vec
//       - isPositive
//       - base
*/
BigInt & BigInt::operator = (const BigInt &b){ //assignment or copy

    /************* You complete *************/
    if(this == &b) return *this; // Checks for Self assignment
    // (which may also lead to memory leak or lost data).
    // (Code would probably not work without this).

    
    // NOTE: Sometimes need further if-statements such as delete[] for dynamic memory.
    // Ex: if(dat) delete[] dat; // Object may have been initialized already
    // (overwriting data members may lead to a memory leak).
    vec = b.vec;
    base = b.base;
    isPositive = b.isPositive;


    return *this; 
}


//******************************************************************
//END OF THE CONSTRUCTORS SECTION
//******************************************************************

//******************************************************************
//START OF THE DISPLAYS SECTION
//******************************************************************

/*
// Convert to string and return the string
// Display it in its corresponding base
//  Note: char '0' = int 48 (see the ASCII table)
//  Note: char 'A' = int 65
*/
string BigInt::to_string(){

    /************* You complete *************/
  
  string s = ""; // Initializing s as an empty string
  if(!isPositive) s += "-";
  for(int i = vec.size() - 1; i >= 0; i--){ // Convert vector (BigInt) back to string
      if(vec[i] >= 10){ // 'A' and higher
          s += (char)(vec[i] + '0' + 7);
      }
      else{
          s += (char)(vec[i] + 48); // Convert from int to char and store in string
      }
  }
  return s;
  

  // return "";//for now
}

/*
//  Convert BigInt to integer base 10 and return that int
//    If BigInt >= INT_MAX, return INT_MAX.
//    If BigInt =< INT_MIN, return INT_MIN.
//  Note: 1. INT_MAX and INT_MIN are already defined for you
//           in the 'climits' library.
//        2. INT_MAX = 2147483647, INT_MIN = -2147483648
//           therefore, INT_MIN does not equal to (-INT_MAX)
*/
int BigInt::to_int() const{

    /************* You complete *************/
    
  long long number = 0; // long number is also a valid choice
  for(unsigned int i = 0; i < vec.size(); i++){
    if(isPositive){
        number += vec[i]*pow(base, i);
    }
    else{ // if it's negative
        number -= vec[i]*pow(base, i);
    }
    if (number > INT_MAX) {
        return INT_MAX;
    }
    if (number < INT_MIN) {
        return INT_MIN;
    }
    
  }

  return number;
  
  // return 0;//for now
}

//******************************************************************
//END OF THE DISPLAYS SECTION
//******************************************************************

//******************************************************************
//START OF THE EQUALITY CHECK OPERATORS SECTION
//******************************************************************

/*
//  Compare a and b.
//     If a = b, return 0.
//     If a < b, return -1.
//     If a > b, return 1.
//  See the HINT below
*/
int BigInt::compare(const BigInt &b) const{
    if(base != b.base){
        throw DiffBaseException();
    }
    /************* You complete *************/

    //HINT:
    //1. do NOT call the to_int() or to_string() function
    //2. do NOT convert bigInt to other datatypes first (e.g., long long, int)
    
    //First let's compare the signs
    //    - if the signs aren't the same,
    //              how do you know which one is larger?

    if(isPositive != b.isPositive){ // Are there different signs?
        if(isPositive) return 1; // a > b, because b must be neg. if a is pos.
        else return -1; // b > a
    }

    //If they have the same sign, let's compare their vec sizes 
    //    - what if both are positive, but a's vec is larger (a or b is larger?)
    //    - other cases?

    // Since both are positive here, only need to check if one is positive now
    if(vec.size() > b.vec.size()){
        if(isPositive) return 1; // a > b
        else if(!isPositive) return -1; // b > a, because smaller negative is the bigger int
    }
    else if(b.vec.size() > vec.size()){
        if(b.isPositive) return -1; // b > a
        else if(!b.isPositive) return 1; // a > b, because smaller negative is the bigger int
    }

    
    //If they have the same vec size, let's compare their digits one by one
    // Starting from the most-significant digits. --> in what vector position?
    // Remember that the BigInt vectors are in reverse order!
    //    - what if both are positive, but the digit of a is greater than that of b (a or b is larger?)
    //    - other cases?
    
    for(int i = vec.size() - 1; i >= 0; i--){
        // NOTE FOR FUTURE: DON'T FORGET THE -1 when initializing i based on size
        if(isPositive){ // If both are positive
            if(vec[i] > b.vec[i]) return 1; // a > b
            else if(b.vec[i] > vec[i]) return -1; // b > a
        }
        else if(!isPositive){ // If both are negative, check for the smaller negative
            if(vec[i] > b.vec[i]) return -1; // b > a
            else if(b.vec[i] > vec[i]) return 1; // a > b
        }

    }

    //If ALL digits are the same, then they MUST be equal!!
    return 0; // a = b
}


//Call the compare function above to check if a == b
bool operator == (const BigInt &a, const BigInt &b){
    /************* You complete *************/

    if(a.compare(b) == 0) return true; // a = b
    else{
        return false;
    }
  

  // return false;//for now
}

//Call the compare function above to check if a != b
bool operator != (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/
    
    if(a.compare(b) != 0) return true; // Return true if not equal, a != b
    else{
        return false;
    }
  
  
  // return false;//for now
}

//Call the compare function above to check if a <= b
bool operator <= (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/

    if(a.compare(b) == -1 || a.compare(b) == 0) return true;
    // Return true if a < b or a == b
    else{
        return false;
    }
  

  // return false;//for now
}

//Call the compare function above to check if a >= b
bool operator >= (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/

    if(a.compare(b) == 1 || a.compare(b) == 0) return true;
    // Return true if a > b or a == b
    else{
        return false;
    }  
  
  
  // return false;//for now
}

//Call the compare function above to check if a > b
bool operator > (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/

    if(a.compare(b) == 1) return true;
    // Return true if a > b
    else{
        return false;
    }
  
  
  // return false;//for now
}

//Call the compare function above to check if a < b
bool operator < (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/

    if(a.compare(b) == -1) return true;
    // Return true if a < b
    else{
        return false;
    }
  
  
  // return false;//for now
}

//******************************************************************
//END OF THE EQUALITY CHECK OPERATORS SECTION
//******************************************************************

//******************************************************************
//START OF THE ARITHMETIC OPERATORS SECTION
//******************************************************************

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call += operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator + (const  BigInt &a, const BigInt & b){

  /************* You complete *************/
  
  BigInt a_copy = a; // Uses copy constructor
  a_copy += b;
  return a_copy;
  

  // return a;//for now
}

/*
//==================
// MEMBER function
//==================
//  Addition assignment operator.
//    i.e., a += b
*/
const BigInt & BigInt::operator += (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    /************* You complete *************/

    int value_of_a = 0;
    int value_of_b = 0;
    bool isOnePositive = false; // Is there exactly one positive vector
    BigInt top;
    BigInt bottom;
    if(isPositive != b.isPositive){
        isOnePositive = true;
        if(isPositive){ // If this vector is positive
            top = *this;
            bottom = b;
            bottom.isPositive = true;
            top -= bottom;
        }
        else{ // If b vector is positive
            top = b;
            bottom = *this;
            bottom.isPositive = true;
            top -= bottom;
        }
    }
    for(size_t i = 0; i < max(vec.size(), b.vec.size()) && isOnePositive == false; i++){
        if(i < vec.size()){ // Alternative to commented code above (this is more efficient)
            // okay to access vec_a at the i-th index.
            value_of_a = vec[i]; // get value of vec_a at the i-th index
        }
        else{
            // not okay to access vec_a at the ith index,
            // give 0 instead.
            value_of_a = 0;
            vec.push_back(0);
        }
        if(i < b.vec.size()){ 
            // okay to access vec_b at the i-th index.
            value_of_b = b.vec[i]; // get value of vec_b at the i-th index
        }
        else{
            // not okay to access vec_b at the ith index,
            // give 0 instead.
            value_of_b = 0;
        }
        vec[i] = value_of_a + value_of_b; // Add both numbers together one digit at a time
        if(vec[i] >= base){ // Checks if I need to carry something over
            if(i + 1 >= vec.size()){ // Checks if the next index doesn't exist yet
                vec.push_back(1); // Carries over an extra 1 if needed
                vec[i] %= base; // Keeps the ones digit only
            }
            else{
                vec[i + 1] += vec[i] / base; // Carries over a number
                vec[i] %= base; // Keeps the ones digit only
            }
        }
    }
    if(isOnePositive == true){
        *this = top;
    }

  return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call -= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator - (const  BigInt &a, const BigInt & b){

  /************* You complete *************/
  
  BigInt a_copy = a; // Uses copy constructor
  a_copy -= b;
  return a_copy;

  // return a;//for now
}


/*
//==================
// MEMBER function
//==================
//  Subtraction assignment operator.
//    i.e., a -= b
//  Note: Think of base cases (e.g., subtract by itself)
*/
const BigInt & BigInt::operator -= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    /************* You complete *************/

    BigInt top;
    BigInt bottom;
    int value_of_a = 0; // value of top
    int value_of_b = 0; // value of bottom
    int largest_valid_index = 0; // helps determine what vector values to pop
    bool isOnePositive = false;
    if(isPositive && b.isPositive){ // Come back later to check if I need to
        // do a separate check for a == b as well
        if(*this >= b){
            top = *this;
            bottom = b;
            top.isPositive = true; // For final result
        }
        else if(b >= *this){
            top = b;
            bottom = *this;
            top.isPositive = false; // For final result
        }
    }
    else if (!isPositive && !b.isPositive){ // If both are negative, then
        // put the smaller number on top of the larger number for subtraction
        if(*this <= b){
            top = *this;
            bottom = b;
            top.isPositive = false; // For final result
        }
        else if(b <= *this){
            top = b;
            bottom = *this;
            top.isPositive = true; // For final result
        }       
    }
    else{ // Occurs if the numbers have different signs
        isOnePositive = true;
        if(isPositive){ // If only *this vector is positive
            top = *this;
            bottom = b;
            bottom.isPositive = true; // Add positive and positive
            top += bottom;
        }
        else{ // If only b vector is positive
            top = *this;
            bottom = b;
            bottom.isPositive = false;
            top += bottom; // Add negative and negative
        }
    }
    for(size_t i = 0; i < max(top.vec.size(), bottom.vec.size()) && isOnePositive == false; i++){
        if(i < top.vec.size()){
            value_of_a = top.vec[i]; // get value of vec_a at the i-th index
        }
        else{
            // not okay to access vec_a at the ith index,
            // give 0 instead.
            value_of_a = 0;
            // top.vec.push_back(0);
        }
        if(i < bottom.vec.size()){ 
            // okay to access vec_b at the i-th index.
            value_of_b = bottom.vec[i]; // get value of vec_b at the i-th index
        }
        else{
            // not okay to access vec_b at the ith index,
            // give 0 instead.
            value_of_b = 0;
        }

        top.vec[i] = value_of_a - value_of_b; // Subtract numbers one digit at a time
        if(top.vec[i] < 0){ // Checks if I need to borrow from the next column
            
            top.vec[i + 1] -= 1; // Borrows from the next column
            top.vec[i] += base; // Add borrowed value depending on base
        }
        if(top.vec[i] != 0){
            largest_valid_index = i;
        }
    }

    
    for(int i = top.vec.size() - 1; i > largest_valid_index && isOnePositive == false; i--){
        // Get rid of excess 0's (prevents answers like 000000001)
        top.vec.pop_back();
    }
    
    if(*this == b){ // If result should have been 0, must be positive
        top.isPositive = true;
    }
    
    
    
    *this = top;
  return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call *= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator * (const  BigInt &a, const BigInt & b){

    /************* You complete *************/
    BigInt a_copy = a;
    a_copy *= b;
    return a_copy;

  // return a;//for now
}



/*
//==================
// MEMBER function
//==================
//  Multiplication assignment operator.
//    i.e., a *= b
//  Implement Long Multiplication
//  Note: What are the base cases?? (e.g., multiply by 0)
*/
const BigInt & BigInt::operator *= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    /************* You complete *************/

    // DEBUG: Add base cases (ie: multiply by zero, by 1, etc.)

    BigInt total(0, base);
    int carry = 0;
    bool isZero = false;
    if(*this == total || b == total){
        isZero = true; // Attempts to check if I need to multiply by 0
    }
    
    for(unsigned int i = 0; i < b.vec.size() && !isZero; i++){ // for each digit in b.vec
        BigInt temp(base);
        for(unsigned int j = 0; j < i; j++){
            // push 0 to temp's vec i times. (prepare for the 0s)
            temp.vec.push_back(0);
        }
        for(unsigned int j = 0; j < vec.size(); j++){ // for each digit in a.vec
        
            int product = (vec[j] * b.vec[i]) + carry; // also accounts for any carry from the previous iteration
            carry = product / base; // Compute carry for the next iteration
            temp.vec.push_back(product % base); // push the adjusted product to temp
            // DEBUG: may need to adjust product again to account carry
        }
        if(carry != 0){ // if there is a carry left over, push that to temp
            temp.vec.push_back(carry);
        }
        carry = 0; // reset carry
        total += temp; // add temp to total
    }
    if(isPositive != b.isPositive && !isZero){
        total.isPositive = false;
    }
    *this = total; // result <-- total

  
    return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call /= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator / (const  BigInt &a, const BigInt & b){

    /************* You complete *************/
  
    BigInt a_copy = a;
    a_copy /= b;
    return a_copy;
    

    // return a;//for now
}


/*
//==================
// MEMBER function
//==================
//  Division assignment operator.
//    - Call 'divisionMain' to get the quotient;
*/
const BigInt & BigInt::operator /= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    if(b.vec.size() == 1 && b.vec[0] == 0){
        throw DivByZeroException();
    }
    /************* You complete *************/

    BigInt q(base);
    BigInt r(base);
    divisionMain(b, q, r);
    *this = q;

    return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call %= operator on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt operator % (const  BigInt &a, const BigInt & b){

    /************* You complete *************/
  
    BigInt a_copy = a;
    a_copy %= b;
    return a_copy;

    
    // return a;//for now
}


/*
//==================
// MEMBER function
//==================
//  Modulus assignment operator.
//    - Call 'divisionMain' to get the remainder;
//    - Note: remainder takes the sign of the dividend.
*/
const BigInt & BigInt::operator %= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    if(b.vec.size() == 1 && b.vec[0] == 0){
        throw DivByZeroException();//divide by zero.
    }
    /************* You complete *************/

    BigInt q(base);
    BigInt r(base);
    divisionMain(b, q, r);
    *this = r;
  
    return *this;
}

/*
//  Main function for the Division (/=) and Modulus (%=) operators.
//     - Compute (q)uotient and (r)emainder
//     - Implement Long Division
//  Note: 1. This should behave like integer division
//        2. What are the base cases?? (e.g., div by itself)
*/
void BigInt::divisionMain(const BigInt &b, BigInt &quotient, BigInt &remainder){

    /************* You complete *************/
    
    
    bool sameSign = true;
    bool dividendSign = isPositive;
    BigInt a_backup = *this;
    BigInt positive_divisor = b;
    BigInt zero(0, base);
    bool isZero = false;
    if(isPositive != b.isPositive){
        sameSign = false;
    }

    // Make both dividend and divisor positive (but also keep track
    // track of original signs through dividendSign and sameSign for later)
    isPositive = true;
    positive_divisor.isPositive = true;

    if(*this < positive_divisor){ // If quotient should be 0 and remainder should be dividend
        remainder = *this;
        remainder.isPositive = dividendSign;
        *this = zero;
        isZero = true;
    }

    int pos = vec.size() - 1; // <-- dividend vec's rightmost position = most significant digit
    BigInt dividend_seq(base); // Will hold vector values to find actual pos
    dividend_seq.vec.push_back(vec[pos]);
    while(dividend_seq < positive_divisor && pos >= 1){
        pos--;
        dividend_seq.vec.insert(dividend_seq.vec.begin(), vec[pos]);
    }
    
    while(pos >= 0){    
        // Now find out how many times I can subtract the divisor from the dividend_seq
        // until dividend_seq becomes less than the divisor
        int times = 0;
        while(dividend_seq >= positive_divisor){
            dividend_seq -= positive_divisor;
            times++;
        }

        quotient.vec.insert(quotient.vec.begin(), times); // Construct the quotient based on times
        

        if(dividend_seq == zero){ // If dividend_seq is 0, empty out dividend_seq's vector
            dividend_seq.vec.clear();
        }

        if(pos >= 1){ // If there are more digits to pull down from the dividend
            dividend_seq.vec.insert(dividend_seq.vec.begin(), vec[pos - 1]);
        }
        pos--; // decrement pos
    }

    // Important: Remainder will always take the sign of the dividend.
    // Unless the remainder is 0 which we treat it as positive.
    if(remainder.vec.empty()){ // If remainder wasn't altered earler in base case
        remainder = dividend_seq; // After step 9, the remainder is the dividend_seq;
        remainder.isPositive = dividendSign;
        if(remainder.vec.empty()){ // If dividend is also empty
            remainder = zero;
        }
    }

    // Now deal with quotient
    if(!sameSign){ // Check if I need to change the sign of quotient
        quotient.isPositive = false;
    }
    if(isZero){
        quotient.isPositive = true;
        quotient = zero;
    }
}



/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call the 'exponentiation' function on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt pow(const  BigInt &a, const BigInt & b){

    /************* You complete *************/

    BigInt a_copy = a;
    a_copy.exponentiation(b);
    return a_copy;


    // return a;//for now
}

/*
//==================
// MEMBER function
//==================
//  Exponentiation assignment function.
//     - i.e., a.exponentiation(b);
// Note: 1. implement Exponentiation by Squaring (see the writeup)
//       2. b should be treated as BigInt, not int or other data type.
*/
const BigInt & BigInt::exponentiation(const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    if(!b.isPositive){
        throw ExpByNegativeException();
    }
    /************* You complete *************/

    BigInt result(1, base);
    BigInt exp_base = *this;
    int n = b.to_int(); // Probably can't use this since we're working with vectors
    if(n == 0){ // Leads to returning 1 since result is 1 right now
        result.isPositive = true;
    }
    else if(n == 1){ // Return base if power is 1
        result = *this;
        n = 0; // Avoids going inside loop
    }
    
    while(n != 0){
        if(n % 2 == 1){ // If n is odd
            result *= exp_base;
            exp_base *= exp_base;
            n--;
        }
        else{ // If n is even
            exp_base *= exp_base;
        }
        n /= 2;
        if(n == 1){
            result *= exp_base; // Apply result to the final form of exp_base
            break; // No need to continue
        }
    }

    *this = result;
  
    return *this;
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call the 'modulusExp' function on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt modPow(const BigInt &a, const BigInt &b, const BigInt &m){

    /************* You complete *************/

    BigInt a_copy = a;
    a_copy.modulusExp(b, m);
    return a_copy;


    // return a;//for now
}


/*
//==================
// MEMBER function
//==================
//  Modulus Exponentiation assignment function.
//     - i.e., a.modulusExp(b)
// Note: 1. implement Modulus Exponentiation (see the writeup)
//       2. b should be treated as BigInt, not int or other data type.
// Hint: same implementation as exponentiation, but take modulus 
//          after every call to the *= operator.
*/
const BigInt & BigInt::modulusExp(const BigInt &b, const BigInt &m){
    if(base != b.base || base != m.base){
        throw DiffBaseException();
    }
    if(!b.isPositive){
        throw ExpByNegativeException();
    }
    /************* You complete *************/

    BigInt result(1, base);
    BigInt exp_base = *this;
    // int n = b.to_int(); // Probably can't use this since we're working with vectors
    BigInt n = b;
    BigInt ZERO(0, base);
    BigInt ONE(1, base);
    BigInt TWO (2, base);
    if(n == ZERO){ // Leads to returning 1 since result is 1 right now
        result.isPositive = true;
    }
    else if(n == ONE){ // Return base if power is 1
        result = *this % m; // x mod b
        n = ZERO; // Avoids going inside loop
    }
    
    while(n != ZERO){
        if(n % TWO == ONE){ // If n is odd
            result = (result * exp_base) % m;
            exp_base = (exp_base * exp_base) % m;
            n -= ONE;
        }
        else{ // If n is even
            exp_base = (exp_base * exp_base) % m;
        }
        n /= TWO;

        if(n == ONE){
            result = (result * exp_base) % m; // Apply result to the final form of exp_base
            break; // No need to continue
        }
    }
    *this = result;
  
  
    return *this;
}

//******************************************************************
//END OF THE ARITHMETIC OPERATORS SECTION
//******************************************************************

//******************************************************************
//START OF SANITY CHECK FUNCTIONS
//YOU CAN USE THEM, BUT DO NOT CHANGE ANYTHING
//THESE FUNCTIONS ARE COMPLETE.
//******************************************************************
void BigInt::printVecItems(){
  cout<<"[";
  for(size_t i = 0;i<vec.size();i++){
    cout<<vec[i];
    if(i < vec.size()-1){
      cout<<",";
    }
  }
  cout<<"]"<<endl;
}

bool BigInt::getSign(){
	return isPositive;
}

int BigInt::getBase(){
	return base;
}
//******************************************************************
//END OF SANITY CHECKS SECTION
//******************************************************************