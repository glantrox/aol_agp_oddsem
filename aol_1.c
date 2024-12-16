// 	Case study 1 (LO 2 – L.Obj 2.2 – SO 2, 30%):
// Using string manipulation, iteration, and selection, create a C program to handle string conversion. 
// The string conversion accept a string input with constraint: 
// 1≤|S|≤100
// s ∈S
// s={UpperCaseCharacters ∪  LowerCaseCharacters}
// The conversion needed is string reversal, followed by inverse capitalize character at each position. 
// Inverse capitalize means that lowercase will convert to uppercase, and uppercase will convert to lowercase. 
// Example: if given string SuniBVerse, the string will reverse to esreVBinuS. After inversion, 
// the program will convert each character with the rules above. Therefore, the final string will become: ESREvbINUs.

#include<stdio.h>
#include<string.h>

int main() {

    // Declare Input String
    char S[100];

    // Input String
    scanf("%[^\n]", S);

    // Declare Lenght of String
    size_t lengthOfString = strlen(S);

    // Process
    for (size_t i = 0; i < lengthOfString / 2; i++)
    {
        // Reverse
        char temp = S[i];
        S[i] = S[lengthOfString - 1 - i];
        S[lengthOfString - 1 - i] = temp;        
    }

    for (size_t i = 0; i < lengthOfString; i++)
    {
        // Swapping Uppercase to Lowercase & Lowercase to Uppercase
        if(S[i] / 32 == 2)  {
            S[i] += 32;
        } else if(S[i] / 32 == 3) {
            S[i] -= 32;
        }
    }
    
    puts(S);
    return 0;
}
