/***
 *                                                        
 *                                                        
 *     _ __ ___    __ _  _ __   _   _                     
 *    | '_ ` _ \  / _` || '_ \ | | | |                    
 *    | | | | | || (_| || | | || |_| |                    
 *    |_| |_| |_| \__,_||_| |_| \__, |                    
 *                               __/ |                    
 *                              |___/                     
 *      __                      _    _                    
 *     / _|                    | |  (_)                   
 *    | |_  _   _  _ __    ___ | |_  _   ___   _ __   ___ 
 *    |  _|| | | || '_ \  / __|| __|| | / _ \ | '_ \ / __|
 *    | |  | |_| || | | || (__ | |_ | || (_) || | | |\__ \
 *    |_|   \__,_||_| |_| \___| \__||_| \___/ |_| |_||___/
 *                                                        
 *                                                        
 *        _                                               
 *       | |                                              
 *       | |__                                            
 *       | '_ \                                           
 *     _ | | | |                                          
 *    (_)|_| |_|                                          
 *                                                        
 *                                                        
 */

// echo simply returns the value that was passed in to it (the
// argument n).
int echo(int n);

// add_four returns the input value plus four. Examples: add_four(-4)
// should return 0, add_four(0) should return 4, and add_four(19)
// should return 23.
int add_four(int n);

// count_odds will return the number of odd numbers between arguments
// a and b (inclusive). a is guaranteed to be less than b.
//
// for example, count_odds(4, 11) returns 4, because there are four
// odd numbers (5, 7, 9, 11) between 4 and 11 inclusive.
int count_odds(int a, int b);

// is_prime returns true if n is a prime number; false otherwise. For
// the purposes of this function and homework assignment, n will be
// less than 1000.
//
// prime numbers are greater than 1 and is only cleanly divisible by 1
// and itself. So, 5 is prime, but 6 is not (it is divisible by 2 and
// 3).
//
// see https://en.wikipedia.org/wiki/Prime_number for more information
// than you probably need or want.
//
// use any means at your disposal to implement this.
bool is_prime(int n);

// quadratic computes the value of ax^2 + bx + c and returns it.
//
// for example, quadratic(3, 7, 4, 2) returns
//    (3*(2^2)) + (7*2) + 4
// ==  12       +  14   + 4 == 30
float quadratic(float a, float b, float c, float x);

// ftol returns true if a is strictly within tol units of b. tol is
// guaranteed to be positive.
//
// For example, ftol(14.001, 14.0, 0.00001) returns false because
// 14.001 is not in the range (14.0 - 0.00001, 14.0 + 0.00001).
//
// But ftol(10.0, 11.0, 2.0) returns true because 10 is in the range
// (11-2, 11+2).
bool ftol(float a, float b, float tol);

// is_bleep returns true if the input number n is divisible by 3 or 7,
// or if it is between 10 and 20 exclusive. It returns false
// otherwise.
bool is_bleep(int n);

// is_blop returns true if the input number n is divisible by 4, or if
// it is larger than 35 and divisble by 5.
bool is_blop(int n);

// is_bleebleblam returns true if the input number is both bleep and
// blop (as determined by is_bleep and is_blop).
bool is_bleebleblam(int n);
