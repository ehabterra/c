#include <stdio.h>

typedef struct stu_address
{
     int street;
     char *state;
     char *city;
     char *country;
} addr;

typedef struct Student {
    int id;
    char *name;
    addr address;
} Stud;

int main()
{
    Stud student = {.id = 4, .name = "Ehab Terra", .address.city = "Giza", .address.country= "Egypt", .address.street = 13};

    printf("Student id = %d\n", student.id);
    printf("Student name = %s\n", student.name);
    printf("Student address = %s, %s\n", student.address.city, student.address.country);

    return 0;
}
