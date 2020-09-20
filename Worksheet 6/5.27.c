#include <stdio.h>
#include <ctype.h>
#include <string.h>

int isPalindrome(char str[]);

int main(void) {
    char input[50];
    fgets(input, 50, stdin);
    input[strlen(input)-1] = '\0'; // replace newline with null

    if (isPalindrome(input)) {
        printf("%s is a palindrome\n", input);
    } else {
        printf("%s is not a palindrome\n", input);
    }
    
}

int isPalindrome(char str[]) {
    int len = strlen(str); 
    int left = 0;
    int right = len - 1;
    
    // convert to lowercase
    for (int i = 0; i < len; i++){
        str[i] = tolower(str[i]);
    }
    while (left <= right) {
        // move left ptr if nonalpha character
        if (!(str[left] >= 'a' && str[left] <= 'z')) {
            left++;
        } 
        // move right ptr if nonalpha character
        else if (!(str[right] >= 'a' && str[right] <= 'z')) {
            right--;
        } 
        // move both ptrs ahead if same character
        else if (str[left] == str[right]) {
            left++; 
            right--;
        } else {
            return 0;
        }
    }
    return 1;
}
