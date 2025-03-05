#include <stdio.h>
#include <stdlib.h>

// Define the "class" using a struct
typedef struct s_Person {
    int value;
    // Function pointer for a method
    void (*increment)(struct s_Person *self);
} Person;

// Method implementation for increment
void increment_person(struct s_Person *self) {
    self->value++;
}

// Constructor-like function to initialize a Person
Person* person_new(int initial_value) {
    Person *p = (Person*)malloc(sizeof(Person));
    p->value = initial_value;
    p->increment = increment_person;
    return p;
}

// Destructor-like function
void person_free(Person *p) {
    free(p);
}

int main() {
    // Creating an instance of Person
    Person *p = person_new(5);

    // Using the method
    printf("Initial value: %d\n", p->value);
    p->increment(p);  // Incrementing the value
    printf("After increment: %d\n", p->value);

    // Freeing the allocated memory
    person_free(p);
    return 0;
}
